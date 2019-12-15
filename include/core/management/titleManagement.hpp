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

#ifndef TITLEMANAGEMENT_HPP
#define TITLEMANAGEMENT_HPP

#include <3ds.h>
#include <algorithm>
#include <citro2d.h>
#include <string>

class TitleManagement
{
public:
	TitleManagement(void) = default;
	~TitleManagement(void);

	// Title Handling.
	bool load(u64 id, FS_MediaType mediaType);
	u32 highId(void);
	u32 lowId(void);
	u64 ID(void);
	FS_MediaType mediaType(void);
	std::string name(void);
	std::string Author(void);
	C2D_Image icon(void);

private:
	u64 mId;
	FS_MediaType mMedia;
	FS_CardType mCard;
	C2D_Image mIcon;
	std::string mName;
	std::string mAuthor;
};

#endif