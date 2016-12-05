#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>

const int PADDLE_SIZE = 5;

bool game_on = true;

char player_1_score = '0'; 
int food_x;
int food_y;

//board
struct Board {
	
	char line1[120] =    { "#######################################################         ######################################################" };
	char line2[120] =  { "\n#                                                                                                                    #" };
	char line3[120] =  { "\n#                                                                                                                    #" };
	char line4[120] =  { "\n#                                                                                                                    #" };
	char line5[120] =  { "\n#                                                                                                                    #" };
	char line6[120] =  { "\n#                                                                                                                    #" };
	char line7[120] =  { "\n#                                                                                                                    #" };
	char line8[120] =  { "\n#                                                                                                                    #" };
	char line9[120] =  { "\n#                                                                                                                    #" };
	char line10[120] = { "\n#                                                                                                                    #" };
	char line11[120] = { "\n#                                                                                                                    #" };
	char line12[120] = { "\n#                                                                                                                    #" };
	char line13[120] = { "\n#                                                                                                                    #" };
	char line14[120] = { "\n#                                                                                                                    #" };
	char line15[120] = { "\n#                                                                                                                    #" };
	char line16[120] = { "\n#                                                                                                                    #" };
	char line17[120] = { "\n#                                                                                                                    #" };
	char line18[120] = { "\n#                                                                                                                    #" };
	char line19[120] = { "\n#                                                                                                                    #" };
	char line20[120] = { "\n#                                                                                                                    #" };
	char line21[120] = { "\n#                                                                                                                    #" };
	char line22[120] = { "\n#                                                                                                                    #" };
	char line23[120] = { "\n#                                                                                                                    #" };
	char line24[120] = { "\n#                                                                                                                    #" };
	char line25[120] = { "\n#                                                                                                                    #" };
	char line26[120] = { "\n#                                                                                                                    #" };
	char line27[120] = { "\n#                                                                                                                    #" };
	char line28[120] = { "\n#                                                                                                                    #" };
	char line29[120] = { "\n#                                                                                                                    #" };
	char line30[120] = { "\n######################################################################################################################" };

	char* rows[30] = { line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,
		line11,line12,line13,line14,line15,line16,line17,line18,line19,line20,
		line21,line22,line23,line24,line25,line26,line27,line28,line29,line30 };
};

struct Segment {
	int x;
	int y;
	int x_speed;
	int y_speed;
	Segment* next=NULL;
};

struct Snake {
	Segment* head;
	Segment* tail;
	int size;
};

void draw(Board*, Snake*);
void move_snake(Snake*);

void main() {
	int y;
	food_x=rand()%118+1;
	food_y=rand()%28+1;

	Snake* snake = new Snake;
	Segment* segment = new Segment;
	snake->head = segment;
	snake->tail = segment;
	snake->size = 1;
	snake->head->x = 59;
	snake->head->y = 15;
	snake->head->x_speed = 1;
	snake->head->y_speed = 0;

	while (game_on) {
		Board *board = new Board;
		draw(board, snake);
		move_snake(snake);
		Sleep(10);
	}
				
	std::cout << "\nyou dead son\n";
	std::cin >> y;

	
}

void draw(Board *board, Snake* snake) {
	system("cls");
	board->rows[food_y][food_x] = (char)254u;

	board->rows[0][59] = player_1_score;
	Segment* curr = snake->tail;
	while (curr->next != NULL) {
		board->rows[curr->y][curr->x] = (char)178u;
		curr = curr->next;
	}
	board->rows[curr->y][curr->x] = (char)178u;


	std::cout << board->line1 << board->line2 << board->line3 << board->line4 << board->line5 << board->line6 << board->line7 << board->line8
		<< board->line9 << board->line10 << board->line11 << board->line12 << board->line13 << board->line14 << board->line15 << board->line16
		<< board->line17 << board->line18 << board->line19 << board->line20 << board->line21 << board->line22 << board->line23 << board->line24
		<< board->line25 << board->line26 << board->line27 << board->line28 << board->line29 << board->line30;
}

void move_snake(Snake* snake) {


	if (snake->head->x == food_x&&snake->head->y == food_y) {
		Segment* segment = new Segment;
		segment->next = snake->tail;
		snake->tail = segment;
		snake->size++; 
		food_x = rand() % 118 + 1;
		food_y = rand() % 28 + 1;
	}

	Segment* curr = snake->tail;
	while (curr != snake->head) {
		curr->x = curr->next->x;
		curr->x_speed = curr->next->x_speed;
		curr->y = curr->next->y;
		curr->y_speed = curr->next->y_speed;
		curr = curr->next;
	}

	if (GetAsyncKeyState(VK_UP)) {
		if (snake->head->x_speed != 0) {
			snake->head->y_speed = -1;
			snake->head->x_speed = 0;
		}
	}else if (GetAsyncKeyState(VK_DOWN)) {
		if (snake->head->x_speed != 0) {
			snake->head->y_speed = 1;
			snake->head->x_speed = 0;
		}
	}else if (GetAsyncKeyState(VK_LEFT)) {
		if (snake->head->y_speed != 0) {
			snake->head->y_speed = 0;
			snake->head->x_speed = -1;
		}
	}else if (GetAsyncKeyState(VK_RIGHT)) {
		if (snake->head->y_speed != 0) {
			snake->head->y_speed = 0;
			snake->head->x_speed = 1;
		}
	}

	if (snake->head->x == 0 || snake->head->x == 118 || snake->head->y == 0 || snake->head->y == 29) {
		game_on = false;
	}
	
	if (snake->size > 3) {
		curr = snake->tail;
		while (curr->next->next != snake->head) {
			if (snake->head->x == curr->x && snake->head->y == curr->y) {
				game_on = false;
			}
			curr = curr->next;
		}
	}

	snake->head->x = snake->head->x + snake->head->x_speed;
	snake->head->y = snake->head->y + snake->head->y_speed;

}
