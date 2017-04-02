#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "polinomio.h"

typedef struct list Poli;

Poli *newitem(int conTemp, char varTemp, int expTemp) {
	Poli *temp;
	temp = (Poli*) malloc(sizeof(Poli));
	temp -> Frac = (struct frac *) malloc(sizeof(struct frac));
	temp -> var = malloc(2*sizeof(char));
	temp -> con = conTemp;
	*(temp -> var) = varTemp;
	temp->Frac->numerador = 0;
	temp->Frac->denominador = 0;
	temp -> exp = expTemp;
	temp -> next = NULL;
	return temp;
}

Poli *newMon(Poli *poli, Poli *temp) {
	temp -> next = poli;
	return temp;
}

Poli *append (Poli *poli1, Poli *poli2, Poli *original){
	Poli *p;
	p=poli1;

	if (p->next==NULL){
		p->next=poli2;
		return original;
	}
	else {
		p=p->next;
		return append(p,poli2,original);
	}
}

void delete(Poli *poli) {
	
	if(poli->next == NULL){
		return;
	}

	Poli *temp = poli->next->next;
	free(poli->next);
	poli->next=temp;
	return;
}

void printPoli(Poli *poli){
	int flag=0;
	
	for ( ; poli!=NULL; poli = poli->next) {
		if (poli->con==0 && poli->next==NULL && flag==0) printf("0");
		
		else{
			if(flag==1 && poli->con!=0) printf("+ ");
			else if (flag==0) flag=1;
			
			if(poli->Frac->numerador != 0 && poli->Frac->denominador != 0){
				if(poli->con==0);
				
				else if(poli->exp==0) printf("%d/%d ", poli->Frac->numerador,
									  poli->Frac->denominador);
				
				else if(poli->exp==1) printf("%d/%d(%s) ", poli->Frac->numerador,
					   				  poli->Frac->denominador, poli->var);
								  
				else printf("%d/%d(%s^%d) ", poli->Frac->numerador,
					 poli->Frac->denominador, poli->var, poli->exp);
			}
			else {
				if(poli->con==0);
				else if(poli->exp==0) printf("%d ", poli->con);
				else if(poli->exp==1) printf("%d%s ", poli->con, poli->var);
				else printf("%d%s^%d ", poli->con, poli->var, poli->exp);
			}
		}
	}
	printf("\n");
}

Poli *polToList(char poli[50]){
	int conTemp;
	char varTemp;
	int expTemp;
	int i;
	
	Poli *temp=NULL;
	
	for(i=0; i < strlen(poli); i++){
		if(poli[i] == '-'){
			i++;
			conTemp=-1*(poli[i]-48);
		}
		else if(poli[i-1] == '-'){
			conTemp=-1*(poli[i]-48);
		}
		else conTemp = poli[i]-48;
		i++;
		
		while(poli[i] >= '0' && poli[i] <= '9' && i<strlen(poli)){
			
			if(conTemp >= 0) conTemp=(conTemp*10+(poli[i]-48));
			else if(conTemp < 0) conTemp=(conTemp*10-(poli[i]-48));
			i++;
		}
		
		if(poli[i] != '+' && poli[i] != '-' && i<strlen(poli)){
			varTemp = poli[i];
			i++;
			if(poli[i]=='^'){
				i++;
				expTemp = poli[i]-48;
				i++;
			}
			else{
				expTemp = 1;
			}
		}
		else{
			varTemp = '<';
			expTemp = 0;
		}
		temp = newMon(temp, newitem(conTemp, varTemp, expTemp));
	}
	return temp; 
}
