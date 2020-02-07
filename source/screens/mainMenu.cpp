/*
*   This file is part of HomeMen3D
*   Copyright (C) 2019-2020 DeadPhoenix8091, Epicpkmn11, Flame, RocketRobz, StackZ, TotallyNotGuy
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

#include "mainMenu.hpp"
#include "utils.hpp"

extern bool exiting;

// Because we display 4 Icons.
#define ENTRIES_PER_SCREEN 4

// Get the Max Amount of available Titles.
MainMenu::MainMenu() {
	maxTitles = (int)GameManagement::installedTitles.size();
}

void MainMenu::Draw(void) const
{
	if (ScreenMode == 1) {
		DrawMenu();
	}
}

void MainMenu::DrawMenu(void) const {
	GFX::DrawTop();
	Gui::DrawString(0, 2, 0.7f, WHITE, timeStr());
	GFX::DrawBatteryTop();
	Gui::DrawString(397-Gui::GetStringWidth(0.6f, "Titles: " + std::to_string(selectedTitle + 1) + " / " + std::to_string(maxTitles)), 237-Gui::GetStringHeight(0.6f, "Titles: " + std::to_string(selectedTitle + 1) + " / " + std::to_string(maxTitles)), 0.6f, WHITE, "Titles: " + std::to_string(selectedTitle + 1) + " / " + std::to_string(maxTitles));
	GFX::DrawBottom();

	Gui::Draw_Rect(0, 215, 160, 25, C2D_Color32(0, 0, 160, 255));
	Gui::Draw_Rect(160, 215, 160, 25, C2D_Color32(0, 0, 160, 190));

	// Draw Boxees.
	Gui::Draw_Rect(50, 160, 48, 48, C2D_Color32(160, 160, 160, 255));
	Gui::Draw_Rect(110, 160, 48, 48, C2D_Color32(160, 160, 160, 255));
	Gui::Draw_Rect(170, 160, 48, 48, C2D_Color32(160, 160, 160, 255));
	Gui::Draw_Rect(230, 160, 48, 48, C2D_Color32(160, 160, 160, 255));

	Gui::Draw_Rect(10, 50, 300, 100, C2D_Color32(130, 130, 130, 255));

	for(int i=0;i<ENTRIES_PER_SCREEN && i<maxTitles;i++) {
		if(screenPos + i == selection) {
			Gui::Draw_Rect(50 +(i*60)-1, 160-1, 50, 50, C2D_Color32(0, 200, 0, 255));
		}
		C2D_DrawImageAt(GameManagement::installedTitles[screenPos+i]->icon(), 50 +(i*60), 160, 0.5f); // Installed Title Icon.
	}

	Gui::DrawStringCentered(0, 75, 0.7f, BLACK, GameManagement::installedTitles[selectedTitle]->name());
	Gui::DrawStringCentered(0, 105, 0.7f, BLACK, GameManagement::installedTitles[selectedTitle]->Author());
	Gui::DrawString(35, 217, 0.7f, WHITE, "\uE000: Start");
	Gui::DrawString(175, 217, 0.7f, WHITE, "\uE07B / \uE07C: Navigate");
}

void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	// Exit the App with <START> here.
	if (hDown & KEY_START) {
		exiting = true;
	}

	// Selection == 0/2 maybe for a submenu or so? Dunno.
	if (ScreenMode == 1) {
		if (selectedTitle == -2)
		{
			if (!GameManagement::installedTitles.empty())
			{
				selectedTitle = 0;
				selection = 0;
			}
		}

		// Scroll with D-Pad Right to the next available Title.
		if (hDown & KEY_RIGHT)
		{
			if (selectedTitle == (int)GameManagement::installedTitles.size() - 1 || selectedTitle == maxTitles - 1)
			{
				if ((int)GameManagement::installedTitles.size() > maxTitles && selectedTitle > maxTitles - 1)
				{
					if (selectedTitle > maxTitles - 1)
					{
						selectedTitle = maxTitles;
						selection = maxTitles;
					}
					else if (selectedTitle == maxTitles - 1)
					{
						selectedTitle = 0;
						selection = 0;
					}
				}
				else
				{
					selectedTitle = 0;
					selection = 0;
				}
			}
			else
			{
				selectedTitle++;
				selection++;
			}
		}

	// Scroll with D-Pad Left to the last available Title.
		if (hDown & KEY_LEFT)
		{
			if (selectedTitle == -1)
			{
				selectedTitle = (int)GameManagement::installedTitles.size() < maxTitles ? GameManagement::installedTitles.size() - 1 : maxTitles - 1;
				selection = (int)GameManagement::installedTitles.size() < maxTitles ? GameManagement::installedTitles.size() - 1 : maxTitles - 1;
			}
			else if (selectedTitle == maxTitles)
			{
				selectedTitle = (int)GameManagement::installedTitles.size() - 1;
				selection = (int)GameManagement::installedTitles.size() - 1;
			}
			else if (selectedTitle == 0)
			{
				selectedTitle = (int)GameManagement::installedTitles.size() > maxTitles ? maxTitles - 1 : (int)GameManagement::installedTitles.size() - 1;
				selection = (int)GameManagement::installedTitles.size() > maxTitles ? maxTitles - 1 : (int)GameManagement::installedTitles.size() - 1;
			}
			else
			{
				selectedTitle--;
				selection--;
			}
		}
		// Launch the Title with <A>.
		if (hDown & KEY_A) {
			if (!GameManagement::installedTitles.empty()) {
				u8 param[0x300];
				u8 hmac[0x20];
				memset(param, 0, sizeof(param));
				memset(hmac, 0, sizeof(hmac));
				APT_PrepareToDoApplicationJump(0, GameManagement::installedTitles[selectedTitle]->ID(), MEDIATYPE_SD);
				APT_DoApplicationJump(param, sizeof(param), hmac);
			}
		}
	}
	if(selection < screenPos) {
		screenPos = selection;
	} else if (selection > screenPos + ENTRIES_PER_SCREEN - 1) {
		screenPos = selection - ENTRIES_PER_SCREEN + 1;
	}
}