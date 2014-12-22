%{
    #include <stdio.h>
    #include <stdlib.h>
	# include "./include/ast.h"
	# include "./include/mips.h"
	# include "./include/symbolTable.h"
	# include "./include/tree.h"
    # include "./include/quad.h"
	// # define YYSTYPE node
	int yylex () ;
	void yyerror (char *) ;
	extern FILE * yyin ;
	SymbolTable table = NULL ;
    QuadList qlist = NULL ;
    FILE * mips = NULL ;
%}


%union {
  // type any used for QuadList
  void * any;
  char* string;
  int value;
}

%token ASSIGN END_INS PLUS MOINS MULT DIV POPEN PCLOSE WHILE IF ELSE AOPEN ACLOSE EQUAL NOT_EQUAL SUP INF SUP_EQUAL INF_EQUAL OR AND
%token <string> ID TYPE
%token <value> NUM

%type<any> statement_list statement expression condition//quadlist

%left OR
%left AND
%left PLUS MOINS
%left MULT DIV
%left POPEN PCLOSE


%%


statement_list: 
    statement_list statement {
                               qlist = Q_concat($1, $2);
                               $$ = qlist;
                               mips = fopen ("stenc.s" , "a") ;
                               if (mips != NULL)
                               {
								   M_addQuadList (mips , qlist) ;
	                               fclose (mips) ;
							   }
							   else
							   {
								   perror ("Fichier mips non ouvert dans statement_list statement\n") ;
							   }
                               }
    | statement { 
                    qlist = $1;
                    $$ = $1;
                    mips = fopen ("stenc.s" , "a") ;
                    if (mips != NULL)
                    {
						M_addQuadList (mips , qlist) ;
	                    fclose (mips) ;
					}
					else
					{
						perror ("Fichier mips non ouvert dans statement\n") ;
					}
                  }
    ;

statement:
    TYPE ID ASSIGN expression END_INS { // ! newsymbol peut modifier un symbol
                                        QuadList expr = $4;
                                        Quad last_expr = Q_lastQuad(expr);
                                        Symbol sres = S_newSymbol(table, last_expr->result->n, $2, 'g');
                                        Quad tmp = Q_new('=', NULL, NULL, sres);
                                        mips = fopen ("stenc.s" , "a") ;
                                        if (mips != NULL)
                                        {
											addQuad (mips , tmp) ;
											fclose (mips) ;
										}
                                        expr = Q_add(expr, tmp);
                                        $$ = expr; 
                                      }
    | ID ASSIGN expression END_INS { Symbol sres = S_lookupSymbol(table, $1);
                                     if(sres == NULL)
                                     {
                                         fprintf(stderr, "You must specify the type of a variable before using it");
                                         exit(1);
                                     }
                                     QuadList expr = $3;
                                     Quad last_expr = Q_lastQuad(expr);
                                     sres = S_newSymbol(table, last_expr->result->n, $1, 'g');
                                     Quad tmp = Q_new('=', NULL, NULL, sres);
									 mips = fopen ("stenc.s" , "a") ;
									 if (mips != NULL)
									 {
										 addQuad (mips , tmp) ;
										 fclose (mips) ;
									 }
                                     expr = Q_add(expr, tmp);
                                     $$ = expr; 
                                   }
    | WHILE POPEN condition PCLOSE AOPEN statement_list ACLOSE   {}
    | IF POPEN condition PCLOSE AOPEN statement_list ACLOSE      {}
    | IF POPEN condition PCLOSE AOPEN statement_list ACLOSE ELSE AOPEN statement_list ACLOSE {}
    ;
    
