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

// Returns size of proceedings, outputs proceedings to the parameter "arrayForProceedings"
#include <stdlib.h>
int makeProceedings(char *text, int size, char arrayForProceedings[size]) {
	FILE *fp;
	fp = fopen(text,"r");

	int pos = 0;
	int x;
	while (pos <= size - 1) {
		x = fgetc(fp);
		arrayForProceedings[pos] = x;
		pos++;
	}

	fclose(fp);
	remove(text);
	return size;
}
