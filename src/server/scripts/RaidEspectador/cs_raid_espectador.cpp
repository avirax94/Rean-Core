/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
 * Copyright (C) 2009-2018 Eilo <https://github.com/eilo>
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

 /* ScriptData
 Name: raid_espectador_commandscript
 %Complete: 12
 Comment: Raid Espectador

          Esta es una script para entrar a las raids siendo un pj normal y poder visualizar
          asi como controlar que no exista bugueos, me interesa además que la gente nueva en
          el server pueda observar el movimiento del mismo, esto con el afán de mostrar lo
          que se tiene y crear mejor hype entre la comunidad de wow que viene a jugar tlk
          en un servidor privado como es wowrean.

 Category: raidespectadorscripts
 EndScriptData */

#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "Chat.h"
#include "DatabaseEnv.h"
#include "Language.h"
#include "ObjectAccessor.h"
#include "Opcodes.h"
#include "Player.h"
#include "Realm.h"
#include "World.h"
#include "WorldSession.h"
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>

class raidespectador_commandscript : public CommandScript
{
public:
    raidespectador_commandscript() : CommandScript("raidespectador_commandscript") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> raidespectadorCommandTable =
        {
            { "entrar",         rbac::RBAC_PERM_COMMAND_RAID_ESPECTADOR_ENTRAR,     false, &HandleREEntrarCommand,      "" },
            { "salir",          rbac::RBAC_PERM_COMMAND_RAID_ESPECTADOR_SALIR,      false, &HandleRESalidCommand,       "" },
            { "",               rbac::RBAC_PERM_COMMAND_RAID_ESPECTADOR,            false, &HandleRECommand,            "" },
        };
        static std::vector<ChatCommand> commandTable =
        {
            { "raidespectador", rbac::RBAC_PERM_COMMAND_RAID_ESPECTADOR, false, nullptr, "", raidespectadorCommandTable },
        };
        return commandTable;
    }

    // Comando para entrar a ver la raid (holder)
    static bool HandleREEntrarCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            handler->SendSysMessage("aki puedes poner las cosas que necesitas");
            return false;

        return true;
    }

    // Comando para salir de la raid (holder)
    static bool HandleRESalidCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            handler->SendSysMessage("aki puedes poner las cosas que necesitas");
            return false;

        return true;
    }

    // Información acerca del comando en sí y como usarlo (holder)
    static bool HandleRECommand(ChatHandler* handler, char const* args)
    {
        Player* _player = handler->GetSession()->GetPlayer();

        if (!*args)
        {
            handler->SendSysMessage("Simplemente para saber que estoy aqui y que debe aparecer texto indicando que tengo 3 opciones, sino aqui incluirlo");
            return true;
        }

        return false;
    }
};

void AddSC_raidespectador_commandscript()
{
    new raidespectador_commandscript();
}
