/*
    Copyright (C) 2017 Riley Baird <riley@openmailbox.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stdio.h>
#include "getTitle.c"
#include "firstPointer.c"
char const* nextSection(char const* pointer, int isCouncil) {
	char* section;
	if (isCouncil == 0) {
		char const* type1;
		char const* type2;
		char const* closestsection = 0;
		type1 = strstr(pointer, "\n\n\t");
		if (type1 != 0) {
			// We want to make sure that there are no lower-case
			// letters in the second letter of the title. Because
			// the position of the second letter of the title
			// varies, we check two different places. The reason
			// we perform this check is to prevent one-letter titles
			// from being treated as valid.

			while ((*(type1+6) >= 0x61 && *(type1+6) <= 0x7A) || \
			    (*(type1+7) >= 0x61 && *(type1+7) <= 0x7A)) {
				type1 = strstr(type1+1, "\n\n\t");
			}
		}
		int length = 3;
		int num = 1;
		while (num <= 200) {
			char needle[20] = {0};
			sprintf(needle, "\t%d\t", num);
			type2 = strstr(pointer, needle);
			if (type2 != 0) {
				if ((intptr_t) type2 < (intptr_t) closestsection || (intptr_t) closestsection == 0 ) {
					closestsection = type2;
					if (num <= 9)
						length = 3;
					else if (num <= 99)
						length = 4;
					else
						length = 5;
				}
			}
			num++;
		}
		section = firstPointer(type1, closestsection);

		if (section != 0) {
			section = section + length;
		}
	}
	else {
		char const* closestsection = 0;
		int num = 1;
		int length = 0;
		while (num <= 200) {
			char needle[20] = {0};
			sprintf(needle, "\n%d\t", num);
			char const* commtype1 = strstr(pointer, "-----\n\n\n");
			char const* commtype2 = strstr(pointer, "*   *\n\n");
			char const* committeesection = firstPointer(commtype1, commtype2);
			char const* normalsection = strstr(pointer, needle);
			if (normalsection != 0) {
				if (firstPointer(normalsection, committeesection) == normalsection) {
					if ((intptr_t) normalsection < (intptr_t) closestsection || (intptr_t) closestsection == 0 ) {
						closestsection = normalsection;
						if (num <= 9)
							length = 3;
						else if (num <= 99)
							length = 4;
						else
							length = 5;
					}
				}
				else {
					if ( ((intptr_t) committeesection < (intptr_t) closestsection) || ((intptr_t) closestsection == 0) ) {
						closestsection = committeesection;
						length = 7;
					}
				}
			}
			num++;
		}
		section = closestsection;
		if (section != 0)
			section = section + length;
	}
	return section;
}
