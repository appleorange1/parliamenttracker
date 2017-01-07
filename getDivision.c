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

//Returns 1 if no division found; returns 0 if a division is found.
//Returns 2 if end of file reached
#include "checkForMatch.c"
#include <string.h>
int getDivision(int tableOfAyes[1000], int tableOfNoes[1000], char (*politicians)[100], char* pointer, char *endOfFile, int requestedDiv, int isCouncil) {
	int loop = 0;
	int posi = 0;
	int divNum = 0;
	while (loop == 0) {
		//Searching for Ayes ("\n\nAyes " in Assembly; "  AYES," in Council)
		if ((isCouncil == 0 && *(pointer+posi) == 0x0a \
		  && *(pointer+1+posi) == 0x0a \
		  && *(pointer+2+posi) == 0x41 \
		  && *(pointer+3+posi) == 0x79 \
		  && *(pointer+4+posi) == 0x65 \
		  && *(pointer+5+posi) == 0x73 \
		  && *(pointer+6+posi) == 0x20) \
		  || (isCouncil == 1 && *(pointer+posi) == 0x20 \
		  && *(pointer+1+posi) == 0x20 \
		  && *(pointer+2+posi) == 0x41 \
		  && *(pointer+3+posi) == 0x59 \
		  && *(pointer+4+posi) == 0x45 \
		  && *(pointer+5+posi) == 0x53 \
		  && *(pointer+6+posi) == 0x2c)) {
			if (requestedDiv == divNum) {
				char* M = strstr(pointer, "M");
				char* D = strstr(pointer, "D");
				if (D == 0 || M < D)
					pointer = M;
				else
					pointer = D;
				char* startOfAyes = pointer;
				char* startOfNoes;
				char* endOfNoes;
				if (isCouncil == 0) {
					startOfNoes = strstr(pointer,"Noes");
					endOfNoes = strstr(startOfNoes,".\n\n");
				}
				else {
					startOfNoes = strstr(pointer,"NOES");
					endOfNoes = strstr(startOfNoes,")\n");
				}
				M = strstr(startOfNoes, "M");
				D = strstr(startOfNoes, "D");
				if (D == 0 || M < D)
					startOfNoes = strstr(startOfNoes, "M");
				else
					startOfNoes = strstr(startOfNoes, "D");

				int polipos = 1;
				int tableofayespos = 1;
				int tableofnoespos = 1;
				while (polipos <= 88) {
					//Find the length of each politician's surname
					int i = 0;
					int highestindex = 0;
					while (i <= 99) {
						if (politicians[polipos][i] != 0x00) {
							highestindex = i;
						}
						i++;
					}

					int matchFound;
					matchFound = checkForMatch(startOfAyes, startOfNoes, highestindex, politicians, polipos, tableOfAyes, tableofayespos);
					if (matchFound == 1) {
						tableofayespos++;
					}

					matchFound = checkForMatch(startOfNoes, endOfNoes, highestindex, politicians, polipos, tableOfNoes, tableofnoespos);
					if (matchFound == 1) {
						tableofnoespos++;
					}

					polipos++;
					pointer = startOfAyes;
				}

				loop = 1;
				return 0;
			}
			else {
				divNum++;
			}
		}

		//Searching for next section ("\n\n\t[0-9]" in Assembly,
		//"\n[0-9]" in Council, "*   *"  or ""-----\n\n\n"
		//in Council Committee)
		if((isCouncil == 0 && *(pointer+posi) == 0x0a && \
		   *(pointer+1+posi) == 0x0a && \
		   *(pointer+2+posi) == 0x09 && \
		   *(pointer+3+posi) >= 0x30 && \
		   *(pointer+3+posi) <= 0x39) || \
		   (isCouncil == 1 && *(pointer+posi) == 0x0a && \
		   *(pointer+1+posi) >= 0x30 && \
		   *(pointer+2+posi) <= 0x39) || \
		   (isCouncil == 1 && *(pointer+posi) == 0x2a && \
		   *(pointer+1+posi) == 0x20 && \
		   *(pointer+2+posi) == 0x20 && \
		   *(pointer+3+posi) == 0x20 && \
		   *(pointer+4+posi) == 0x2a) || \
		   (isCouncil == 1 && *(pointer+posi) == 0x2d && \
		   *(pointer+1+posi) == 0x2d && *(pointer+2+posi) == 0x2d && \
		   *(pointer+3+posi) == 0x2d && *(pointer+4+posi) == 0x2d && \
		   *(pointer+5+posi) == 0x2d && *(pointer+6+posi) == 0x0a && \
		   *(pointer+7+posi) == 0x0a && *(pointer+8+posi) == 0x0a)) {
			loop = 1;
			return 1;
		}

		//Searching for end of file
		if(pointer+posi > endOfFile) {
			loop = 1;
			return 2;
		}


		pointer++;
	}
}
