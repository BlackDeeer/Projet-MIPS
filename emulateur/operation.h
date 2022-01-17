#ifndef __OPERATION_H__
#define __OPERATION_H__



void ADDI(char* bin_instruction, char *instruction);
void ADD(char* bin_instruction, char *instruction);
void J(char* bin_instruction, char *instruction);
void BEQ(char* bin_instruction, char *instruction);
void BNE(char* bin_instruction, char *instruction);
void MFHI(char* bin_instruction, char *instruction);
void DIV(char* bin_instruction, char *instruction);
void AND(char* bin_instruction, char *instruction);
void OR(char* bin_instruction, char *instruction);
void XOR(char* bin_instruction, char *instruction);
void SUB(char* bin_instruction, char *instruction);
void BGTZ(char* bin_instruction, char *instruction);
void MFLO(char* bin_instruction, char *instruction);
void MULT(char* bin_instruction, char *instruction);
void BLEZ(char* bin_instruction, char *instruction);
void LUI(char* bin_instruction, char *instruction);
void BNE(char* bin_instruction, char *instruction);
void SW(char* bin_instruction, char *instruction);
void LW(char* bin_instruction, char *instruction);
void NOP(char* bin_instruction, char *instruction);
void ROTR(char* bin_instruction, char *instruction);
void SLL(char* bin_instruction, char *instruction);
void SLT(char* bin_instruction, char *instruction);
void SRL(char* bin_instruction, char *instruction);
void JR(char* bin_instruction, char *instruction);
void JAL(char* bin_instruction, char *instruction);

#endif