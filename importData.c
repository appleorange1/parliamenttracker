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

#include <stdio.h>
void importData_2Dc(FILE *dataset, int size1, int size2, char (*array)[100]) {
	int pos = 1;
	int ch = 0;
	while (pos <= size1 - 1) {
		while (ch <= size2 - 1) {
			array[pos][ch] = 0x00;
			ch++;
		}
		ch = 0;
		pos++;
	}

	pos = 1;
	while (array[pos-1][0] != 0x0a) {
		fgets(array[pos], size2, dataset);
		pos++;
	}
	pos = 1;
	ch = 0;
	while (pos <= size1 - 1) {
		while (ch <= size2 - 1) {
			if (array[pos][ch] == 0x0a) {
				array[pos][ch] = 0x00;
			}
			ch++;
		}
		ch = 0;
		pos++;
	}
}
void importData_1Di (FILE *dataset, int size1, int array[size1]) {
	int pos = 1;
	while (pos <= size1 - 1) {
		array[pos] = 0x00;
		pos++;
	}

	pos = 1;
	int end = 0;
	while (end == 0) {
		char *endptr;
		char str[50];
		fgets(str, 49, dataset);
		int number = (int) strtol(str, &endptr, 10);
		if (number == 0)
			end = 1;
		array[pos] = number;
		pos++;
	}
}

