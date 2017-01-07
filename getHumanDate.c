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

//Pointer refers to the end of the minutes if we're using Assembly data,
//but pointer refers to the start of the minutes if we're using Council data
#include <string.h>
char * getHumanDate(char *pointer, int isCouncil) {
	int shift;
	int pos = 0;
	if (isCouncil == 0) {
		while (!( (*(pointer-pos) == 0x0a && \
			 *(pointer-pos+1) == 0x0a && \
			 *(pointer-pos+2) == 0x4e && \
			 *(pointer-pos+3) == 0x6f && \
			 *(pointer-pos+4) == 0x20) || \
			 (*(pointer-pos) == 0x53 && \
			 *(pointer-pos+1) == 0x70 && \
			 *(pointer-pos+2) == 0x65 && \
			 *(pointer-pos+3) == 0x61 && \
			 *(pointer-pos+4) == 0x6b && \
			 *(pointer-pos+5) == 0x65 && \
			 *(pointer-pos+6) == 0x72 && \
			 *(pointer-pos+7) == 0x0a && \
			 *(pointer-pos+8) == 0x4e && \
			 *(pointer-pos+9) == 0x6f && \
			 *(pointer-pos+10) == 0x20) || \
			 (*(pointer-pos) == 0x20 && \
			 *(pointer-pos+1) == 0x0a && \
			 *(pointer-pos+2) == 0x20 && \
			 *(pointer-pos+3) == 0x0a && \
			 *(pointer-pos+4) == 0x4e && \
			 *(pointer-pos+5) == 0x6f && \
			 *(pointer-pos+6) == 0x20) )) {
			pos++;
		}
		shift = 4;
	}
	else {
		while (!(*(pointer-pos) == 0x20 && \
			 *(pointer-pos+1) == 0x20 && \
			 *(pointer-pos+2) == 0x20 && \
			 *(pointer-pos+3) == 0x4e && \
			 *(pointer-pos+4) == 0x6f && \
			 *(pointer-pos+5) == 0x2e)) {
			pos++;
		}
		shift = 5;
	}
	pointer = strstr(pointer-pos, "day");
	if (pointer != 0)
		pointer = pointer + shift;

	static char humandate[100] = {0};
	int hdatepos = 0;

	//while (!((*pointer == 0x0a) && (*(pointer+1) == 0x0a))) {
	while (!(*pointer == 0x0a)) {
		humandate[hdatepos] = *pointer;
		hdatepos++; pointer++;
	}
	while (hdatepos <= 99) {
		humandate[hdatepos] = 0;
		hdatepos++;
	}

	return humandate;
}
