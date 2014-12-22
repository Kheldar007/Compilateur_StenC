/**
 * @file    ast.c
 * @brief   Implementer les methodes du fichier "ast.h".
 * @author  Aurelien Vezin, Isabelle Muller
 */


# include "../include/ast.h"


Ast A_newOperation (char * t , Ast l , Ast r)
{
	Ast result = (Ast) malloc (sizeof (ast)) ; // Allouer de l'espace pour la structure ast.
	result -> type = strdup (t) ;
	result -> u.operation.left = l ;
	result -> u.operation.right = r ;
	return result ;
}

Ast A_newNumber (int n)
{
	Ast result = (Ast) malloc (sizeof (ast)) ; // Allouer de l'espace pour la structure ast.
	result -> type = "number" ;
	result -> u.number = n ;
	return result ;
}

Ast A_newId (char * i)
{
	Ast result = (Ast) malloc (sizeof (ast)) ; // Allouer de l'espace pour la structure ast.
	result -> type = "id" ;
	result -> u.id = strdup (i) ;
	return result ;
}

void A_print (Ast a , int indent)
{
	int i = 0 ;
	while (i < indent)
	{
		printf ("   ") ;
		i ++ ;
	}
	printf ("%s" , a -> type) ; // Afficher le type.
	if (strcmp (a -> type , "number") == 0) // Si c'est un nombre.
	{
		printf (" (%d)\n" , a -> u.number) ; // Afficher le nombre.
	}
	else if (strcmp (a -> type , "id") == 0) // Si c'est un identifiant.
	{
		printf (" (%s)\n" , a -> u.id) ; // Afficher l'identifiant.
	}
	else
	{
		printf ("\n") ;
		A_print (a -> u.operation.left ,  indent + 1) ;
		A_print (a -> u.operation.right , indent + 1) ;
	}
}
