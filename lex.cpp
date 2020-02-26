#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

struct sym{
	string name;
};

struct lit{
    string name;
};

struct keyword{
	string name;
};

int s_ind = 0,k_ind = 0,l_ind = 0;
int lex_ind= 0;
struct sym s[10];
struct keyword k[30];
struct lit l[20];

bool check_lit(string& name){
    for(int i = 0 ; i < l_ind ; i++){
		if(name == l[i].name){
			return false;
		}
	}
	return true;
}

void put_lit(string& name){
    if(check_lit(name)){
        l[l_ind].name = name;
        l_ind++;
    }
}

void show_lit_tab(){
	cout << "INDEX" << "\t\t" << "NAME\n"; 
	for(int i = 0 ; i < l_ind ; i++){
		cout << i << "\t\t" << l[i].name << endl;
	}
}

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
    	put_key("printf");
    	put_key("scanf");
    	put_key("(");
    	put_key(")");
    	put_key("{");
    	put_key("}");
    	put_key(";");
    	put_key(",");
    	put_key("<");
    	put_key(">");
    	put_key("=");
    	put_key(">=");
    	put_key("<=");
    	put_key("==");
    	put_key("+");
    	put_key("-");
    	put_key("++");
    	put_key("--");
}

void show_key_tab(){
    cout << "INDEX" << "\t\t" << "NAME\n"; 
	for(int i = 0 ; i < k_ind ; i++){
		cout << i << "\t\t" << k[i].name << endl;
	}
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

int ret_index_sym(string a){
    for(int i = 0; i < s_ind ; i++){
		if(a == s[i].name){
			return i;
		}
	}
	return -1;
}

int ret_index_lit(string a){
    for(int i = 0; i < l_ind ; i++){
		if(a == l[i].name){
			return i;
		}
	}
	return -1;
}

int ret_index_key(string a){
    for(int i = 0; i < k_ind ; i++){
		if(a == k[i].name){
			return i;
		}
	}
	return -1;
}

void fill_tab(string& a){
	int i = 0;
	string b,c,d;
	if(a[0] == '#'){
		//cout << a << endl;
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
					d += a[i+1];
                    lex_ind = ret_index_key(d);
					f << lex_ind << "\t\t" << d  << "\t\t" << "TERMINAL" <<"\n";
					d.clear();
					i++;
				}else if(a[i] == '>' && (a[i+1] == '>' || a[i+1] == '=')){
					d += a[i+1];
                    lex_ind = ret_index_key(d);
					f << lex_ind << "\t\t" << d << "\t\t" << "TERMINAL" <<"\n";
					d.clear();
					i++;
				}else if(a[i] == '+' && (a[i+1] == '+' || a[i+1] == '=')){
					d += a[i+1];
                    lex_ind = ret_index_key(d);
					f << lex_ind << "\t\t" << d<< "\t\t" << "TERMINAL"  <<"\n";
					d.clear();
					i++;
				}else if(a[i] == '-' && (a[i+1] == '-' || a[i+1] == '=')){
					d += a[i+1];
                    lex_ind = ret_index_key(d);
					f << lex_ind << "\t\t" << d << "\t\t" << "TERMINAL" <<"\n";
					d.clear();
					i++;
				}
				if(b.size() != 0 ){
					if(isKeyword(b)){
                        lex_ind = ret_index_key(b);
                        f <<  lex_ind << "\t\t" << b << "\t\t";
						f << "KEYWORD" << "\n";
					}else{
                        put_sym(b);
                        lex_ind = ret_index_sym(b);
                        f <<  lex_ind << "\t\t" << b << "\t\t";
						f << "SYMBOL"<<"\n";
					}
					b.clear();
				}
				if(a[i] == ',' || a[i] == ';'){
					//d += a[i];
                    lex_ind = ret_index_key(d);
					f << lex_ind << "\t\t" << d << "\t\t" << "TERMINAL" <<"\n";
					d.clear();
					//i++;
                }
                if(a[i] == '(' && a[i+1] == '"'){
					size_t found = a.find('"',i+2);
                    lex_ind = ret_index_key(d);
                    f << lex_ind << "\t\t" << d << "\t\tTERMINAL" <<"\n";
					d.clear();
                    if(found != string::npos){
                        string temp = a.substr(i+2,found-i-2);
                        put_lit(temp);
                        lex_ind = ret_index_lit(temp);
                        f << lex_ind << "\t\t" << temp << "\t\tLITERAL" << "\n";
                        i = found;
                    }
				}
				if(d.size() != 0){
                    lex_ind = ret_index_key(d);
					f << lex_ind << "\t\t" << d << "\t\tTERMINAL" <<"\n";
					d.clear();
				}
				
			}
	}
	if(b.size() != 0){
       
		if(isKeyword(b)){
            lex_ind = ret_index_key(b);
		    f << lex_ind << "\t\t" << b <<"\t\t" ;
			f << "KEYWORD" << "\n";
		}else{
            put_sym(b);
            lex_ind = ret_index_sym(b);
		    f << lex_ind << "\t\t" << b <<"\t\t" ;
			f << "SYMBOL"<<"\n";
		}
	}
	f.close(); 
}


int main(){
	ifstream f("input.c");
	string a;
	put_keywords();
	make_lex_file();
	if(f.is_open()){
		while(getline(f,a)){
           		 fill_tab(a);
		}
	}
    	cout << "**SYMBOL TABLE**\n";
	show_sym_tab();
    	cout << "\n**LITERAL TABLE**\n";
    	show_lit_tab();
    	cout << "\n**KEYWORD TABLE**\n";
    	show_key_tab();
	f.close();
	return 0;
}
