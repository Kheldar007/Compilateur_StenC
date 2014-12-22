/**
 * @file    tree.c
 * @brief   Implementer les methodes du fichier "tree.h", sur la structure node.
 * @author  Aurelien Vezin, Isabelle Muller
 */
 

 # include <stdio.h> 
 # include "../include/tree.h"


Node T_new (char * n , Node c1 , Node c2 , Node c3)
{
	Node result = (Node) malloc (sizeof (node)) ; // Noeud a initialiser.
	result -> name = strdup (n) ;
	result -> child1 = c1 ;
	result -> child2 = c2 ;
	result -> child3 = c3 ;
	return result ; // On retourne le noeud.
}

void T_print (Node n)
{
	if (n == NULL) // Si l'arbre est null.
	{
		printf ("NULL\n") ;
	}
	else
	{
		printf ("%s\n" , n -> name) ;
		T_print (n -> child1) ;
		T_print (n -> child2) ;
		T_print (n -> child3) ;
	}
}
