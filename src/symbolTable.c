/**
 * @file    symbolTable.c
 * @brief   Implementer les methodes du fichier "symbolTable.h".
 * @author  Aurelien Vezin, Isabelle Muller
 */


# include "../include/symbolTable.h"


SymbolTable S_new ()
{
	SymbolTable result = (SymbolTable) malloc (sizeof (symbolTable)) ; // Allouer la memoire.
	
	result -> length = 0 ;
	result -> size = SIZE ;
	result -> s     = (Symbol *) malloc (SIZE * sizeof (Symbol)) ;
	int i = 0 ;
	while (i < SIZE)
	{
		result -> s [i] = (Symbol) malloc (sizeof (symbol)) ;
		i ++ ;
	}
	nextQuad = 0 ; // Pour l'instant, il n'y a pas de quads crees.
	idTemporary = 0 ; // Pas de symbole temporaire pour le moment.
	
	return result ; // Nouvelle table des symboles.
}

int S_lookup (SymbolTable s , char * id)
{
	int result = -1 ; // Dans le cas d'une erreur.
	
	int i = 0 ;
	while (i < s -> length)
	{
		if (strcmp (s -> s [i] -> identifier , id) == 0) // Si le resultat est celui souhaite.
		{
			result = i ; // Trouver le resultat
		}
		i ++ ;
	}
	
	return result ;
}

Symbol S_lookupSymbol (SymbolTable s , char * id)
{
	int lookup = S_lookup (s , id) ; // Rechercher l'identifiant id dans la table s.
	if (lookup != -1)
	{
		return s -> s [lookup] ; // Retourner le symbol recherche.
	}
	else // Le symbole n'existe pas dans la table.
	{
		return NULL; // Retourner un nouveau symbole de valeur 0 par defaut.
	}
}

Symbol S_newSymbol (SymbolTable table , int value , char * id , char r)
{
	int lookup = S_lookup (table , id) ; // Rechercher le label dans la table.
	if (lookup != -1) // Si le label a ete trouve.
	{
		table -> s [lookup] -> n = value ; // On affecte la valeur au symbole recherche.
	}
	else // Si le label n'est pas situe dans la table.
	{
		lookup = table -> length ;
		if (table -> length >= table -> size) // Si la memoire est pleine.
		{
			table -> size += SIZE ; // Agrandir la table.
			table -> s = realloc (table -> s , table -> size) ; // Allouer plus d'espace.
		}
		table -> s [lookup] -> identifier = strdup (id) ; // Lui affecter l'identifiant.
		table -> s [lookup] -> n = value ; // Lui affecter la valeur.
		table -> s [lookup] -> range = r ; // Lui affecter la portee.
		table -> length ++ ; // Il y a un symbole de plus.
	}
	return table -> s [lookup] ; // Retourner le symbole cree.
}

Symbol S_temporarySymbol (SymbolTable table , int value, char r)
{
    char * id;
    asprintf (& id , "_tmp_%d" , table->length) ;
    return S_newSymbol(table, value, id, r);
}

void S_print (SymbolTable s)
{
	if (s != NULL)
	{
		int i = 0 ;
		while (i < s -> length)
		{
			printf ("Number : %d d'identifiant %s de valeur %d et de portee %c.\n" , i ,
				s -> s [i] -> identifier , s -> s [i] -> n , s -> s [i] -> range) ;
			i ++ ;
		}
	}
	else // La table est vide.
	{
		printf ("La table des symboles est vide.\n") ;
	}
}

void S_delete (SymbolTable s)
{
	if (s != NULL) // Si la table n'est pas vide.
	{
		free (s -> s) ; // Liberer le pointeur.
	}
	free (s) ;
}
