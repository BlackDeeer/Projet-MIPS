#include 


void ADD(char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation des registres en entier de l'opération */
    int rs,rt,rd;

    /* Initialisation des 3 registres en binaire de l'opération  */     
    char bin_rs[5];
    char bin_rt[5];
    char bin_rd[5];

    /* Lecture de la valeur des registres */
    for (k=6;k<11;k++){
        bin_rs[j] = bin_instruction[k];
        j++;
    }
    j = 0;
    for(k=11;k<16;k++){
        bin_rt[j] = bin_instruction[k];
        j++;
    }
    j = 0;
    for(k=16;k<22;k++){
        bin_rd[j] = bin_instruction[k];
        j++;
    }
    
    /* Convertion des registres en binaires en entier */
    rs = bin_to_int(bin_rs,5);
    rt = bin_to_int(bin_rt,5);
    rd = bin_to_int(bin_rd,5);

    /* Ecriture en registres et affichage*/
    ecriture_reg(rd,lecture_reg(rs) + lecture_reg(rt));
    update_affichage(rt);
    sprintf(log_current,"Le registre $%d a pris la valeur du registre $%d + %d\t%s",rd,rs,rt,instruction);
}

void ADDI( char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation des registres en entier de l'opération */
    int rs,rd,imm;

    /* Initialisation des 3 registres en binaire de l'opération  */     
    char bin_rs[5];
    char bin_rt[5];
    char bin_imm[16];

    /* Lecture de la valeur des registres */
    for (k=6;k<11;k++){
        bin_rs[k-6] = bin_instruction[k];
        j++;
    }
    j = 0;
    for(k=11;k<16;k++){
        bin_rd[k-11] = bin_instruction[k];
        j++;
    }
    j = 0;
    for(k=16;k<32;k++){
        bin_imm[k-16] = bin_instruction[k];
        j++;
    }
    
    /* Convertion des registres en binaires en entier */
    rs = bin_to_int(bin_rs,5);
    rd = bin_to_int(bin_rd,5);
    imm = bin_to_int(bin_imm,16);

    /* Ecriture en registres et affichage*/
    ecriture_reg(rd,lecture_reg(rs)+imm);
    update_affichage(rd);
    sprintf(log_current,"Le registre $%d a pris la valeur du registre $%d + %d\t%s",rd,rs,imm,instruction);
}


void AND(char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation des registres en entier de l'opération */
    int rs,rt,rd;

    /* Initialisation des 3 registres en binaire de l'opération  */     
    char bin_rs[5];
    char bin_rt[5];
    char bin_rd[5];

    /* Lecture de la valeur des registres */
    for (k=6;k<11;k++){
        bin_rs[j] = bin_instruction[k];
        j++;
    }
    j = 0;
    for(k=11;k<16;k++){
        bin_rt[j] = bin_instruction[k];
        j++;
    }
    j = 0;
    for(k=16;k<22;k++){
        bin_rd[j] = bin_instruction[k];
        j++;
    }

    
    
    /* Convertion des registres en binaires en entier */
    rs = bin_to_int(bin_rs,5);
    rt = bin_to_int(bin_rt,5);
    rd = bin_to_int(bin_rd,5);

    /* Opération AND bit à bit */

    ( int x, int length, int binary[] )

    int_to_binary(lecture_reg(rs),32,  );
    lecture_reg(rt);
    
    for(k=0,k < 5, k++)
    {
        bin_rs[k] = bin_t

    }

    /* Ecriture en registres et affichage*/
    ecriture_reg(rd,lecture_reg(rs) + lecture_reg(rt));
    update_affichage(rt);
    sprintf(log_current,"Le registre $%d a pris la valeur du registre $%d + %d\t%s",rd,rs,rt,instruction);
}

