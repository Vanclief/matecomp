#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <set>

using namespace std;

bool ends_with(string const & value, string const & ending){
    if (ending.size() > value.size()) return false;
    return equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int main(int argc, char* argv[]){

	string p;
	set<char> alf;
	set<char>::iterator it;
	int m;
	int a;
	int k;

	cin >> p;
	
	m = p.length();

	for(int i = 0; i < m; i++){
		alf.insert(p[i]);
	}

	int delta[m][alf.size()];

	for(int i = 0; i < m; i++){
		for(int j = 0; j < alf.size(); j++){
			delta[i][j] = 0;
		}
	}

	cout << "delta = \n";
	for(int q = 0; q <= m; q++){
		a = 0;
		for (it = alf.begin(); it != alf.end(); it++){
			k = min(m+1,q+2);
			do{
				if(k > 0 && k <= m+1){
					k--;
				} else{
					break;
				}
				// cout << q << " " << *it << " - " << k << " - " << p[k] << " - " << p[q] << endl;
				// cout << *it << " - " << p[k-1] << " || " << p[k] << " - " << p[q] << endl;
			}while(*it != p[k-1]  || !ends_with(p.substr(0,k),(p.substr(0,q)+*it)));
			delta[q][a] = k; // No quiero que se quiebre cuando k = 3 en b
			cout <<  q << " - " << *it << " - " << k << endl;
			a++;
		}
	}

	return 0;
}