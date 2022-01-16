#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

extern char * log_current;
extern char ** log_mips;
extern int nb_log;

void start_affichage();
void update_affichage();
void init_affichage();
void print_log(char* str);

#endif