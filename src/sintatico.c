// programa

// l->lexeme, l->symbol

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

void analisadorSintatico(char *c, Token **token) {
    //int rotulo = 1;
	getToken(c, &(*token));
	if (isEqualString((*token)->symbol, "sprograma")) {
		freeToken(&(*token));
		getToken(token);
		if (isEqualString((*token)->symbol, "sidentificador")) {
            //insere_tabela(token.lexema,"nomedeprograma"," "," ");
			freeToken(&(*token));
			getToken(token);
			if (isEqualString((*token)->symbol, "spontovirgula")) {
				freeToken(&(*token));
				analisaBloco(c, token);
				if (isEqualString((*token)->symbol, "sponto")) {
					if (isNotEndOfFile(*c) || checkComment(*c))
						if(debug)
                            printf("\nDEBUG - Analisando comentario no final do arquivo\n");
					else
						detectError(5,lineCount,NULL);
                } else
					detectError(1,lineCount,'\0');
			} else
				detectError(1,lineCount,'\0');
		} else
			detectError(2,lineCount,NULL);
	} else
		detectError(7,lineCount,NULL);
}

// bloco
void analisaBloco(char *c, Token **token) {
	getToken(c, &(*token));
	Analisa_et_variaveis(c, token);
	Analisa_subrotinas(c, token);
	Analisa_comandos(c, token);
}

// declaração de variáveis
void Analisa_et_variaveis(char *c, Token **token) {
	if (isEqualString((*token)->symbol, "svar")) {
		freeToken(&(*token));
		getToken(c, &(*token));
		if (isEqualString((*token)->symbol, "sidentificador")) {
			while (isEqualString((*token)->symbol, "sidentificador")) {
				// analisaVariaveis(c, token);
				if (isEqualString((*token)->symbol, "spontvirg")) {
					freeToken(&(*token));
					getToken(c, &(*token));
				}else{
					freeToken(&(*token));
					detectError(1,lineCount,'\0');
				}
			}
        } else{
			freeToken(&(*token));
			detectError(1,lineCount,'\0');
		}
	}
	else{
		freeToken(&(*token));
		detectError(1,lineCount,'\0');
	}
}

// declaração de variáveis
void analisaVariaveis(char *c, Token **token) { //Verificar os FreeToken
	do {
		if (isEqualString((*token)->symbol, "sidentificador")) {
            // Pesquisa_duplicvar_tabela(token.lexema);
            // if (nao_encontrou_duplicidade() ) {
            // insere_tabela(token.lexema, variavel ," "," ");
			freeToken(&(*token));
			getToken(c, &(*token));
			if (isEqualString((*token)->symbol,"Svírgula") || isEqualString((*token)->symbol,"Sdoispontos"))
			if ((*token)->symbol = "Svírgula") {
			    freeToken(&(*token));
			    getToken(c, &(*token));
			    if (isEqualString((*token)->symbol,"Sdoispontos"))
			        detectError(1,lineCount,'\0');
			}else detectError(1,lineCount,'\0');
		else detectError(1,lineCount,'\0');
        //}else detectError(1,lineCount,'\0');
		} else{
			freeToken(&(*token));
			detectError(1,lineCount,'\0');
		}
	} while (!isEqualString((*token)->symbol, "sdoispontos"));
	getToken(c, &(*token));
	Analisa_Tipo(c, token);
}

// tipo
void Analisa_Tipo(char *c, Token **token) {
	if (!isEqualString((*token)->symbol, "sinteiro") && isEqualString((*token)->symbol, "sbooleano")) {
		freeToken(&(*token));
		detectError(1,lineCount,'\0');
	} else
        //coloca_tipo_tabela(token.lexema);
		getToken(c, &(*token));
}

// comandos
void Analisa_comandos(char *c, Token **token) {
	if (isEqualString((*token)->symbol, "sinicio")) {
		freeToken(&(*token));
		getToken(c, &(*token));
		Analisa_comando_simples();
		while (!isEqualString((*token)->symbol, "sfim")) {
			if (isEqualString((*token)->symbol, "spontovirgula")) {
				freeToken(&(*token));
				getToken(c, &(*token));
				if (!isEqualString((*token)->symbol, "sfim"))
					Analisa_comando_simples();
			} else{
				freeToken(&(*token));
				detectError(1,lineCount,'\0');
			}
		}
		getToken(c, &(*token));
	} else
		detectError(1,lineCount,'\0');
}

// comandos
void Analisa_comando_simples(char *c, Token **token) {
    if(isEqualString((*token)->symbol, "sidentificador"))
		Analisa_atrib_chprocedimento(c, token);
	else if(isEqualString((*token)->symbol, "sse"))
		Analisa_se(c, token);
	else if(isEqualString((*token)->symbol, "senquanto"))
		Analisa_enquanto(c, token);
	else if(isEqualString((*token)->symbol, "sleia"))
		Analisa_leia(c, token);
	else if(isEqualString((*token)->symbol, "sescreva"))
		Analisa_escreva(c, token);
	else
		Analisa_comandos(c, token);
}