expression:
    expression PLUS expression {  //cacul fait pour la table des symboles normal ?
                                QuadList expr1 = $1;
                                QuadList expr2 = $3;
                                Quad last_expr1 = Q_lastQuad(expr1);
                                Quad last_expr2 = Q_lastQuad(expr2);
                                int ires = last_expr1->result->n + last_expr2->result->n;
                                Symbol sres = S_temporarySymbol(table, ires, 'g');
                                Quad qres = Q_new('+', last_expr1->result, last_expr2->result, sres);
								mips = fopen ("stenc.s" , "a") ;
								if (mips != NULL)
								{
									addQuad (mips , qres) ;
									fclose (mips) ;
								}
                                QuadList qlres = Q_concat(expr1, expr2);
                                qlres = Q_add(qlres, qres);
                                $$ = qlres;
                                }
    | expression MOINS expression { 
                                    QuadList expr1 = $1;
                                    QuadList expr2 = $3;
                                    Quad last_expr1 = Q_lastQuad(expr1);
                                    Quad last_expr2 = Q_lastQuad(expr2);
                                    int ires = last_expr1->result->n - last_expr2->result->n;
                                    Symbol sres = S_temporarySymbol(table, ires, 'g');
                                    Quad qres = Q_new('-', last_expr1->result, last_expr2->result, sres);
									mips = fopen ("stenc.s" , "a") ;
									if (mips != NULL)
									{
										addQuad (mips , qres) ;
										fclose (mips) ;
									}
                                    QuadList qlres = Q_concat(expr1, expr2);
                                    qlres = Q_add(qlres, qres);
                                    $$ = qlres; 
                                  }
    | expression MULT expression { 
                                    QuadList expr1 = $1;
                                    QuadList expr2 = $3;
                                    Quad last_expr1 = Q_lastQuad(expr1);
                                    Quad last_expr2 = Q_lastQuad(expr2);
                                    int ires = last_expr1->result->n * last_expr2->result->n;
                                    Symbol sres = S_temporarySymbol(table, ires, 'g');
                                    Quad qres = Q_new('*', last_expr1->result, last_expr2->result, sres);
									mips = fopen ("stenc.s" , "a") ;
									if (mips != NULL)
									{
										addQuad (mips , qres) ;
										fclose (mips) ;
									}
                                    QuadList qlres = Q_concat(expr1, expr2);
                                    qlres = Q_add(qlres, qres);
                                    $$ = qlres;
                                 }
    | expression DIV expression { 
                                    QuadList expr1 = $1;
                                    QuadList expr2 = $3;
                                    Quad last_expr1 = Q_lastQuad(expr1);
                                    Quad last_expr2 = Q_lastQuad(expr2);
                                    int ires = last_expr1->result->n / last_expr2->result->n;
                                    Symbol sres = S_temporarySymbol(table, ires, 'g');
                                    Quad qres = Q_new('/', last_expr1->result, last_expr2->result, sres);
									mips = fopen ("stenc.s" , "a") ;
									if (mips != NULL)
									{
										addQuad (mips , qres) ;
										fclose (mips) ;
									}
                                    QuadList qlres = Q_concat(expr1, expr2);
                                    qlres = Q_add(qlres, qres);
                                    $$ = qlres; 
                                }
    | POPEN expression PCLOSE    { 
                                  $$ = $2; 
                                  }
    | ID { // create a quad list and pass it to the next level
           Symbol sres = S_lookupSymbol(table, $1);
           if(sres == NULL)
           {
               fprintf(stderr, "You must specify the type of a variable before use it");
               exit(1);
           }
           Quad load = Q_new('l', NULL, NULL, sres);
			mips = fopen ("stenc.s" , "a") ;
			if (mips != NULL)
			{
				addQuad (mips , load) ;
				fclose (mips) ;
			}
           QuadList res = Q_newList();
           res = Q_add(res, load);
           $$ = res;
          }
    | NUM { //create a quad list and passing it to the next level
            Symbol sres = S_temporarySymbol(table, $1, 'g');
            Quad load = Q_new('l', NULL, NULL, sres);
			mips = fopen ("stenc.s" , "a") ;
			if (mips != NULL)
			{
				addQuad (mips , load) ;
				fclose (mips) ;
			}
            QuadList res = Q_newList();
            res = Q_add(res, load);
            $$ = res;
          }
    ; 
  

