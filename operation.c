#include <string.h>

#include "memoire.h"
#include "registres.h"
#include "affichage.h"
#include "conversion.h"



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
    update_affichage(rd);
    sprintf(log_current,"I=%s\tLe registre $%d a pris la valeur du registre $%d + la valeur du registre $%d",instruction,rd,rs,rt);
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
    sprintf(log_current,"I=%s\tLe registre $%d a pris la valeur du registre $%d + %d",instruction,rt,rs,imm);
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
    char bin_valeur_rd[32];

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

    
    /* Opération AND bit à bit */
    for(k=0; k < 32; k++)
    {
        bin_valeur_rd[k] = (bin_valeur_rs[k] & bin_valeur_rt[k]) + 48;
    }

    /* Ecriture en registres et affichage*/
    ecriture_reg(rd, bin_to_int(bin_valeur_rd,32));
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

    update_affichage(34); 
    /* Branch on Equal */
    if ( lecture_reg(rs) == lecture_reg(rt))
    {
        PC = PC + offset - 4;
    }

    /* Affichage*/
    sprintf(log_current,"I=%s\tSi le registre $%d est égal au registre $%d, alors PC est incrémenté de la valeur de l'offset ",instruction,rs,rt);
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

    update_affichage(34); 
    /* Branch on Greater Than Zero */
    if(lecture_reg(rs) > 0)
    {
        PC = PC + offset - 4;
    }
    
    /* Affichage*/
    sprintf(log_current,"I=%s\tSi le registre $%d est supérieur à 0, alors PC est incrémenté de la valeur de l'offset",instruction,rs);
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

    update_affichage(34); 
    /* Branch on Less Than or Equal to Zero */
    if(lecture_reg(rs) <= 0)
    {
        PC = PC + offset - 4;
    }
    
    /* Affichage*/
    
    sprintf(log_current,"I=%s\tSi le registre $%d est inférieur ou égale à 0, alors PC est incrémenté de la valeur de l'offset",instruction,rs);
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

    update_affichage(34); 
    /* Branch on Not Equal */
    if ( lecture_reg(rs) != lecture_reg(rt))
    {
        PC = PC + offset - 4;
    }

    /* Affichage*/
    sprintf(log_current,"I=%s\tSi le registre $%d est différent du registre $%d, alors PC est incrémenté de la valeur de l'offset ",instruction,rs,rt);
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

    ecriture_reg(33, (lecture_reg(rs) / lecture_reg(rt)) ); /* On place le quotient de la division dans LO */ 
    ecriture_reg(32, (lecture_reg(rs) % lecture_reg(rt)) ); /* On place le reste de la division dans HI */

    /* Affichage*/
    update_affichage(32); 
    update_affichage(33); 
    sprintf(log_current,"I=%s\tLe registre $%d et $%d ont pris la valeur du quotient et du reste de la valeur du registre $%d / la valeur du registre $%d",instruction,33,32,rs,rt);
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
    index = bin_to_int(bin_jump,26);
    
    update_affichage(34); 
    /* Jump */

    PC = index - 4;

    /* Affichage*/
    sprintf(log_current,"I=%s\tJump au PC = %d",instruction,index);
}




void JAL(char* bin_instruction, char *instruction)
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
    index = bin_to_int(bin_jump,26);
    
    /* Jump and Link */

    ecriture_reg(31,PC+4); /* On place l'adresse de retour dans le registre 31 */ 

    update_affichage(34); 
    PC = index - 4;

    /* Affichage*/
    
    sprintf(log_current,"I=%s\tJump and Link au PC = %d",instruction,index);
}

void JR(char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation du registre */
    int rs;

    /* Initialisation du registre en binaire */ 
    char bin_rs[5];    

    /* Lecture du registre */
    for (k=6;k<11;k++){
        bin_rs[j] = bin_instruction[k];
        j++;
    }
    
    /* Convertion du binaire en entier */
    rs = bin_to_int(bin_rs,5);
    
    /* Jump Register */

    update_affichage(34); 
    PC = lecture_reg(rs)-4; /* On lit la valeur du registre comme nouvelle valeur du PC */ 

    /* Affichage*/
    
    sprintf(log_current,"I=%s\tJump Register au PC = %d",instruction,lecture_reg(rs));
}

void LUI(char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation des registres en entier de l'opération */
    int rt,imm,imm_upp;

    /* Initialisation des registres en binaire de l'opération  */     
    char bin_rt[5];
    char bin_imm[16];

    /* Lecture de la valeur des registres */
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
    rt = bin_to_int(bin_rt,5);
    imm = bin_to_int(bin_imm,16);

    imm_upp = imm*pow(2,16);

    ecriture_reg(rt,imm_upp);

    /* Affichage*/ 
    update_affichage(rt);
    sprintf(log_current,"I=%s\tLoad Upper Immediate de la valeur immédiate %d dans le registre $%d ",instruction,imm,rt);
}


