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

#include "plotValues.c"
#include "writeCount.c"
void plotAndWrite(FILE *svg, FILE *webpage, int * parties, char (*partynames)[100], char (*colors)[100], int coordinates[2], int votes[1000], int isNoes) {
	int party = 1;
	fputs("\n\t<p><i>", webpage);
	if (isNoes == 1)
		fputs("Noes", webpage);
	else
		fputs("Ayes", webpage);
	fputs(" :</i></p>\n\t<ul>", webpage);

	while (party <= 89) {
		int numberOfMPs;
		numberOfMPs = plotValues(svg, parties, votes, coordinates, party, colors[party], isNoes);
		writeCount(webpage, numberOfMPs, party, partynames);
		party++;
	}

	fputs("\n\t</ul>", webpage);
}
