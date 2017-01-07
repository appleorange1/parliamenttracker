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

int plotValues(FILE *svg, int parties[88], int ayes[1000], int coordinates[2], int partynumber, char* colour, int right) {
	int k = 1;
	int numberOfMPs = 0;

	int ayeshorizontal = coordinates[0];
	int ayesvertical = coordinates[1];
	while (k <= 999) {
		if (parties[ayes[k]] == partynumber) {
			numberOfMPs++;

			fputs("	<circle cx=\"",svg);

			char tmp[20] = {0};
			sprintf(tmp,"%d",ayeshorizontal);
			fputs(tmp,svg);
			if (right == 0) {
				if (ayeshorizontal <= 25)
					ayeshorizontal = 100;
				else
					ayeshorizontal -= 25;
			}
			else {
				if (ayeshorizontal >= 225)
					ayeshorizontal = 150;
				else
					ayeshorizontal += 25;
			}

			fputs("\" cy=\"",svg);

			char tmp2[20] = {0};
			sprintf(tmp2,"%d",ayesvertical);
			fputs(tmp2,svg);
			if (right == 0) {
				if (ayeshorizontal >= 100)
					ayesvertical -= 25;
			}
			else {
				if (ayeshorizontal <= 150)
					ayesvertical -= 25;
			}

			fputs("\" r=\"10\" fill=\"",svg);

			char tmp3[20] = {0};
			sprintf(tmp3,"%s",colour);
			fputs(tmp3,svg);

			fputs("\" />\n",svg);
		}
		k++;
	}
	coordinates[0] = ayeshorizontal;
	coordinates[1] = ayesvertical;

	return numberOfMPs;
}
