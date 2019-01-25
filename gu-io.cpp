#include <ncurses.h>
#include <time.h>
#include <chrono>

//using namespace std;

int x = 100;
int y = 10;

bool orientacion = true;

const int NUM_SECONDS = 2;

typedef std::chrono::high_resolution_clock Clock;

void drawscreen(){
	
	clear();
	refresh();

	for (int i = 0; i < y; i++ ){
		for (int j=0; j < x; j++){
			if ( i==0 || i == y-1 || j == 0 || j == x-1){
				printw("#");
			}else{
				if(orientacion){
					printw("/");
				}else{
					printw("(");

			       	}
			}		
		}
	}
	
	refresh();
	
	if(orientacion){
		orientacion=false;
	}else{
		orientacion=true;
	}

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
