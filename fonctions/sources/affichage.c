#include <ncurses.h>
#include <string.h>
#include "../header/memoire.h"
#include "../header/registres.h"

WINDOW *fenReg, *fenMem, *fenLog;

char **log_mips;
int nb_log;

void start_affichage(){
	erase();
	init_pair(1,COLOR_BLUE,COLOR_BLACK);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	
	attron(COLOR_PAIR(1) | A_BOLD);
	fenReg = subwin(stdscr, 3*LINES / 5+2, COLS /2, 0,0);
	fenMem = subwin(stdscr, 3*LINES / 5+2, COLS /2, 0,COLS/2+1);
	fenLog = subwin(stdscr, 2*LINES / 5-2, COLS, 3*LINES/5+2,0);

	box(fenReg, ACS_VLINE, ACS_HLINE);
	box(fenMem, ACS_VLINE, ACS_HLINE);
	box(fenLog, ACS_VLINE, ACS_HLINE);

	

	mvwprintw(fenReg,0,5,"| REGISTRES |");
	mvwprintw(fenMem,0,5,"| MEMOIRE |");
	mvwprintw(fenLog,0,5,"| LOG |");


	wrefresh(fenReg);
	wrefresh(fenMem);
	wrefresh(fenLog);

	

}

void update_affichage(){
	int nbCol = 5;
	int nbLin = 8;
	int paddingCol = 6;
	int paddingLin = 3;
	int interC = ( COLS/2 - paddingCol-1 ) / nbCol;
	int interL = ( (3*LINES/5) - (paddingLin-1)/2 ) / nbLin;

	wattron(fenReg,COLOR_PAIR(2) | A_NORMAL);
	int i;
	int j;
	int k = 0;
	for (i=0;i<4;i++){
		for (j=0;j<8;j++){
			mvwprintw(fenReg,paddingLin + interL*j , paddingCol + i*interC,"$%2d : %8d",k,tableau_reg[k]);
			k++;
		}
	}
	wattron(fenReg,A_BOLD);
	mvwvline(fenReg, paddingLin, paddingCol + 4*interC - 3 , ACS_VLINE, 3*8+1);
	mvwprintw(fenReg,paddingLin, paddingCol + 4*interC,"HI : XXXXXXXX");
	mvwprintw(fenReg,paddingLin + interL, paddingCol + 4*interC,"LO : XXXXXXXX");
	mvwprintw(fenReg,paddingLin + interL*3, paddingCol + 4*interC,"PC : XXXXXXXX");
	mvwprintw(fenReg,paddingLin + interL*4, paddingCol + 4*interC,"IR : XXXXXXXX");


	wattron(fenMem,COLOR_PAIR(2) | A_NORMAL);
	interC = ( COLS/2 - paddingCol-1 ) / (nbCol-1);
	k=0;
	for (i=0;i<4;i++){
		for (j=0;j<8;j++){
			mvwprintw(fenMem,paddingLin + interL*j , paddingCol + i*interC,"$%4d : XXXXXXXX",k);
			k+=4;
		}
	}
	wrefresh(fenReg);

}


void init_affichage(){

	initscr();
	cbreak();
	nodelay(stdscr,FALSE);
	/*noecho();*/
	start_color();

	mvhline( LINES/2-3, 0 , ACS_HLINE, COLS);
	mvprintw( LINES/2-1, COLS/2-12 , "-- PRESS F11 TO START --");
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
	nodelay(stdscr,TRUE);
	start_affichage();
	update_affichage();
	
	

	
}


void print_log(char *str){
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
		log_temp2+=nb_log-lmax-1;
		for (k=0;k<lmax-1;k++){
			mvwprintw(fenLog,k+1,2,">\t%s",*log_temp2);
			log_temp2++;
		}
	}
}
