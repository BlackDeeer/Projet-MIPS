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
    for(k=16;k<21;k++){
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
    int rs,rt,imm;

    /* Initialisation des 3 registres en binaire de l'opération  */     
    char bin_rs[5];
    char bin_rt[5];
    char bin_imm[16];

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
    for(k=16;k<32;k++){
        bin_imm[j] = bin_instruction[k];
        j++;
    }
    
    /* Convertion des registres du binaire en entier */
    rs = bin_to_int(bin_rs,5);
    rt = bin_to_int(bin_rt,5);
    imm = bin_to_int(bin_imm,16);

    /* Ecriture en registres et affichage*/
    ecriture_reg(rt,lecture_reg(rs)+imm);
    update_affichage(rt);
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

    /* Initialisation des tableau en binaire des valeurs dans les registres */
    int bin_valeur_rs[32];
    int bin_valeur_rt[32];
    int bin_valeur_rd[32];

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
    for(k=16;k<21;k++){
        bin_rd[j] = bin_instruction[k];
        j++;
    }

    
    
    /* Convertion des registres du binaire en entier */
    rs = bin_to_int(bin_rs,5);
    rt = bin_to_int(bin_rt,5);
    rd = bin_to_int(bin_rd,5);

    /* Convertion des valeurs en registre en binaire */
    int_to_binary(lecture_reg(rs),32,bin_valeur_rs);
    int_to_binary(lecture_reg(rt),32,bin_valeur_rt);
    int_to_binary(lecture_reg(rd),32,bin_valeur_rd);
    
    /* Opération AND bit à bit */
    for(k=0; k < 32; k++)
    {
        bin_valeur_rd[k] = bin_valeur_rs[k] & bin_valeur_rt[k];
    }

    /* Ecriture en registres et affichage*/
    ecriture_reg(rd, bin_to_int(bin_valeur_rd))
    update_affichage(rd);
    sprintf(log_current,"I=%s\tLe registre $%d a pris la valeur du registre $%d AND la valeur du registre $%d",instruction,rd,rs,rt);
}

void BEQ(char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation des registres et de l'offset en entier de l'opération */
    int rs,rt,offset;

    /* Initialisation des registres et de l'offset en binaire de l'opération  */     
    char bin_rs[5];
    char bin_rt[5];
    char bin_offset[16];

    /* Lecture de la valeur des registres et de l'offset */
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
    for(k=16;k<32;k++){
        bin_offset[j] = bin_instruction[k];
        j++;
    }
  
    /* Convertion des registres du binaire en entier */
    rs = bin_to_int(bin_rs,5);
    rt = bin_to_int(bin_rt,5);
    offset = bin_to_int(bin_offset,16);

    /* Branch on Equal */
    if ( lecture_reg(rs) == lecteur_reg(rt))
    {
        PC = PC + offset;
    }

    /* Affichage*/
    update_affichage(34); 
    sprintf(log_current,"I=%s\t Si le registre $%d est égal au registre $%d, alors PC est incrémenté de la valeur de l'offset ",instruction,rs,rt);
}


void BGTZ(char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation du registre et de l'offset en entier de l'opération */
    int rs,offset;

    /* Initialisation du registre et de l'offset en binaire de l'opération  */     
    char bin_rs[5];
    char bin_offset[16];

    /* Lecture de la valeur du registre et de l'offset */
    for (k=6;k<11;k++){
        bin_rs[j] = bin_instruction[k];
        j++;
    }
    j = 0;
    for(k=16;k<32;k++){
        bin_offset[j] = bin_instruction[k];
        j++;
    }
  
    /* Convertion des registres du binaire en entier */
    rs = bin_to_int(bin_rs,5);
    offset = bin_to_int(bin_offset,16);

    /* Branch on Greater Than Zero */
    if(lecture_reg(rs) > 0)
    {
        PC = PC + offset;
    }
    
    /* Affichage*/
    update_affichage(34); 
    sprintf(log_current,"I=%s\t Si le registre $%d est supérieur à 0, alors PC est incrémenté de la valeur de l'offset",instruction,rs);
}


void BLEZ(char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation du registre et de l'offset en entier de l'opération */
    int rs,offset;

    /* Initialisation du registre et de l'offset en binaire de l'opération  */     
    char bin_rs[5];
    char bin_offset[16];

    /* Lecture de la valeur du registre et de l'offset */
    for (k=6;k<11;k++){
        bin_rs[j] = bin_instruction[k];
        j++;
    }
    j = 0;
    for(k=16;k<32;k++){
        bin_offset[j] = bin_instruction[k];
        j++;
    }
  
    /* Convertion des registres du binaire en entier */
    rs = bin_to_int(bin_rs,5);
    offset = bin_to_int(bin_offset,16);

    /* Branch on Less Than or Equal to Zero */
    if(lecture_reg(rs) <= 0)
    {
        PC = PC + offset;
    }
    
    /* Affichage*/
    update_affichage(34); 
    sprintf(log_current,"I=%s\t Si le registre $%d est inférieur ou égale à 0, alors PC est incrémenté de la valeur de l'offset",instruction,rs);
}

void BNE(char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation des registres et de l'offset en entier de l'opération */
    int rs,rt,offset;

    /* Initialisation des registres et de l'offset en binaire de l'opération  */     
    char bin_rs[5];
    char bin_rt[5];
    char bin_offset[16];

    /* Lecture de la valeur des registres et de l'offset */
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
    for(k=16;k<32;k++){
        bin_offset[j] = bin_instruction[k];
        j++;
    }
  
    /* Convertion des registres du binaire en entier */
    rs = bin_to_int(bin_rs,5);
    rt = bin_to_int(bin_rt,5);
    offset = bin_to_int(bin_offset,16);

    /* Branch on Not Equal */
    if ( lecture_reg(rs) != lecteur_reg(rt))
    {
        PC = PC + offset;
    }

    /* Affichage*/
    update_affichage(34); 
    sprintf(log_current,"I=%s\t Si le registre $%d est différent du registre $%d, alors PC est incrémenté de la valeur de l'offset ",instruction,rs,rt);
}

void DIV(char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation des registres en entier de l'opération */
    int rs,rt;

    /* Initialisation des registres en binaire de l'opération  */     
    char bin_rs[5];
    char bin_rt[5];

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
  
    /* Convertion des registres du binaire en entier */
    rs = bin_to_int(bin_rs,5);
    rt = bin_to_int(bin_rt,5);

    /* Opération de division */

    ecriture_reg(33, lecteur_reg(rs) / lecture_reg(rt) ); /* On place le quotient de la division dans LO */ 
    ecriture_reg(32, lecteur_reg(rs) % lecture_reg(rt) ); /* On place le reste de la division dans HI */

    /* Affichage*/
    update_affichage(32); 
    update_affichage(33); 
    sprintf(log_current,"I=%s\t Le registre $%d et $%d ont pris la valeur du quotient et du reste de la valeur du registre $%d / la valeur du registre $%d",instruction,33,32,rs,rt);
}

void J(char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation de l'index */
    int index;

    /* Initialisation de l'index du jump en binaire */     
    char bin_jump[26];

    /* Lecture de l'index */
    for (k=6;k<32;k++){
        bin_jump[j] = bin_instruction[k];
        j++;
    }
    
    /* Convertion du binaire en entier */
    index = bin_to_int(bin_jump);
    
    /* Jump */

    PC = index;

    /* Affichage*/
    update_affichage(34); 
    sprintf(log_current,"I=%s\t Jump au PC =  ",instruction,index);
}


