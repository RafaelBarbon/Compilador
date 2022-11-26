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
#include "codeGeneration.h"

// Treat errors, files and structures
void errorSintax(Token **token, int errorCode, char symbol,Ui::MainWindow *ui) {
	freeToken(token);
	detectError(errorCode,lineCount, symbol,ui);
	fclose(sourceFile);
	fclose(outputCode);
	exit(1);
}

// Verify if the symbol is relational
bool verifyRelationalSymbol(Token *token) {
	return isEqualString(token->symbol, "smaior") || isEqualString(token->symbol, "smaiorig") ||
		   isEqualString(token->symbol, "sig") || isEqualString(token->symbol, "smenor") ||
		   isEqualString(token->symbol, "smenorig") || isEqualString(token->symbol, "sdif");
}

// Calls lexic to get a new token in source file
void getNewToken(char *c, Token **token, Symbol *symbolList, ExpressionAnalyzer **InFix,Ui::MainWindow *ui) {
	freeToken(token);
	getToken(c, token);
	if(insertArray) { // Store the expression to be analyze later
		// If is an identifier, search on symbol table to get the type
		if(isEqualString((*token)->symbol, "sidentificador")){
			SymbolType type = searchVarFuncType(symbolList, (*token)->lexeme);
			switch(type) {
				case FuncBooleana:
					insertInFix(InFix, (*token)->lexeme, FuncBool);
					break;
				case FuncInteira:
					insertInFix(InFix, (*token)->lexeme, FuncInt);
					break;
				case VarInteira:
					insertInFix(InFix, (*token)->lexeme, VarInt);
					break;
				case VarBooleana:
					insertInFix(InFix, (*token)->lexeme, VarBool);
					break;
				default:
					break;
			}
		} else if(verifyRelationalSymbol((*token)))
			insertInFix(InFix, (*token)->lexeme, Rel);
		else if(isEqualString((*token)->symbol, "smais") || isEqualString((*token)->symbol, "smenos"))
			insertInFix(InFix, (*token)->lexeme, OpMaisMenos);
		else if(isEqualString((*token)->symbol, "smult") || isEqualString((*token)->symbol, "sdiv"))
			insertInFix(InFix, (*token)->lexeme, OpMultDiv);
		else if(isEqualString((*token)->symbol, "snumero"))
			insertInFix(InFix, (*token)->lexeme, Inteiro);
		else if(isEqualString((*token)->symbol, "snao"))
			insertInFix(InFix, (*token)->lexeme, Nao);
		else if(isEqualString((*token)->symbol, "se"))
			insertInFix(InFix, (*token)->lexeme, E);
		else if(isEqualString((*token)->symbol, "sou"))
			insertInFix(InFix, (*token)->lexeme, OU);
		else if(isEqualString((*token)->symbol, "sabre_parenteses"))
			insertInFix(InFix, (*token)->lexeme, AbreP);
		else if(isEqualString((*token)->symbol, "sfecha_parenteses"))
			insertInFix(InFix, (*token)->lexeme, FechaP);
		else if(isEqualString((*token)->symbol, "sverdadeiro"))
			insertInFix(InFix, (*token)->lexeme, Booleano);
		else if(isEqualString((*token)->symbol, "sfalso"))
			insertInFix(InFix, (*token)->lexeme, Booleano);
	}
}

