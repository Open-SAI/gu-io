#include <ncurses.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <utility>

//#include <iostream>


//using namespace std;

int snake_x = 10;
int snake_y = 1;
int snake_size = 5;

int max_scr_x = 0;
int max_scr_y = 0;


int orientacion = 1;
char espiga = '\\';

struct SnakeRing {
	int x;
	int y;

	bool operator==(const SnakeRing& other) const {
		return y == other.y && x == other.x;
	}
};


/*void updateSnake(const std::vector<SnakeRing>& mySnake){
	mySnake.push_back({max_scr_y, 20}); // Head at row 10, col 20
	mySnake.push_back({max_scr_y, 19}); // Body segment
	mySnake.push_back({max_scr_y, 18}); // Body segment

}*/

void displaySnake(const std::vector<SnakeRing>& snake){
	if (snake.empty()){
		return;
	}


	mvprintw(snake[0].y, snake[0].x, "o");

	for (size_t i=1; i<snake.size(); ++i){
		mvprintw(snake[i].y, snake[i].x, "*");
	}

}



const int NUM_SECONDS = 1;

typedef std::chrono::high_resolution_clock Clock;

void drawscreen(){
	
	clear();
	refresh();

	for (int i = 0; i < max_scr_y; i++ ){
		for (int j=0; j < max_scr_x; j++){
			if ( i==0 || i == max_scr_y-1 || j == 0 || j == max_scr_x-1){
				addch('#');
			}else{

				addch(espiga);
			}
		}		
	}
	 	
	max_scr_x = getmaxx(stdscr);
	max_scr_y = getmaxy(stdscr);

	
	std::vector<SnakeRing> mySnake;

	for (int i = 0; i < snake_size; i++){
		mySnake.push_back({snake_x-i, snake_y});
	}

	// Display the snake
	displaySnake(mySnake);	
	
//	refresh();
	
	if(orientacion==1){espiga='|'; orientacion=2; return;}
	if(orientacion==2){espiga='/'; orientacion=3; return;}
	if(orientacion==3){espiga='\\'; orientacion=1; return;}

	snake_x+=1;
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

// 	getmaxyx(stdscr,max_scr_y,max_scr_x);	
	max_scr_x = getmaxx(stdscr);
	max_scr_y = getmaxy(stdscr);

	drawscreen();

	do{

		//getmaxyx(stdscr,y,x);	

		
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
