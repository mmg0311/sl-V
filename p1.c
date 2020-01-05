#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

struct sym_tab{
	char sym[10];
	int addr;
	int length;
};

struct mnemonic_table{
	char mnemonic_name[10];
	int opcode;
	char type[3];
	int no_of_op;
};

struct lit_tab{
	char lit[10];
	int addr;
};

struct sym_tab s[20];
struct mnemonic_table m[20];
struct lit_tab	l[20];
int sym_index=0,lc=0,lit_index=0,last_ltorg=0;
bool LTORG=false;

int length(char * s1){
	int i=0;
	while(s1[i]!='\0'){
		i++;
	}
	return i;
}

bool compare(char *s1,char *s2){
	int l1 = length(s1);
	int l2 = length(s2);
	int i=0;
	if(l1 == l2){
		for(i=0;i<l1;i++){
			if(s1[i] != s2[i]){
				return false;
			}
		}
	}
	else{
		return false;
	}
	return true;
}

bool checkForSym(char sy[10]){
	int i=0;
	bool x = compare(sy,"AREG") || compare(sy,"BREG") || compare(sy,"CREG") || compare(sy,"DREG");
	if(sy[0] == '='){
		return true;
	}
	for(i = 0; i < sym_index ; i++){
		if(compare(sy,s[i].sym) || x){	//if already present
			return true;
		}
	}
	return false;
}

void insert_into_sym_tab(char sy[10],int ad,int len){
	strcpy(s[sym_index].sym,sy);
	s[sym_index].addr = ad;
	s[sym_index].length = len;
	sym_index++;
}

void display_sym_tab(){
	int i;
	printf("\t\t\tSYMBOL TABLE\n");
	printf("===============================================================\n");
	printf("\tINDEX\t\tSYMBOL\t\tADDRESS\t\tLENGTH\n");
	printf("===============================================================\n");
	for(i = 0; i < sym_index ; i++ ){
		printf("\t%d\t\t%s\t\t%d\t\t%d\n",i,s[i].sym,s[i].addr,s[i].length);
	}
	printf("===============================================================\n\n");
}

void update_in_sym_tab(char sy[10],int ad,int len){	//when variable gets declared
	int i;
	for(i = 0; i < sym_index ; i++){
		if(compare(sy,s[i].sym)){	//if already present
			s[i].addr = ad;
			s[i].length = len;
			break;
		}
	}
}

void update_in_sym_tab_all(){
	int i;
	for(i = 0; i < sym_index ; i++){
		if(s[i].addr == -1){	
			s[i].addr = lc++;
		}
	}
}

void insert(int ind,char mn[10],int op,char type[3],int no){
	strcpy(m[ind].mnemonic_name,mn);
	m[ind].opcode = op;
	strcpy(m[ind].type,type);
	m[ind].no_of_op = no;
}

bool isLiteral(char li[10]){
	if(li[0] != '='){
		return false;
	}
	return true;
}

void insert_into_literal_tab(char li[10],int add){
	//if ltorg then don't see the above entries
	int i,ck=0;
	if(LTORG){
		LTORG = false;
		strcpy(l[lit_index].lit,li);
		l[lit_index].addr = add;
		last_ltorg = lit_index;
		lit_index++;
	}else{
		for(i = last_ltorg ; i < lit_index ; i++){
			if(compare(l[i].lit,li)){
				ck++;
				break;
			}
		}
		if(ck == 0){
			//then insert
			strcpy(l[lit_index].lit,li);
			l[lit_index].addr = add;
			lit_index++;
		}
	}
}

void update_lit_tab(){
	int i;
	for( i = last_ltorg ; i < lit_index ; i++){
		l[i].addr = lc++;
	}
}

void show_lit_tab(){
	int i;
	printf("\t\t\tLITERAL TABLE\n");
	printf("===============================================================\n");
	printf("\tINDEX\t\tLITERAL\t\tADDRESS\n");
	printf("===============================================================\n");
	for(i = 0; i < lit_index ; i++ ){
		printf("\t%d\t\t%s\t\t%d\n",i,l[i].lit,l[i].addr);
	}
	printf("===============================================================\n");
}

void create_mnemonic_tab(){
	//ASSEMBLER DIRECTIVES
	insert(0,"START",01,"AD",1);
	insert(1,"END",20,"AD",0);
	insert(2,"ORIGIN",03,"AD",1);
	insert(3,"EQU",04,"AD",2);
	insert(4,"LTORG",05,"AD",0);

	//IMPERATIVE STATEMENTS
	insert(5,"STOP",00,"IS",0);
	insert(6,"ADD",01,"IS",2);
	insert(7,"SUB",02,"IS",2);
	insert(8,"MULT",03,"IS",2);
	insert(9,"MOVER",04,"IS",2);
	insert(10,"MOVEM",05,"IS",2);
	insert(11,"COMP",06,"IS",2);
	insert(12,"BC",07,"IS",2);
	insert(13,"DIV",8,"IS",2);
	insert(14,"READ",9,"IS",1);
	insert(15,"PRINT",10,"IS",1);
	
	//DECLARATIVE STATEMENTS
	insert(16,"DC",01,"DS",1);
	insert(17,"DS",02,"DS",1);
}

