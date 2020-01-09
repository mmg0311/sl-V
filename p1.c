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
int pool_tab[10]={-1},size_of_pool=0;
bool LTORG=true;

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

int checkForSym(char sy[10]){
	int i=0;
	bool x = compare(sy,"AREG") ;
	bool y = compare(sy,"BREG") ;
	bool z = compare(sy,"CREG") ;
	bool w = compare(sy,"DREG");
	if( x || y || z || w){
		return -1;
	}
	if(sy[0] == '='){
		return -1;
	}
	for(i = 0; i < sym_index ; i++){
		if(compare(sy,s[i].sym) ){	//if already present
			return 1;
		}
	}
	return 0;
}

void insert_into_sym_tab(char sy[10],int ad,int len){
	int i;
	for(i=0;i<sym_index;i++){
		if(compare(sy,s[i].sym)){
			s[i].addr = ad;
			s[i].length = len;
			return;
		}
	}
	strcpy(s[sym_index].sym,sy);
	s[sym_index].addr = ad;
	s[sym_index].length = len;
	sym_index++;
}

int get_sym_index(char sy[10]){
	int i;
	for(i=0;i<sym_index;i++){
		if(compare(sy,s[i].sym)){
			return i;
		}
	}
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

bool if_undec(){
	int i;
	for(i = 0; i < sym_index ; i++){
		if(s[i].addr == -1){	
		printf("%s ",s[i].sym);
			return true;
		}
	}
	return false;
}

int get_addr_of_sym(char sy[10]){
	int i;
	for(i = 0; i < sym_index ; i++){
		if(compare(sy,s[i].sym)){	//if already present
			return s[i].addr;
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
		pool_tab[size_of_pool++] = last_ltorg;
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
	printf("===============================================================\n\n");
}

void show_pool_tab(){
	int i;
	printf("\t\tPOOL TABLE\n");
	printf("===============================\n");
	printf("\tINDEX\n");
	printf("===============================\n");
	for(i = 0; i < size_of_pool ; i++ ){
		printf("\t%d\n",pool_tab[i]);
	}
	printf("================================\n");
}

void create_mnemonic_tab(){
	//ASSEMBLER DIRECTIVES
	insert(0,"START",01,"AD",1);
	insert(1,"END",20,"AD",0);
	insert(2,"ORIGIN",03,"AD",1);
	insert(3,"EQU",04,"AD",1);
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
	insert(16,"DC",01,"DL",1);	//gives a constant value
	insert(17,"DS",02,"DL",1);	//var ds n will give n bytes to var i.e lc += n
}

int get_register(char a[10]){
	if(compare(a,"AREG")){
		return 01;
	}else if(compare(a,"BREG")){
		return 02;
	}else if(compare(a,"CREG")){
		return 03;
	}else if(compare(a,"DREG")){
		return 04;
	}else{
		return 0;
	}
}

bool validate(char c[20],char d[20],char e[20],int ct){
	int i=0,ck=0,n=0,h=0,j=0,k=0,val=0,cc=0;
	char op1[10]={'\0'},op2[10]={'\0'};
	FILE *fout;
	char *token;
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
			if(checkForSym(c) == 0){
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
		i = 0;
		while(e[i++] != '\0'){
		if(e[i] >= 65 && e[i] <= 90){
					printf("%s must have operand as constant\n",d);
					return true;
				}
		}
		if(checkForSym(c) == 0){
				insert_into_sym_tab(c,lc,1);
		}
		else{
			update_in_sym_tab(c,lc,1);
		}
		fout = fopen("output","a");
		fprintf(fout,"(%s,%d)\t(C,%d)\n",m[j].type,m[j].opcode,atoi(e));
		fclose(fout);
		if( j == 16 ){
			lc++;
		}else{
			lc += atoi(e);
		}
		return false;
	}
	if(j>=0 && j<5){//ASSEMBLER DERECTIVES
		if(j==4){
			update_lit_tab();
			LTORG = true;
		}
	}
	if(j>4 && j<16){//IMPERATIVE STATEMENTS
		lc++;
	}
	//NO OPERAND
	if(n == 0){
		i = 0;
		if( e[i] != '*'){
		 	printf("%s must have no operand\n",d);
		 	return true;
		}
		if( j == 1){
			//update_in_sym_tab_all();	//after the end 
			update_lit_tab();
			if(if_undec()){
				printf("undeclared variables exists\n");
				return true;
			}
			//will update all default addresses the variable is been assigned
		}
		fout = fopen("output","a");
		fprintf(fout,"(%s,%d)\n",m[j].type,m[j].opcode);
		fclose(fout);
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
			}else if(j == 3 || j == 2){
				//EQU AND ORIGIN
				token = strtok(e,"+");
				while(token != NULL){
					if(op1[0] == '\0'){
						strcpy(op1,token);
					}else{
						strcpy(op2,token);
					}
					token = strtok(NULL,"+");
				}
				val = 0;
				k=0;
				h = 0;
				cc = 0;
				if(op1[0] >= 65 && op1[0] <= 90){
					val = get_addr_of_sym(op1);
					h++;
				}else{
					val = atoi(op1);
				}
				if(op2[0] >= 65 && op2[0] <= 90){
					k = get_addr_of_sym(op2);
					cc++;
				}else if(op2[0] != '\0'){
					k = atoi(op2);
				}
				if(j == 2){
					//ORIGIN
					lc = val + k;
				}else{
					insert_into_sym_tab(c,val+k,1);
				}
				fout  = fopen("output","a");
				if(h != 0){
					if(cc != 0){
						//both are symbol
						h = get_sym_index(op1);
						k = get_sym_index(op2);
						fprintf(fout,"(%s,%d)\t(S,%d)+(S,%d)\n",m[j].type,m[j].opcode,h,k);
					}else{
						h = get_sym_index(op1);
						fprintf(fout,"(%s,%d)\t(S,%d)+%d\n",m[j].type,m[j].opcode,h,k);
					}
				}else{
					fprintf(fout,"(%s,%d)\t(C,%d)\n",m[j].type,m[j].opcode,val);
				}
				fclose(fout);
			    return false;
			}
			else{
				if(e[i] == ',' || (e[i] >= 49 && e[i] <= 57)){
					printf("%s must have only one operand and must not be a constant\n",d);
					return true;
				}
			}
		}
		if(j==0){
			fout  =  fopen("output","w");
			lc = atoi(e);
			fprintf(fout,"(%s,%d)\t(C,%d)\n",m[j].type,m[j].opcode,lc);
			fclose(fout);
		}
		else{
			if(checkForSym(e) == 0){
				insert_into_sym_tab(e,-1,1);
			}
			fout  = fopen("output","a");
			fprintf(fout,"(%s,%d)\t(S,%d)\n",m[j].type,m[j].opcode,sym_index-1);
			fclose(fout);
		}
	}
	//TWO OPERANDS
	else if(n == 2){
		i=0;
		h=0;
		k=0;
		fout  = fopen("output","a");
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
		if(checkForSym(op1) == 0){
			cc = 1;
			insert_into_sym_tab(op1,-1,1);
			fprintf(fout,"(%s,%d)\t(S,%d)",m[j].type,m[j].opcode,sym_index-1);
		}else if(checkForSym(op1) == 1){
			cc = get_sym_index(op1);
			fprintf(fout,"(%s,%d)\t(S,%d)",m[j].type,m[j].opcode,cc);
		}
		else if(isLiteral(op1)){
			cc = 2;
			insert_into_literal_tab(op1,-1);
			fprintf(fout,"(%s,%d)\t(L,%d)",m[j].type,m[j].opcode,lit_index-1);
		}
		val = get_register(op1);
		if(val != 0){
			cc = 3;
			fprintf(fout,"(%s,%d)\t(R,%d)",m[j].type,m[j].opcode,val);
			val = 0;
		}
		if(cc == 0){
			fprintf(fout,"(%s,%d)\t(S,%d)",m[j].type,m[j].opcode,sym_index-1);
		}
		if(checkForSym(op2) == 0){
			cc = 4;
			insert_into_sym_tab(op2,-1,1);
			fprintf(fout,",(S,%d)\n",sym_index-1);
		}else if(checkForSym(op2) == 1){
			cc = get_sym_index(op2);
			fprintf(fout,",(S,%d)\n",cc);
		}
		else if(isLiteral(op2)){
			cc = 5;
			insert_into_literal_tab(op2,-1);
			fprintf(fout,",(L,%d)\n",lit_index-1);
		}
		val = get_register(op2);
		if(val != 0){
			cc = 6;	
			fprintf(fout,",(R,%d)",val);
			val = 0;
		}
		if(cc == 0){
			fprintf(fout,",(S,%d)\n",sym_index-1);
		}
		fclose(fout);
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
	char ft[20] = {'\0'};
	char temp[200] = {'\0'};
	f = fopen("low_level","r");
	if(f == NULL){
		printf("file doesn't exists");
		return ;
	}
	char *token ;
	while (fscanf(f, "%[^\n]\n",temp) != EOF)
	{
		token = strtok(temp," ");
		 while (token != NULL) 
		{ 
			if(c[0] == '\0'){
				strcpy(c,token);
			}else if(d[0] == '\0'){
				strcpy(d,token);
			}else{
				strcpy(e,token);
			}
			token = strtok(NULL," "); 
		} 
		count++;
		if(d[0] == '\0'  && e[0] == '\0'){
			e[0] = d[0] = '*';
			if(validate(e,c,d,count)){
				i++;
				printf("Error in line number %d\n",count);
				break;
			}
		}
		else if(e[0] == '\0'){
			e[0] = '*';
			if(validate(e,c,d,count)){
				i++;
				printf("Error in line number %d\n",count);
				break;
			}
		}else{
			if(validate(c,d,e,count)){
						i++;
						printf("Error in line number %d\n",count);
						break;
					}
		}
		if(count == 1 && lc == 0){
			//i.e first line has been executed
			//there is no start at the begining
			printf("LOCATION COUNTER NOT DEFINED\n");
			i++;
			break;
		}
		strcpy(c,ft);
		strcpy(d,ft);
	 	strcpy(e,ft);
	}
	
	if(i == 0){
		display_sym_tab();
		show_lit_tab();
		show_pool_tab();
		printf("****COMPILED SUCCESSFULLY****\n");
	}
}
