/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2009-2012 Eilo <https://github.com/eilo>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* SystemData
Name: BossHistory
%Complete: 100
Autor: Codels, some improvements by Eilo

Name: RaidInfo
%Complete: 100
Autor: Eilo
*/

#include "ScriptPCH.h"
#include "Config.h"
#include "Group.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "DatabaseEnv.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "World.h"

#define SQL_BOSS_HISTORY_LOG "INSERT INTO `boss_history` (`GuildId`, `CreatureEntry`, `PlayerCount`, `KillTime`, `KillData`, `MapSpawnMode`, `MapId`, `MapRaid`, `CreatureName`, `MapName`, `MapMaxPlayers`) VALUES ('%u', '%u', '%u', '%u', '%s', '%u', '%u', '%u', '%s', '%s', '%u')"
#define DATA_SEPARATOR ":"
#define PEOPLE_SEPARATOR " "

bool    BossHistoryEnable       = false;
bool    BossHistoryMode         = false;
bool    BossHistoryLog          = false;
bool    RaidInfoAnnounce        = false;
int32   RaidInfoDifficulty      = 0;
int32   BossHistoryNormalText   = 11006;
int32   BossHistoryHeroicText   = 11007;
uint32  KillTime                = 0;
uint32  minutes                 = 0;
uint32  seconds                 = 0;

class mod_BossHistory_WorldScript : public WorldScript
{
    public:
        mod_BossHistory_WorldScript() : WorldScript("mod_BossHistory_WorldScript") { }

    void OnConfigLoad(bool /*reload*/)
    {
        BossHistoryEnable      = sConfigMgr->GetBoolDefault("BossHistory.Enable", false);

        if (!BossHistoryEnable)
            return;

        BossHistoryMode        = sConfigMgr->GetBoolDefault("BossHistory.Mode", false);
        BossHistoryLog         = sConfigMgr->GetBoolDefault("BossHistory.Log", false);
        RaidInfoAnnounce       = sConfigMgr->GetBoolDefault("RaidInfo.Announce", false);
        RaidInfoDifficulty     = sConfigMgr->GetIntDefault("RaidInfo.Difficulty", 0);
    }
};

class mod_BossHistory_AllCreatureScript : public AllCreatureScript
{
    public:
        mod_BossHistory_AllCreatureScript() : AllCreatureScript("mod_BossHistory_AllCreatureScript") { }

    void AllCreatureReset()
    {
        KillTime = 0;
    }

    void AllCreatureUpdateAI(const uint32 diff)
    {
        KillTime += diff;
    }

    void AllCreatureJustDied(Creature* creature)
    {
        if (!BossHistoryEnable)
            return;

        if (creature->GetCreatureTemplate()->rank != CREATURE_ELITE_WORLDBOSS)
            return;

        Player* recipient = creature->GetLootRecipient();
        if (!recipient)
            return;

        Map* map = creature->GetMap();
        if (!map)
            return;

        uint32 Entry = creature->GetEntry();
        InstanceMap* instance = map->ToInstanceMap();

        if (BossHistoryMode && (!map->Instanceable() || !instance))
            return;

        std::string bossName(creature->GetNameForLocaleIdx(sObjectMgr->GetDBCLocaleIndex()));
        std::string mapName(creature->GetMap()->GetMapName());

        uint8 spawnMode = map->GetSpawnMode();
        uint32 GuildId = 0;
        bool IsGuildKill = true;
        uint32 PlayerCount = 0;
        std::string KillTeam;

        if(Group *pGroup = recipient->GetGroup())
        {
            for(GroupReference *itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
            {
                Player* Temp = itr->GetSource();

                if(!Temp)
                    continue;

                PlayerCount++;
                uint32 playerGuildId = Temp->GetGuildId();
                if (BossHistoryLog)
                {
                    std::ostringstream PeopleData;
                    PeopleData << Temp->GetGuild() << DATA_SEPARATOR;
                    PeopleData << Temp->GetName() << DATA_SEPARATOR;
                    PeopleData << uint32(Temp->getLevel()) << DATA_SEPARATOR;
                    PeopleData << playerGuildId << DATA_SEPARATOR;
                    PeopleData << uint32(Temp->IsAlive()) << DATA_SEPARATOR;
                    PeopleData << uint32(Temp->IsAtGroupRewardDistance(creature)) << PEOPLE_SEPARATOR;
                    KillTeam += PeopleData.str();
                }

                if (IsGuildKill)
                {
                    if (GuildId == 0)
                        GuildId = playerGuildId;

                    IsGuildKill = GuildId != 0 && playerGuildId == GuildId;
                }
            }
        }
        else
        {
            PlayerCount = 1;
            GuildId = recipient->GetGuildId();
            IsGuildKill = GuildId != 0;

            if (BossHistoryLog)
            {
                std::ostringstream PeopleData;
                PeopleData << recipient->GetGuild() << DATA_SEPARATOR;
                PeopleData << recipient->GetName() << DATA_SEPARATOR;
                PeopleData << uint32(recipient->getLevel()) << DATA_SEPARATOR;
                PeopleData << recipient->GetGuildId() << DATA_SEPARATOR;
                PeopleData << uint32(recipient->IsAlive()) << DATA_SEPARATOR;
                PeopleData << uint32(1) << PEOPLE_SEPARATOR;
                KillTeam += PeopleData.str();
            }
        }

        if (GuildId == 0 && IsGuildKill)
            IsGuildKill = false;

        if (!IsGuildKill)
            GuildId = 0;

        uint32 mapMaxPlayers = instance ? instance->GetMaxPlayers() : 40;

        if (RaidInfoAnnounce && IsGuildKill)
        {
            int32 TextId = BossHistoryNormalText;
            std::string guildName(sGuildMgr->GetGuildById(GuildId)->GetName());

            if (map->IsRaid())
            {
                if (spawnMode == RAID_DIFFICULTY_25MAN_HEROIC || spawnMode == RAID_DIFFICULTY_10MAN_HEROIC)
                    TextId = BossHistoryHeroicText;
            }
            else if (spawnMode == DUNGEON_DIFFICULTY_HEROIC)
                TextId = BossHistoryHeroicText;

            // Aqui va la conversion
            if (KillTime > 0)
            {
                seconds = (uint32)floor(float(KillTime) / 1000);
                
                if (seconds >= 60)
                {
                    minutes =  (uint32)floor(float(KillTime) / 60000);
                    seconds -= 60*minutes;
                }
                else 
                    minutes = 0;
            }
            // Acondicionando parametros para mostrar
            if (spawnMode >= RaidInfoDifficulty)
                sWorld->SendWorldText(TextId, mapName.c_str(), mapMaxPlayers, bossName.c_str(), guildName.c_str(), PlayerCount, mapMaxPlayers, minutes, seconds);
        }

        if (!BossHistoryLog) return;

        CharacterDatabase.EscapeString(KillTeam);
        CharacterDatabase.EscapeString(bossName);
        CharacterDatabase.EscapeString(mapName);
        CharacterDatabase.PExecute(SQL_BOSS_HISTORY_LOG, GuildId, Entry, PlayerCount, KillTime, KillTeam.c_str(), spawnMode, map->GetId(), uint8(map->IsRaid()), bossName.c_str(), mapName.c_str(), mapMaxPlayers);
    }
};

void AddSC_Mod_BossHistory()
{
    new mod_BossHistory_AllCreatureScript();
    new mod_BossHistory_WorldScript();
}
