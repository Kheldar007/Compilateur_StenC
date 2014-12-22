/**
 * @file    tree.h
 * @author  Aurelien Vezin, Isabelle Muller 
 * @brief   Construire un arbre et traiter ses noeuds.
 */


# ifndef TREE_H
# define TREE_H


# include <string.h>
# include <stdlib.h>


/**
 * @brief Un noeud de l'arbre.
 */
typedef struct node
{
	char * name ;
	struct node * child1 ;
	struct node * child2 ;
	struct node * child3 ;
}
node , * Node ;


/**
 * @brief  Allouer de la memoire pour un arbre.
 * @param  n  Le nom de la racine.
 * @param  c1 Le premier fils.
 * @param  c2 Le deuxieme fils.
 * @param  c3 Le troisieme fils.
 * @return Un arbre.
 */
Node T_new (char * n , Node c1 , Node c2 , Node c3) ;
/**
 * @brief Afficher un arbre.
 * @param tree L'arbre a afficher.
 */
void T_print (Node tree) ;


# endif
