#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexico.h"
#include "error.h"
#include "symbol.h"
#include "token.h"
#include "verifyChar.h"
#include "sintatico.h"

void errorSintax(Token **token, int errorCode, char symbol) {
	freeToken(&(*token));
	detectError(errorCode,lineCount, symbol);
}

bool verificaSimboloRelacional(Token *token) {
	return isEqualString(token->symbol, "smaior") || isEqualString(token->symbol, "smaiorig") ||
		   isEqualString(token->symbol, "sig") || isEqualString(token->symbol, "smenor") ||
		   isEqualString(token->symbol, "smenorig") || isEqualString(token->symbol, "sdif");
}

void Analisador_Sintatico(char *c, Token **token) {
    //int rotulo = 1;
	getToken(&(*c), &(*token));
	if (isEqualString((*token)->symbol, "sprograma")) {
		freeToken(&(*token));
		getToken(&(*c), &(*token));
		if (isEqualString((*token)->symbol, "sidentificador")) {
            //insere_tabela(token.lexema,"nomedeprograma"," "," ");
			freeToken(&(*token));
			getToken(&(*c), &(*token));
			if (isEqualString((*token)->symbol, "spontovirgula")) {
				Analisa_Bloco(&(*c), (&(*token))); // Deve sair com o token lido
				if (isEqualString((*token)->symbol, "sponto")) {
					if (isNotEndOfFile(*c) || checkComment(&(*c))) {
						if(debug)
                            printf("\nDEBUG - Analisando comentario no final do arquivo\n");
					} else
						errorSintax(&(*token), 10, '\0');
                } else
					errorSintax(&(*token), 1, '.');
			} else
				errorSintax(&(*token), 1, ';');
		} else
			errorSintax(&(*token), 9, '\0');
	} else
		errorSintax(&(*token), 8, '\0');
}

// bloco
void Analisa_Bloco(char *c, Token **token) {
	freeToken(&(*token));
	getToken(&(*c), &(*token));
	Analisa_et_variaveis(&(*c), &(*token)); // Saindo com o prox token lido
	Analisa_Subrotinas(&(*c), &(*token)); // Saindo com o prox lido
	Analisa_comandos(&(*c), &(*token));
}

// declaração de variáveis
void Analisa_et_variaveis(char *c, Token **token) {
	if (isEqualString((*token)->symbol, "svar")) {
		freeToken(&(*token));
		getToken(&(*c), &(*token));
		if (isEqualString((*token)->symbol, "sidentificador")) {
			while (isEqualString((*token)->symbol, "sidentificador")) {
				freeToken(&(*token));
				getToken(&(*c), &(*token));
				Analisa_Variaveis(&(*c), &(*token)); //Ja retorna com o prox lido
				if (isEqualString((*token)->symbol, "spontvirg")) {
					freeToken(&(*token));
					getToken(&(*c), &(*token));
				}else errorSintax(&(*token), 1,';');
			}
        } else errorSintax(&(*token), 11, '\0');
	}
}

// declaração de variáveis
void Analisa_Variaveis(char *c, Token **token) { //Verificar os FreeToken
	do {
		if (isEqualString((*token)->symbol, "sidentificador")) {
            // Pesquisa_duplicvar_tabela(token.lexema);
            // if (nao_encontrou_duplicidade() ) {
            	// insere_tabela(token.lexema, variavel ," "," ");
				freeToken(&(*token));
				getToken(&(*c), &(*token));
					if (isEqualString((*token)->symbol,"Svírgula") || isEqualString((*token)->symbol,"Sdoispontos")) {
						if (isEqualString((*token)->symbol, "Svírgula")) {
						    freeToken(&(*token));
						    getToken(&(*c), &(*token));
						    if (isEqualString((*token)->symbol,"Sdoispontos"))
								errorSintax(&(*token), 11, '\0');
						} else errorSintax(&(*token), 1, ',');
					} else errorSintax(&(*token), 12, '\0');
        	//}else errorSintax(&(*token),1,lineCount,'\0');
		} else errorSintax(&(*token), 11, '\0');

	} while (!isEqualString((*token)->symbol, "sdoispontos"));
	freeToken(&(*token));
	getToken(&(*c), &(*token));
	Analisa_Tipo(&(*c), &(*token));
}