condition:
    expression EQUAL expression  {
                                    QuadList expr1 = $1;
                                    QuadList expr2 = $3;
                                    Quad last_expr1 = Q_lastQuad(expr1);
                                    Quad last_expr2 = Q_lastQuad(expr2);
                                    int ires = last_expr1->result->n == last_expr2->result->n;
                                    Symbol sres = S_temporarySymbol(table, ires, 'g');
                                    Quad qres = Q_new('e', last_expr1->result, last_expr2->result, sres);
									mips = fopen ("stenc.s" , "a") ;
									if (mips != NULL)
									{
										addQuad (mips , qres) ;
										fclose (mips) ;
									}
                                    QuadList qlres = Q_concat(expr1, expr2);
                                    qlres = Q_add(qlres, qres);
                                    $$ = qlres; 
                                 }
    | expression NOT_EQUAL expression  {
                                        QuadList expr1 = $1;
                                        QuadList expr2 = $3;
                                        Quad last_expr1 = Q_lastQuad(expr1);
                                        Quad last_expr2 = Q_lastQuad(expr2);
                                        int ires = last_expr1->result->n != last_expr2->result->n;
                                        Symbol sres = S_temporarySymbol(table, ires, 'g');
                                        Quad qres = Q_new('n', last_expr1->result, last_expr2->result, sres);
										mips = fopen ("stenc.s" , "a") ;
										if (mips != NULL)
										{
											addQuad (mips , qres) ;
											fclose (mips) ;
										}
                                        QuadList qlres = Q_concat(expr1, expr2);
                                        qlres = Q_add(qlres, qres);
                                        $$ = qlres; 
                                        }
    | expression INF expression {
                                    QuadList expr1 = $1;
                                    QuadList expr2 = $3;
                                    Quad last_expr1 = Q_lastQuad(expr1);
                                    Quad last_expr2 = Q_lastQuad(expr2);
                                    int ires = last_expr1->result->n < last_expr2->result->n;
                                    Symbol sres = S_temporarySymbol(table, ires, 'g');
                                    Quad qres = Q_new('<', last_expr1->result, last_expr2->result, sres);
									mips = fopen ("stenc.s" , "a") ;
									if (mips != NULL)
									{
										addQuad (mips , qres) ;
										fclose (mips) ;
									}
                                    QuadList qlres = Q_concat(expr1, expr2);
                                    qlres = Q_add(qlres, qres);
                                    $$ = qlres; 
                                }
    | expression SUP expression {
                                    QuadList expr1 = $1;
                                    QuadList expr2 = $3;
                                    Quad last_expr1 = Q_lastQuad(expr1);
                                    Quad last_expr2 = Q_lastQuad(expr2);
                                    int ires = last_expr1->result->n > last_expr2->result->n;
                                    Symbol sres = S_temporarySymbol(table, ires, 'g');
                                    Quad qres = Q_new('>', last_expr1->result, last_expr2->result, sres);
									mips = fopen ("stenc.s" , "a") ;
									if (mips != NULL)
									{
										addQuad (mips , qres) ;
										fclose (mips) ;
									}
                                    QuadList qlres = Q_concat(expr1, expr2);
                                    qlres = Q_add(qlres, qres);
                                    $$ = qlres; 
                                }
    | expression INF_EQUAL expression {
                                        QuadList expr1 = $1;
                                        QuadList expr2 = $3;
                                        Quad last_expr1 = Q_lastQuad(expr1);
                                        Quad last_expr2 = Q_lastQuad(expr2);
                                        int ires = last_expr1->result->n <= last_expr2->result->n;
                                        Symbol sres = S_temporarySymbol(table, ires, 'g');
                                        Quad qres = Q_new('i', last_expr1->result, last_expr2->result, sres);
										mips = fopen ("stenc.s" , "a") ;
										if (mips != NULL)
										{
											addQuad (mips , qres) ;
											fclose (mips) ;
										}
                                        QuadList qlres = Q_concat(expr1, expr2);
                                        qlres = Q_add(qlres, qres);
                                        $$ = qlres;  
                                       }
    | expression SUP_EQUAL expression {
                                        QuadList expr1 = $1;
                                        QuadList expr2 = $3;
                                        Quad last_expr1 = Q_lastQuad(expr1);
                                        Quad last_expr2 = Q_lastQuad(expr2);
                                        int ires = last_expr1->result->n >= last_expr2->result->n;
                                        Symbol sres = S_temporarySymbol(table, ires, 'g');
                                        Quad qres = Q_new('s', last_expr1->result, last_expr2->result, sres);
										mips = fopen ("stenc.s" , "a") ;
										if (mips != NULL)
										{
											addQuad (mips , qres) ;
											fclose (mips) ;
										}
                                        QuadList qlres = Q_concat(expr1, expr2);
                                        qlres = Q_add(qlres, qres);
                                        $$ = qlres;
                                       }
    | condition OR condition {}
    | condition AND condition {}
    | POPEN condition PCLOSE	{
									$$ = $2 ;
								}
    ;
  

%%

void yyerror (char *s) {
    fprintf(stderr, "[Yacc] error: %s\n", s);
}


int main (int argc, char ** argv)
{
	table = S_new () ; // Table des symboles.
	qlist = Q_newList() ; // List des quads (init a NULL car imposible de faire une liste vide
	/*************************** Creation de fichiers. ****************************/
	FILE * stenC = fopen (argv [1]  , "r") ; // Fichier stenC a lire.
	mips  = fopen ("stenc.s" , "a") ; // Creer le fichier assembleur.
	/******************************************************************************/
	
	if ((stenC != NULL) && (mips != NULL)) // Si les fichiers se sont bien ouverts.
	{
		M_initializeFile (mips) ; // Initialiser le fichier mips.
		fclose (mips) ; // Fermer le fichier mips.
		
		yyin = stenC ;
		yyparse () ; // Lancer le yacc.
		
		mips  = fopen ("stenc.s" , "a") ; // Creer le fichier assembleur.
		if (mips != NULL)
		{
			M_terminateFile (mips) ; // Cloturer le fichier mips.
			fclose (mips) ;
		}
		else
		{
			perror ("Fichier mips non ouvert.\n") ;
		}
		
		/*************************** Cloturer les fichiers. ***************************/
		fclose (stenC) ; // Fermer le fichier stenC.
		/******************************************************************************/
	}
	else
	{
		perror ("Les fichiers n'ont pas ete ouverts correctement.\n") ;
	}
	S_print (table) ;
	// S_delete (table) ; // Liberer la memoire.
	// Q_delete (qlist) ;
	
	return 0 ;
}
