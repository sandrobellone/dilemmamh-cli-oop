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
    dmhObj.elabora(n,t);
	cout << "Iterazioni: "<< dmhObj.get_i() << "; scambi: "<< dmhObj.get_nsc()
        << "; successi: "<< dmhObj.get_nsu()  << endl;
    cout << "di cui con scambio: " << dmhObj.get_nsucs()
        << "; senza scambio: "<< dmhObj.get_nsuss() << endl;
	return 0;
}
