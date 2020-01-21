#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int lc = 0,ltorg=0;
char add[20]={'\0'};
char* read_from_sym_tab(int index){
	FILE *f;
	char a[20],b[20],c[20],d[20]={'\0'},e[20];
	int i;
	f = fopen("sym_file","r");
	for(i = 0;i<index+1 ;i++){
		fscanf(f,"%s\t%s\t%s\t%s",a,b,c,e);
	}
	strcpy(a,d);strcpy(b,d);strcpy(c,d);
	strcpy(e,d);
	fscanf(f,"%s\t%s\t%s\t%s",a,b,c,e);
	strcpy(add,c);
	fclose(f);
	return add;
}       

void reach_end_of_lit(int index){
	FILE *f;
	char a[20],b[20],c[20],d[20]={'\0'};
	int i;
	f = fopen("lit_file","r");
	for(i = 0;i<index+1 ;i++){
		fscanf(f,"%s\t%s\t%s",a,b,c);
	}
	strcpy(a,d);strcpy(b,d);strcpy(c,d);
	while(fscanf(f,"%s\t%s\t%s",a,b,c)!= EOF){
		lc++;
	}
	fclose(f);
}

void inc_lc_for_ltorg(int i){
	char a[10];
	int i1 = 0 , i2 = 0 ,i3 = i;
	FILE *f;
	f = fopen("pool_file","r");
	fscanf(f,"%s",a);
	i3 = i+1;
	while(i3--){
		fscanf(f,"%s",a);
		if(i3 == 1){
			i1 = atoi(a);
		}else if(i3 == 0){
			i2 = atoi(a);
		}
	}
	if(i1 == i2){
		reach_end_of_lit(i1);
	}else{
		lc = lc + i2 - i1;
	}
	fclose(f);
}

char* read_from_lit_tab(int index){
FILE *f;
	char a[20],b[20],c[20],d[20]={'\0'};
	int i;
	f = fopen("lit_file","r");
	for(i = 0;i<index+1 ;i++){
		fscanf(f,"%s\t%s\t%s",a,b,c);
	}
	strcpy(a,d);strcpy(b,d);strcpy(c,d);
	fscanf(f,"%s\t%s\t%s",a,b,c);
	strcpy(add,c);
	fclose(f);
	return add;
}

int seperate(char a[10]){
int c = 0;
	char *t = strtok(a,"(,)");
	while(t != NULL){
		if(strcmp(t,"S") ){
			c++;
		}
		if(c != 0){
			lc = atoi(read_from_sym_tab(atoi(t)));
		}
		t = strtok(NULL,"(,)");
	}
}

void generate_mac_code(char a[20],char b[20]){
	char *token = NULL,*t = NULL;
	FILE *f;
	int op = 0;
	int i =0 ,index=0,mem_op,c=0;
	char temp[10]= {'\0'},temp2[10]={'\0'};
	char code[5]={'\0'},opcode[2]={'\0'},reg[2]={'\0'};
	token = strtok(a,"(,)");
	while(token != NULL){
		i++;
		if(i == 1){
			strcpy(code,token);
		}
		else
		{
			strcpy(opcode,token);
		}
		token = strtok(NULL,"(,)");
	}
	op = atoi(opcode);
	if( strcmp(code,"AD") == 0)//write nothing
	{
		if(op == 1 ){	//start
			i = 0;
			token = strtok(b,"(,)");
			while(token != NULL){
				i++;
				if(i == 2){
					lc = atoi(token);
				}
				token = strtok(NULL,"(,)");
			}
			//printf("%d\n",lc);
			return;
		}
		else if(strcmp("3",opcode) == 0){
			//ORIGIN
			i = 0;
			token = strtok(b,"+");
			while(token != NULL){
				//seperate(temp);
				if(temp[0] == '\0'){
					strcpy(temp,token);
				}else{
					strcpy(temp2,token);
				}
				
				token = strtok(NULL,"+");
			}
			printf("%d)\t",lc);
			seperate(temp);
			lc += atoi(temp2);
			printf("\n");
		}
		else if(strcmp("5",opcode) == 0){
			printf("%d)\n",lc);
			ltorg++;
			inc_lc_for_ltorg(ltorg);
		}else{
			printf("%d)\n",lc);
		}
		//f = fopen("output2","a");
		
		//fclose(f);
		return;
	}
	if(strcmp(code,"DL")==0 ){
		//declarative statements
		//  f = fopen("output2","a");
		//  fprintf("%d)\n",lc++)
		//  fclose(f);
		printf("%d)\n",lc++);
		 return;
	}
	i = 0;
	printf("%d)\t%s\t",lc++,opcode);
	token = strtok(b,"(,)");
	while(token != NULL){
		//printf("%s\t",token);
		if(strcmp(token,"R") == 0){
			token = strtok(NULL,"(,)");
			strcpy(reg,token);
			printf("%s\t",reg);
		}else if(strcmp(token,"S") == 0){
			//search for address in symbol table
			token = strtok(NULL,"(,)");
			index = atoi(token);
			//printf("%d",index);
			//mem_op = read_from_sym_tab(index);
			printf("%s",read_from_sym_tab(index));
		}else if(strcmp(token,"L") == 0){
			//search for address in literal table
			token = strtok(NULL,"(,)");
			index = atoi(token);
			//printf("%d",index);
			printf("%s",read_from_lit_tab(index));
		}else{
			
		}
		token = strtok(NULL,"(,)");
	}
	printf("\n");
// 	f = fopen("output2","a");
// 	fprintf("%d\t%s\t%s\t%s\n",lc++,opcode,reg,)
// 	fclose(f);
 }

int main(){
	FILE *f;
	FILE *f2;
	char temp[50] = {'\0'};
	char c[20] = {'\0'},d[20]={'\0'},e[20] = {'\0'};
	char * token = NULL;
	//f2 = fopen("output2","w");
	printf("LC\tOPCODE\tREG\tMEMORY OPERAND\n");
	//fclose(f2);
	f = fopen("output","r");
	while(fscanf(f,"%[^\n]\n",temp)!=EOF){
		token = strtok(temp,"\t");
		while(token != NULL){
			if(c[0] == '\0'){
				strcpy(c,token);
			}else{
				strcpy(d,token);
			}
			token = strtok(NULL,"\t");
		}
		generate_mac_code(c,d);
		strcpy(c,e);
		strcpy(d,e);
	}
	fclose(f);
	return 0;
}
