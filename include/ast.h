/**
 * @file    ast.h
 * @author  Aurelien Vezin, Isabelle Muller 
 */


# ifndef AST_H
# define AST_H


# include <stdlib.h>
# include <stdio.h>
# include <string.h>


typedef struct ast
{
	char * type ;
	union
	{
		struct
		{
			struct ast * left ;
			struct ast * right ;
		}
		operation ;
		int number ;
		char * id ;
	}
	u ;
}
ast , * Ast ;


/**
 * @brief  C'est une nouvelle operation.
 * @param  t Le type.
 * @param  l Gauche.
 * @param  r Droit.
 * @result Structure ast.
 */
Ast A_newOperation (char * t , Ast l , Ast r) ;
/**
 * @brief  C'est un nouveau nombre.
 * @param  n La valeur du nombre.
 * @result Structure ast.
 */
Ast A_newNumber (int n) ;
/**
 * @brief  C'est un nouvel identifiant.
 * @param  i L'identifiant.
 * @result Structure ast.
 */
Ast A_newId (char * i) ;
/**
 * @brief Afficher la structure.
 * @param a     L'ast a afficher.
 * @param ident
 */
void A_print (Ast a , int indent) ;


# endif
