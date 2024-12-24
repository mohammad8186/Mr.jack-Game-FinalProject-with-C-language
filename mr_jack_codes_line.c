#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 9
#define COLS 13

#define UP 119
#define LEFT 97
#define RIGHT 100
#define DOWN 115
#define ESC 27
#define ENTER 10

enum Style
{
	BLANKE = '0',
	WELL = '1',
	LIGHT = '2',
	HOUSE = '3',
	BLOCK = 'B'
};

enum Character
{
	SG, //
	IL, //
	WG, //
	SH, //
	JB, //
	JW,
	MS,
	JS
};

typedef struct Person person;
struct Person
{
	char name[2];
	person *next;
};

typedef struct Cell cell;
struct Cell
{
	char c;
	int Active;
	enum Style s;
	person *p;
};

typedef struct Point point;
struct Point
{
	int x;
	int y;
};

typedef struct Tokens tokens;
struct Tokens
{
	point wells[2];
	point ligth_on[6];
	point block_cel[2];
};

void initial_board(cell board[][COLS], tokens t);
void display_board(cell board[][COLS], tokens t);
int get_user_move();
int convert_user_input(int user_input, int);
int legal_position(int move, cell board[][COLS]);
void make_move(int move, int *cor, cell board[][COLS]);
void game_run(cell board[][COLS], tokens t);

int main()
{
	cell board[ROWS][COLS];
	tokens t;
	initial_board(board, t);
	display_board(board, t);
	game_run(board, t);
	return 0;
}
void initial_board(cell board[][COLS], tokens t)
{
	int i, j;
	char temp_char[26];
	FILE *f_in;
	f_in = fopen("mr_jack_data.txt", "r");

	fread(temp_char, sizeof(char), 26, f_in);
	for (i = 0; i < ROWS; i++)
	{
		fread(temp_char, sizeof(char), 26, f_in);
		for (j = 0; j < COLS; j++)
		{
			board[i][j].s = temp_char[2 * j];
			board[i][j].Active = 0;
			board[i][j].p = NULL;
		}
	}
	for (j = 0; j < 6; j++)
	{
		fread(temp_char, sizeof(char), 4, f_in);
		board[temp_char[0] - '0'][temp_char[2] - '0'].Active = 1; // light
		t.ligth_on[j].x = temp_char[0] - '0';
		t.ligth_on[j].y = temp_char[2] - '0';
	}

	fread(temp_char, sizeof(char), 4, f_in);
	for (j = 0; j < 2; j++)
	{
		fread(temp_char, sizeof(char), 4, f_in);
		board[temp_char[0] - '0'][temp_char[2] - '0'].Active = 1; // well
		t.wells[j].x = temp_char[0] - '0';
		t.wells[j].y = temp_char[2] - '0';
	}
	fread(temp_char, sizeof(char), 4, f_in);
	for (j = 0; j < 2; j++)
	{
		fread(temp_char, sizeof(char), 4, f_in);
		board[temp_char[0] - '0'][temp_char[2] - '0'].Active = 1; // block
		t.block_cel[j].x = temp_char[0] - '0';
		t.block_cel[j].y = temp_char[2] - '0';
	}
	fread(temp_char, sizeof(char), 4, f_in);
	for (j = 0; j < 8; j++)
	{
		char char_name[8][3] = {"SG\0", "IL\0", "WG\0", "SH\0", "JB\0", "JW\0", "MS\0", "JS\0"};
		fread(temp_char, sizeof(char), 4, f_in);
		person *p = (person *)malloc(sizeof(person));
		strcpy(p->name, char_name[j]);
		// p->name = char_name[j];
		// printf("%s  ", char_name[j]);
		p->next = NULL;
		board[temp_char[0] - '0'][temp_char[2] - '0'].p = p; // character
	}
	fclose(f_in);
}

