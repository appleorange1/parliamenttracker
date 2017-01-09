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

#include <ctype.h>
#include <sys/stat.h>
#include <zlib.h>
#include "getDivision.c"
#include "getTitle.c"
#include "importData.c"
#include "individualBreakdown.c"
#include "insertTitle.c"
#include "nextSection.c"
#include "plotAndWrite.c"

int parse(FILE *index, int size, char proceedings[size], int isCouncil, int * useddates) {
	char * rootdir = getcwd(Z_NULL,0);

	int pos = 0;
	char titles[1000][1000] = {0};
	char* section = nextSection(proceedings, isCouncil);

	while (pos <= 999 && section != 0) {
		char title1[1000] = {0};
		getTitle(title1, section);
		insertTitle(titles,pos,title1);
		section = nextSection(section+1, isCouncil);
		pos++;
	}


	section = nextSection(proceedings, isCouncil);

	char olddate[8] = "00000000";

	FILE *dataset;
	if (isCouncil == 0) {
		char * ymddate;
		char *endptr;
		ymddate = getYMDDate(section, isCouncil);
		if (strtol(ymddate, &endptr, 10) < 20151031L) {
			dataset = fopen("assembly.data.0","r");
		}
		else
			dataset = fopen("assembly.data.1","r");
		chdir("assembly/divisions");
	}
	else {
		char * ymddate;
		char *endptr;
		ymddate = getYMDDate(section, isCouncil);
		if (strtol(ymddate, &endptr, 10) < 20161013L)
			dataset = fopen("council.data.0","r");
		else
			dataset = fopen("council.data.1","r");
		chdir("council/divisions");
	}
	char (*partynames)[100] = calloc(90, sizeof(*partynames));
	char (*colors)[100] = calloc(90, sizeof(*colors));
	char (*politicians)[100] = calloc(90, sizeof(*politicians));
	char (*fullnames)[100] = calloc(90, sizeof(*fullnames));
	char (*electorates)[100] = calloc(90, sizeof(*electorates));
	int parties[89] = {0};

	importData_2Dc(dataset, 90, 100, partynames);
	importData_2Dc(dataset, 90, 100, colors);
	importData_1Di(dataset, 90, parties);
	importData_2Dc(dataset, 90, 100, politicians);
	importData_2Dc(dataset, 90, 100, fullnames);
	importData_2Dc(dataset, 90, 100, electorates);

	FILE *questions;
	questions = fopen("../../questions.data", "r");
	int qhouses[500] = {0};
	int qdates[500] = {0};
	uLong qadlers[500] = {0};
	char qtext[500][500] = {0};

	int i = 0;
	char isNewline = 0x0a;
	while (i <= 499 && isNewline == 0x0a) {
		char *endptr;
		char qhouse[10] = {0};
		fgets(qhouse, 10, questions);
		qhouses[i] = (int) strtol(qhouse, &endptr, 10);

		char qdate[20] = {0};
		fgets(qdate, 20, questions);
		qdates[i] = (int) strtol(qdate, &endptr, 10);

		char qadler[20] = {0};
		fgets(qadler, 20, questions);
		qadlers[i] = strtoul(qadler, &endptr, 16);

		fgets(qtext[i], 500, questions);

		//Skip linebreak
		isNewline = getc(questions);

		i++;
	}

	int j = 0;
	int divNum = 0;
	while (j <= 1000 && section != 0) {
		while (divNum <= 20) {
			int ayes[1000] = {0};
			int noes[1000] = {0};

			char title1[1000] = {0};
			getTitle(title1,section);

			char uniquetitle[1004] = {0};
			sprintf(uniquetitle, "%s%d%d", title1, j, divNum);

			uLong adler = adler32(0L,Z_NULL,0);
			adler = adler32(adler,uniquetitle,1000);

			if (getDivision(ayes,noes,politicians,section,proceedings+size, divNum, isCouncil) == 0) {
				char * humandate = getHumanDate(section, isCouncil);
				char * ymddate = getYMDDate(section, isCouncil);

				struct stat st = {0};
				if (stat(ymddate, &st) == -1) {
					mkdir(ymddate, 0777);
				}
				chdir(ymddate);

				FILE *division;
				char filename[1000];
				sprintf(filename,"%7x.svg",adler);
				division = fopen(filename,"w");

				FILE *webpage;
				char webname[1000];
				sprintf(webname,"%7x.html",adler);
				webpage = fopen(webname,"w");

				char *endptr;
				int intdate = (int) strtol(ymddate, &endptr, 10);
				if (strncmp(ymddate, olddate, 8) != 0) {
					int usedpos = 0;
					int alreadyUsed = 0;
					while (useddates[usedpos] != 0) {
						if (intdate == useddates[usedpos]) {
							alreadyUsed = 1;
						}
						usedpos++;
					}

					if (alreadyUsed == 0) {
						fputs("\n\t<center>\n\t\t<i>\n\t\t\t", index);
						fputs(humandate, index);
						fputs("\n\t\t</i>\n\t</center>", index);
					}
					usedpos = 0;
					while (useddates[usedpos] != 0x00)
						usedpos++;
					useddates[usedpos] = intdate;
				}


				int datepos = 0;
				while (datepos <= 7) {
					olddate[datepos] = ymddate[datepos];
					datepos++;
				}

				fputs("<html>\n<head>\n<title>\n\t", webpage);
				printf("%s\n", title1);
				fputs(title1, webpage);
				fputs("\n</title>\n<style>\nimg {\n\tfloat: right;\n\tmargin: 0 0 10px 10px;\n}\np {\n\tfont-size: 3vh;\n}\n#heading {\n\tfloat: left;\n}\n#menu {\n\tfloat: right;\n}#individuals {\n\tclear:both;\n}\n</style>\n</head>\n\n<body>", webpage);
				fputs("\n\t<div id=\"heading\">\n\t<b style=\"font-size: large\">Victorian Parliament Tracker</b>\n\t</div>\n\n\t<div id=\"menu\">\n\t<a href=\"../../../index.html\">Home</a>\n\t<a href=\"../../../members.html\">People</a>\n\t<a href=\"../../../about.html\">About</a>\n\t</div>\n", webpage);

				fputs("\n\t<div id=\"individuals\">\n\t<br>\n\t<b>\n\t\t<center>\n\t\t\t", webpage);
				fputs(title1, webpage);
				fputs(" (", webpage);
				fputs(humandate, webpage);
				fputs(")", webpage);
				fputs("\n\t\t</center>\n\t</b>", webpage);

				fputs("\n\t<center><i>", webpage);
				int found = 0;
				int questionspos = 0;
				char summary[500] = {0};
				while (questionspos <= 499 && found == 0) {
					if (qhouses[questionspos] == isCouncil && qdates[questionspos] == intdate && qadlers[questionspos] == adler) {
						found = 1;
						int tmppos = 0;
						while (tmppos <= 499) {
							summary[tmppos] = qtext[questionspos][tmppos];
							tmppos++;
						}
						fputs(summary, webpage);
					}
					questionspos++;
				}

				if (found == 0) {
					fputs("This division doesn't have an easy to read summary yet! To find out more, try searching using the below links, and if you can, send us a summary so that we can put it on the website.", webpage);
				}
				fputs("</i></center>", webpage);

				int character = 0;
				char day[3] = {0};
				int daypos = 0;
				while (humandate[character] != 0x20) {
					day[daypos] = humandate[character];
					character++; daypos++;
				}
				character++;
				char month[10] = {0};
				int monthpos = 0;
				while (humandate[character] != 0x20) {
					month[monthpos] = humandate[character];
					character++; monthpos++;
				}
				character++;
				char year[6] = {0};
				int yearpos = 0;
				while (yearpos <= 3) {
					year[yearpos] = humandate[character];
					character++; yearpos++;
				}

				char lowercasetitle[1000] = {0};
				pos = 0;
				while (pos <= 999) {
					lowercasetitle[pos] = tolower(title1[pos]);
					pos++;
				}

				fputs("\n\t<p>\n\t\t<center>\n\t\t\t<a href=\"http://hansard.parliament.vic.gov.au/search/?IW_BATCHSIZE=&IW_SORT=&IW_FIELD_ADVANCE_AND=", webpage);
				fputs(lowercasetitle, webpage);
				fputs("&IW_FIELD_ADVANCE_PHRASE=&IW_FIELD_ADVANCE_OR=&IW_FIELD_ADVANCE_NOT=&IW_FIELD_IN_SpeechTitle=&IW_FIELD_IN_MemberParty=&IW_FILTER_DATE_AFTER=&IW_FIELD_IN_MEMBERNAME=&IW_FIELD_IN_MEMBERNAME=&IW_FIELD_IN_HOUSENAME=", webpage);
				if (isCouncil == 0)
					fputs("ASSEMBLY", webpage);
				else
					fputs("COUNCIL", webpage);
				fputs("&IW_FIELD_IN_ACTIVITYTYPE=&IW_FIELD_IN_ParliamentNo=&IW_FIELD_IN_SittingYear=", webpage);
				fputs(year, webpage);
				fputs("&IW_FIELD_IN_SittingMonth=", webpage);
				fputs(month, webpage);
				fputs("&IW_FIELD_IN_SittingDay=", webpage);
				/*
				fputs(day, webpage);
				*/
				fputs("&IW_DATABASE=*", webpage);
				fputs("\">View debates in Hansard</a>\n\t\t\t<a href=\"https://duckduckgo.com/?q=", webpage);
				fputs(title1, webpage);
				fputs("\">Search on DuckDuckGo</a>\n\t\t</center>\n\t</p>\n\t</div>", webpage);


				fputs("\n\t<img width=\"40%\" height=\"60%\" alt=\"Coloured circles repesenting parties with \'Ayes\' on the left and \'Noes\' on the right\" src=\"", webpage);
				fputs(filename, webpage);
				fputs("\" />", webpage);



				int m = 1;
				int ystart;
				while (m <= 999) {
					if ((ayes[m] != 0) || (noes[m] != 0))
						ystart = 525-(25*((m/4)));
					else break;
					m++;
				}

				int coordinates[2] = {100, 550};

				fputs("<svg viewBox=\"0 ", division);

				char tmp4[20];
				sprintf(tmp4, "%d", ystart);
				fputs(tmp4, division);

				fputs(" 250 ", division);

				char tmp5[20];
				sprintf(tmp5, "%d", 575 - ystart);
				fputs(tmp5, division);

				fputs("\" style=\"background: white\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n",division);

				plotAndWrite(division, webpage, parties, partynames, colors, coordinates, ayes, 0);

				coordinates[0] = 150;
				coordinates[1] = 550;
				plotAndWrite(division, webpage, parties, partynames, colors, coordinates, noes, 1);

				fputs("</svg>",division);

				individualBreakdown(webpage, parties, partynames, ayes, noes, politicians, fullnames, electorates, isCouncil, summary, adler, ymddate);

				fputs("\n</body>\n</html>", webpage);
				
				fputs("\n\t<p>\n\t\t<a href=\"../", index);
				if (isCouncil == 0)
					fputs("assembly", index);
				else
					fputs("council", index);
				fputs("/divisions/", index);
				fputs(ymddate, index);
				fputs("/", index);
				fputs(webname, index);
				fputs("\">\n\t\t\t", index);
				fputs(title1, index);
				fputs("\n\t\t</a>", index);
				fputs("\n\t</p>\n", index);

				chdir("..");
			}
			divNum++;
		}
		divNum = 0;

		section = nextSection(section+1, isCouncil);
		j++;
	}

	chdir(rootdir);
	
	return 0;
}

