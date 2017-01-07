//Returns 1 if match found, returns 0 if no match found
int checkForMatch(char* start, char* end, int highestindex, char (*politiciansarray)[100], int polipos, int resulttable[1000], int resultpos) {
	int d = 0;
	while(start < end && d <= highestindex) {
		if (*(start+d) == politiciansarray[polipos][d]) {
	       		d++;
                }
                else {
              		start++;
              		d = 0;
                }
	}
	if (start < end) {
        	resulttable[resultpos] = polipos;
		return 1;
        }
	return 0;
}

