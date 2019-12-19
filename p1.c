#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
char* check[] = {"START","MOVER","READ","STOP","PRINT","MOVEM","END"};

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

bool validate(char c[1000],int ct){
	int i=0,j=0,h=0;
	int ck=0;
	char *temp = (char *)malloc(sizeof(char)*10);
	while(c[j]!=' '){
		*(temp+j) = c[j];
		j++;
	}
	for(i=0;i<7;i++){
		if(compare(temp,check[i])){
			ck++;
			break;
		}
	}
	//i has what instruction is that
	//j++ has start of operands
		free(temp);
	if(i==0 || i==2 || i==4){
		//ONLY ONE OPERAND
		while(c[j++]!='\n'){
			if(c[j] == ','){
				//i.e it has two operands
				printf("%s must have only one operand\n",check[i]);
				return true;
			}
		}
	}
	else if(i==3 || i==6){
		//NO OPERAND
		if(c[j++]!='\0'){
				printf("%s must have no operand\n",check[i]);
				return true;
		}
	}
	else if(i == 1 || i==5){
		//TWO OPERANDS
		while(c[j++] != '\n'){
			if(c[j]==','){
			 	h++;
			}
		}
		if(h!=1){
			printf("%s must have two operands\n",check[i]);	
			return true;		
		}
	}
	if(ck!=0){
		return false;
	}
	return true;
}

void main(){
	FILE * f;
	int count=0,i;
	char c[1000];
	char *ch;
	
	f = fopen("low_level.txt","r");
	while(fscanf(f,"%[^\n]",c)!= EOF){
		/*ch = (char *)malloc(sizeof(char)*1000);
		i=0;
		while(c[i]!='\n'){
			ch[i] = c[i];
			i++;
		}*/
		fgetc(f);
		count++;
		
			//printf("%s",c);
		
		//printf("%s",ch);
		if(validate(c,count)){
			printf("Error in line number %d\n",count);
			break;
		}
		//memset(c,'\0',1000*sizeof(char));
		//free(ch);
	}
}
