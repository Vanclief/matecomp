//Se asume que la gramatica se encuentra en el archivo "G.in"
//De la forma:
//S > A AA        S Simbolo Inicial
//A > a B
//B > b
// ...

//Erick Ibarra
//Franco Valencia
//Gerardo Garcia
//Andree Toledo

#include <fstream>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <set>

using namespace std;

map<string, set<string> > map_no_terminal;
map<string, set<string> > map_terminal;
vector<vector<set<string> > > dp;

string S;
set<string> cadenas;

void read_strings(string filename);
void read_productions(string filename);
void print_glc();
void init_dp(string s);
bool CYK(int n);
void print_dp(int n);

int main(int argc, char* argv[]){
  int n;

  read_productions("G.in");
  read_strings("W.in");
  print_glc();


  for (set<string>::iterator it_cadenas = cadenas.begin(); it_cadenas != cadenas.end(); it_cadenas++) {
    n = (*it_cadenas).size();
    init_dp(*it_cadenas);
    cout << "\nCadena: " << *it_cadenas << " - ";
    if(CYK(n)){
      cout << "Aceptada\n";
    } else {
      cout << "No Aceptada\n";
    }
    print_dp(n);
  }
  
  return 0;
}


void read_productions(string filename){
  ifstream g_file(filename);
  string line, production;
  int i = 0;
  while (getline(g_file, line) && line.size()) {
    stringstream sstream(line);
    string no_terminal;
    sstream >> no_terminal;
    if (i++ == 0){
      S = no_terminal;
    } 
    while (sstream >> production) {
      if(production != ">"){
        map_no_terminal[no_terminal].insert(production);
        map_terminal[production].insert(no_terminal);    
      }
    }
  }
}

void print_glc(){
  int i;
  cout << "Producciones GLC(G.in):\n";
  for (map<string, set<string> >::iterator it_no_terminal = map_no_terminal.begin(); it_no_terminal != map_no_terminal.end(); it_no_terminal++) {
    cout << "\t" << it_no_terminal->first << " -> ";
    i = 0;
    for (set<string>::iterator it_prod = (it_no_terminal->second).begin(); it_prod != (it_no_terminal->second).end(); it_prod++) {
      if (i != 0){
        cout << " | ";
      } 
      cout << *it_prod;
      i++;
    }
    cout << "\n";
  }
}
void read_strings(string filename){
  ifstream g_file(filename);
  string line, cadena;
  int i = 0;
  cout << "Leyendo cadenas (W.in):\n";
  while (getline(g_file, line) && line.size()) {
    stringstream sstream(line);
    while (sstream >> cadena) {
      cout << "\t" << cadena << "\n";
      cadenas.insert(cadena);
    }
    i++;
  }  
}

void init_dp(string s){
  int n = s.size();
  dp = vector<vector<set<string> > >(n, vector<set<string> >(n, set<string>()));
  for(int i = 0; i < n; i++) {
    string query(1, s[i]);
    set<string> prod = map_terminal[query];
    for (set<string>::iterator it = prod.begin(); it != prod.end(); it++) {
      dp[i][i].insert(*it);
    }
  }
}


bool CYK(int n){
  string concat;
  bool valid = false;

  for (int i = 1; i < n; i++) {
    for (int j = i-1; j >= 0; j--) {
      for (int k = j; k < i; k++) {
        set<string> a = dp[j][k];
        set<string> b = dp[k+1][i];
        if (a.size() == 0 || b.size() == 0) continue;

        for (set<string>::iterator p = a.begin(); p != a.end(); p++) {
          for (set<string>::iterator q = b.begin(); q != b.end(); q++) {
            concat = *p + *q;

            set<string> res = map_terminal[concat];
            for (set<string>::iterator it = res.begin(); it != res.end(); it++) {
              dp[j][i].insert(*it);
            }
          }
        }

      }
    }
  }

  for (set<string>::iterator it = dp[0][n-1].begin(); it != dp[0][n-1].end(); it++) {
    valid = *it == S; 
    if(valid){
      break;
    }
  }

  return valid;
}


void print_dp(int n){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++){
      for (set<string>::iterator it = dp[i][j].begin(); it != dp[i][j].end(); it++) {
        cout << *it;
      }
      cout << "\t";
    }
    cout << "\n";
  }
}