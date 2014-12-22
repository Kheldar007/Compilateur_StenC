/**
 * @file    mips.c
 * @brief   Implementer les methodes du fichier "mips.h".
 * @author  Aurelien Vezin, Isabelle Muller
 */


# include "../include/mips.h"


void M_initializeFile (FILE * file)
{
	fprintf (file , ".data\n\n") ;
	fprintf (file , "title : .asciiz \"\\nTranscription mips.\\n\\n\"\n\n") ;
	fprintf (file , ".text\n") ;
	fprintf (file , ".globl __start\n\n") ;
	fprintf (file , "__start :\n\n") ;
	
	fprintf (file , "li $v0 , 4\n") ;
	fprintf (file , "la $a0 , title\n") ; // Afficher le titre.
	fprintf (file , "syscall\n\n\n") ;
}

void M_terminateFile (FILE * file)
{	
	fprintf (file , "\nquit :\n") ;	
	fprintf (file , "\tli $v0 , 10\n") ; // Quitter le programme.
	fprintf (file , "\tsyscall\n\n") ;
}

void addQuad (FILE * file , Quad q)
{
	Q_printQuad (q) ;
	fprintf (file , "Label_%d :\n" , q -> label) ; // Ecrire le numero de l'instruction.

	switch (q -> operation) // Pour chaque cas different.
	{
		case '+' : // Pour une addition.
		{
			fprintf (file , "\tadd $t3 , $t1 , $t2\n") ; // Ecrire l'instruction dans le fichier mips.
			break ;
		}
		case '-' :
		{
			if (q -> argument2 != NULL) // Pour une soustraction.
			{
				fprintf (file , "\tsub $t3 , $t1 , $t2\n") ;
			}
			else // Operation unaire.
			{
				fprintf (file , "\tli $t2 , 0\n\tsub $t3 , $t1 , $t2\n") ;
			}
			break ;
		}
		case '*' : // Pour la multiplication.
		{
			fprintf (file , "\tmul $t3 , $t1 , $t2\n") ;
			break ;
		}
		case '/' : // Pour la division.
		{
			fprintf (file , "\tdiv $t3 , $t1 , $t2\n") ;
			break ;
		}
		case '=' : // Pour l'affectation.
		{
			fprintf (file , "\tmove $t2 , $t1\n") ;
			break ;
		}
		case 'e' : // Si egal.
		{
			fprintf (file , "\tbeq $t1 , $t2 ,             \n") ; // Label encore inconnu.
			break ;
		}
		case 'n' : // Si different.
		{
			fprintf (file , "\tbne $t1 , $t2 ,             \n") ;
			break ;
		}
		case '<' : // Si inferieur.
		{
			fprintf (file , "\tblt $t1 , $t2 ,             \n") ;
			break ;
		}
		case '>' : // Si superieur.
		{
			fprintf (file , "\tbgt $t1 , $t2 ,             \n") ;
			break ;
		}
		case 'i' : // Si inferieur ou egal.
		{
			fprintf (file , "\tble $t1 , $t2 ,             \n") ;
			break ;
		}
		case 's' : // Si superieur ou egal.
		{
			fprintf (file , "\tbge $t1 , $t2 ,             \n") ;
			break ;
		}
		case 'g' : // Goto.
		{
			fprintf (file , "\tb             \n") ;
			break ;
		}
		default :
		{
			break ;
		}
	}
	
	fprintf (file , "\n") ;
}

void M_addQuadList (FILE * file , QuadList ql)
{
	if (ql != NULL) // Si la liste n'est pas vide.
	{
		QuadList qlTemporary = ql ; // Pointeur servant a parcourir la liste.
		int i = 0 ;
		do
		{
			if (qlTemporary -> q != NULL)
			{
				// addQuad (file , qlTemporary -> q) ; // Ajouter le quad au fichier mips.
			}
			qlTemporary = qlTemporary -> next ; // Deplacer le pointeur.
			i ++ ;
		}
		while (qlTemporary -> next != NULL) ; // Parcourir la liste.
	}
}

void M_addSymbolTableToStack (FILE * file , SymbolTable st)
{
	int i = 0 ;
	while (i < st -> length)
	{
		fprintf (file , "li $t0 , %d\n" , st -> s [i] -> n) ;
		fprintf (file , "sw $t0 , %i($sp)\n" , (int) (i * sizeof (int))) ;
		i ++ ;
	}
}

void M_fetchSymbolFromStack (FILE * file , int i)
{
	fprintf (file , "lw $t0 , %d($sp)\n" , (int) (i * sizeof (int))) ;
}
