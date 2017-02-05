/*!  dilemmamh.c - versione 0.01
 *
 *   Copyright 2015 2017 Sandro Bellone
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

#include<iostream>
#include<unistd.h> // per getopt()
#include"dmh.h"

using namespace std;

int main(int argc, char *argv[]){
	int n=1000;	// numero di iterazioni
	char t='r';  // tipo di scelta
	int numero_successi=0, numero_scambi=0, numero_successi_con_scambio=0,
        numero_successi_senza_scambio=0, i=0;
	int opt_char;
	while ((opt_char=getopt(argc, argv, "n:t:h"))!=-1)
        switch(opt_char){
            case 'n': n=atoi(optarg); break;
            case 't': t=optarg[0];    break;
            case 'h': cout << dmh::guida();        return 0;
            default :
              cout << "opzione sconosciuta!" <<endl;
              cout << (dmh::guida()); return -1;
        }
    cout << "Numero iterazioni: " << n << endl;
    cout << "Tipo di scelta: " << t<<' ';
    switch(t) {
        case 'r': cout << "(scelta  randomica)" << endl; break;
        case 's': cout << "(scelta sempre accettata)" <<endl; break;
        case 'm': cout << "(scelta mai accettata)" << endl; break;
        case 'a': cout << "(scelta accettata alternativamente)" << endl; break;
        default: cout << "(tipo di scelta non prevista)" << endl; return -1;}
    dmh dmhObj;
    dmhObj.elabora(n,t, &i, &numero_successi, &numero_scambi, &numero_successi_con_scambio,
        &numero_successi_senza_scambio);
	cout << "Iterazioni: "<< i << "; scambi: "<< numero_scambi << "; successi: "<< numero_successi << endl;
    cout << "di cui con scambio: " << numero_successi_con_scambio << "; senza scambio: "<< numero_successi_senza_scambio << endl;
	return 0;
}
