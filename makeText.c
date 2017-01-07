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
char * makeText(char *document) {
	char str[80] = "docx2txt.pl ";
	char* output = tmpnam(NULL);
	strcat(str," \"");
	strcat(str,document);
	strcat(str,"\" ");

	strcat(str,output);
	int command = system(str);
	if (command != 0) {
		printf("Error reading votes and proceedings file\n");
	}

	return output;
}
