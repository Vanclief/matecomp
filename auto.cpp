#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <set>

using namespace std;

//Comprueba si una string termina con otra
bool suffix(string const & value, string const & ending){
    if (ending.size() > value.size()) return false;
    return equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int main(int argc, char* argv[]){
	//Declarar alfabeto como set, para no repetir y su iterador
	set<char> alfabeto;
	set<char>::iterator it;
	int m, a, k;
	string p;

	cout << "Introduce la palabra P: ";
	cin >> p;
	
	m = p.length();

	for(int i = 0; i < m; i++){
		alfabeto.insert(p[i]);
	}

	int delta[m][alfabeto.size()];

	for(int i = 0; i < m; i++){
		for(int j = 0; j < alfabeto.size(); j++){
			delta[i][j] = 0;
		}
	}

	cout << "delta = \n";
	//Para cada estado posible
	for(int q = 0; q <= m; q++){
		//Identificador de la letra del alfabeto
		a = 0;
		//Para cada letra en el alfabeto
		for (it = alfabeto.begin(); it != alfabeto.end(); it++){
			//Minimo entre el tamano de la palabra o el estado mas 2
			k = min(m+1,q+2);
			do{
				if(k > 0 && k <= m+1){
					//Si k es valida restar 1, siempre inicialmente
					k--;
				} else{
					break;
				}
			//Mientra la palabraQ formada hasta el estado actual mas la posible entrada no coinida con la palabraK hasta el momento
			}while(!suffix(p.substr(0,k),(p.substr(0,q)+*it)));
			//Almacenar la trancision si se recibe a, en el estado q
			delta[q][a] = k; 
			//Imprimir trancisiones
			cout <<  q << " - " << *it << " - " << k << endl;
			a++;
		}
	}

	return 0;
}