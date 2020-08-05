#include<stdio.h>
#include<stdlib.h>
typedef struct Arvore{
	int dado,fb;
	struct Arvore *esq,*dir;
}arvore;

void rotacaoRR(arvore **a){
	arvore *aux = (*a)->esq;
	(*a)->esq = aux->dir;
	aux->dir = *a;
	(*a)->fb = profundidade((*a)->dir)-profundidade((*a)->esq);
	aux->fb = profundidade(aux->dir)-profundidade(aux->esq);
	*a = aux;
}
void rotacaoLL(arvore **a){
	arvore *aux = (*a)->dir;
	(*a)->dir = aux->esq;
	aux->esq = *a;
	(*a)->fb = profundidade((*a)->dir)-profundidade((*a)->esq);
	aux->fb = profundidade(aux->dir)-profundidade(aux->esq);
	*a = aux;
}
void rotacaoLR(arvore **a){
	rotacaoRR(&((*a)->esq));
	rotacaoLL(&(*a));
}
void rotacaoRL(arvore **a){
	rotacaoLL(&((*a)->dir));
	rotacaoRR(&(*a));
}
void balanceamento(arvore **a){
    arvore *filho;
    int aux;
    if((*a)->fb==2){
        filho=(*a)->dir;
        if(filho->fb < 0){
           	aux = filho->esq->fb;
            rotacaoRL(&(*a));
            if(aux == 1){
                (*a)->fb = -1;
            }
            if(aux == 1){
                (*a)->fb = 1;
            }
        }else{
            rotacaoLL(&(*a));
        }
    }else{
        filho=(*a)->esq;
        if(filho->fb > 0){
            aux = filho->dir->fb;
            rotacaoLR(&(*a));
            if(aux == -1){
                (*a)->fb = 1;
            }
            if(aux == 1){
                (*a)->fb = -1;
            }
        }else{
            rotacaoRR(&(*a));
        }
    }
}
void verifica(arvore **a,int dado){
		if(*a!=NULL){
            (*a)->fb = profundidade((*a)->dir) - profundidade((*a)->esq);
            if(abs((*a)->fb)>1)
                balanceamento(&(*a));
            if((*a)->dado>dado)
            	verifica(&((*a)->esq),dado);
            else
				verifica(&((*a)->dir),dado);
        }
}

void inserir(arvore **a,int num,arvore **raiz){
		if(*a==NULL){
			*a = (arvore *)malloc(sizeof(arvore));
			(*a)->dado = num;
			(*a)->esq = (*a)->dir = NULL;
			if(*a!=NULL){
			//printf("\n\nDado %d inserido com sucesso\n\n",(*a)->dado);
			verifica(&(*raiz),(*a)->dado);
			
		}
		}
		else{
			if(num<(*a)->dado)
				inserir(&((*a)->esq),num,raiz);
			else if(num>(*a)->dado)
				inserir(&((*a)->dir),num,raiz);
		}
}
int profundidade (arvore *a) {
   if (a==NULL) 
      return -1;
   else {
      int esq = profundidade(a->esq);
      int dir = profundidade(a->dir);
      if (esq<dir) 
	  return dir + 1;
      else 
	  	return esq + 1;
   }
}

void deletar(arvore **a,int num,arvore **raiz){
		if((*a)->dado>num)
			deletar(&((*a)->esq),num,raiz);
		else if((*a)->dado<num)
			deletar(&((*a)->dir),num,raiz);
		else{
			if((*a)->esq==NULL&&(*a)->dir==NULL){
				free(*a);
				*a = NULL;
			}
			else if((*a)->esq==NULL){
				arvore *x = *a;
				*a = (*a)->dir;
				free(x);
			}
			else if((*a)->dir==NULL){
				arvore *x = (*a);
				(*a) = (*a)->esq;
				free(x);
			}
			else{
				arvore *y = (*a)->esq;
				while(y->dir!=NULL){
					y = y->dir;
				}
				(*a)->dado = y->dado;
				y->dado = num;
				deletar(&((*a)->esq),num,raiz);
			}
			verifica(a,num);
		}
}
void pre_order (arvore *a){
	if(a!=NULL){
		printf("%d\t",a->dado);
		pre_order(a->esq);
		pre_order(a->dir);
	}
}

void in_order (arvore *a){
	if(a!=NULL){
		in_order(a->esq);
		printf("%d\t",a->dado);
		in_order(a->dir);
	}
}

void pos_order (arvore *a){
	if(a!=NULL){
		 pos_order(a->esq);
		 pos_order(a->dir);
		printf("%d\t",a->dado);
	}
}
void mostrar(arvore *a){
		if(a!=NULL){
		printf("\nPre-order: ");
		pre_order(a);
		printf("\n");
		printf("\nIn-order: ");
		in_order(a);
		printf("\n");
		printf("\nPos order: ");
		pos_order(a);
	}
	else{
		printf("Arvore vazia\n");
	}
}
int numnos (arvore *a) { 
    if (a==NULL) 
		return 0;
    else {          
        int numesq = numnos(a->esq);         
        int numdir = numnos(a->dir); 
        return numesq+numdir+1;   
    }
}

void printnode(int c, int b) {
    int i;
    for (i=0;i<b; i++) 
		printf("   ");
    printf("%d\n", c);
}
void caminho(arvore *x, int b) {
    if (x == NULL) {
        return;
    }
    caminho(x->esq, b+1);    
    printnode(x->dado, b);
    caminho(x->dir, b+1);   
}
void busca(arvore *a,int num){
	if(a==NULL)
		printf("Numero nao encontrado");
	else if(num<a->dado)
		busca(a->esq,num);
	else if(num>a->dado)
		busca(a->dir,num);
	else
		printf("\n%d\n",a->dado);
	
}
main(){
	arvore *a = NULL;
	int opt,num,x,i;
	printf("Inserindo\n");
	for(i=0;i<200000;i++){
		if(i%1000==0)
			printf("\n%d\n",i);
		inserir(&a,i,&a);
	}
	do{
        printf("\n\n1-Inserir;\n2-Mostrar arvore;\n3-Profundidade da arvore;\n4-Deletar\n5-Numero de nos\n6-Caminhos\n7-Fator de balanceamento\n8-Buscar\n0-Fechar programa\n");
        scanf("%d",&opt);
        switch(opt){
        	case 1: 
		printf("Digite o numero que deseja inserir: ");
		scanf("%d", &num);
				inserir(&a,num,&a);
        			break;
        case 2:	mostrar(a);
        		break;
        case 3: printf("\nA profundidade e %d\n",profundidade(a));
        		break;
        case 4:
				if(a==NULL)
					printf("Arvore vazia\n");
				else{
			printf("Digite o numero que deseja deletar: ");
		scanf("%d", &num);
				deletar(&a,num,&a);
			}
        			break;
        case 5: printf("A arvore possui %d nos",numnos(a));
        		break;
        case 6: caminho(a,0);
        		break;
		case 7: printf("O fb da arvore e %d",a->fb);
		case 8:
				printf("Digite o numero do registro a ser buscado: ");
				scanf("%d",&x);
				busca(a,x);
        case 0: break;
        default: printf("Opcao invalida\n");
        			break;
        }
	}while(opt!=0);
}
