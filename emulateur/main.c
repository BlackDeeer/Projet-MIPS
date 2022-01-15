#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#include "../fonctions/header/memoire.h"
#include "../fonctions/header/registres.h"
#include "../fonctions/header/affichage.h"
#include "../fonctions/header/conversion.h"


int main(){

    initialisation_reg();
    initialisation_mem();
    init_affichage();
    int key;
    int fin = FALSE;
    while (key != 'q' && !fin){
    
    /*
    int k=0;
    for(k=1;k<32;k++){
        ecriture_reg(k-1,k*2);
        update_affichage();
        wgetch(stdscr);
    }
    */


    /* -------------------------------------- DEBUT LECTURE LIGNE PAR LIGNE ---------------------------------*/
    char* fichier = "hexa_in.txt";
    FILE * fichier_txt;
    char *instruction = malloc(8);
    char *bin_instruction = malloc(32); 
    char *opcode = malloc(6);

	fichier_txt = fopen(fichier,"r"); /* Ouverture du fichier assembleur */

	if (fichier_txt == NULL){
		fprintf(stderr,"Impossible d'ouvrir le fichier : '%s'\n",fichier);
		exit(EXIT_FAILURE);
	}

	/* Tant qu'il existe des fragments à prendre dans le fichier : */
	while(fgets(instruction, 8, fichier_txt) != NULL){
        /*hexa_to_bin(8,instruction,bin_instruction,32);*/
        bin_instruction = "00100001000010000000000000000101";
        int k;
        for (k=0;k<6;k++){
            opcode[k] = bin_instruction[k];
        }
        if (strcmp(opcode,"000000")!=0){
            
            if(strcmp(opcode,"001000")==0){
                char *bin_rs = malloc(5);
                char *bin_rd = malloc(5);
                char *bin_imm = malloc(16);

                for (k=6;k<11;k++){
                    bin_rs[k-6] = bin_instruction[k];
                }
                for (k=11;k<16;k++){
                    bin_rd[k-11] = bin_instruction[k];
                }
                for (k=16;k<32;k++){
                    bin_imm[k-16] = bin_instruction[k];
                }
                
                int rs = bin_to_int(bin_rs,5);
                int rd = bin_to_int(bin_rd,5);
                int imm = bin_to_int(bin_imm,16);



                ecriture_reg(rd,lecture_reg(rs)+imm);
                
                update_affichage();
                char *log_current = (char *) malloc(COLS);
                sprintf(log_current,"Le registre $%d a pris la valeur du registre $%d + %d\n",rd,rs,imm);
                print_log(log_current);
            }
        }
        
    
	}
    fin = TRUE;
	fclose(fichier_txt);

    key = wgetch(stdscr);
    }
    nodelay(stdscr, FALSE);
    getch();
    endwin();
    return(0);

}