// tipo
void Analisa_Tipo(char *c, Token **token) {
	if (isEqualString((*token)->symbol, "sinteiro") || isEqualString((*token)->symbol, "sbooleano")){
		//coloca_tipo_tabela(token.lexema);
		freeToken(&(*token));
		getToken(&(*c), &(*token));
	}else errorSintax(&(*token), 13, '\0');
}

// comandos
void Analisa_comandos(char *c, Token **token) {
	if (isEqualString((*token)->symbol, "sinicio")) {
		freeToken(&(*token));
		getToken(&(*c), &(*token));
		Analisa_comando_simples(&(*c), &(*token));
		while (!isEqualString((*token)->symbol, "sfim")) {
			if (isEqualString((*token)->symbol, "spontovirgula")) {
				freeToken(&(*token));
				getToken(&(*c), &(*token));
				if (!isEqualString((*token)->symbol, "sfim"))
					Analisa_comando_simples(&(*c), &(*token));
			} else errorSintax(&(*token), 1, ';');
		}
		getToken(&(*c), &(*token));
	} else errorSintax(&(*token), 16, '\0');
}

// comandos
void Analisa_comando_simples(char *c, Token **token) {
    if(isEqualString((*token)->symbol, "sidentificador"))
		Analisa_atrib_chprocedimento(&(*c), &(*token));
	else if(isEqualString((*token)->symbol, "sse"))
		Analisa_se(&(*c), &(*token));
	else if(isEqualString((*token)->symbol, "senquanto"))
		Analisa_enquanto(&(*c), &(*token));
	else if(isEqualString((*token)->symbol, "sleia"))
		Analisa_leia(&(*c), &(*token));
	else if(isEqualString((*token)->symbol, "sescreva"))
		Analisa_escreva(&(*c), &(*token));
	else
		Analisa_comandos(&(*c), &(*token));
}

// atribuição_chprocedimento
void Analisa_atrib_chprocedimento(char *c, Token **token) {
	freeToken(&(*token));
	getToken(&(*c), &(*token));
	if (isEqualString((*token)->symbol, "satribuicao"))
		Analisa_atribuicao(&(*c), &(*token));
	else
		Chamada_procedimento(&(*c), &(*token));
}

void Analisa_atribuicao(char *c, Token **token) {
	// Verificar chamada de função e identificador seguido de expressões aritméticas e/ou booleana, terminando por ;
}

void Chamada_procedimento(char *c, Token **token) {
	// Verifica identificador e ponto e virgula
}

void Analisa_chamada_funcao(char *c, Token **token) {
}

// Usado na Analisa_leia
void pesquisar_em_toda_a_tabela() {
}

// comando leitura
void Analisa_leia(char *c, Token **token) {
	freeToken(&(*token));
	getToken(&(*c), &(*token));
	if (isEqualString((*token)->symbol, "sabre_parenteses")) {
		freeToken(&(*token));
		getToken(&(*c), &(*token));
		if (isEqualString((*token)->symbol, "sidentificador")) {
            //if (pesquisa_declvar_tabela(token.lexema)) {
				//pesquisa_em_toda_a_tabela();
				freeToken(&(*token));
				getToken(&(*c), &(*token));
				if (isEqualString((*token)->symbol,"sfecha_parenteses")) {
					freeToken(&(*token));
					getToken(&(*c), &(*token));
				} else errorSintax(&(*token), 1, ')');
        	//}else errorSintax(&(*token),1,lineCount,'\0');
        } else errorSintax(&(*token), 11, '\0');
	} else errorSintax(&(*token), 1, '(');
}

// comando escrita
void Analisa_escreva(char *c, Token **token) {
	freeToken(&(*token));
	getToken(&(*c), &(*token));
	if (isEqualString((*token)->symbol, "sabre_parenteses")) {
		freeToken(&(*token));
		getToken(&(*c), &(*token));
		if (isEqualString((*token)->symbol, "sidentificador")) {
			// if (pesquisa_declvarfunc_tabela(token.lexema)) {
				freeToken(&(*token));
				getToken(&(*c), &(*token));
				if (isEqualString((*token)->symbol,"sfecha_parenteses")) {
					freeToken(&(*token));
					getToken(&(*c), &(*token));
				} else errorSintax(&(*token), 1, ')');
			//}else errorSintax(&(*token),1,lineCount,'\0');
		} else errorSintax(&(*token), 11, '\0');
	} else errorSintax(&(*token), 1, '(');
}