// Analyze if the expression matches with the expected type
void analyzeExpressionType(ExpressionAnalyzer **expression, LexemeType expectedType,Ui::MainWindow *ui) {
	ExpressionAnalyzer *exp = (*expression), Op1, Op2, ant;
	bool FirstNao = false;
	simpleStack *stack = NULL;
	ExpressionAnalyzer *typeResult = (ExpressionAnalyzer *)malloc(sizeof(ExpressionAnalyzer));
	strcpy(typeResult->lexeme, "RESULT");

	while(exp != NULL) {
		if(exp->type == OpMultDiv || exp->type == OpMaisMenos){
			//Colect two elements of the stack and verify the if they are integers, if so an element with integer type is inserted in the stack
			Op1 = pop(&stack);
			Op2 = pop(&stack);
			if((Op1.type == Inteiro || Op1.type == FuncInt) && (Op2.type == Inteiro || Op2.type == FuncInt)){
				typeResult->type = Inteiro;
				push(&stack, typeResult);
			}else{
				detectError(27, lineCount,'\0',ui);
				free(typeResult);
				return;
			}
		} else if(exp->type == E || exp->type == OU) {
			//Colect two elements of the stack and verify the if they are boolean, if so an element with boolean type is inserted in the stack
			Op1 = pop(&stack);
			Op2 = pop(&stack);

			if((Op1.type ==  Booleano || Op1.type == FuncBool) && (Op2.type == Booleano || Op2.type == FuncBool)){
				typeResult->type = Booleano;
				push(&stack, typeResult);
			}else{
				detectError(27, lineCount,'\0',ui);
				free(typeResult);
				return;
			}
		} else if(exp->type == UnarioN || exp->type == UnarioP || exp->type == Nao) {
			if(exp->next != NULL) {
				ant = pop(&stack);
				if(exp->type == Nao){ //If is "Nao" colect the next operator of the stack and verify if is Boolean, if so an element with boolean type is inserted in the stack
					if(ant.type == Booleano || ant.type == FuncBool) {
						typeResult->type = Booleano;
						push(&stack, typeResult);
					} else {
						detectError(27, lineCount,'\0',ui);
						free(typeResult);
						//printf("\nTBool_Type: %s" ,ant.lexeme);
						return;
					}
				} else if(ant.type == Inteiro || ant.type == FuncInt) { //If is Unary operator, colect the next operator of the stack and verify if is Integer, if so an elemente with integer type is inserted in the stack
					typeResult->type = Inteiro;
					push(&stack, typeResult);
				} else {
					detectError(27, lineCount,'\0',ui);
					free(typeResult);
					return;
				}
			}
		}else if(exp->type == Rel){ //Relational, it can be integer or boolean
			// Colect two elements of the stack and verify the relational operation can be done, if so an element with boolean type is inserted in the stack
			Op1 = pop(&stack);
			Op2 = pop(&stack);

			if(((Op1.type == Inteiro ||  Op1.type == FuncInt) && (Op2.type == Inteiro || Op2.type == FuncInt)) || ((Op1.type == Booleano ||  Op1.type == FuncBool) && (Op2.type == Booleano || Op2.type == FuncBool))){
				typeResult->type = Booleano;
				push(&stack, typeResult);
			}else{
				detectError(27, lineCount,'\0',ui);
				free(typeResult);
				//printf("\nT1_Type: %d   -   T2_Type: %d", Op1.type, Op2.type);
				return;
			}
		}else {
			//Variable or constant, insert in the stack
			push(&stack, exp);
		}
		exp = exp->next;
	}
	// At the end, the stack must contain an element with the result rype of the expression.
	Op1 = pop(&stack);
	if(stack != NULL){// If the stack is not empty, there are still operators in the stack, so the expression is work and cannot be accepted
		detectError(27, lineCount,'\0',ui);
		freeSimpleStack(&stack);
	}else if(Op1.type != expectedType){
		printf("DEBUG - Semantico - Type %d - Expected %d\n", Op1.type,  expectedType);
		detectError(17, lineCount,'\0',ui);
	}

	free(typeResult);
	if(debug)
		printf("DEBUG - Semantico - Type %d - Expected %d\n", Op1.type,  expectedType);
}

//Responsible for convert the expression to POS_FIX, verify if the expression is correct and generate the assembly code for the expression
void semanticAnalyzer(ExpressionAnalyzer **inFix, LexemeType type, Symbol *symbol,Ui::MainWindow *ui) {
	ExpressionAnalyzer *posFix = NULL;
	ExpressionAnalyzer *analyze = NULL;
	if(debug)
		printExpression(*inFix, "IN_FIX", false);
	convertPosFix(inFix, &posFix);
	if(debug){
		printExpression(posFix, "POS_FIX", false);
		printExpression(posFix, "TYPE_POSFIX", true);
	}
	copyExpression(&analyze, posFix);
	if(debug)
		printExpression(analyze, "COPY_POS_FIX", false);
	analyzeExpressionType(&analyze, type,ui);

	generateExpressionCode(posFix, symbol,ui);

	freeExpression(inFix);
	freeExpression(&posFix);
	freeExpression(&analyze);
}

