#include "biblioteca.c"

// OLÁ PROFESSOR COMO NAO SEI REFERENCIAR UM CODIGO-FONTE NO RELATORIO, O QUAL NAO ACHEI NA INTERNET, ESTAREI POR MEIO DESSE COMENTARIO
// DEIXANDO EXPLICITO QUE O CODIGO-FONTE NAO É DE PRODUCAO MINHA E PEGUEI A IDEIA BASE PARA A PRODUCAO DO MESMO
// O CÓDIGO NO QUAL PEGUEI A BASE PERTENCE AOS ALUNOS ... ... ALUNOS DE ESTRUTURA DE DADOS DO SEMESTRE DE 2018/1

int main(){
    ABP * tree = NULL;
    Hash ***tabela;
    int opcao=0;
    registro buffer[4];
    int k=0;
    int opcaointerna=0;
    unsigned long valorBusca;
    struct timeval tempo_inicio, tempo_fim;
    double ti, tf, tempo;
    
    
    
    while(opcao!=5){
        printf(" \n 1. Montar ABP \n");
        printf(" \n 2. Montar Cuckoo Hashing \n");
        printf(" \n 3. Sair \n");
        
        scanf("%d",&opcao);
        fflush(stdin);
        switch(opcao){
            case 1:{
                FILE *p;
                printf("Construindo ABP...");
                p = fopen("base.bin","rb");

                if(p == NULL) {
                    return 0;
                }
                
                while(!feof(p)){
                    
                    fread(&buffer[0], sizeof(registro)*4, 1, p); // Lendo 4096 bytes do arquivo
                    
                    for(int i=0; i<4; i++){
                        inserirABP(&tree, buffer[i].naochave, k); // inserindo bloco por bloco
                    }
                    k++;
                    
                    
                }
                
                travessiaEmOrdem(tree);
                fclose(p);

                while(opcaointerna!=2){
                    printf(" \n 1. Buscar \n");
                    printf(" \n 2. Sair \n");
                    scanf("%d",&opcaointerna);
                    fflush(stdin);
                    switch(opcaointerna){
                        case 1:{
                            
                            printf(" \n Digite o valor naochave o qual deseja buscar : \n");
                            scanf("%lu",&valorBusca);
                            fflush(stdin);
                            gettimeofday(&tempo_inicio,NULL);
                            buscaABP(&tree,valorBusca);
                            gettimeofday(&tempo_fim,NULL);
                            //calculo tempo de busca
                            tf = (double) tempo_fim.tv_usec / (1000.0) + ((double)tempo_fim.tv_sec * (1000.0));
							ti = (double) tempo_inicio.tv_usec / (1000.0) + ((double)tempo_inicio.tv_sec * (1000.0));
                            tempo = (tf - ti);

                            printf(" \n O tempo de busca foi %lf ms. \n ", tempo);
                            //system("pause");
                            system("clear");
                            break;

                        }
                        case 2:{
                            return 0;
                        }
                        default:
                            break;
                    }
                }
                break;
            }
            case 2:{
                FILE *p;
                
                p = fopen("base.bin","rb");

                if(p == NULL)
                    return 0;

                printf("Construindo Cuckoo Hashing...");
                
                tabela = malloc(N * sizeof(Hash**));

                for (int i = 0; i < N; i++){
					tabela[i] = malloc(TAM * sizeof(Hash*)); 
					 for (int j = 0; j < TAM; j++){
						  tabela[i][j] = NULL; //Inicializa com NULL.
					 }
				}


                while(!feof(p)){    
                    
                   fread(buffer, sizeof(registro)*4, 1, p);

                        for(int i=0; i<4;i++){
                            InserirHash(tabela, buffer[i].naochave, k, 0, 0);
                            if(k<10){
                                printf("%lu \n", buffer[i].naochave);
                            }
                        }
                        k++;
                }
                
                fclose(p);

                while(opcaointerna!=2){
                    
                    printf(" \n 1. Buscar \n");
                    printf(" \n 2. Sair \n");
                    scanf("%d",&opcaointerna);
                    fflush(stdin);

                    switch(opcaointerna){
                        case 1:{
                            printf(" \n Digite o valor naochave o qual deseja buscar : \n");
                            scanf("%lu",&valorBusca);
                            fflush(stdin);
                            gettimeofday(&tempo_inicio, NULL);
                            PesquisarHash(tabela, valorBusca);
                            gettimeofday(&tempo_fim, NULL);
                            tf = (double) tempo_fim.tv_usec / (1000.0) + ((double)tempo_fim.tv_sec * (1000.0));
							ti = (double) tempo_inicio.tv_usec / (1000.0) + ((double)tempo_inicio.tv_sec * (1000.0));
                            tempo = (tf - ti);

                            printf(" \n O tempo de busca foi %lf ms. \n ", tempo);
                            
                            break;
                        }
                        case 2:{
                            return 0;
                        }
                    }    
                }
            }
            case 3:{
                return 0;
                break;
            }
        }
    }
}