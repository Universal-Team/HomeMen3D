/*
*   This file is part of HomeMen3D
*   Copyright (C) 2019 DeadPhoenix8091, Epicpkmn11, Flame, RocketRobz, StackZ, TotallyNotGuy
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "colors.hpp"
#include "gui.hpp"

#include "core/management/gameManagement.hpp"

#include "screens/mainMenu.hpp"
#include "screens/screenCommon.hpp"

#include "utils/ptmu_x.h"

#include <dirent.h>

bool exiting = false;

// Set to true, if Citra is used.
bool isCitra = false;

touchPosition touch;

int main()
{
	gfxInitDefault();
	romfsInit();
	Gui::init();
	acInit();
	// For battery status
	ptmuInit();
	// For AC adapter status
	ptmuxInit();
	
	if (!isCitra) {
		mcuInit();
	}
	cfguInit();

	mkdir("sdmc:/3ds", 0777);
	mkdir("sdmc:/3ds/HomeMen3D", 0777);

	DisplayMsg("Scanning for available 3DS Titles...");
	GameManagement::scanTitleID();

	// Set Screen to MainMenu.
	Screen::set(std::make_unique<MainMenu>());

	osSetSpeedupEnable(true);	// Enable speed-up for New 3DS users.

	// Loop as long as the status is not exit.
	while (aptMainLoop() && !exiting)
	{
		// Scan Input.
		hidScanInput();
		u32 hHeld = hidKeysHeld();
		u32 hDown = hidKeysDown();
		hidTouchRead(&touch);

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, BLACK);
		C2D_TargetClear(Bottom, BLACK);
		Gui::clearTextBufs();
		Screen::loop(hDown, hHeld, touch);
		C3D_FrameEnd(0);
	}
	Gui::exit();
	gfxExit();
	cfguExit();
	romfsExit();
	return 0;
}