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

#include "common.hpp"
#include "ptmu_x.h"

// Main GUI.
void GFX::DrawTop(void) {
	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 25, C2D_Color32(0, 0, 200, 255));
	Gui::Draw_Rect(0, 25, 400, 190, C2D_Color32(0, 0, 100, 255));
	Gui::Draw_Rect(0, 215, 400, 25, C2D_Color32(0, 0, 200, 255));
}

void GFX::DrawBottom(void) {
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 25, C2D_Color32(0, 0, 200, 255));
	Gui::Draw_Rect(0, 25, 320, 190, C2D_Color32(0, 0, 100, 255));
	Gui::Draw_Rect(0, 215, 320, 25, C2D_Color32(0, 0, 200, 255));
}

extern C2D_SpriteSheet sprites;

void GFX::DrawSprite(int img, int x, int y, float ScaleX, float ScaleY)
{
	C2D_DrawImageAt(C2D_SpriteSheetGetImage(sprites, img), x, y, 0.5f, NULL, ScaleX, ScaleY);
}

void GFX::DrawBatteryTop(void) {
	u8 batteryChargeState = 0;
	u8 batteryPercent;
	mcuGetBatteryLevel(&batteryPercent);
	if (batteryPercent >= 0 && batteryPercent <= 5) {
		DrawSprite(sprites_battery0_idx, 361, 0);
	} else if (batteryPercent >= 6 && batteryPercent <= 25) {
		DrawSprite(sprites_battery1_idx, 361, 0);
	} else if(batteryPercent >= 26 && batteryPercent <= 50) {
		DrawSprite(sprites_battery2_idx, 361, 0);
	} else if(batteryPercent >= 51 && batteryPercent <= 75) {
		DrawSprite(sprites_battery3_idx, 361, 0);
	} else if(batteryPercent >= 76 || batteryPercent == 100) {
		DrawSprite(sprites_battery4_idx, 361, 0);
	}

	if (R_SUCCEEDED(PTMU_GetBatteryChargeState(&batteryChargeState)) && batteryChargeState) {
		DrawSprite(sprites_batteryCharge_idx, 361, 0);
	}
}