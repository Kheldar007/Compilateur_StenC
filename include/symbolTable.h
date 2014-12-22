/**
 * @file   symbolTable.h
 * @author Aurelien Vezin, Isabelle Muller 
 * @brief  Definir la table des symboles.
 */
 
 
# ifndef SYMBOLTABLE_H
# define SYMBOLTABLE_H
# define _GNU_SOURCE

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define SIZE 1024


int nextQuad ; // Prochain quad a generer.
int idTemporary ; // Lors de la creation de quads temporaires.


typedef struct symbol
{
	int n ; // Le nombre.
	char * identifier ; // L'identifiant.
	char range ; // La portee.
} symbol , * Symbol ; // Un symbole.

typedef struct symbolTable
{
	int length ; // Le nombre de symbols de la table.
	int size ; // La taille allouee.
	Symbol * s ;
} symbolTable , * SymbolTable ; // Une table des symboles.


/**
 * @brief  Creer une nouvelle table des symboles, vide.
 * @return La table.
 */
SymbolTable S_new () ;
/**
 * @brief  Retourner l'entree de la table des symboles associee a id.
 * @param  s  La table des symboles.
 * @param  id Le symbole a chercher.
 * @return L'indice du symbole, -1 si le symbole n'est pas dans la table.
 */
int S_lookup (SymbolTable s , char * id) ;
/**
 * @brief  Utiliser le lookup et retourner un Symbol.
 * @param  s  La table des symboles.
 * @param  id Le symbole a chercher.
 * @return Le symbole trouve.
 */
Symbol S_lookupSymbol (SymbolTable s , char * id) ;
/**
 * @brief  Creer un symbole.
 * @param  table La table des symboles.
 * @param  id    L'identifiant du symbole.
 * @param  value La valeur a mettre dans le symbole.
 * @param  r     La portee du symbole.
 * @return Le symbole.
 */
Symbol S_newSymbol (SymbolTable table , int value , char * id , char r) ;
/**
 * @brief create a new temporary symbol.
 * 
 */
Symbol S_temporarySymbol (SymbolTable table , int value, char r);
/**
 * @brief Afficher la table des symboles.
 */
void S_print (SymbolTable s) ;
/**
 * @brief Liberer la memoire.
 * @param s Table des symboles.
 */
void S_delete (SymbolTable s) ;


# endif


