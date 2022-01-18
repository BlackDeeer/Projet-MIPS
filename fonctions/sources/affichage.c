#include <ncurses.h>
#include <string.h>
#include "../header/memoire.h"
#include "../header/registres.h"

WINDOW *fenReg, *fenMem, *fenLog;

char *log_current;
char **log_mips;
int nb_log;

void start_affichage(){
	erase();
	init_pair(1,COLOR_BLUE,COLOR_BLACK);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_RED,COLOR_BLACK);
	init_pair(5,COLOR_WHITE,COLOR_RED);

	attron(COLOR_PAIR(1) | A_BOLD);
	fenReg = subwin(stdscr, 3*LINES / 5+2, COLS /2 -1, 0,0);
	fenMem = subwin(stdscr, 3*LINES / 5+2, COLS /2 -1, 0,COLS/2+1);
	fenLog = subwin(stdscr, 2*LINES / 5-2, COLS, 3*LINES/5+2,0);

	box(fenReg, ACS_VLINE, ACS_HLINE);
	box(fenMem, ACS_VLINE, ACS_HLINE);
	box(fenLog, ACS_VLINE, ACS_HLINE);

	

	mvwprintw(fenReg,0,5,"| REGISTRES |");
	mvwprintw(fenMem,0,5,"| MEMOIRE |");
	
	mvwprintw(fenLog,0,5,"| LOG |");
	wattron(fenLog,COLOR_PAIR(5)|A_NORMAL);
	mvwprintw(fenLog,0,COLS/2-13,"Appuyez sur q pour quitter");
	wattron(fenLog,COLOR_PAIR(2)|A_NORMAL);

	wrefresh(fenReg);
	wrefresh(fenMem);
	wrefresh(fenLog);

	

}

void update_affichage(registre_mod){

	werase(fenReg);
	werase(fenMem);
	wattron(fenReg,COLOR_PAIR(1) | A_BOLD);
	wattron(fenMem,COLOR_PAIR(1) | A_BOLD);
	box(fenReg, ACS_VLINE, ACS_HLINE);
	box(fenMem, ACS_VLINE, ACS_HLINE);
	mvwprintw(fenReg,0,5,"| REGISTRES |");
	mvwprintw(fenMem,0,5,"| MEMOIRE |");
	wattron(fenReg,COLOR_PAIR(2) | A_NORMAL);
	wattron(fenMem,COLOR_PAIR(2) | A_NORMAL);

	int nbCol = 5;
	int nbLin = 8;
	int paddingCol = 6;
	int paddingLin = 3;
	int interC = ( COLS/2 - paddingCol-1 ) / nbCol;
	int interL = ( (3*LINES/5) - (paddingLin-1)/2 ) / nbLin;

	
	int i;
	int j;
	int k = 0;
	for (i=0;i<4;i++){
		for (j=0;j<8;j++){

			if(k!=registre_mod){
				wattron(fenReg,COLOR_PAIR(2) | A_NORMAL);
			} else {
				wattron(fenReg,COLOR_PAIR(4)|A_BOLD);
			}
			
			mvwprintw(fenReg,paddingLin + interL*j , paddingCol + i*interC,"$%2d : %8d",k,tableau_reg[k]);
			k++;
		}
	}
	wattron(fenReg,COLOR_PAIR(3)|A_BOLD);
	mvwprintw(fenReg,paddingLin, paddingCol + 4*interC,"HI : %8d",tableau_reg[32]);
	mvwprintw(fenReg,paddingLin + interL, paddingCol + 4*interC,"LO : %8d",tableau_reg[33]);
	if (registre_mod == 34){
		wattron(fenReg,COLOR_PAIR(4)|A_BOLD);
	} else {
		wattron(fenReg,COLOR_PAIR(3) | A_BOLD);
	}
	mvwprintw(fenReg,paddingLin + interL*3, paddingCol + 4*interC,"PC : %8d",PC);
	mvwprintw(fenReg,paddingLin + interL*4, paddingCol + 4*interC,"IR : %8s",IR);


	wattron(fenMem,COLOR_PAIR(2) | A_NORMAL);
	interC = ( COLS/2 - paddingCol-1 ) / (nbCol-1);
	k=0;
	for (i=0;i<4;i++){
		for (j=0;j<8;j++){
			mvwprintw(fenMem,paddingLin + interL*j , paddingCol + i*interC,"%4d : %8d",k,tableau_mem[k/16]);
			k+=16;
		}
	}
	wrefresh(fenReg);
	wrefresh(fenMem);

}


void init_affichage(){

	
	initscr();
	cbreak();
	/*noecho();*/
	start_color();
	nodelay(stdscr,FALSE);
	mvhline( LINES/2-3, 0 , ACS_HLINE, COLS);
	mvprintw( LINES/2-1, COLS/2-32 , "-- PRESS F11 TO START (OU AFFICHER LA CONSOLE EN PLEIN ECRAN) --");
	mvprintw( LINES/2-0, COLS/2-10 , "ou q pour quitter ...");
	mvhline( LINES/2+2, 0 , ACS_HLINE, COLS);

	
	int key = 0;
	refresh();
	
	while(COLS<209){
		key = wgetch(stdscr);
		refresh();
		if (key == 'q' || COLS<209){
			endwin();
			exit(EXIT_SUCCESS);
		}
	}
	
	log_mips = malloc(COLS);
	*log_mips = (char *) malloc(COLS-10);
	nb_log=1;
	log_current = (char *) malloc(COLS-10);
	start_affichage();
	update_affichage();
	
	

	
}


void print_log(char *str){
	werase(fenLog);
	wattron(fenLog,COLOR_PAIR(1) | A_BOLD);
	box(fenLog, ACS_VLINE, ACS_HLINE);
	mvwprintw(fenLog,0,5,"| LOG |");
	wattron(fenLog,COLOR_PAIR(5)|A_NORMAL);
	mvwprintw(fenLog,0,COLS/2-13,"Appuyez sur q pour quitter");
	wattron(fenLog,COLOR_PAIR(2)|A_NORMAL);

	char **log_temp, **log_temp2;
	int k;
	int lmax = 2*LINES/5-4;

	nb_log ++;
	log_mips = realloc(log_mips,(nb_log)*COLS);
	
	log_temp = log_mips;
	log_temp+=nb_log-2;
	*log_temp = (char *) malloc(COLS-10);
	strcpy(*log_temp,str);
	

	log_temp2 = log_mips;
	

	if (nb_log<lmax){
		for (k=0;k<nb_log-1;k++){
			mvwprintw(fenLog,k+1,2,">\t%s",*log_temp2);
			log_temp2++;
		}
	} else {
		log_temp2+=nb_log-lmax;
		for (k=0;k<lmax-1;k++){
			mvwprintw(fenLog,k+1,2,">\t%s",*log_temp2);
			log_temp2++;
		}
	}
	wrefresh(fenLog);
}
