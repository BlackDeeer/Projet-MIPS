#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#include "../fonctions/header/memoire.h"
#include "../fonctions/header/registres.h"
#include "../fonctions/header/affichage.h"
#include "../fonctions/header/conversion.h"
#include "../fonctions/header/fichier.h"
#include "operation.h"
#include "traduction.h"


int main(int argc, char* argv[]){
    
    /*
    ADDI $2,$0,20
    ADDI $3,$0,15
    ADD $4,$2,$3
    */
    /*char* tableauHexa[4] = {"20020014","2003000F","00432020","\0"};*/

    

    /* Récupération du nom du fichier assembleur txt */
	if (argc==1){ /* S'il n'y a pas d'argument alors on signale un erreur et on quitte le programme */
		fprintf(stderr,"ERREUR : nom du fichier à traduire manquant \n");
		exit(EXIT_FAILURE);
	}
	char* fichier = argv[1]; /* On récupère le nom du fichier */


    
    char** tableauHexa = traduction(fichier);
    nodelay(stdscr,FALSE);
    getch();
    initialisation_reg(); /* initailisation des registres */
    initialisation_mem(); /* initailisation de la mémoire */
    init_affichage(); /* initialisation de l'affichage (ncurses) */
    
    
    int key; /* Contiendra la touche du clavier capturée par getch() */

    int fin = FALSE; /* indiquera la fin de l'éxécution du code */
    while (key != 'q' && !fin){

        /* initialisation */
        char bin_instruction[32];
        char opcode[7];


        /* Tant qu'il y a des instructions : */
        while(tableauHexa[PC/4][0] != '\0'){
            IR = tableauHexa[PC/4]; /* on recupère l'instruction correspondant au PC*/

            hexa_to_bin(8,IR,bin_instruction,32); /* traduction en binaire */
            

            /* On cherche l'opcode */
            int k;
            for (k=0;k<6;k++){
                opcode[k] = bin_instruction[k];
            }
            opcode[k+1]='\0';
            if (!strcmp(opcode,"000000")){ /* Cas des instruction de type R ou l'opcode est à la fin */
                for (k=0;k<6;k++){
                opcode[k] = bin_instruction[26+k];
                }
            }
            
            /* On cherche la bonne instruction à éxécuter */    
            if(!strcmp(opcode,"001000")){
                ADDI(bin_instruction,IR);
                print_log(log_current);
            } else if (!strcmp(opcode,"100000")){
                ADD(bin_instruction,IR);
                print_log(log_current);
            } else if (!strcmp(opcode,"000100")){
                BEQ(bin_instruction,IR);
                print_log(log_current);
            } else if (!strcmp(opcode,"000101")){
                BNE(bin_instruction,IR);
                print_log(log_current);
            }else if (!strcmp(opcode,"000010")){
                J(bin_instruction,IR);
                print_log(log_current);
            }else if (!strcmp(opcode,"011010")){
                DIV(bin_instruction,IR);
                print_log(log_current);
            }else if (!strcmp(opcode,"010000")){
                MFHI(bin_instruction,IR);
                print_log(log_current);
            }else if (!strcmp(opcode,"100100")){
                AND(bin_instruction,IR);
                print_log(log_current);
            }


            PC+=4;
                       
            getch();
            
        }
        fin = TRUE;

        key = wgetch(stdscr);
    }

    nodelay(stdscr, FALSE);
    getch();
    endwin();

    char fichier_state[] = "state/state_reg_";
	strcat(fichier_state,fichier+6);
	ecriture_fichier_int(fichier_state,tableau_reg,32);
	printf("Ecriture dans '%s' OK\n",fichier_state);

    strcpy(fichier_state,"state/state_mem_");
	strcat(fichier_state,fichier+6);
	ecriture_fichier_int(fichier_state,tableau_mem,32);
	printf("Ecriture dans '%s' OK\n",fichier_state);

    strcpy(fichier_state,"state/state_log_");
	strcat(fichier_state,fichier+6);
	ecriture_fichier(fichier_state,log_mips,nb_log-1);
	printf("Ecriture dans '%s' OK\n",fichier_state);

    return(0);

}