//Starts the compilation of the code
void syntacticAnalyzer(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	getNewToken(c, token, *symbol, inFix,ui);
	if (isEqualString((*token)->symbol, "sprograma")) {
		getNewToken(c, token, *symbol, inFix,ui);
		if (isEqualString((*token)->symbol, "sidentificador")) {
            insertSymbol(symbol, (*token)->lexeme, false, Programa, 0);
			generateAssembly("START   ", label, 0,ui);
			getNewToken(c, token, *symbol, inFix,ui);
			if (isEqualString((*token)->symbol, "sponto_virgula")) {
				generateAssembly("ALLOC   ", 1, address++,ui);
				analyzeBlock(c, token, symbol, inFix);
				generateAssembly("DALLOC  ", address, 0,ui);
				if (isEqualString((*token)->symbol, "sponto")) {
					if (!isNotEndOfFile(*c) || checkComment(c,ui) || checkSpaces(c)) {
						if(debug)
                            printf("\nDEBUG - Sintatico - Analisando comentario no final do arquivo\n");
						generateAssembly("HLT     ", label, 0,ui);
					} else
						errorSintax(token, 10, '\0',ui);
                } else
					errorSintax(token, 1, '.',ui);
			} else
				errorSintax(token, 1, ';',ui);
		} else
			errorSintax(token, 9, '\0',ui);
	} else
		errorSintax(token, 8, '\0',ui);
}

//Analyze a block of program
void analyzeBlock(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa bloco\n");
	int FirstAdres = address;
	getNewToken(c, token, *symbol, inFix,ui);
	analyzeEtVariables(c, token, symbol,ui);
	analyzeSubroutines(c, token, symbol, inFix,ui);
	analyzeCommands(c, token, symbol, inFix,ui);
}

//Analyze the declarion of variables
void analyzeEtVariables(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa et variaveis\n");
	if (isEqualString((*token)->symbol, "svar")) {
		getNewToken(c, token, *symbol, NULL,ui);
		if (isEqualString((*token)->symbol, "sidentificador")) {
			while (isEqualString((*token)->symbol, "sidentificador")) {
				analyzeVariables(c, token, symbol,ui);
				if (isEqualString((*token)->symbol, "sponto_virgula"))
					getNewToken(c, token, *symbol, NULL,ui);
				else errorSintax(token, 1,';',ui);
			}
        } else
			errorSintax(token, 11, '\0',ui);
	}
}

//Also used to analyze the declarion of variables
void analyzeVariables(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa variaveis\n");
	int countVariable = 0;
	int initialAddress = address;
	do {
		countVariable++;
		if (isEqualString((*token)->symbol, "sidentificador")) {
            if (!searchDuplicity(*symbol, (*token)->lexeme)) {
            	insertSymbol(symbol, (*token)->lexeme, false, Var, address++);
				getNewToken(c, token, *symbol, NULL,ui);
				if (isEqualString((*token)->symbol,"svirgula") || isEqualString((*token)->symbol,"sdoispontos")) {
					if (isEqualString((*token)->symbol, "svirgula")) {
						getNewToken(c, token, *symbol, NULL,ui);
						if (isEqualString((*token)->symbol,"sdoispontos"))
							errorSintax(token, 11, '\0',ui);
					}
				} else errorSintax(token, 12, '\0',ui);
        	} else errorSintax(token,21,'\0',ui);
		} else errorSintax(token, 11, '\0',ui);
	} while (!isEqualString((*token)->symbol, "sdoispontos"));
	getNewToken(c, token, *symbol, NULL,ui);
	analyzeType(c, token, symbol,ui);
	//Generate the assembly code to allocate the variables
	if(countVariable > 0) {
		generateAssembly("ALLOC   ", countVariable, initialAddress,ui);
	}
}

