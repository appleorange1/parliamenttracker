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

void individualBreakdown(FILE *webpage, int * parties, char (*partynames)[100], int ayes[1000], int noes[1000], char (*politicians)[100], char (*fullnames)[100], char (*electorates)[100], int isCouncil, char summary[500], uLong adler, char * ymddate) {
	fputs("\n\t<div id=\"individuals\"><p><u>Breakdown by party</u></p>", webpage);
	int party = 1;
	while ((party <= 88) && (partynames[party] != 0x00)) {
		fputs(partynames[party], webpage);
		fputs("\n\t<ul>", webpage);

		int pos = 1;
		while (pos <= 88) {
			if (parties[pos] == party) {
				fputs("\n\t\t<li>\n\t\t\t<a href=\"../../members/", webpage);
				fputs(fullnames[pos], webpage);
				fputs(".html\">", webpage);
				fputs(fullnames[pos], webpage);
				fputs("</a> (<a href=\"https://en.wikipedia.org/wiki/", webpage);
				if (isCouncil == 1) {
					fputs(electorates[pos], webpage);
					fputs(" Region", webpage);
				}
				else {
					fputs("Electoral district of ", webpage);
					fputs(electorates[pos], webpage);
				}
				fputs("\">", webpage);
				fputs(electorates[pos], webpage);
				fputs("</a>): ", webpage);
				int i = 1;
				int vote = 0;
				while (i <= 999) {
					if (ayes[i] == pos)
						vote = 1;
					else if (noes[i] == pos)
						vote = -1;
					i++;
				}
				if (vote == 1) {
					fputs("Yes", webpage);
				}
				else if (vote == -1) {
					fputs("No", webpage);
				}
				else if (vote == 0) {
					fputs("Absent", webpage);
				}
				fputs("</li>", webpage);

				if (summary[0] != 0) {
					FILE *member;
					char filename[100] = {0};
					sprintf(filename, "../../members/%s.html", fullnames[pos]);
					member = fopen(filename, "a");
					fputs("\n\t\t<li>", member);
					fputs("<a href=\"../divisions/", member);
					fputs(ymddate, member);
					fputs("/", member);
					char stradler[100] = {0};
					sprintf(stradler, "%7x.html", adler);
					fputs(stradler, member);
					fputs("\">", member);
					fputs(summary, member);
					fputs("</a>: ", member);
					if (vote == 1)
						fputs("Yes", member);
					else if (vote == -1)
						fputs("No", member);
					else
						fputs("Absent", member);
					fputs("</li>\n", member);
					fclose(member);
				}
			}
			pos++;
		}
		fputs("\n\t</ul>", webpage);
		party++;
	}
	fputs("</div>",webpage);
}
