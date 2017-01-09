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
#include "firstPointer.c"
char* nextSection(char const* pointer, int isCouncil) {
	char* section;
	if (isCouncil == 0) {
		section = strstr(pointer, "\n\n\t");
			
		if (section != 0) {
			section = section + 3;
		}
	}
	else {
		char* closestsection = 0;
		int num = 1;
		int length = 0;
		while (num <= 200) {
			char needle[20] = {0};
			sprintf(needle, "\n%d\t", num);
			char* commtype1 = strstr(pointer, "-----\n\n\n");
			char* commtype2 = strstr(pointer, "*   *\n\n");
			char* committeesection = firstPointer(commtype1, commtype2);
			char* normalsection = strstr(pointer, needle);
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