//Analyze the type of the token and put it on the symbol table
void analyzeType(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa tipo\n");
	if (isEqualString((*token)->symbol, "sinteiro") || isEqualString((*token)->symbol, "sbooleano")){
		putType(symbol,isEqualString((*token)->symbol, "sinteiro") ? VarInteira : VarBooleana);
		getNewToken(c, token, *symbol, NULL,ui);
	} else errorSintax(token, 13, '\0',ui);
}

// Analyze the program commands
void analyzeCommands(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa comandos\n");
	if (isEqualString((*token)->symbol, "sinicio")) {
		getNewToken(c, token, *symbol, inFix,ui);
		analyzeSimpleCommand(c, token, symbol, inFix,ui);
		while (!isEqualString((*token)->symbol, "sfim")) {
			if (isEqualString((*token)->symbol, "sponto_virgula")) {
				getNewToken(c, token, *symbol, inFix,ui);
				if (!isEqualString((*token)->symbol, "sfim")) {
					analyzeSimpleCommand(c, token, symbol, inFix,ui);
				}
			} else errorSintax(token, 1, ';',ui);
		}
		getNewToken(c, token, *symbol, inFix,ui);
	} else errorSintax(token, 16, '\0',ui);
}

// Also used to analyze the program commands
void analyzeSimpleCommand(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa comando simples\n");
    if(isEqualString((*token)->symbol, "sidentificador"))
		analyzeAttributionProcedureCall(c, token, symbol, inFix,ui);
	else if(isEqualString((*token)->symbol, "sse"))
		analyzeConditional(c, token, symbol, inFix,ui);
	else if(isEqualString((*token)->symbol, "senquanto"))
		analyzeWhile(c, token, symbol, inFix,ui);
	else if(isEqualString((*token)->symbol, "sleia"))
		analyzeRead(c, token, symbol,ui);
	else if(isEqualString((*token)->symbol, "sescreva"))
		analyzeWrite(c, token, symbol,ui);
	else
		analyzeCommands(c, token, symbol, inFix,ui);
}

// Analyze an attribution or a procedure call
void analyzeAttributionProcedureCall(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa atribuicao chamada procedimento\n");
	char nameVarOrProcedure[maxIdentifierLength];
	strcpy(nameVarOrProcedure, (*token)->lexeme);
	getNewToken(c, token, *symbol, inFix,ui);
	if (isEqualString((*token)->symbol, "satribuicao")){
		analyzeAttribution(c, token, (*symbol), inFix, nameVarOrProcedure,ui);
		//printf("Teste %d", searchVarFuncAddress(*symbol, nameVarOrProcedure));
	}else
		procedureCall(c, token, nameVarOrProcedure, symbol,ui);
}

// Analyze attributions
void analyzeAttribution(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix, char *name,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa atribuicao\n");

	insertArray = true;
	getNewToken(c, token, symbol, inFix,ui); // Also adds in inFix to analyze later

	analyzeExpression(c, token, symbol, inFix,ui);

	insertArray = false;
	LexemeType type = getVarType(symbol, name,ui);
	if(type == Rel)
		errorSintax(token,28,'\0',ui);
	semanticAnalyzer(inFix, type, symbol,ui);
	type = isFunction(symbol, name);
	if(type != FuncInt && type != FuncBool) //Generate the assembly code to store the attribution in the destination variable address
		generateAssembly("STR     ", searchVarFuncAddress(symbol, name), 0,ui);
}

// Analyze a procedure call
void procedureCall(char *c, Token **token, char *nameProcedure, Symbol **symbol,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Chamada procedimento\n");

	if(isEqualString((*token)->symbol, "sponto_virgula") || isEqualString((*token)->symbol, "sfim") || isEqualString((*token)->symbol, "ssenao")) { //Can be called in the last command, or right after a conditional command with only one command and with 'senao'
		if(!verifyProcedureDeclaration((*symbol), nameProcedure))
			errorSintax(token, 25, '\0',ui);
		else
			generateAssembly("CALL    ", searchProcAddr(*symbol, nameProcedure), 0,ui);
	} else errorSintax(token, 20, '\0',ui);
}

