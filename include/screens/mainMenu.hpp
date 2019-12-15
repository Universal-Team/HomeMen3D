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

#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "core/management/gameManagement.hpp"

#include "screens/screenCommon.hpp"

#include <vector>

class MainMenu : public screen
{
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
	MainMenu();
	
private:
	// Tests.
	void DrawMenu(void) const;
	int ScreenMode = 1; // Modes.

	// Title Loader stuff.
	int selectedTitle = 0;
	bool GameSelected   = false;
	int maxTitles;

	mutable int screenPos = 0;
	mutable int screenPosList = 0;
	mutable int selection = 0;

	std::shared_ptr<TitleManagement> titleFromIndex(int i) const
	{
		if (i == -2)
		{
			return nullptr;
		}
		else if ((size_t)i < GameManagement::installedTitles.size())
		{
			return GameManagement::installedTitles[i];
		}
		return nullptr;
	}
};

#endif