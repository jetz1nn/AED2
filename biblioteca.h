#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <dirent.h>

// OLÁ PROFESSOR COMO NAO SEI REFERENCIAR UM CODIGO-FONTE NO RELATORIO, O QUAL NAO ACHEI NA INTERNET, ESTAREI POR MEIO DESSE COMENTARIO
// DEIXANDO EXPLICITO QUE O CODIGO-FONTE NAO É DE PRODUCAO MINHA E PEGUEI A IDEIA BASE PARA A PRODUCAO DO MESMO
// O CÓDIGO NO QUAL PEGUEI A BASE PERTENCE AOS ALUNOS ... ... ALUNOS DE ESTRUTURA DE DADOS DO SEMESTRE DE 2018/1

#define N 6 // Constante que determina o numero de funcoes e tabelas hash
#define TAM 720059	// tamanho das tabelas


typedef struct registro {
    unsigned long chave;
    unsigned long naochave;
    unsigned char outros[1008];
}registro;

typedef struct Hash {
	unsigned long naochave;
	int bloco;
}Hash;

typedef struct EnderecoDisco{
    unsigned int bloco;
    struct EnderecoDisco * prox;
}EnderecoDisco;

typedef struct ABP{
    unsigned long naochave;
    struct ABP * esq;
    struct ABP * dir;
    struct EnderecoDisco * prox;
}ABP;

void InserirHash(Hash*** tabela, unsigned long naochave, unsigned int bloco, int funcao, int colisao);

void inserirABP(ABP **raiz, unsigned long naochave, unsigned int bloco);

void imprimirRegistros(EnderecoDisco *registros, unsigned long naochave);

void buscaABP(ABP **raiz, unsigned long naochave);

void destruirArvore(ABP *raiz);

void travessiaEmOrdem(ABP *raiz);

int hash(int funcao, unsigned long chave);

void PesquisarHash(Hash*** tabela, unsigned long naochave);
