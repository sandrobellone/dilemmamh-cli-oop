    // dilemmamh.c - versione 0.03

    // Copyright 2015 2017 Sandro Bellone

    // This program is free software: you can redistribute it and/or modify
    // it under the terms of the GNU General Public License as published by
    // the Free Software Foundation, either version 3 of the License, or
    // (at your option) any later version.

    // This program is distributed in the hope that it will be useful,
    // but WITHOUT ANY WARRANTY; without even the implied warranty of
    // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    // GNU General Public License for more details.

    // You should have received a copy of the GNU General Public License
    // along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include<iostream>
#include<random>
#include<unistd.h> // per getopt()

using namespace std;

class dmh {
public:
	void elabora(int nite, char t, int *i, int *numero_successi, int *numero_scambi,
        int *numero_successi_con_scambio, int *numero_successi_senza_scambio);
   	static void guida();
    dmh();
private:
	int scelta (int);
	static int terza_scelta(int,int);
	int escludi_vera(int,int);
    std::random_device random_device;
    std::mt19937 random_engine{random_device()};
    std::uniform_int_distribution<int> die_distribution{0, 9999};
};

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
            case 'h': dmh::guida();        return 0;
            default :
              cout << "opzione sconosciuta!" <<endl;
              dmh::guida(); return -1;
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

void dmh::guida() {
	cout << "Software di simulazione del dilemma di Monty Hall\n"
						"Sandro Bellone\nGennaio 2017\n\n"
						"Copyright 2015 2017 Sandro Bellone\n"
						"GNU General Public License vers. 3\n\n"
						"Utilizzo: dilemmamh-cli [-n <numero iterazioni>] [-t <tipo scelta>]\n"
						"Guida:    dilemmamh-cli -h\n"
						"Con <numero iterazioni>=1000 valore di default\n"
						"<tipo scelta>: r: scelta randomica (default)   s: accettata sempre\n"
						"               m: accettata mai                a: accettata in modo alternato\n";
}

void dmh::elabora(int nite, char t, int *i, int *numero_successi, int *numero_scambi, int *numero_successi_con_scambio,
        int *numero_successi_senza_scambio){
    int x, y, z, c, ii;
    for (*i=0; *i<nite; (*i)++) {
        x=scelta(3);		// ok
        y=scelta(3);		// tentativo
        z=escludi_vera(x,y);
        if(t=='r') {
            if(scelta(2)) c=y;
            else c=terza_scelta(y,z);
        } else if(t=='s') c=y;
        else if (t=='m') c=terza_scelta(y,z);
        else if (t=='a') {
            if (*i%2) c=y;
            else c=terza_scelta(y,z);
        }
        if (x==c) {
            (*numero_successi)++;
            if(y!=c) {
                (*numero_successi_con_scambio)++;
            } else (*numero_successi_senza_scambio)++;
        }
        if (y!=c) (*numero_scambi)++;
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
}
