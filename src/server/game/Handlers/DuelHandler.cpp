/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "GameTime.h"
#include "Log.h"
#include "Player.h"

void WorldSession::HandleDuelAcceptedOpcode(WorldPacket& recvPacket)
{
    ObjectGuid guid;
    Player* player;
    Player* plTarget;

    recvPacket >> guid;

    if (!GetPlayer()->duel)                                  // ignore accept from duel-sender
        return;

    player = GetPlayer();
    plTarget = player->duel->opponent;

    if (player == player->duel->initiator || !plTarget || player == plTarget || player->duel->startTime != 0 || plTarget->duel->startTime != 0)
        return;

    //TC_LOG_DEBUG("network", "WORLD: Received CMSG_DUEL_ACCEPTED");
    TC_LOG_DEBUG("network", "Player 1 is: %u (%s)", player->GetGUID().GetCounter(), player->GetName().c_str());
    TC_LOG_DEBUG("network", "Player 2 is: %u (%s)", plTarget->GetGUID().GetCounter(), plTarget->GetName().c_str());

    time_t now = GameTime::GetGameTime();
    player->duel->startTimer = now;
    plTarget->duel->startTimer = now;
    // Reset CoolDown before DUEL
    player->SendDuelCountdown(3000);
    plTarget->SendDuelCountdown(3000);
    // Reset CoolDown before DUEL
    player->RemoveArenaSpellCooldowns();
    plTarget->RemoveArenaSpellCooldowns();
    player->SetHealth(player->GetMaxHealth());
    player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
    plTarget->SetHealth(plTarget->GetMaxHealth());
    plTarget->SetPower(POWER_MANA, plTarget->GetMaxPower(POWER_MANA));
}

void WorldSession::HandleDuelCancelledOpcode(WorldPacket& recvPacket)
{
    TC_LOG_DEBUG("network", "WORLD: Received CMSG_DUEL_CANCELLED");
    ObjectGuid guid;
    recvPacket >> guid;

    // no duel requested
    if (!GetPlayer()->duel)
        return;

    // player surrendered in a duel using /forfeit
    if (GetPlayer()->duel->startTime != 0)
    {
        GetPlayer()->CombatStopWithPets(true);
        if (GetPlayer()->duel->opponent)
            GetPlayer()->duel->opponent->CombatStopWithPets(true);

        GetPlayer()->CastSpell(GetPlayer(), 7267, true);    // beg
        GetPlayer()->DuelComplete(DUEL_WON);
        return;
    }

    GetPlayer()->DuelComplete(DUEL_INTERRUPTED);
}