void LW( char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation des registres en entier de l'opération */
    int base,rt,offset;

    /* Initialisation des registres en binaire de l'opération  */     
    char bin_base[5];
    char bin_rt[5];
    char bin_offset[16];

    /* Valeur chargé depuis la mémoire */
    int valeur_mem;

    /* Lecture de la valeur des registres */
    for (k=6;k<11;k++){
        bin_base[j] = bin_instruction[k];
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
    base = bin_to_int(bin_base,5);
    rt = bin_to_int(bin_rt,5);
    offset = bin_to_int(bin_offset,16);

    /* Ecriture en registres et affichage*/
    valeur_mem = lecture_mem(base)>>offset;
    ecriture_reg(rt, valeur_mem);


    update_affichage(rt);
    sprintf(log_current,"I=%s\tLe registre $%d a pris la valeur de la case mémoire $%d + %d ",instruction,rt,base,offset);
}

void MFHI( char* bin_instruction, char *instruction)
{
    int k,j,HI = 0;

    /* Initialisation des registres en entier de l'opération */
    int rd;

    /* Initialisation des registres en binaire de l'opération  */     
    char bin_rd[5];
    
    /* Lecture de la valeur des registres */
    j=0;
    for(k=16;k<21;k++){
        bin_rd[j] = bin_instruction[k];
        
        j++;
    }
    
    /* Convertion des registres du binaire en entier */
    rd = bin_to_int(bin_rd,5);

    /* Move From HI Register */
    
    HI = lecture_reg(32);
    ecriture_reg(rd, HI);

    /* Affichage */
    update_affichage(rd);
    sprintf(log_current,"I=%s\tLa valeur du registre HI a été copié dans le registre $%d",instruction,rd);
}

void MFLO( char* bin_instruction, char *instruction)
{
    int k,j,LO= 0;

    /* Initialisation des registres en entier de l'opération */
    int rd;

    /* Initialisation des registres en binaire de l'opération  */     
    char bin_rd[5];

    /* Lecture de la valeur des registres */
    j=0;
    for(k=16;k<21;k++){
        bin_rd[j] = bin_instruction[k];
        j++;
    }
    
    /* Convertion des registres du binaire en entier */
    rd = bin_to_int(bin_rd,5);

    /* Move From LO Register */

    LO = lecture_reg(33);
    ecriture_reg(rd, LO);

    /* Affichage */
    update_affichage(rd);
    sprintf(log_current,"I=%s\tLa valeur du registre LO a été copié dans le registre $%d",instruction,rd);
}

void MULT(char* bin_instruction, char *instruction)
{
    int k,j = 0;
    int result;
    int result_HI, result_LO;

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

    /* Convertion des registres en binaires en entier */
    rs = bin_to_int(bin_rs,5);
    rt = bin_to_int(bin_rt,5);

    /* Ecriture en registres et affichage*/

    result = lecture_reg(rs)*lecture_reg(rt);

    result_HI = result/pow(2,32);
    result_LO = result - result_HI;
    

    ecriture_reg(33, result_HI);
    ecriture_reg(32, result_LO);
    update_affichage(32);
    update_affichage(33);
    sprintf(log_current,"I=%s\tLes registres HI et LO ont pris la valeur du registre $%d * la valeur du registre $%d",instruction,rs,rt);
}

void NOP(char* bin_instruction, char *instruction)
{
    sprintf(log_current,"I=%s\tNOP",instruction);
}

void OR(char* bin_instruction, char *instruction)
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
    char bin_valeur_rd[32];

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
    
    /* Opération OR bit à bit */
    for(k=0; k < 32; k++)
    {
        bin_valeur_rd[k] = (bin_valeur_rs[k] | bin_valeur_rt[k]) + 48;
    }

    /* Ecriture en registres et affichage*/
    ecriture_reg(rd, bin_to_int(bin_valeur_rd,32));
    update_affichage(rd);
    sprintf(log_current,"I=%s\tLe registre $%d a pris la valeur du registre $%d OR la valeur du registre $%d",instruction,rd,rs,rt);
}

void SUB(char* bin_instruction, char *instruction)
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
    ecriture_reg(rd,lecture_reg(rs) - lecture_reg(rt));
    update_affichage(rd);
    sprintf(log_current,"I=%s\tLe registre $%d a pris la valeur du registre $%d - la valeur du registre $%d",instruction,rd,rs,rt);
}

void SW( char* bin_instruction, char *instruction)
{
    int k,j = 0;

    /* Initialisation des registres en entier de l'opération */
    int base,rt,offset;

    /* Initialisation des registres en binaire de l'opération  */     
    char bin_base[5];
    char bin_rt[5];
    char bin_offset[16];

    /* Valeur chargé depuis la mémoire */
    int valeur_mem;

    /* Lecture de la valeur des registres */
    for (k=6;k<11;k++){
        bin_base[j] = bin_instruction[k];
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
    base = bin_to_int(bin_base,5);
    rt = bin_to_int(bin_rt,5);
    offset = bin_to_int(bin_offset,16);

    /* Ecriture en registres et affichage*/

    ecriture_mem( base*16 ,lecture_reg(rt)<<offset);   
    update_affichage();
    sprintf(log_current,"I=%s\tLa mémoire %d + %d a pris la valeur du registre $%d ",instruction,base,offset,rt);
}


void XOR(char* bin_instruction, char *instruction)
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
    char bin_valeur_rd[32];

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
    
    /* Opération XOR bit à bit */
    for(k=0; k < 32; k++)
    {
        bin_valeur_rd[k] = (bin_valeur_rs[k] ^ bin_valeur_rt[k]) + 48;
    }

    /* Ecriture en registres et affichage*/
    ecriture_reg(rd, bin_to_int(bin_valeur_rd,32));
    update_affichage(rd);
    sprintf(log_current,"I=%s\tLe registre $%d a pris la valeur du registre $%d XOR la valeur du registre $%d",instruction,rd,rs,rt);
}

