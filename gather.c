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

#define _XOPEN_SOURCE

#include <dirent.h>
#include <libgen.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <time.h>
#include "getSize.c"
#include "getYMDDate.c"
#include "makeProceedings.c"
#include "makeText.c"
#include "parse.c"

int main(int argc, char *argv[]) {
	const rlim_t stacksize= 32L * 1024L * 1024L; //Set stack size to 32M
	struct rlimit rl;
	rl.rlim_cur = stacksize;
	setrlimit(RLIMIT_STACK, &rl);

	struct stat st = {0};
	if (stat("assembly", &st) == -1) {
		mkdir("assembly", 0777);
	}
	if (stat("assembly/divisions", &st) == -1) {
		mkdir("assembly/divisions", 0777);
	}
	if (stat("assembly/members", &st) == -1) {
		mkdir("assembly/members", 0777);
	}
	if (stat("council", &st) == -1) {
		mkdir("council", 0777);
	}
	if (stat("council/divisions", &st) == -1) {
		mkdir("council/divisions", 0777);
	}
	if (stat("council/members", &st) == -1) {
		mkdir("council/members", 0777);
	}
	if (stat("index", &st) == -1) {
		mkdir("index", 0777);
	}

	char housename[4][20] = {"assembly", "assembly", "council", "council"};

	int polipos = 1;
	int data = 0;
	while (data <= 3) {
		FILE *dataset;
		if (data == 0)
			dataset = fopen("assembly.data.0", "r");
		else if (data == 1)
			dataset = fopen("assembly.data.1", "r");
		else if (data == 2)
			dataset = fopen("council.data.0", "r");
		else
			dataset = fopen("council.data.1", "r");

		char (*partynames)[100] = calloc(90, sizeof(*partynames));
		char (*colors)[100] = calloc(90, sizeof(*colors));
		char (*politicians)[100] = calloc(90, sizeof(*politicians));
		char (*electorates)[100] = calloc(90, sizeof(*electorates));
		char (*fullnames)[100] = calloc(90, sizeof(*fullnames));

		int parties[89] = {0};
		
		importData_2Dc(dataset, 90, 100, partynames);
		importData_2Dc(dataset, 90, 100, colors);
		importData_1Di(dataset, 90, parties);
		importData_2Dc(dataset, 90, 100, politicians);
		importData_2Dc(dataset, 90, 100, fullnames);
		importData_2Dc(dataset, 90, 100, electorates);

		while (polipos <= 88) {
			FILE *member;
			char filename[100] = {0};
			sprintf(filename, "%s/members/%s.html", housename[data], fullnames[polipos]);
			member = fopen(filename, "w");
			fputs("<html>\n<style>\n#heading {\n\tfloat: left;\n}\n#menu {\n\tfloat: right;\n}\n#notices {\n\tclear: both;\n}\nli {\n\tmargin: 10px 0;\n}", member);
			fputs("\n</style>\n<body>\n\t<title>\n\t\t", member);
			fputs(fullnames[polipos], member);
			fputs(" - Victorian Parliament Tracker\n\t</title>\n\t<div id=\"heading\">\n\t\t<b>Victorian Parliament Tracker</b>\n\t</div>\n\t<div id=\"menu\">\n\t\t<a href=\"../../index.html\">Home</a>\n\t\t<a href=\"../../members.html\">People</a>\n\t\t<a href=\"../../about.html\">About</a>\n\t</div>\n\t<div id=\"notices\">\n\t<center><br><b><a href=\"https://en.wikipedia.org/wiki/", member);
			fputs(fullnames[polipos], member);
			fputs("\">", member);
			fputs(fullnames[polipos], member);
			fputs("</a></b>\n\t<br>\n\t(<a href=\"https://en.wikipedia.org/wiki/", member);
			if (data <= 1) {
				fputs("Electoral district of ", member);
				fputs(electorates[polipos], member);
			}
			else {
				fputs(electorates[polipos], member);
				fputs(" Region", member);
			}
			fputs("\">", member);
			fputs(electorates[polipos], member);
			fputs("</a>, ", member);
			fputs(partynames[parties[polipos]], member);
			fputs(")", member);
			fputs("</center>\n\t\t<ul>", member);
			fclose(member);
			polipos++;
		}
		//fclose(dataset);
		polipos = 1;
		data++;
	}

	FILE *assemblyindex;
	assemblyindex = fopen("index/assembly.html", "w");

	FILE *councilindex;
	councilindex = fopen("index/council.html", "w");

	fputs("<html>\n<head>\n<style>\n#heading {\n\tfloat: left;\n}\n#menu {\n\tfloat: right;\n}\n#contents {\n\tclear: both;\n}\n</style>\n\t<title>List of Legislative Assembly Divisions - Victorian Parliament Tracker</title>\n</head>\n\n<body>\n<div id=\"heading\">\n\t<b style=\"font-size: large\">Victorian Parliament Tracker</b>\n</div>\n<div id=\"menu\">\n\t<a href=\"../index.html\">Home</a>\n\t<a href=\"../members.html\">People</a>\n\t<a href=\"../about.html\">About</a>\n</div>\n<div id=\"contents\">\n\t<b>\n\t\tList of Legislative Assembly Divisions\n\t</b>", assemblyindex);
	fputs("<html>\n<head>\n<style>\n#heading {\n\tfloat: left;\n}\n#menu {\n\tfloat: right;\n}\n#contents {\n\tclear: both;\n}\n</style>\n\t<title>List of Legislative Council Divisions - Victorian Parliament Tracker</title>\n</head>\n\n<body>\n<div id=\"heading\">\n\t<b style=\"font-size: large\">Victorian Parliament Tracker</b>\n</div>\n<div id=\"menu\">\n\t<a href=\"../../index.html\">Home</a>\n\t<a href=\"../../members.html\">People</a>\n\t<a href=\"../../about.html\">About</a>\n</div>\n<div id=\"contents\">\n\t<b>\n\t\tList of Legislative Council Divisions\n\t</b>", councilindex);


	char dates[argc][8];

	int highestsize = 0;
	int udpos = 0;
	int doc = 1;

	while (doc <= argc - 1) {
		char* output = makeText(argv[doc]);
		signed int size = getSize(output);
		if (size > highestsize)
			highestsize = size;
		doc++;
	}
	char arrayOfProceedings[argc-1][highestsize];
	int arrayOfSizes[argc-1];
	int arrayOfIsCouncil[argc-1];
	doc = 1;

	int isCouncil;
	while (doc <= argc - 1) {
		if (basename(argv[doc])[0] == 0x6D)
			isCouncil = 1;
		else
			isCouncil = 0;

		char* output = makeText(argv[doc]);
		signed int size = getSize(output);
		char proceedings[size];
		makeProceedings(output, size, proceedings);
		int i = 0;
		while (i <= size - 1) {
			arrayOfProceedings[doc-1][i] = proceedings[i];
			i++;
		}
		arrayOfSizes[doc-1] = size;
		arrayOfIsCouncil[doc-1] = isCouncil;

		int pos = 0;
		char * date;
		date = getYMDDate(&proceedings[size-1], isCouncil);

		while (pos <= 7) {
			dates[udpos][pos] = date[pos];
			pos++;
		}
		udpos++;
		doc++;
	}
	
	int pos = 0;
	char olddates[argc][8];
	while (pos <= argc - 1) {
		int ch = 0;
		while (ch <= 7) {
			olddates[pos][ch] = dates[pos][ch];
			ch++;
		}
		pos++;
	}

	int compare(const void *a, const void *b) {
		return strncmp((char *) a, (char *) b, 8);
	}
	qsort(dates, udpos, sizeof(dates[0]),compare);


	int * assemblyuseddates = calloc(20000, sizeof(int));
	int * counciluseddates = calloc(20000, sizeof(int));
	//int useddates[500] = {0};

	pos = 0;
	int olddatespos = 0;
	while (pos <= argc - 2) {
		while (olddatespos <= argc - 2) {
			if ((strncmp(dates[pos], olddates[olddatespos], 8) == 0) && (strncmp(dates[pos], dates[pos-1], 8) != 0)) {
				if (arrayOfIsCouncil[olddatespos] == 0) {
					printf("Processing: %s, %.*s, Assembly\n", argv[olddatespos+1], 8, dates[pos]);
					parse(assemblyindex, arrayOfSizes[olddatespos], arrayOfProceedings[olddatespos], arrayOfIsCouncil[olddatespos], assemblyuseddates);
				}
				else {
					printf("Processing: %s, %.*s, Council\n", argv[olddatespos+1], 8, dates[pos]);
					parse(councilindex, arrayOfSizes[olddatespos], arrayOfProceedings[olddatespos], arrayOfIsCouncil[olddatespos], counciluseddates);
				}
			}
			olddatespos++;
		}
		olddatespos = 0;
		pos++;
	}

	fputs("</body>\n</html>", assemblyindex);
	fputs("</body>\n</html>", councilindex);

	DIR *d;
	struct dirent *dir;
	data = 0;
	while (data <= 1) {
		if (data == 0)
			d = opendir("assembly/members");
		else
			d = opendir("council/members");
		while ((dir = readdir(d)) != NULL) {
			//Check if the file is actually a directory (we can't write a string to a directory!)
			if (!(opendir(dir->d_name))) {
				char * filename = calloc(200, sizeof(char));
				if (data == 0)
					sprintf(filename, "assembly/members/%s", dir->d_name);
				else
					sprintf(filename, "council/members/%s", dir->d_name);
				FILE *member;
				member = fopen(filename, "a");
				fputs("\n\t</ul>\n</div>\n</body>\n</html>", member);
			}
		}
		data++;
	}

	return 0;
}