// Analyze a function call
void analyzeFunctionCall(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa chamada funcao\n");
	getNewToken(c, token, symbol, inFix,ui); // Also adds in inFix to analyze later
}

// Analyze the read command
void analyzeRead(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa leia\n");
	int mem;
	getNewToken(c, token, NULL, NULL,ui);
	if (isEqualString((*token)->symbol, "sabre_parenteses")) {
		getNewToken(c, token, *symbol, NULL,ui);
		if (isEqualString((*token)->symbol, "sidentificador")) {
            if (verifyVarDeclaration(*symbol, (*token)->lexeme, &mem)){ // Verify if the variable is declared and if is visible in this scope
				getNewToken(c, token, *symbol, NULL,ui);
				if (isEqualString((*token)->symbol,"sfecha_parenteses"))
					getNewToken(c, token, *symbol, NULL,ui);
				else errorSintax(token, 1, ')',ui);
        	} else errorSintax(token,22,'\0',ui);
        } else errorSintax(token, 11, '\0',ui);
	} else errorSintax(token, 1, '(',ui);
	generateAssembly("RD      ", 0, 0,ui);
	generateAssembly("STR     ", mem, 0,ui);
}

// Analyze the write command
void analyzeWrite(char *c, Token **token, Symbol **symbol,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa escreva\n");
	int mem;
	getNewToken(c, token, *symbol, NULL,ui);
	if (isEqualString((*token)->symbol, "sabre_parenteses")) {
		getNewToken(c, token, NULL, NULL,ui);
		if (isEqualString((*token)->symbol, "sidentificador")) {
			if (verifyVarDeclaration(*symbol, (*token)->lexeme, &mem)){// Verify if the variable is declared and if is visible on that scope using the symbol table
				getNewToken(c, token, NULL, NULL,ui);
				if (isEqualString((*token)->symbol,"sfecha_parenteses")) {
					getNewToken(c, token, NULL, NULL,ui);
				} else errorSintax(token, 1, ')',ui);
			} else errorSintax(token,22,'\0',ui);
		} else errorSintax(token, 11, '\0',ui);
	} else errorSintax(token, 1, '(',ui);
	generateAssembly("LDV     ", mem, 0,ui);
	generateAssembly("PRN     ", 0, 0,ui);
}

// Analyze the while command
void analyzeWhile(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa enquanto\n");
    int auxrot1 = label++, auxrot2 = label++; //auxrot1 = the beginning of the While command on Assembly code || auxrot2 = after the while commands on Assembly code
	generateAssembly("NULL    ", auxrot1, 0,ui); //ROTULO DO WHILE;
	insertArray = true;
	getNewToken(c, token, *symbol, inFix,ui);
	analyzeExpression(c, token, (*symbol), inFix,ui);
	insertArray = false;
	semanticAnalyzer(inFix, Booleano, *symbol,ui);
	if (isEqualString((*token)->symbol, "sfaca")) {
		generateAssembly("JMPF    ", auxrot2, 0,ui);
		getNewToken(c, token, *symbol, inFix,ui);
		analyzeSimpleCommand(c, token, symbol, inFix,ui);
		generateAssembly("JMP     ", auxrot1, 0,ui); //JUMP to the beginning of the while commands to continue the LOOP
	} else
		errorSintax(token, 19, '\0',ui);
	generateAssembly("NULL    ", auxrot2, 0,ui);
}

// Analyze the conditional command
void analyzeConditional(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa Se\n");
	int auxrot1 = label++, auxrot2;
	insertArray = true;
	getNewToken(c, token, *symbol, inFix,ui);
	analyzeExpression(c, token, (*symbol), inFix,ui);
	insertArray = false;
	semanticAnalyzer(inFix, Booleano, *symbol,ui);
	generateAssembly("JMPF    ", auxrot1, 0,ui);
	if (isEqualString((*token)->symbol, "sentao")) {
		getNewToken(c, token, *symbol, inFix,ui);
		analyzeSimpleCommand(c, token, symbol, inFix,ui);
		if (isEqualString((*token)->symbol, "ssenao")) {
			auxrot2 = label++;
			generateAssembly("JMP     ", auxrot2, 0,ui);
		}
		generateAssembly("NULL    ", auxrot1, 0,ui);
		if (isEqualString((*token)->symbol, "ssenao")) {
			getNewToken(c, token, *symbol, inFix);
			analyzeSimpleCommand(c, token, symbol, inFix);
			generateAssembly("NULL    ", auxrot2, 0,ui);
		}
	} else
		errorSintax(token, 18, '\0',ui);
}

