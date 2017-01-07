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

char politicians[89][100] = {"INTENTIONALLY EMPTY","Allan","Andrews","Angus","Asher","Battin", \
			"Blackwood","Blandthorn","Britnell","Brooks", \
			"Bull (Sunbury)","Bull (Gippsland East)", \
			"Burgess","Carbines","Carroll","Clark", \
			"Couzens","Crisp","D'Ambrosio","Dimopoulos", \
			"Dixon","Donnellan","Edbrooke","Edwards", \
			"Eren","Foley","Fyffe","Garrett","Gidley", \
			"Graley","Green","Guy","Halfpenny","Hennessy", \
			"Hibbins","Hodgett","Howard","Hutchins","Kairouz", \
			"Katos","Kealy","Kilkenny","Knight","Languiller", \
			"Lim","McCurdy","McGuire","McLeish","Merlino", \
			"Morris","Nardella","Neville","Noonan","Northe", \
			"O'Brien (Gippsland South)","O'Brien (Malvern)", \
			"Pakula","Pallas","Paynter","Pearson","Perera", \
			"Pesutto","Richardson (Northcote)", \
			"Richardson (Mordialloc)","Riordan","Ryall","Ryan", \
			"Sandell","Scott","Sheed","Smith (Warrandyte)", \
			"Smith (Kew)","Southwick","Spence","Staikos", \
			"Staley","Suleyman","Thomas","Thompson","Thomson", \
			"Tilley","Victoria","Wakeling","Walsh","Ward","Watt", \
			"Wells","Williams","Wynne"};

// Greens = 1
// Labor = 2
// Liberal = 3
// Nationals = 4
// Sheed = 5
int parties[89] = {0,2,2,3,3,3,3,2,3,2,2,4,3,2,2,3,2,4,2,2,3,2,2,2,2,2,3,2,3,2, \
		   2,3,2,2,1,3,2,2,2,3,4,2,2,2,2,4,2,3,2,3,2,2,2,4,4,3,2,2,3, \
		   2,2,3,2,2,3,3,4,1,2,5,3,3,3,2,2,3,2,2,3,2,3,3,3,4,2,3,3,2, \
		   2};

char partynames[6][100] = {"INTENTIONALLY EMPTY", "Greens", "Labor", "Liberal", "Nationals", "Suzanna Sheed"};

char colors[6][100] = {"INTENTIONALLY EMPTY","limegreen","red","blue","darkgreen","gray"};