void SLT(char* bin_instruction, char *instruction)
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

    /* Set on Less Than */

    if(lecture_reg(rs) < lecture_reg(rt))
    {
        ecriture_reg(rd,1);
    }
    else
    {
        ecriture_reg(rd,0);
    }

    update_affichage(rd);
    sprintf(log_current,"I=%s\tLe registre $%d a pris la valeur du registre $%d < la valeur du registre $%d ",instruction,rd,rs,rt);
}

void SLL(char* bin_instruction, char *instruction)
{
    int k,j,i,l = 0;
    int temp;

    /* Initialisation des registres en entier de l'opération */
    int rt,rd,sa;

    /* Initialisation des 3 registres en binaire de l'opération  */     
    char bin_rt[5];
    char bin_rd[5];
    char bin_sa[5];

    /* Initialisation des tableau en binaire des valeurs dans les registres */
    
    int bin_valeur_rt[32];

    /* Lecture de la valeur des registres */
    
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
    j = 0;
    for (k=21;k<26;k++){
        bin_sa[j] = bin_instruction[k];
        j++;
    }
    
    /* Convertion des registres en binaires en entier */
    
    rt = bin_to_int(bin_rt,5);
    rd = bin_to_int(bin_rd,5);
    sa = bin_to_int(bin_sa,5);

    /* Convertion des valeurs en registre en binaire */
    
    /*int_to_binary(lecture_reg(rt),32,bin_valeur_rt);*/

    /* for(i = 0; i <= sa; i++)
    {
        for(l = 31; l > 0; l--)
        {
            temp = bin_valeur_rt[l-1];
            bin_valeur_rt[l] = temp;
        }
        bin_valeur_rt[i] = 0;
    } */

    ecriture_reg(rd,lecture_reg(rt)<<sa);


    /*ecriture_reg(rd, strtol(bin_valeur_rt,NULL,2))*/

    update_affichage(rd);
    sprintf(log_current,"I=%s\tLe registre $%d a pris la valeur du registre $%d << %d ",instruction,rd,rt,sa);
}


void SRL(char* bin_instruction, char *instruction)
{
    int k,j = 0;

    

    /* Initialisation des registres en entier de l'opération */
    int rt,rd,sa;

    /* Initialisation des 3 registres en binaire de l'opération  */     
    char bin_rt[5];
    char bin_rd[5];
    char bin_sa[5];

    /* Initialisation des tableau en binaire des valeurs dans les registres */
    

    /* Lecture de la valeur des registres */
    
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
    j=0;
    for (k=21;k<26;k++){
        bin_sa[j] = bin_instruction[k];
        j++;
    }
    
    /* Convertion des registres en binaires en entier */
    
    rt = bin_to_int(bin_rt,5);
    rd = bin_to_int(bin_rd,5);
    sa = bin_to_int(bin_sa,5);



    ecriture_reg(rd,lecture_reg(rt)>>sa);


    update_affichage(rd);
    sprintf(log_current,"I=%s\tLe registre $%d a pris la valeur du registre $%d >> %d ",instruction,rd,rt,sa);
}

void ROTR(char* bin_instruction, char *instruction)
{
    int k,j,i,l = 0;

    int temp;
    /* Initialisation des registres en entier de l'opération */
    int rt,rd,sa;

    /* Initialisation des 3 registres en binaire de l'opération  */     
    char bin_rt[5];
    char bin_rd[5];
    char bin_sa[5];

    /* Initialisation des tableau en binaire des valeurs dans les registres */
    
    int bin_valeur_rt[32];
    char*  bin_valeur_rt_str = malloc(32);

    int dernier_bit;


    /* Lecture de la valeur des registres */
    
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
    j=0;
    for (k=21;k<26;k++){
        bin_sa[j] = bin_instruction[k];
        j++;
    }
    
    /* Convertion des registres en binaires en entier */
    
    rt = bin_to_int(bin_rt,5);
    rd = bin_to_int(bin_rd,5);
    sa = bin_to_int(bin_sa,5);


    int haut = lecture_reg(rt) >> sa;

    int rotation_bits = lecture_reg(rt) << (32-sa);

    unsigned int resultat =  haut | rotation_bits;
    
    ecriture_reg(rd, (int) resultat);

    update_affichage(rd);
    sprintf(log_current,"I=%s\tLe registre $%d a pris la valeur du registre $%d << %d ",instruction,rd,rt,sa);
}