// Analyze declaration of subroutines
void analyzeSubroutines(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa Subrotina\n");
	bool flag = false;
	int auxLabel;
	if(isEqualString((*token)->symbol, "sprocedimento") || isEqualString((*token)->symbol, "sfuncao")){
		auxLabel = label;
		generateAssembly("JMP     ", label++, 0,ui);
		flag = true;
	}

	while (isEqualString((*token)->symbol, "sprocedimento") || isEqualString((*token)->symbol, "sfuncao")) {
		if (isEqualString((*token)->symbol, "sprocedimento"))
            analyzeProcedureDeclaration(c, token, symbol, inFix,ui);
		else
            analyzeFunctionDeclaration(c, token, symbol, inFix,ui);
		if (isEqualString((*token)->symbol, "sponto_virgula")) {
            getNewToken(c, token, *symbol, inFix,ui);
		}else
            errorSintax(token, 1, ';',ui);
	}

	if(flag)
        generateAssembly("NULL    ", auxLabel, 0,ui);
}

// Analyze procedure declarations
void analyzeProcedureDeclaration(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa declaracao procedimento\n");
    getNewToken(c, token, *symbol, inFix,ui);
    // int returnAddress = address;
	if (isEqualString((*token)->symbol, "sidentificador")) {
		if (!verifyProcedureFunctionDuplicity(*symbol, (*token)->lexeme)){ // Search if the procedure does not exists
			insertSymbol(symbol, (*token)->lexeme, true, Procedimento, label); // Store in the symbol table
			generateAssembly("NULL    ", label++, 0,ui); // CALL will retrieve this label in the symbol table
			getNewToken(c, token, *symbol, inFix,ui);
			if (isEqualString((*token)->symbol, "sponto_virgula"))
				analyzeBlock(c, token, symbol, inFix,ui);
			else
				errorSintax(token, 1, ';',ui);
		} else
			errorSintax(token, 26, '\0',ui);
	} else
		errorSintax(token, 14, '\0',ui);
	int countAddressToDalloc = unStack(symbol);
	if(countAddressToDalloc > 0){
		generateAssembly("DALLOC  ", countAddressToDalloc, address - countAddressToDalloc, ui);
		address -= countAddressToDalloc;
	}
	generateAssembly("RETURN  ", label, 0,ui);
}

// Function declaration
void analyzeFunctionDeclaration(char *c, Token **token, Symbol **symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa declaracao Funcao\n");
	getNewToken(c, token, *symbol, inFix,ui);
	if (isEqualString((*token)->symbol, "sidentificador")) {
		if (!verifyProcedureFunctionDuplicity(*symbol, (*token)->lexeme)) { // Verify if the function have not been declared
			insertSymbol(symbol, (*token)->lexeme, true, Func, label);
            getNewToken(c, token, *symbol, inFix,ui);
			if (isEqualString((*token)->symbol, "sdoispontos")) {
				getNewToken(c, token, *symbol, inFix,ui);
				if (isEqualString((*token)->symbol, "sinteiro") || isEqualString((*token)->symbol, "sbooleano")) { // Insert the right type
					putTypeFunc(symbol,isEqualString((*token)->symbol, "sinteiro") ? FuncInteira : FuncBooleana);
                    getNewToken(c, token, *symbol, inFix,ui);
					if (isEqualString((*token)->symbol, "sponto_virgula"))
						generateAssembly("NULL    ", label++, 0,ui); // CALL will retrieve this label in the symbol table
						analyzeBlock(c, token, symbol, inFix,ui); // Analyze the function body
				} else
					errorSintax(token, 13, '\0',ui);
			} else
				errorSintax(token, 1, ':',ui);
		} else
			errorSintax(token,23,'\0',ui);
	} else
		errorSintax(token, 15, '\0',ui);
	int countAddressToDalloc = unStack(symbol);
	generateAssembly("STR     ", 0, 0,ui); // Address 0 represents the function return value
	if(countAddressToDalloc > 0) {
		generateAssembly("DALLOC  ", countAddressToDalloc, address  - countAddressToDalloc,ui);
		address -= countAddressToDalloc;
	}
	generateAssembly("RETURNF ", label, 0,ui);
}

