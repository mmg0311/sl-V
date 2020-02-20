#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;

struct sym{
	string name;
};

struct lit{
	int add;
};

struct keyword{
	string name;
};

int s_ind = 0,k_ind = 0;
int lex_ind= 0;
struct sym s[10];
struct keyword k[20];


void make_lex_file(){
	ofstream f("lex.txt");
	f << "INDEX\t\tLEXEME\t\tTYPE\n";
	f.close();
}

void put_key(string key){
	k[k_ind].name = key;
	k_ind++; 
}

void put_keywords(){
	put_key("int");
	put_key("void");
	put_key("cin");
	put_key("cout");
	put_key("return");
	put_key("if");
	put_key("else");
}

bool check_sym( string& a){
	for(int i = 0 ; i < s_ind ; i++){
		if(a == s[i].name){
			return false;
		}
	}
	return true;
}

void put_sym(string& a){
	if(check_sym(a)){
		s[s_ind].name = a;
		s_ind++;
	}
}

void show_sym_tab(){
	cout << "INDEX" << "\t\t" << "NAME\n"; 
	for(int i = 0 ; i < s_ind ; i++){
		cout << i << "\t\t" << s[i].name << endl;
	}
}

bool isKeyword(string& a){
	for(int i = 0; i < k_ind ; i++){
		if(a == k[i].name){
			return true;
		}
	}
	return false;
}

void fill_tab(string& a){
	int i = 0;
	string b,c,d;
	if(a[0] == '"' || a[0] == '#'){
		cout << a << endl;
		return;
	}
	ofstream f("lex.txt",ios::app);
	for(i = 0 ; i < a.size() ; i++ ){
			if(isalpha(a[i]) > 0){
				//ALPHABET a[i] >= 65 && a[i] <= 90
				//cout << "ALPHABET " << a[i] << endl;
				b += a[i];	
			}else if(a[i]>= 48 && a[i] <= 57){
				//DIGIT
			//	cout << "DIGIT " << a[i] << endl;
				if(b.size() != 0){
					f <<  lex_ind << "\t\t" << b << "\t\t" << "" << "\n";
					lex_ind++;
					b.clear();
				}
			}else{
				//SPECIAL CHARACTER
				//cout << "SPECIAL CHARACTER  " << a[i] << endl;
				d += a[i];
				if(a[i] == ' ' || a[i] == '\t'){
					d.clear();
				}
				if(a[i] == '<' && (a[i+1] == '<' || a[i+1] == '=')){
					d += a[i];
					f << lex_ind << "\t\t" << d  << "\t\t" << "OPERATOR" <<"\n";
					lex_ind++;
					d.clear();
					i++;
				}else if(a[i] == '>' && (a[i+1] == '>' || a[i+1] == '=')){
					d += a[i];
					f << lex_ind << "\t\t" << d << "\t\t" << "OPERATOR" <<"\n";
					lex_ind++;
					d.clear();
					i++;
				}else if(a[i] == '+' && (a[i+1] == '+' || a[i+1] == '=')){
					d += a[i];
					f << lex_ind << "\t\t" << d<< "\t\t" << "OPERATOR"  <<"\n";
					lex_ind++;
					d.clear();
					i++;
				}else if(a[i] == '-' && (a[i+1] == '-' || a[i+1] == '=')){
					d += a[i];
					f << lex_ind << "\t\t" << d << "\t\t" << "OPERATOR" <<"\n";
					d.clear();
					lex_ind++;
					i++;
				}
				if(b.size() != 0 ){
					f <<  lex_ind << "\t\t" << b << "\t\t";
					if(isKeyword(b)){
						f << "KEYWORD" << "\n";
					}else{
						f << "SYMBOL"<<"\n";
						put_sym(b);
					}
					lex_ind++;
					b.clear();
				}
				if(a[i] == ',' || a[i] == ';'){
					//d += a[i];
					f << lex_ind << "\t\t" << d << "\t\t" << "SEPERATOR" <<"\n";
					d.clear();
					lex_ind++;
					//i++;
				}
			//	cout << d << endl;
				if(d.size() != 0){
					f << lex_ind << "\t\t" << d << "\t\tOPERATOR" <<"\n";
					d.clear();
					lex_ind++;
				}
				
			}
	}
	if(b.size() != 0){
		f << lex_ind << "\t\t" << b <<"\t\t" ;
		if(isKeyword(b)){
			f << "KEYWORD" << "\n";
		}else{
			f << "SYMBOL"<<"\n";
			put_sym(b);
		}
		lex_ind++;
	}
	
	f.close(); 
	//cout << endl;
}


int main(){
	ifstream f("input.c");
	string a;
	//for tokenizing
	vector<string> tokens;
	string intermediate;
	put_keywords();
	make_lex_file();
	if(f.is_open()){
		while(getline(f,a)){
			stringstream check1(a);
			while(getline(check1,intermediate,' ')){
				//tokens.push_back(intermediate);
				//cout << intermediate << " => ";
				if(intermediate[0] == '"'){
					/*string b = intermediate;
					while(getline(check1,intermediate,' ')){
						if(intermediate[0] == '"'){
						cout << b << endl;
							break;
						}
						b += ' ';
						b += intermediate;
					}*/
					size_t found = a.find('"');
					if(found != string::npos){
					cout << a << "->" ;
						cout << found << "->";
						cout << a.substr(0,found) << endl;
					}
					//fill_tab(b);
				}else{
					//fill_tab(intermediate);
				}
				//cout << endl;
			}
		}
	}
	//show_sym_tab();
	f.close();
	return 0;
}