bool validate(char c[20],char d[20],char e[20],int ct){
	int i=0,ck=0,n=0,h=0,j=0,k=0;
	char op1[10]={'\0'},op2[10]={'\0'};
	//FILE *fout = fopen("");
	if(c[0] != '*'){
		//either there will be label or mnemonic
		for(i = 0; i < 18 ; i++){
			if(compare(m[i].mnemonic_name,c)){
				ck++;
				break;
			}
		}
		if(ck != 0){
			//mnemonic present
			strcpy(e,d);
			strcpy(d,c);
		}
		else {
			//label is present
			//put it in symbol table
			ck = 0;
			if(!checkForSym(c)){
				insert_into_sym_tab(c,lc,1);
			}
		}
	}
	if(ck == 0){
		for(i = 0; i < 18 ; i++){
			if(compare(m[i].mnemonic_name,d)){
				ck++;
				break;
			}
		}
	}
	if(ck == 0){		//weather mnemonic is persent or not
		return true;
	}
	//check for operands
	n = m[i].no_of_op;
	//index will be stored in j
	j = i;
	if(j == 16 || j == 17){	//declarative statements
		if(!checkForSym(c)){
				insert_into_sym_tab(c,lc,1);
			}
		else{
			update_in_sym_tab(c,lc,1);
		}
		lc++;
		return false;
	}
	if(j>=0 && j<5){//ASSEMBLER DERECTIVES
		if(j==4){
			update_lit_tab();
			LTORG = true;
		}
	}
	if(j>=5 && j<16){//IMPERATIVE STATEMENTS
		lc++;
	}
	//NO OPERAND
	if(n == 0){
		i = 0;
		// if( e[i] != '\0'){
		// 	printf("%s must have no operand\n",d);
		// 	return true;
		// }
		if( j == 1){
			update_in_sym_tab_all();	//after the end 
			update_lit_tab();
			//will update all default addresses the variable is been assigned
		}
	}
	//ONLY ONE OPERAND
	else if(n == 1){
		i=0;
		while(e[i++] != '\0'){
			if(j == 0){
				//START
				if(e[i] >= 65 && e[i] <= 90){
					printf("%s must have operand as constant\n",d);
					return true;
				}
			}
			else{
				if(e[i] == ',' || (e[i] >= 49 && e[i] <= 57)){
					printf("%s must have only one operand and must not be a constant\n",d);
					return true;
				}
			}
		}
		if(j==0){
			lc = atoi(e);
		}
		else{
			if(!checkForSym(e)){
				insert_into_sym_tab(e,-1,1);
			}
		}
		
	}
	//TWO OPERANDS
	else if(n == 2){
		i=0;
		h=0;
		k=0;
		while(e[i] != '\0'){
			if(e[i] == ','){
				h++;
			}
			if(h==0){
				op1[i] = e[i];
			}
			else if(h == 1 && e[i]!=','){
				op2[k++] = e[i];
			}
			i++;
		}
		if(h != 1){
			printf("%s must have two operands\n",d);	
			return true;		
		}
		if(!checkForSym(op1)){
			insert_into_sym_tab(op1,-1,1);
		}else if(isLiteral(op1)){
			insert_into_literal_tab(op1,-1);
		}else {
			// printf("it is a register");
		}
		if(!checkForSym(op2)){
			insert_into_sym_tab(op2,-1,1);
		}else if(isLiteral(op2)){
			insert_into_literal_tab(op2,-1);
		}else {
			// printf("it is a register");
		}
	}
	if(ck == 0){
		return true;
	}
	return false;
}

void main(){
	FILE * f;
	int count=0,i=0;
	create_mnemonic_tab();
	char c[20] = {'\0'};
	char d[20] = {'\0'};
	char e[20] = {'\0'};
	char temp[20] = {'\0'};
	f = fopen("low_level","r");
	if(f == NULL){
		printf("file doesn't exists");
		return ;
	}
	while(fscanf(f,"%s\t%s\t%s",c,d,e)!= EOF){
		count++;
		if(validate(c,d,e,count)){
			i++;
			printf("Error in line number %d\n",count);
			break;
		}
		strcpy(c,temp);
		strcpy(d,temp);
		strcpy(e,temp);
		if(count == 1 && lc == 0){
			//i.e first line has been executed
			//there is no start at the begining
			printf("LOCATION COUNTER NOT DEFINED\n");
			i++;
			break;
		}
	}
	if(i == 0){
		display_sym_tab();
		show_lit_tab();
		printf("****COMPILED SUCCESSFULLY****\n");
	}
	
}
