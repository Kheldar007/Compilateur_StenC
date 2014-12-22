/**
 * @file   quad.h
 * @author Aurelien Vezin, Isabelle Muller 
 * @brief  Definir les quads.
 */


# ifndef QUAD_H
# define QUAD_H
# define _GNU_SOURCE

# include <stdio.h>
# include <stdlib.h>
# include "symbolTable.h"


typedef struct quad
{
	int label ; // Label.
	char operation ; // Operation.
	Symbol argument1 ; // Argument 1.
	Symbol argument2 ; // Argument 2.
	Symbol result ; // Resultat.
	struct quad * next ; // Quad suivant.
} quad , * Quad ;

typedef struct quadList
{
	Quad q ;
	struct quadList * next ;
} quadList , * QuadList ; // Liste de quads.


/**
 * @brief  Creer un nouveau Quad.
 * @param  r  Le resultat.
 * @param  o  Une operation.
 * @param  a1 Une operande.
 * @param  a2 Une operande.
 * @return Un Quad.
 */
Quad Q_new (char o , Symbol a1 , Symbol a2 , Symbol r) ;
/**
 * @brief  Ajouter un Quad a une liste de quads.
 * @param  list1 Premiere liste.
 * @param  list2 Deuxieme liste.
 * @return Deux quads assembles.
 */
QuadList Q_add (QuadList list1, Quad quad1) ;
/**
 * @brief  Nouvelle liste de quads.
 * @param  q Un quad.
 * @return La liste.
 */
QuadList Q_newList () ;
/**
 * @brief  Concatener deux listes de quads.
 * @param  list1 Premiere liste.
 * @param  list2 Deuxieme liste.
 * @return Liste de quads.
 */
QuadList Q_concat (QuadList list1 , QuadList list2) ;
/**
 * @brief get the last element of a quadlists
 */
Quad Q_lastQuad(QuadList ql) ;
/**
 * @brief  Completer une liste de quads.
 * @param  table Une liste des symboles.
 * @param  list  La liste.
 * @param  label Label pour completer la liste.
 */
void Q_complete (SymbolTable table , QuadList list , int label) ;
/**
 * @brief Afficher le quad.
 * @param q Un Quad.
 */
void Q_printQuad (Quad q0) ;
/**
 * @brief Afficher la liste de quads.
 * @param q Une liste de quads.
 */
void Q_printList (QuadList q0) ;
/**
 * @brief Liberer la memoire.
 * @param q Liste de quads.
 */
void Q_delete (QuadList q) ;


# endif
