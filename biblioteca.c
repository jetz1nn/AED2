#include "bibliotecaprojeto.h"

// OLÁ PROFESSOR COMO NAO SEI REFERENCIAR UM CODIGO-FONTE NO RELATORIO, O QUAL NAO ACHEI NA INTERNET, ESTAREI POR MEIO DESSE COMENTARIO
// DEIXANDO EXPLICITO QUE O CODIGO-FONTE NAO É DE PRODUCAO MINHA E PEGUEI A IDEIA BASE PARA A PRODUCAO DO MESMO
// O CÓDIGO NO QUAL PEGUEI A BASE PERTENCE AOS ALUNOS ... ... ALUNOS DE ESTRUTURA DE DADOS DO SEMESTRE DE 2018/1

void inserirABP(ABP **raiz, unsigned long naochave, unsigned int bloco){
    // CASO BASE DE INSERCAO
    if(*raiz == NULL){
        ABP *novo = (ABP*) malloc(sizeof(ABP));
        novo->naochave = naochave;
        novo->dir = NULL;
        novo->esq = NULL;
        novo->prox = (EnderecoDisco*) malloc(sizeof(EnderecoDisco));
        novo->prox->bloco = bloco;
        *raiz = novo;
        return;
    }

    if((*raiz)->naochave == naochave){
        //VERIFICA SE O VALOR NAO CHAVE EH O MESMO PARA INSERCAO NA LISTA

        EnderecoDisco * aux = (*raiz)->prox;
        //percorrendo a lista iterativamente
        while(aux != NULL){
            aux = aux->prox;
        }
        
        aux = (EnderecoDisco*) malloc(sizeof(EnderecoDisco));
        aux->bloco = bloco;
        aux->prox = NULL;
        return;
    }

    if((*raiz)->naochave < naochave)
        return inserirABP(&((*raiz)->dir), naochave, bloco);
    else
        return inserirABP(&((*raiz)->esq), naochave, bloco);

}

void imprimirRegistros(EnderecoDisco * registros, unsigned long naochave){
    //declarando variavel auxiliar para percorrer a lista de registros
    EnderecoDisco *aux = registros;
    if(aux == NULL)
        return;

    FILE *p = fopen("base.bin","rb"); //fazendo a leitura do arquivo
    //verificação da abertura de arquivo
    if(p == NULL){
        printf("Erro na abertura do arquivo!!!");
        return;
    }

    registro dado[4]; //total sao 4 registros por bloco
    //percorrer iterativamente lista de blocos que contem os valores naochave
    while(aux != NULL){
        
        fseek(p, (aux->bloco)*4096, SEEK_SET);
        if(fread(&dado[0],sizeof(registro)*4,1,p)){
            for(int i=0; i<4; i++){
                if(dado[i].naochave == naochave){
                    printf("%lu \n",dado[i].chave);
                    printf("%lu \n",dado[i].naochave);
                    printf("%s \n",dado[i].outros);
                }
            }
        }
        aux=aux->prox;
    }

    fclose(p);
    return;
}

void buscaABP(ABP **raiz, unsigned long naochave){
    //funcao feita para busca da arvore feita na main com os elementos naochave
    // do arquivo
    if(*raiz == NULL){
        printf("Essa chave nao existe!!!");
        return;
    }

    if((*raiz)->naochave == naochave){
        //EnderecoDisco *registro = (*raiz)->prox;
        imprimirRegistros((*raiz)->prox, naochave);
        return;
    }
    //caso a chave nao exista

    if((*raiz)->naochave < naochave)
        return buscaABP(&((*raiz)->dir),naochave);
    else
        return buscaABP(&((*raiz)->esq),naochave);

    return;
}
//funcao que faz uma travessia posOrdem para destruir a arvore
void destruirArvore(ABP *raiz){
    if(raiz == NULL)
        return;
    destruirArvore(raiz->esq);
    destruirArvore(raiz->dir);
    free(raiz);
}

