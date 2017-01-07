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

void writeCount(FILE *file, int numberOfMPs, int partynumber, char (*partytable)[100]) {
	if (numberOfMPs > 0) {


		fputs("\n\t\t<li>", file);
		fputs(partytable[partynumber], file);
		fputs(": ", file);

		char number[20];
		sprintf(number, "%d</li>", numberOfMPs);
		fputs(number, file);
	}
}