// atribuição_chprocedimento
void Analisa_atrib_chprocedimento(char *c, Token **token) {
	freeToken(&(*token));
	getToken(c, &(*token));
	if (isEqualString((*token)->symbol, "satribuicao"))
		Analisa_atribuicao();
	else
		Chamada_procedimento();
}

// Usado na Analisa_leia
void pesquisar_em_toda_a_tabela() {
}

// comando leitura
void Analisa_leia(char *c, Token **token) {
	freeToken(&(*token));
	getToken(c, &(*token));
	if (isEqualString((*token)->symbol, "sabre_parenteses")) {
		freeToken(&(*token));
		getToken(c, &(*token));
		if (isEqualString((*token)->symbol, "sidentificador")) {
            //if (pesquisa_declvar_tabela(token.lexema)) {
            //pesquisa_em_toda_a_tabela();
			freeToken(&(*token));	
			getToken(c, &(*token));
			if (isEqualString((*token)->symbol,"sfecha_parenteses")) {
				freeToken(&(*token));
			    getToken(c, &(*token));
			} else detectError(1,lineCount,'\0');

        //}else detectError(1,lineCount,'\0');
        } else detectError(1,lineCount,'\0');
	} else
		detectError(1,lineCount,'\0');
}

// comando escrita
void Analisa_escreva(char *c, Token **token) {
	freeToken(&(*token));
	getToken(c, &(*token));
	if (isEqualString((*token)->symbol, "sabre_parenteses")) {
		freeToken(&(*token));
		getToken(c, &(*token));
		if (isEqualString((*token)->symbol, "sidentificador")) {
// if (pesquisa_declvarfunc_tabela(token.lexema)) {
			freeToken(&(*token));
			getToken(c, &(*token));
			if (isEqualString((*token)->symbol,"sfecha_parenteses")) {
				freeToken(&(*token));
				getToken(c, &(*token));
			}else detectError(1,lineCount,'\0');
//}else detectError(1,lineCount,'\0');
			} else detectError(1,lineCount,'\0');
	}
	else
		detectError(1,lineCount,'\0');
}

// comando repetição
void Analisa_enquanto(char *c, Token **token, int rotulo) {
    //int auxrot1 = rutulo,auxrot2;
    //Gera(rotulo,NULL,' ',' ')
    //while (Gera(auxrot2, NULL, auxrot1, ' ') == true) {
        //rotulo++;
		freeToken(&(*token));
		getToken(c, &(*token));
		Analisa_expressao(token);
		if (isEqualString((*token)->symbol, "sfaca")) {
            //auxrot2 = rotulo;
            //if (Gera(' ', JMPF, rotulo, ' ') == true)
            //rotulo = rotulo + 1;
			freeToken(&(*token));
			getToken(c, &(*token));
			Analisa_comando_simples(c, token);
            // Gera(' ',JMP,auxrot1,' ')  {retorna início loop}
            // if(Gera(auxrot2,NULL,' ', ' ')  == false)
            //    exit;
		} else
			detectError(1,lineCount,'\0');
    //}
}

// comando condicional
void Analisa_se(char *c, Token **token) {
	freeToken(&(*token));
	getToken(c, &(*token));
	Analisa_expressao(token);
	if (isEqualString((*token)->symbol, "sentao")) {
		freeToken(&(*token));
		getToken(c, &(*token));
		Analisa_comando_simples(c, token);
		if (isEqualString((*token)->symbol, "Ssenao")) {
			freeToken(&(*token));
			getToken(c, &(*token));
			Analisa_comando_simples(c, token);
		} else
			detectError(1,lineCount,'\0');
	} else
		detectError(1,lineCount,'\0');
}

// etapa de declaração de sub-rotinas
void Analisa_Subrotinas(char *c, Token **token) {
//int auxrot, flag = 0;
//if (isEqualString((*token)->symbol, "sprocedimento") || isEqualString((*token)->symbol, "sfuncao")) {
//auxrot = rotulo;
//if (GERA(' ', JMP, rotulo, ' ') == true)
//exit;
//rotulo++;
//flag = 1;
//} else
//detectError(1,lineCount,'\0');

	while (isEqualString((*token)->symbol, "sprocedimento") || isEqualString((*token)->symbol, "sfuncao")) {
		if (isEqualString((*token)->symbol, "sprocedimento"))
			analisa_declaracao_procedimento(c, token);
		else
			analisa_declaracao_funcao(c, token);

		if (isEqualString((*token)->symbol, "sponto-virgula")) {
			freeToken(&(*token));
			getToken(c, &(*token));
		}else
			detectError(1,lineCount,'\0');
	}
//if (flag = 1)
//if (Gera(auxrot, NULL, ' ', ' ') == true)
//inicio_principal();
}

