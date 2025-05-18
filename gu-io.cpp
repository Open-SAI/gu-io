#include <ncurses.h>
#include <time.h>
#include <chrono>
//#include <iostream>

//using namespace std;

int x = 100;
int y = 10;

int orientacion = 1;
char espiga = '\\';

const int NUM_SECONDS = 1;

typedef std::chrono::high_resolution_clock Clock;

void drawscreen(){
	
	clear();
	refresh();

	for (int i = 0; i < y; i++ ){
		for (int j=0; j < x; j++){
			if ( i==0 || i == y-1 || j == 0 || j == x-1){
				addch('#');
			}else{

				addch(espiga);
			}
		}		
	}
	
	refresh();
	
	if(orientacion==1){espiga='|'; orientacion=2; return;}
	if(orientacion==2){espiga='/'; orientacion=3; return;}
	if(orientacion==3){espiga='\\'; orientacion=1; return;}
}



int main(){
	char key;

	double time_counter = 0;

	clock_t this_time = clock();
	clock_t last_time = this_time;


	auto t1 = Clock::now();
	auto t2 = Clock::now();


	initscr();		
	noecho();
	cbreak();
//	raw();
	nodelay(stdscr, TRUE);

 	getmaxyx(stdscr,y,x);	
	drawscreen();

	do{

 		getmaxyx(stdscr,y,x);	

		
		if ((key = getch()) == ERR) {
			/* user hasn't responded */
			this_time = clock();
			time_counter += (double)(this_time - last_time);
			last_time = this_time;

			if(time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC))
		        {
				time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
				drawscreen();
			}

		}else {
			/* user has pressed a key ch */
		}

	}while(key != 'q');

	endwin();

	return 0;
}
