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

#include "core/management/titleManagement.hpp"

#include "utils/utils.hpp"

// Properly free the Icon.
TitleManagement::~TitleManagement(void)
{
	if (mCard != CARD_TWL && mIcon.tex)
		C3D_TexDelete(mIcon.tex);
}

// Load the Icon from the SMDH.
static C2D_Image loadTextureIcon(smdh_s* smdh)
{
	C3D_Tex* tex                          = new C3D_Tex;
	static const Tex3DS_SubTexture subt3x = {48, 48, 0.0f, 48 / 64.0f, 48 / 64.0f, 0.0f};
	C3D_TexInit(tex, 64, 64, GPU_RGB565);

	u16* dest = (u16*)tex->data + (64 - 48) * 64;
	u16* src  = (u16*)smdh->bigIconData;
	for (int j = 0; j < 48; j += 8)
	{
		std::copy(src, src + 48 * 8, dest);
		src += 48 * 8;
		dest += 64 * 8;
	}

	return C2D_Image{tex, &subt3x};
}

// Load the Title. (Used for the Scan as well.)
bool TitleManagement::load(u64 id, FS_MediaType media)
{
	bool loadTitle = false;
	mId            = id;
	mMedia         = media;

	smdh_s* smdh = loadSMDH(lowId(), highId(), mMedia);
	if (smdh == NULL)
	{
		return false;
	}

	mName   = UTF16toUTF8((char16_t*)smdh->applicationTitles[1].shortDescription);
	mAuthor = UTF16toUTF8((char16_t*)smdh->applicationTitles[1].publisher);
	loadTitle = true;
	mIcon     = loadTextureIcon(smdh);
	delete smdh;
	return loadTitle;
}


u32 TitleManagement::highId(void)
{
	return (u32)(mId >> 32);
}

u32 TitleManagement::lowId(void)
{
	return (u32)mId;
}

u64 TitleManagement::ID(void)
{
	return (u64)highId() << 32 | lowId();
}

FS_MediaType TitleManagement::mediaType(void)
{
	return mMedia;
}

// Get the Icon from the SMDH.

C2D_Image TitleManagement::icon(void)
{
	return mIcon;
}

// get the name of the Title from the SMDH.
std::string TitleManagement::name(void)
{
	return mName;
}

std::string TitleManagement::Author(void)
{
	return mAuthor;
}