void travessiaEmOrdem(ABP *raiz){
    
    if(raiz==NULL)
        return;
    
    travessiaEmOrdem(raiz->esq);
    printf("%lu ",raiz->naochave);
    travessiaEmOrdem(raiz->dir);
}

int hash(int funcao, unsigned long naochave){//funcoes do hash  
	if(naochave<0) //operacao modular para 
		naochave = naochave *-1;    
	switch (funcao){
     	case 0: return (naochave/337) % TAM;						
        case 1: return (naochave/10003) % TAM;
		case 2: return (naochave/11) % TAM;
        case 3: return (naochave/23) % TAM;    
		case 4: return (naochave/17) % TAM;
		case 5: return (naochave/TAM) % TAM; 	
	}
}


void PesquisarHash(Hash*** tabela, unsigned long naochave) {
	int i, indice, bloco=-1;
    unsigned long k;	
	FILE *p;
	registro dados[4];
	p = fopen("base.bin","rb");
	
	for(i=0; i<N ; i++){//BUSCA O ELEMENTO EM TODOS OS INDICES DO MESMO		
		
        indice = hash(i, naochave);

		if(tabela[i][indice]!=NULL){					  //CASO TENHA ALGUM ELEMENTO 		
			if(tabela[i][indice]->naochave == naochave){ //VERIFICA SE O ELEMENTO DESEJADO
                bloco = tabela[i][indice]->bloco;		  //SE FOR, GUARDAMOS O VALOR DO BLOCO
            }
        }
		
        //colocando bloco diferente de -1 para evitar acessos no disco enquanto nao achar o valor
        // assim otimizando em caso de colisão
		if(bloco!=-1){
            fseek(p, 4096*bloco, SEEK_SET); //damos fseek para posicionar o cabeço no bloco que está o valor buscado
		
		    if(fread(&dados[0], 4096, 1, p)){
			    for	(int j=0; j<4 ; j++){
				    if(dados[j].naochave == naochave){
					    printf(" \n Chave: %lu \n",dados[j].chave);
					    printf(" \n NaoChave: %lu \n",dados[j].naochave);
					    printf(" \n Outros: %s \n",dados[j].outros);
                        printf(" \n %lu \n", k);
                        k++;
                    }
			    }
		    }
        }
    }
        if(bloco == -1){
            printf("Elemento nao encontrado...");
        }
    return;
}
void InserirHash(Hash*** tabela, unsigned long naochave, unsigned int bloco, int funcao, int colisao){			
		
	int indice = hash(funcao, naochave);//JOGA O VALOR NAOCHAVE NA FUNÇÃO HASH	

    if(colisao<7){
		if(tabela[funcao][indice] == NULL){						//VERIFICA SE NÃO TEM NADA NA POSIÇÃO,
			
			tabela[funcao][indice] = malloc(sizeof(hash));	//CASO NÃO TENHA ALOCA NO INDICE O ELEMENTO
			tabela[funcao][indice]->naochave = naochave;
			tabela[funcao][indice]->bloco = bloco;
			return;	
		
		}else{															//TEM ELEMENTO NA POSIÇÃO	
			
            Hash *aux = tabela[funcao][indice];					//GUA1RDA ELE EM UM AUX
			tabela[funcao][indice] = malloc(sizeof(hash));	//ALOCA O ELEMENTO NA POSIÇÃO DO INDICE
			tabela[funcao][indice]->naochave = naochave;		//COLOCA O VALOR NÃOCHAVE
			tabela[funcao][indice]->bloco = bloco;				//COLOCA O BLOCO DO REGISTRO QUE POSSUI O VALOR NAOCHAVE
			funcao = (funcao+1) % N;
            colisao++;										//PASSA PRA PROXIMA TABELA														
			return InserirHash(tabela, aux->naochave, aux->bloco, funcao, colisao); //JOGA O ELEMENTO DO AUX PARA TENTAR INSERIR NA PROXIMA TABELA
        }	
    }
	return;
}