// comando repetição
void Analisa_enquanto(char *c, Token **token/*, int rotulo*/) {
    //int auxrot1 = rutulo,auxrot2;
    //Gera(rotulo,NULL,' ',' ')
    //while (Gera(auxrot2, NULL, auxrot1, ' ') == true) {
        //rotulo++;
		freeToken(&(*token));
		getToken(&(*c), &(*token));
		Analisa_expressao(&(*c), &(*token));
		if (isEqualString((*token)->symbol, "sfaca")) {
            //auxrot2 = rotulo;
            //if (Gera(' ', JMPF, rotulo, ' ') == true)
            	//rotulo = rotulo + 1;
			freeToken(&(*token));
			getToken(&(*c), &(*token));
			Analisa_comando_simples(&(*c), &(*token));
            // Gera(' ',JMP,auxrot1,' ')  {retorna início loop}
            // if(Gera(auxrot2,NULL,' ', ' ')  == false)
            //    exit;
		} else
			errorSintax(&(*token), 19, '\0');
    //}
}

// comando condicional
void Analisa_se(char *c, Token **token) {
	freeToken(&(*token));
	getToken(&(*c), &(*token));
	Analisa_expressao(&(*c), &(*token));
	if (isEqualString((*token)->symbol, "sentao")) {
		freeToken(&(*token));
		getToken(&(*c), &(*token));
		Analisa_comando_simples(&(*c), &(*token));
		if (isEqualString((*token)->symbol, "ssenao")) {
			freeToken(&(*token));
			getToken(&(*c), &(*token));
			Analisa_comando_simples(&(*c), &(*token));
		}
	} else
		errorSintax(&(*token), 18, '\0');
}

// etapa de declaração de sub-rotinas
void Analisa_Subrotinas(char *c, Token **token/*, int rotulo*/) {
	//int auxrot, flag = 0;
	//if (isEqualString((*token)->symbol, "sprocedimento") || isEqualString((*token)->symbol, "sfuncao")) {
		//auxrot = rotulo;
		//if (GERA(' ', JMP, rotulo, ' ') == true)
			//exit;
		//rotulo++;
		//flag = 1;
	//} else errorSintax(&(*token),1,lineCount,'\0');

	while (isEqualString((*token)->symbol, "sprocedimento") || isEqualString((*token)->symbol, "sfuncao")) {
		if (isEqualString((*token)->symbol, "sprocedimento"))
			Analisa_declaracao_procedimento(c, &(*token));
		else
			Analisa_declaracao_funcao(c, &(*token));
		if (isEqualString((*token)->symbol, "sponto-virgula")) {
			freeToken(&(*token));
			getToken(&(*c), &(*token));
		}else
		errorSintax(&(*token), 1, ';');
	}
	//if (flag = 1)
		//if (Gera(auxrot, NULL, ' ', ' ') == true)
			//inicio_principal();
}

// declaração de procedimento
void Analisa_declaracao_procedimento(char *c, Token **token) {
	freeToken(&(*token));
	getToken(&(*c), &(*token));
	//nivel = "L" // marca ou novo galho
	if (isEqualString((*token)->symbol, "sidentificador")) {
		//pesquisa_declproc_tabela(token.lexema);
		//if (nao_encontrou();) {
			//Insere_tabela(token.lexema, "procedimento", nivel, rotulo); // guarda na TabSimb
			//Gera(rotulo, NULL, ' ', ' ');								// CALL irá buscar este rotulo na TabSimb}
			//rotulo++;
				freeToken(&(*token));
				getToken(&(*c), &(*token));
				if (isEqualString((*token)->symbol, "sponto_virgula"))
					Analisa_Bloco(&(*c), &(*token));
				else errorSintax(&(*token), 1, ';');
		//} else errorSintax(&(*token),1,lineCount,'\0');
	} else errorSintax(&(*token), 14, '\0');
// DESEMPILHA OU VOLTA NÍVEL();
}

