#ifndef _SINTATICO_H_
#define _SINTATICO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"

// programa
void Analisador_Sintatico(char *c, Token **token);

//bloco
void Analisa_Bloco (char *c, Token **token);

//declaração de variáveis
void Analisa_et_variaveis (char *c, Token **token);
       
//declaração de variáveis
void Analisa_Variaveis (char *c, Token **token, char *variavel);
 
//tipo
void Analisa_Tipo (char *c, Token **token);
 
//comandos
void Analisa_comandos (char *c, Token **token);

//comandos
void Analisa_comando_simples (char *c, Token **token);

//atribuição_chprocedimento
void Analisa_atrib_chprocedimento (char *c, Token **token);

// Usado na Analisa_leia
void pesquisar_em_toda_a_tabela();

//comando leitura
void Analisa_leia (char *c, Token **token);

// comando escrita
void Analisa_escreva (char *c, Token **token);
 
//comando repetição
void Analisa_enquanto (char *c, Token **token);
 
// comando condicional
void Analisa_se (char *c, Token **token);

// etapa de declaração de sub-rotinas
void Analisa_Subrotinas (char *c, Token **token, int rotulo);

//declaração de procedimento
void Analisa_declaracao_procedimento (char *c, Token **token);

//declaração de função
void Analisa_declaracao_funcao (char *c, Token **token);

//expressão
void Analisa_expressao (char *c, Token **token);
 
//expressão simples
void Analisa_expressao_simples (char *c, Token **token);

//termo
void Analisa_termo (char *c, Token **token);
 
//fator
void Analisa_fator (char *c, Token **token);

//usado no Analisa_expressao
void analisaExpressaoRelacional(Token **token);

#endif