// declaração de procedimento
void Analisa_declaracao_procedimento(char *c, Token **token) {
	freeToken(&(*token));
	getToken(c, &(*token));
//nivel = "L" // marca ou novo galho
		if (isEqualString((*token)->symbol, "sidentificador")) {
//pesquisa_declproc_tabela(token.lexema);
//if (nao_encontrou();) {
//Insere_tabela(token.lexema, "procedimento", nivel, rotulo); // guarda na TabSimb
//Gera(rotulo, NULL, ' ', ' ');								// CALL irá buscar este rotulo na TabSimb}
//rotulo++;
			freeToken(&(*token));
			getToken(c, &(*token));
			if (isEqualString((*token)->symbol, "sponto_virgula"))
				Analisa_bloco();
			else
				detectError(1,lineCount,'\0');
//} else
//detectError(1,lineCount,'\0');
	} else detectError(1,lineCount,'\0');
// DESEMPILHA OU VOLTA NÍVEL();
}

// declaração de função
void Analisa_declaracao_funcao(char *c, Token **token) {
	freeToken(&(*token));
	getToken(c, &(*token));
//nivel = "L" // marca ou novo galho
		if (isEqualString((*token)->symbol, "sidentificador")) {
//pesquisa_declfunc_tabela(token.lexema);
//if (nao_encontrou();) {
//Insere_tabela(token.lexema, " ", nivel, rotulo);
			freeToken(&(*token));
			getToken(c, &(*token));
			if (isEqualString((*token)->symbol, "sdoispontos")) {
				freeToken(&(*token));
				getToken(c, &(*token));
				if (isEqualString((*token)->symbol, "Sinteiro") || isEqualString((*token)->symbol, "Sbooleano")) {
//if (isEqualString((*token)->symbol, "Sinteger"))
//TABSIMB[pc].tipo = "funcao inteiro";
//else
//TABSIMB[pc].tipo = "funcao booleana";
					freeToken(&(*token));
					getToken(c, &(*token));
					if (isEqualString((*token)->symbol, "sponto_virgula"))
						Analisa_bloco();
					else
						detectError(1,lineCount,'\0');
				} else
					detectError(1,lineCount,'\0');
			} else
				detectError(1,lineCount,'\0');
//} else
			detectError(1,lineCount,'\0');
	} else detectError(1,lineCount,'\0');
// DESEMPILHA OU VOLTA NÍVEL();
}

// expressão
void Analisa_expressao(char *c, Token **token) {
	Analisa_expressao_simples(c, token);
	if (analisaExpressaoRelacional(token)) {
		freeToken(&(*token));
		getToken(c, &(*token));
		Analisa_expressao_simples();
	} // else detectError(1,lineCount,'\0');
}

// expressão simples
void Analisa_expressao_simples(char *c, Token **token) {
	if (isEqualString((*token)->symbol,"smais") || isEqualString((*token)->symbol,"smenos"))
		freeToken(&(*token));
		getToken(c, &(*token));
	Analisa_termo();
	while (isEqualString((*token)->symbol,"smais") || isEqualString((*token)->symbol,"smenos") || isEqualString((*token)->symbol,"sou")) {
		freeToken(&(*token));
		getToken(c, &(*token));
		Analisa_termo(c, token);
	}
}

// termo
void Analisa_termo(char *c, Token **token) {
	Analisa_fator(c, token);
	while (isEqualString((*token)->symbol, "smult") || isEqualString((*token)->symbol, "sdiv") || isEqualString((*token)->symbol, "se")) {
		freeToken(&(*token));
		getToken(c, &(*token));
		Analisa_fator(c, token);
	}
}

// fator
void Analisa_fator(char *c, Token **token) {
    if (isEqualString((*token)->symbol,"sidentificador")) { // Variável ou Função
//if (pesquisa_tabela(token.lexema, nível, ind)) {
//if (TabSimb[ind].tipo = "função inteiro" || TabSimb[ind].tipo = "função booleano") 
        Analisa_chamada_funcao(c, token);  
//else getToken(token);
//} else detectError(1,lineCount,'\0');
	}
	else if (isEqualString((*token)->symbol,"snumero")) { // Número
		freeToken(&(*token));
		getToken(c, &(*token));
	}else if (isEqualString((*token)->symbol,"snao")) { // NAO
		freeToken(&(*token));
		getToken(c, &(*token));
		Analisa_fator(c, token);
	}
	else if (isEqualString((*token)->symbol,"sabre_parenteses")) { // expressão entre parenteses
		freeToken(&(*token));
		getToken(c, &(*token));
		Analisa_expressao(token);
		if (isEqualString((*token)->symbol,"sfecha_parenteses")){
			freeToken(&(*token));
			getToken(c, &(*token));
		}else
			detectError(1,lineCount,'\0');
	}
	else if ((*token)->symbol = true || (*token)->symbol = false){
		freeToken(&(*token));
		getToken(c, &(*token));
	}else
		detectError(1,lineCount,'\0');
}

bool analisaExpressaoRelacional(Token *token) {
	return isEqualString((*token)->symbol, "smaior") || isEqualString((*token)->symbol, "smaiorig") ||
		   isEqualString((*token)->symbol, "sig") || isEqualString((*token)->symbol, "smenor") ||
		   isEqualString((*token)->symbol, "smenorig") || isEqualString((*token)->symbol, "sdif");
}