// declaração de função
void Analisa_declaracao_funcao(char *c, Token **token) {
	freeToken(&(*token));
	getToken(&(*c), &(*token));
	//nivel = "L" // marca ou novo galho
	if (isEqualString((*token)->symbol, "sidentificador")) {
		//pesquisa_declfunc_tabela(token.lexema);
		//if (nao_encontrou();) {
			//Insere_tabela(token.lexema, " ", nivel, rotulo);
			freeToken(&(*token));
			getToken(&(*c), &(*token));
			if (isEqualString((*token)->symbol, "sdoispontos")) {
				freeToken(&(*token));
				getToken(&(*c), &(*token));
				if (isEqualString((*token)->symbol, "Sinteiro") || isEqualString((*token)->symbol, "Sbooleano")){
					//if (isEqualString((*token)->symbol, "Sinteger"))
						//TABSIMB[pc].tipo = "funcao inteiro";
					//else
						//TABSIMB[pc].tipo = "funcao booleana";
					freeToken(&(*token));
					getToken(&(*c), &(*token));
					if (isEqualString((*token)->symbol, "sponto_virgula"))
						Analisa_Bloco(&(*c), &(*token));
					else
						errorSintax(&(*token), 1, ';');
				} else
					errorSintax(&(*token), 13, '\0');
			} else
				errorSintax(&(*token), 1, ':');
		//} else
			//errorSintax(&(*token),1,'\0');
	} else errorSintax(&(*token), 15, '\0');
// DESEMPILHA OU VOLTA NÍVEL();
}

// expressão
void Analisa_expressao(char *c, Token **token) {
	Analisa_expressao_simples(&(*c), &(*token));
	if (verificaSimboloRelacional(*token)) {
		freeToken(&(*token));
		getToken(&(*c), &(*token));
		Analisa_expressao_simples(&(*c), &(*token));
	}
}

// expressão simples
void Analisa_expressao_simples(char *c, Token **token) {
	if (isEqualString((*token)->symbol,"smais") || isEqualString((*token)->symbol,"smenos"))
		freeToken(&(*token));
		getToken(&(*c), &(*token));
	Analisa_termo(&(*c), &(*token));
	while (isEqualString((*token)->symbol,"smais") || isEqualString((*token)->symbol,"smenos") || isEqualString((*token)->symbol,"sou")) {
		freeToken(&(*token));
		getToken(&(*c), &(*token));
		Analisa_termo(&(*c), &(*token));
	}
}

// termo
void Analisa_termo(char *c, Token **token) {
	Analisa_fator(&(*c), &(*token));
	while (isEqualString((*token)->symbol, "smult") || isEqualString((*token)->symbol, "sdiv") || isEqualString((*token)->symbol, "se")) {
		freeToken(&(*token));
		getToken(&(*c), &(*token));
		Analisa_fator(&(*c), &(*token));
	}
}

// fator
void Analisa_fator(char *c, Token **token) {
    if (isEqualString((*token)->symbol,"sidentificador")) { // Variável ou Função
		//if (pesquisa_tabela(token.lexema, nível, ind)) {
			//if (TabSimb[ind].tipo = "função inteiro" || TabSimb[ind].tipo = "função booleano")
        		Analisa_chamada_funcao(&(*c), &(*token));
			//else getToken(token);
		//} else errorSintax(&(*token),1,lineCount,'\0');
	} else if (isEqualString((*token)->symbol,"snumero")) { // Número
		freeToken(&(*token));
		getToken(&(*c), &(*token));
	} else if (isEqualString((*token)->symbol,"snao")) { // NAO
		freeToken(&(*token));
		getToken(&(*c), &(*token));
		Analisa_fator(&(*c), &(*token));
	} else if (isEqualString((*token)->symbol,"sabre_parenteses")) { // expressão entre parenteses
		freeToken(&(*token));
		getToken(&(*c), &(*token));
		Analisa_expressao(&(*c), &(*token));
		if (isEqualString((*token)->symbol,"sfecha_parenteses")){
			freeToken(&(*token));
			getToken(&(*c), &(*token));
		} else
			errorSintax(&(*token), 1, ')');
	} else if (isEqualString((*token)->symbol, "sverdadeiro") || isEqualString((*token)->symbol, "sfalso")){
		freeToken(&(*token));
		getToken(&(*c), &(*token));
	} else
		errorSintax(&(*token), 17, '\0');
}