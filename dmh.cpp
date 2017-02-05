/*!  dmh.cpp - versione 0.01
 *
 *   Copyright 2017 Sandro Bellone
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include<random>
#include"dmh.h"

string dmh::guida() {
	return "Software di simulazione del dilemma di Monty Hall\n"
			"Sandro Bellone\nGennaio 2017\n\n"
			"Copyright 2015 2017 Sandro Bellone\n"
            "GNU General Public License vers. 3\n\n"
            "Utilizzo: dilemmamh-cli [-n <numero iterazioni>] [-t <tipo scelta>]\n"
            "Guida:    dilemmamh-cli -h\n"
            "Con <numero iterazioni>=1000 valore di default\n"
            "<tipo scelta>: r: scelta randomica (default)   s: accettata sempre\n"
            "               m: accettata mai                a: accettata in modo alternato\n";
}

void dmh::elabora(int nite, char t){
    int x, y, z, c;
    for (i=0; i<nite; i++) {
        x=scelta(3);		// ok
        y=scelta(3);		// tentativo
        z=escludi_vera(x,y);
        if(t=='r') {
            if(scelta(2)) c=y;
            else c=terza_scelta(y,z);
        } else if(t=='s') c=y;
        else if (t=='m') c=terza_scelta(y,z);
        else if (t=='a') {
            if (i%2) c=y;
            else c=terza_scelta(y,z);
        }
        if (x==c) {
            numero_successi++;
            if(y!=c) {
                numero_successi_con_scambio++;
            } else numero_successi_senza_scambio++;
        }
        if (y!=c) numero_scambi++;
    }
}

int dmh::scelta(int i) {				// ritorna un numero intero casuale da 0 a i
    int die_roll = die_distribution(random_engine);
	return die_roll%i;
}

int dmh::terza_scelta(int x, int y) { // dati due numeri differenti da 1 a 3, ritorna il terzo
	if((x+y)==1) return 2;
	if((x+y)==2) return 1;
	return 0;
}

int dmh::escludi_vera(int x, int y) {			// sceglie un numero sbagliato
	int k;
	if (x==y) {
		k=scelta(2);
		if (x==0) return k+1;	// x==0; y==0;
		if (x==1) return k*2;	// x==1; y==1;
		else return k;			// x==2; y==2;
	}
	return terza_scelta(x,y);
}

dmh::dmh() {
    this->numero_scambi=0;
    this->numero_successi=0;
    this->numero_successi_con_scambio=0;
    this->numero_successi_senza_scambio=0;
}

int dmh::get_nsc() { return this->numero_scambi;}
int dmh::get_nsu() { return this->numero_successi;}
int dmh::get_nsucs() { return this->numero_successi_con_scambio; }
int dmh::get_nsuss() { return this->numero_successi_senza_scambio; }
int dmh::get_i() { return this->i; }
