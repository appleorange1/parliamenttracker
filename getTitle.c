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

void getTitle(char tableOfZeroes[1000], char const* pointer) {
	int isTitle = 1;
        int pos = 0;
	int first = 0;
        int titlepos = 0;
	while (isTitle == 1) {
		// First value must be a capital letter
 		if (*(pointer+pos) >= 0x41 && *(pointer+pos) <= 0x5A && first == 0) {
                        tableOfZeroes[titlepos] = *(pointer+pos);
                        titlepos++;
			first = 1;
			pos++;
                }
		// After this, valid values are capital letters, numbers, commas and spaces. Hyphens are valid if the previous value isn't a space
 		if (((*(pointer+pos) >= 0x41 && *(pointer+pos) <= 0x5A) || //
		     (*(pointer+pos) >= 0x30 && *(pointer+pos) <= 0x39)) || //
		     (*(pointer+pos) == 0x20) || //
		     (*(pointer+pos) == 0x28) || //
		     (*(pointer+pos) == 0x29) || //
		     (*(pointer+pos) == 0x2C) || //
		     ((*(pointer+pos) == 0x2D) && (*(pointer+pos+1) != 0x2D))) {
		     //((*(pointer+pos) == 0x2D) && (*(pointer+pos-1) != 0x20))) {
			if (first == 1) {
				tableOfZeroes[titlepos] = *(pointer+pos);
				titlepos++;
			}
		}
		else if (first == 1) {isTitle = 0;}
       		pos++;
        }
}
