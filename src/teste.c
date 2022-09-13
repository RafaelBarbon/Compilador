/*void Analisador_Sintatico(){
//Def rotulo inteiro 
   //rotulo:= 1 
   lexico(Token **l ); 
   switch(token.simbolo){
        case sprograma:
        lexico(Token **l ); 
        return 1;
        break;

        case sidentificador:
        lexico(Token **l ); 
        break;

        case spontovirgula:
        analisa_bloco();
        break;

        case sponto:
        if( acabou arquivo ou é comentário)
            //sucesso
        break;

        default:
        //ERRO
        break;
   }
}
 
void Analisa_Bloco(bloco){ 
   lexico(Token **l ); 
   Analisa_et_variaveis();  
   Analisa_subrotinas();
   Analisa_comandos();
}


void Analisa_et_varaveis(etapa de declaração de variaveis){
   switch(token.simbolo){
        case svar:
        lexico(Token **l ); 
        break;

        case sidentificador:
        while (token.símbolo = sidentificador){
            Analisa_Variáveis();
            if(token.símbolo = spontvirg)
                lexico(Token **l ); 
            else ERRO
        }
        break;

        default:
        //ERRO
        break;
   }
}

       
void Analisa_Variaveis(declaração de variáveis){
    do{
        switch(token.simbolo){

            case: sidentificador
            //          Pesquisa_duplicvar_ tabela(token.lexema)  
            // if( não encontrou duplicidade 
            // então início 
            //inif(re_tabela(token.lexema, “variável” ,””,””) 
            lexico(Token **l ); 
            break;

            case: Svírgula
            case: Sdoispontos

                                              if( token.símbolo = Svírgula 
                             então início 
                                                          lexico(Token **l ); 
                                                          if( token.simbolo = Sdoispontos 
                                                          então ERRO 
                                                        fim 
                                            fim    
        if(não ERRO 
                               //fim 
          //if(não ERRO 
   if(não ERRO 
       while(token.símbolo = sdoispontos);
       lexico(Token **l ); 
       Analisa_Tipo();
}
 
Algoritmo Analisa_Tipo    <tipo> 
início 
   if( (token.símbolo  sinteiro e token.símbolo   sbooleano)) 
   então ERRO 
   //if(não coloca_tipo_tabela(token.lexema) 
   lexico(Token **l ); 
fim 
 
Algoritmo Analisa_comandos  <comandos> 
início 
   if( token.simbolo = sinicio 
   então início 
                lexico(Token **l ); 
                Analisa_comando_simples  
                enquanto (token.simbolo =! sfim) 

                faça início 
                           if( token.simbolo = spontovirgula 
                           então início 
                                        lexico(Token **l ); 
                                        if( token.simbolo  sfim 
                                        então Analisa_comando_simples  
                                     fim 
                            if(não ERRO 
                         fim 
                lexico(Token **l ); 
             fim 
   if(não ERRO 
fim 
 
Analisa_comando_simples  <comando> 
início 
   if( token.simbolo = sidentificador 
   então Analisa_atrib_chprocedimento  
   if(não  
   if( token.simbolo = sif( 
   então Analisa_if( 
   if(não 
   if( token.simbolo = if(nquanto 
   então Analisa_enquanto  
   if(não 
   if( token.simbolo = sleia 
   então Analisa_leia  
   if(não 
   if( token.simbolo = if(screva 
   então Analisa_ escreva 
   if(não 
  Analisa_comandos  
fim 
 
Algoritmo Analisa_atrib_chprocedimento <atribuição_chprocedimento> 
início 
   lexico(Token **l ); 
   if( token.simbolo = satribuição 
   então  Analisa_atribuicao 
   if(não  Chamada_procedimento  
fim 
 
Algoritmo Analisa_leia  <comando leitura> 
início 
   lexico(Token **l ); 
   if( token.simbolo = sabre_parenteif(s 
   então início 
                lexico(Token **l ); 
                if( token.simbolo = sidentificador 
                então //if( pesquisa_declvar_tabela(token.lexema)  
                           //então
                            início //(pesquisa em toda a tabela) 
                                       lexico(Token **l ); 
                                       if( token.simbolo = sfecha_parenteif(s 
                                       então lexico(Token **l ); 
                                       if(não ERRO 
                                    fim 
                            //if(não ERRO 
                if(não ERRO 
              fim 
    if(não ERRO 
fim 




Algoritmo Analisa_escreva  <comando escrita> 
início 
   lexico(Token **l ); 
   if( token.simbolo = sabre_parenteif(s 
   então início 
                lexico(Token **l ); 
                if( token.simbolo = sidentificador 
                então //if( pesquisa_ declvarfunc_tabela(token.lexema) 
                           //então
                            início 
                                       lexico(Token **l ); 
                                       if( token.simbolo = sfecha_parenteif(s 
                                       então lexico(Token **l ); 
                                       if(não ERRO 
                                    fim 
                            //if(não ERRO 
                if(não ERRO 
              fim 
    if(não ERRO 
fim 
 
Algoritmo Analisa_enquanto  <comando repetição> 
//Def auxrot1,auxrot2 inteiro 
início 
  // auxrot1:= rotulo 
  // Gera(rotulo,NULL, ́              ́, ́                ́)      {início do while} 
  //  rotulo:= rotulo+1 
   lexico(Token **l ); 
   Analisa_expressão  
   if( token.simbolo = sfaça 
   então início 
               //auxrot2:= rotulo 
               //Gera( ́                 ́,JMPF,rotulo, ́                ́)          {salta if( falso} 
               //rotulo:= rotulo+1 
               lexico(Token **l ); 
               Analisa_comando_simples  
               //Gera( ́            ́,JMP,auxrot1, ́                ́)   {retorna início loop} 
               //Gera(auxrot2,NULL, ́              ́, ́                ́)   {fim do while} 
             fim 
   if(não ERRO 
fim 
 
 
Algoritmo Analisa_if(  <comando condicional> 
início 
   lexico(Token **l ); 
   Analisa_expressão  
   if( token.símbolo = if(ntão 
   então início 
               lexico(Token **l ); 
               Analisa_comando_simples  
               if( token.símbolo = Sif(não 
               então início 
                           lexico(Token **l ); 
                           Analisa_comando_simples  
                         fim 
             fim 
    if(não ERRO 
fim 

Algoritmo Analisa_Subrotinas <etapa de declaração de sub-rotinas> 
//Def. auxrot, flag inteiro 
Início 
   //flag = 0 
   //if (token.simbolo = sprocedimento) ou   
   //                  (token.simbolo = sfunção) 
   //então início 
   //            auxrot:= rotulo 
   //            GERA( ́             ́,JMP,rotulo, ́                   ́)            {Salta sub-rotinas} 
   //            rotulo:= rotulo + 1 
   //            flag = 1 
   //          fim 
   enquanto (token.simbolo = sprocedimento) ou   
                     (token.simbolo = sfunção) 
    faça início 
               if( (token.simbolo = sprocedimento) 
               então analisa_declaração_procedimento  
               if(não analisa_ declaração_função  
               if( token.símbolo = sponto-vírgula 
               então lexico(Token **l ); 
               if(não ERRO 
            fim 
//     if flag = 1 
//     então Gera(auxrot,NULL, ́                 ́, ́                  ́)       {início do principal} 
//fim 
  
Algoritmo Analisa_ declaração_procedimento <declaração de procedimento> 
início 
   lexico(Token **l ); 
   //nível := “L” (marca ou novo galho) 
   if( token.símbolo = sidentificador 
   então início 
               // pesquisa_declproc_tabela(token.lexema) 
               // if( não encontrou 
               // então início 
               //               Inif(re_tabela(token.lexema,”procedimento”,nível, rótulo)             
               //                                                              {guarda na TabSimb} 
               //               Gera(rotulo,NULL, ́         ́, ́             ́)           
               //                             {CALL irá buscar este rótulo na TabSimb}              
               //                rotulo:= rotulo+1 
                              lexico(Token **l ); 
                              if( token.simbolo = sponto_vírgula 
                              então Analisa_bloco 
                              if(não ERRO 
                           //fim 
                //if(não ERRO 
             fim 
   if(não ERRO 
   //DEif(MPILHA OU VOLTA NÍVEL 
fim 



Algoritmo Analisa_ declaração_função <declaração de função> 
início 
   lexico(Token **l ); 
   //nível := “L” (marca ou novo galho) 
   if( token.símbolo = sidentificador 
   então início 
                //pesquisa_declfunc_tabela(token.lexema) 
                //if( não encontrou 
                //então início 
                              //Inif(re_tabela(token.lexema,””,nível,rótulo) 
                              lexico(Token **l ); 
                              if( token.símbolo = sdoispontos 
                              então início 
                                          lexico(Token **l ); 
                                          if( (token.símbolo = Sinteiro) ou  
                                               (token.símbolo = Sbooleano) 
                                          então início 
                                                       //if( (token.símbolo = Sinteger) 
                                                       //então TABSIMB[pc].tipo:=  
                                                       //                                    “função inteiro” 
                                                       //if(não TABSIMB[pc].tipo:=  
                                                       //                                    “função booleana” 
                                                       lexico(Token **l ); 
                                                      if( token.símbolo = sponto_vírgula 
                                                      então Analisa_bloco 
                                                     fim 
                                           if(não ERRO 
                                         fim 
                               if(não ERRO 
                          fim 
                //if(não ERRO 
             fim 
   if(não ERRO 
   //DEif(MPILHA OU VOLTA NÍVEL 
Fim 
 
Algoritmo Analisa_expressão  <expressão> 
início 
   Analisa_expressão_simples  
   if( (token.simbolo = (smaior ou smaiorig ou sig  
                                       ou smenor ou smenorig ou sdif)) 
   então inicio 
                lexico(Token **l ); 
                Analisa_expressão_simples  
              fim 
fim 
 
Algoritmo Analisa_expressão_simples <expressão simples> 
início 
   if( (token.simbolo = smais) ou (token.simbolo = smenos)  
   então lexico(Token **l ); 
   Analisa_termo  
   enquanto ((token.simbolo = smais) ou (token.simbolo = smenos) ou  
                      (token.simbolo = sou)) 
   faça inicio 
                lexico(Token **l ); 
                Analisa_termo  
             fim 
fim 


Algoritmo Analisa_termo   <termo> 
início 
   Analisa_fator  
   enquanto ((token.simbolo = smult) ou (token.simbolo = sdiv) ou       
                      (token.simbolo = if()) 
   então início 
                lexico(Token **l ); 
                Analisa_fator  
             fim
fim 
 
 
Algoritmo Analisa_fator <fator> 
Início 
   if( token.simbolo = sidentificador                    (* Variável ou Função*) 
   Então inicio 
                //if( pesquisa_tabela(token.lexema,nível,ind) 
                //Então if( (TabSimb[ind].tipo = “função inteiro”) ou  
                                //(TabSimb[ind].tipo = “função booleano”) 
                           //Então
                            Analisa_chamada_função  
                           //if(não lexico(Token **l ); 
                //if(não ERRO 
             Fim 
    if(não if( (token.simbolo = snumero)            (*Número*) 
                Então lexico(Token **l ); 
                if(não if( token.símbolo = snao              (*NAO*) 
                            Então início 
                                          lexico(Token **l ); 
                                          Analisa_fator  
                                      Fim 
                             if(não if( token.simbolo = sabre_parenteif(s     
                                                                  (* expressão entre parenteif(s *) 
                                         Então início 
                                                       lexico(Token **l ); 
                                                       Analisa_expressão(token) 
                                                       if( token.simbolo = sfecha_parenteif(s 
                                                        Então lexico(Token **l ); 
                                                        if(não ERRO 
                                                   Fim 
                                         if(não if( (token.lexema = verdadeiro) ou  
                                                          (token.lexema = falso) 
                                                    Então lexico(Token **l ); 
                                                    if(não ERRO 
Fim 
*/