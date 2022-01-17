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
    int nom_fichier = FALSE;
    char* nom_fichier_hexa;
    char* nom_fichier_state;
    if (argc>=2){
        if(!strcmp(argv[2],"-pas")){
            int nom_fichier = FALSE;
            nom_fichier_hexa = NULL;
        } else {
            int nom_fichier = TRUE;
            nom_fichier_hexa = argv[2];
        }
    }

    if (argc>=3){
        nom_fichier_state = argv[3]; 
    } else {
        nom_fichier_state = NULL; 
    }


    
    char** tableauHexa = traduction(fichier,nom_fichier_hexa);
    
    getch();
    initialisation_reg(); /* initailisation des registres */
    initialisation_mem(); /* initailisation de la mémoire */
    init_affichage(); /* initialisation de l'affichage (ncurses) */

    if (argc>=2){
        if(!strcmp(argv[2],"-pas")){
            nodelay(stdscr,FALSE);
        } else {
            nodelay(stdscr,TRUE);
        }
    }
    
    
    int key; /* Contiendra la touche du clavier capturée par getch() */

    int fin = FALSE; /* indiquera la fin de l'éxécution du code */
    while (key != 'q' && !fin){

        /* initialisation */
        char bin_instruction[32];
        char opcode[7];
        int special = FALSE;


        /* Tant qu'il y a des instructions : */
        while(tableauHexa[PC/4][0] != '\0'){
            IR = tableauHexa[PC/4]; /* on recupère l'instruction correspondant au PC*/

            hexa_to_bin(8,IR,bin_instruction,32); /* traduction en binaire */
            

            /* On cherche l'opcode */
            int k;
            for (k=0;k<6;k++){
                opcode[k] = bin_instruction[k];
            }
            special = FALSE;
            opcode[k+1]='\0';
            if (!strcmp(opcode,"000000")){ /* Cas des instruction de type R ou l'opcode est à la fin */
                for (k=0;k<6;k++){
                special = TRUE;
                opcode[k] = bin_instruction[26+k];
                }
            }
            
            /* On cherche la bonne instruction à éxécuter */   
            if(!special){ 
                if(!strcmp(opcode,"001000")){
                    ADDI(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"000100")){
                    BEQ(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"000101")){
                    BNE(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"000111")){
                    BGTZ(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"000110")){
                    BLEZ(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"000101")){
                    BNE(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"001111")){
                    LUI(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"100011")){
                    LW(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"101011")){
                    SW(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"000011")){
                    JAL(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"000010")){
                    J(bin_instruction,IR);
                    print_log(log_current);
                }
            } else {
                if (!strcmp(opcode,"100000")){
                    ADD(bin_instruction,IR);
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
                }else if (!strcmp(opcode,"100010")){
                    SUB(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"011000")){
                    MULT(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"010010")){
                    MFLO(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"100101")){
                    OR(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"100110")){
                    XOR(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"000010")){
                    if (bin_instruction[10]=='1'){
                        ROTR(bin_instruction,IR);

                    } else {
                        SRL(bin_instruction,IR);
                    }
                    print_log(log_current);
                }else if (!strcmp(opcode,"000000")){
                    SLL(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"101010")){
                    SLT(bin_instruction,IR);
                    print_log(log_current);
                }else if (!strcmp(opcode,"001000")){
                    JR(bin_instruction,IR);
                    print_log(log_current);
                }
            }

            
            


            PC+=4;
                       
            key = getch();
            
        }
        fin = TRUE;
        print_log("--- FIN ---");

    }

    nodelay(stdscr, FALSE);
    getch();
    endwin();
    /* Ecriture dans les fichiers les fichiers states */

    char fichier_state[] = "state/state_reg_";
    if(nom_fichier_state == NULL){
        
        strcat(fichier_state,fichier+6);
        ecriture_fichier_int(fichier_state,tableau_reg,32);
        printf("Ecriture dans '%s' OK\n",fichier_state);
    } else {
        ecriture_fichier_int(nom_fichier_state,tableau_reg,32);
        printf("Ecriture dans '%s' OK\n",nom_fichier_state);
    }
    

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