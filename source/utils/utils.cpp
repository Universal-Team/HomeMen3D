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

#include "utils/utils.hpp"

#include <memory>
#include <stdarg.h>

std::u16string UTF8toUTF16(const char* src)
{
	char16_t tmp[256] = {0};
	utf8_to_utf16((uint16_t*)tmp, (uint8_t*)src, 256);
	return std::u16string(tmp);
}

static std::string utf16DataToUtf8(const char16_t* data, size_t size, char16_t delim = 0)
{
	std::string ret;
	ret.reserve(size);
	char addChar[4] = {0};
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == delim)
		{
			return ret;
		}
		else if (data[i] < 0x0080)
		{
			addChar[0] = data[i];
			addChar[1] = '\0';
		}
		else if (data[i] < 0x0800)
		{
			addChar[0] = 0xC0 | ((data[i] >> 6) & 0x1F);
			addChar[1] = 0x80 | (data[i] & 0x3F);
			addChar[2] = '\0';
		}
		else
		{
			addChar[0] = 0xE0 | ((data[i] >> 12) & 0x0F);
			addChar[1] = 0x80 | ((data[i] >> 6) & 0x3F);
			addChar[2] = 0x80 | (data[i] & 0x3F);
			addChar[3] = '\0';
		}
		ret.append(addChar);
	}
	return ret;
}

std::string UTF16toUTF8(const std::u16string& src)
{
	return utf16DataToUtf8(src.data(), src.size());
}

std::string format(std::string fmt_str, ...)
{
	va_list ap;
	char* fp = NULL;
	va_start(ap, fmt_str);
	vasprintf(&fp, fmt_str.c_str(), ap);
	va_end(ap);
	std::unique_ptr<char, decltype(free)*> formatted(fp, free);
	return std::string(formatted.get());
}

std::string timeStr(void)
{
	time_t unixTime       = time(NULL);
	struct tm* timeStruct = gmtime((const time_t*)&unixTime);
	return format("%02i:%02i:%02i", timeStruct->tm_hour, timeStruct->tm_min, timeStruct->tm_sec);
}