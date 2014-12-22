/**
 * @file    mips.h
 * @author  Aurelien Vezin, Isabelle Muller 
 * @brief   Operations sur le fichier en assembleur mips.
 */


# ifndef MIPS_H
# define MIPS_H


# include <stdio.h>
# include "quad.h"


/**
 * @brief Initialiser le fichier.
 * @param file Le fichier mips.
 */
void M_initializeFile (FILE * file) ;
/**
 * @brief Cloturer le fichier.
 * @param file Le fichier mips.
 */
void M_terminateFile (FILE * file) ;
/**
 * @brief Ajouter le contenu d'un quad dans un fichier mips.
 * @param file Le fichier mips.
 * @param q    Le quad.
 */
void addQuad (FILE * file , Quad q) ;
/**
 * @brief Ajouter le contenu d'une liste de quads dans un fichier mips.
 * @param file Le fichier mips.
 * @param ql   La liste de quads.
 */
void M_addQuadList (FILE * file , QuadList ql) ;
/**
 * @brief Ajouter les symboles d'une table dans la pile.
 * @param file Le fichier mips.
 * @param st   La table des symboles.
 */
void M_addSymbolTableToStack (FILE * file , SymbolTable st) ;
/**
 * @brief Recuperer un symbole dans la pile.
 * @param file Le fichier mips.
 * @param i    Le i-eme symbole (pour savoir ou le chercher dans la pile).
 */
void M_fetchSymbolFromStack (FILE * file , int i) ;


# endif
