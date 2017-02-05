/*!  dmh.h - versione 0.01
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
using namespace std;

class dmh {
public:
	void elabora(int nite, char t);
   	static string guida();
   	int get_nsu();
   	int get_nsc();
   	int get_nsucs();
   	int get_nsuss();
   	int get_i();
    dmh();
private:
	int scelta (int);
	static int terza_scelta(int,int);
	int escludi_vera(int,int);
    std::random_device random_device;
    std::mt19937 random_engine{random_device()};
    std::uniform_int_distribution<int> die_distribution{0, 9999};
	int numero_successi, numero_scambi, numero_successi_con_scambio,
        numero_successi_senza_scambio, i;
};