// Expression - Verify expression and possible relational operators
void analyzeExpression(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa Expressao\n");
	analyzeSimpleExpression(c, token, symbol, inFix,ui);
	if (verifyRelationalSymbol(*token)) {
		getNewToken(c, token, symbol, inFix,ui); // Also adds in inFix to analyze later
		analyzeSimpleExpression(c, token, symbol, inFix,ui);
	}
}

// Simple expression - Analyze the lower precedence of expressions
void analyzeSimpleExpression(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa Expressao Simples\n");
	if (isEqualString((*token)->symbol,"smais") || isEqualString((*token)->symbol,"smenos")){
		getNewToken(c, token, symbol, inFix,ui); // Also adds in inFix to analyze later
	}
	analyzeTerm(c, token, symbol, inFix,ui);
	while (isEqualString((*token)->symbol,"smais") || isEqualString((*token)->symbol,"smenos") || isEqualString((*token)->symbol,"sou")) {
		getNewToken(c, token, symbol, inFix,ui); // Also adds in inFix to analyze later
		analyzeTerm(c, token, symbol, inFix,ui);
	}
}

// Term - Analyze the higher precedence of the operations
void analyzeTerm(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
	if(debug)
        printf("\nDEBUG - Sintatico - Analisa termo\n");
	analyzeFactor(c, token, symbol, inFix,ui);
	while (isEqualString((*token)->symbol, "smult") || isEqualString((*token)->symbol, "sdiv") || isEqualString((*token)->symbol, "se")) {
		getNewToken(c, token, symbol, inFix,ui); // Also adds in inFix to analyze later
		analyzeFactor(c, token, symbol, inFix,ui);
	}
}

// Factor - used to extract each token of an expression
void analyzeFactor(char *c, Token **token, Symbol *symbol, ExpressionAnalyzer **inFix,Ui::MainWindow *ui) {
    if(debug)
		printf("\nDEBUG - Sintatico - Analisa Fator\n");
    if (isEqualString((*token)->symbol,"sidentificador")) { // Variable or Function
		if (verifyVarFuncDeclaration(symbol,  (*token)->lexeme)) { // Collects the corresponding identifier to verify it's type
			if (verifyFunctionDeclaration(symbol, (*token)->lexeme))
				analyzeFunctionCall(c, token, symbol, inFix,ui);
			else
				getNewToken(c, token, symbol, inFix,ui); // Also adds in inFix to analyze later
		} else errorSintax(token,24,'\0',ui);
	} else if (isEqualString((*token)->symbol,"snumero")) {
		getNewToken(c, token, symbol, inFix,ui); // Also adds in inFix to analyze later
	} else if (isEqualString((*token)->symbol,"snao")) {
		getNewToken(c, token, symbol, inFix,ui); // Also adds in inFix to analyze later
		analyzeFactor(c, token, symbol, inFix,ui);
	} else if (isEqualString((*token)->symbol,"sabre_parenteses")) {
		getNewToken(c, token, symbol, inFix,ui); // Also adds in inFix to analyze later
		analyzeExpression(c, token, symbol, inFix,ui);
		if (isEqualString((*token)->symbol,"sfecha_parenteses")){
			getNewToken(c, token, symbol, inFix,ui); // Also adds in inFix to analyze later
		} else
			errorSintax(token, 1, ')',ui);
	} else if (isEqualString((*token)->symbol, "sverdadeiro") || isEqualString((*token)->symbol, "sfalso")){
		getNewToken(c, token, symbol, inFix,ui); // Also adds in inFix to analyze later
	} else {
		errorSintax(token, 17, '\0',ui);
	}
}
