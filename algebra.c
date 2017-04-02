/*
 * Made by Bruno Carvalho 	201508043  FCUP
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "polinomio.h"

Poli *normalizar(Poli *pol){
	Poli *p1=NULL, *p2=NULL;
	p1=pol;
	for (; p1!=NULL; p1 = p1->next) {
		for (p2=p1->next; p2!=NULL; p2 = p2->next) {
			if(p1->var[0]==p2->var[0] && p1->exp==p2->exp){
				p1->con = p1->con + p2->con;
				p2->con=0;
				p2->var[0]='<';
				p2->exp=0;
			}
		}
	}
	return pol;
}

void soma(){
	char poli1[50];
	char poli2[50];
	
	scanf("%s", poli1);
	scanf("%s", poli2);
	
	Poli *p1=NULL, *p2=NULL, *temp1=NULL;
	
	p1 = polToList(poli1);
	p2 = polToList(poli2);
	
	temp1 = append(p1,p2,p1);
	
	printPoli(normalizar(temp1));
}

void derivar(){
	char poli[50];
	
	scanf("%s", poli);
	
	Poli *p1=NULL, *temp1=NULL;
	int tempExp;
	
	p1 = polToList(poli);
	temp1=p1;
	
	for (; p1!=NULL; p1 = p1->next) {
		if(p1->exp == 0){
			p1->con=0;
		}
		else if(p1->exp == 1){
			p1->exp=0;
			p1->var[0]='<';
		}
		else{
			tempExp = p1->exp;
			p1->exp--;
			p1->con=p1->con*tempExp;
		}
	}
	printPoli(normalizar(temp1));
}

void primitivar(){
	char poli[50];
	
	scanf("%s", poli);
	
	Poli *p1=NULL, *temp1=NULL;
	
	p1 = normalizar(polToList(poli));
	temp1=p1;
	char *var;
	var=malloc(sizeof(char));
	
	getchar();
	printf("Em função a:\n");
	scanf("%s", var);
	
	for (; p1!=NULL; p1 = p1->next) {
		
		if(p1->exp == 0){
			p1->var=strdup(var);
			p1->exp=1;
		}
		else if(p1->exp == 1 && strcmp(p1->var,var)==0){
			p1->exp=2;
			if(p1->con % 2 == 0) p1->con=p1->con/2;
			else{
				p1->Frac->numerador=p1->con;
				p1->Frac->denominador=2;
			}
		}
		else if (strcmp(p1->var,var)==0){
			p1->exp++;
			if(p1->con % p1->exp == 0) p1->con=p1->con/p1->exp;
			else {
				p1->Frac->numerador=p1->con;
				p1->Frac->denominador=p1->exp;
			}
		}
		else {
			*((p1->var)+1)=*(var);
		}
	}		
	printPoli(temp1);
}

int main() {
	
	char func[50];
	
	printf("Funcao a usar:\n");
	scanf("%s", func);
	printf("Polinomio:\n");
	
	if (strcmp(func,"somar")==0) soma();
	else if (strcmp(func,"derivar")==0) derivar();
	else if (strcmp(func,"integral")==0) primitivar();
	else if (strcmp(func,"normalizar")==0){
		char poli[50];
		scanf("%s", poli);
		printPoli(normalizar(polToList(poli)));
	}
	else printf("Funcao desconhecida\n");
	
	return 0;
	
}

