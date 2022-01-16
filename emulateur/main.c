#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#include "../fonctions/header/memoire.h"
#include "../fonctions/header/registres.h"
#include "../fonctions/header/affichage.h"
#include "../fonctions/header/conversion.h"
#include "operation.h"
#include "traduction.h"


int main(){
    
    /*
    ADDI $2,$0,20
    ADDI $3,$0,15
    ADD $4,$2,$3
    */
    /*char* tableauHexa[4] = {"20020014","2003000F","00432020","\0"};*/

    char** tableauHexa = traduction("tests/hexa_in.txt");
    nodelay(stdscr,FALSE);
    getch();
    initialisation_reg(); /* initailisation des registres */
    initialisation_mem(); /* initailisation de la mémoire */
    init_affichage(); /* initialisation de l'affichage (ncurses) */
    
    
    int key; /* Contiendra la touche du clavier capturée par getch() */

    int fin = FALSE; /* indiquera la fin de l'éxécution du code */
    while (key != 'q' && !fin){

        /* initialisation */
        char instruction[10];
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
            }
                       
            getch();
            PC+=4;
        }
        fin = TRUE;

        key = wgetch(stdscr);
    }

    nodelay(stdscr, FALSE);
    getch();
    endwin();
    return(0);

}