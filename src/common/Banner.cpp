/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
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

#include "Banner.h"
#include "GitRevision.h"
#include "StringFormat.h"

void Trinity::Banner::Show(char const* applicationName, void(*log)(char const* text), void(*logExtraInfo)())
{
    log(Trinity::StringFormat("%s (%s)", GitRevision::GetFullVersion(), applicationName).c_str());
    log("Presione <Ctrl-C> para detenerlo.\n");
    log("   _______       __ ");
    log("  /\\  ____\\   __/\\ \\      ________");
    log("  \\ \\ \\___/  /\\_\\ \\ \\    /\\  ____ \\");
    log("   \\ \\ \\____ \\/_/_ \\ \\   \\ \\ \\__/\\ \\");
    log("    \\ \\  ___\\  /\\ \\ \\ \\   \\ \\ \\ \\ \\ \\");
    log("     \\ \\ \\__/  \\ \\ \\ \\ \\   \\ \\ \\___\\ \\");
    log("      \\ \\ \\_____\\ \\ \\ \\ \\___\\ \\_______\\");
    log("       \\ \\_______\\/_/\\ \\_____\\/_______/");
    log("        \\/_______/    \\/_____/       World");
    log("");
    log("   * Basado en TrinityCore *");
    log("         ComunidadRean");

    if (logExtraInfo)
        logExtraInfo();
}