void display_board(cell board[][COLS], tokens t)
{
	int c, r;
	printf("\n");
	for (r = 0; r < ROWS; r++)
	{
		printf("\033[37m%d ", ROWS - (r + 1));
		for (c = 0; c < COLS; c++)
			if (board[r][c].p == NULL)
			{
				if (board[r][c].s == BLOCK)
					printf("\033[31m"); // Red
				else if (board[r][c].s == WELL)
					printf("\033[34m"); // Blue
				else if (board[r][c].s == LIGHT)
					printf("\033[35m"); //
				else if (board[r][c].s == HOUSE)
					printf("\033[33m"); //
				else
					printf("\033[37m"); // White
				printf(" %c%c ", board[r][c].s, board[r][c].Active ? '`' : ' ');
			}
			else
				printf(" \033[32m%s ", board[r][c].p->name); // Green
		printf("\n");
	}
	printf("   \033[37m");
	for (c = 0; c < COLS; c++)
		if (c < 10)
			printf("%d   ", c);
		else
			printf("%d  ", c);

	printf("\n");
}

int legal_position(int move, cell board[][COLS])
{
	// if (valid_position(move) == -1)
	// return -1;
	// if (board[move / COLS][move % ROWS].c == PATH)
	// return 1;
	// else
	// return -1;
}

void make_move(int move, int *corrent, cell board[][COLS])
{
	// board[*corrent / COLS][*corrent % ROWS].c = PATH; // I -> 0
	// board[move / COLS][move % ROWS].c = PLAYER;		  // 0 -> I
	// *corrent = move;
}

int get_user_move()
{
	int move;
	move = getchar();
	// scanf("%c", &move);
	// printf("%d ove:", move);

	// scanf_s("%d", &move);
	return move;
}

int convert_user_input(int user_input, int corrent)
{
	switch (user_input)
	{
	case UP:
		return corrent - COLS;
	case LEFT:
		return corrent - 1;
	case RIGHT:
		return corrent + 1;
	case DOWN:
		return corrent + COLS;

	case ENTER:
		return ENTER;

	case ESC:
		return ESC;

	default:
		return -1;
	}
}
int is_select(int list[4], int k, int r)
{
	for (int i = 0; i < k; i++)
	{
		if (list[i] == r)
		{
			return 1;
		}
	}
	return 0;
}
void add_invert_data(int listA[4], int listB[4])
{
	int find, index = 0;
	for (int i = 0; i < 8; i++)
	{
		find = 0;
		for (int j = 0; j < 4; j++)
		{
			if (listA[j] == i)
			{
				find = 1;
				break;
			}
		}
		if (find == 0)
		{
			listB[index++] = i;
			// printf("%d\n", i);
		}
	}
}

void print_card(int list[4])
{
	char char_name[8][3] = {"SG\0", "IL\0", "WG\0", "SH\0", "JB\0", "JW\0", "MS\0", "JS\0"};
	for (int i = 0; i < 4; i++)
	{
		printf("%s ", char_name[list[i]]);
	}
	printf("\n");
}
void choose_card(int listA[4], int listB[4])
{
	int r, i = 0;
	for (i = 0; i < 4; i++)
	{
		r = rand() % 8;
		while (is_select(listA, i, r))
		{
			// printf("%d ", cell);
			r = rand() % 8;
		}
		listA[i] = r;
		// printf("%d\n", r);
	}
	// printf("\n");
	add_invert_data(listA, listB);
}

void game_run(cell board[][COLS], tokens t)
{
	int continue_game = 1, turn = 0, jack_seen = 0, user_input, move;
	int listA[4], listB[4];
	srand(1400);
	while (continue_game)
	{
		choose_card(listA, listB);
		print_card(turn ? listA : listB);
		user_input = get_user_move();
		move = convert_user_input(user_input, 0);
		// printf("    m = %d\n", corrent);
		if (move == ESC)
			break;
		if (move == ENTER)
			continue;
		if (legal_position(move, board) != -1)
		{
			// make_move(move, &corrent, board);
			display_board(board, t);
			move++;
		}
		else
			printf("Invalid move. Please choose an appropriate square.\n");
	}

}
