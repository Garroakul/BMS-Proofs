#include <stdio.h>
#include <stdlib.h>

/*Project Tic Tac Toe
  Some things to prove:
  a- the computer's move is valid
  b- the computer will reject an invalid move from the user
  c- the final result reported by the computer is correct (e.g., if
  it says the user won, then the user really did win)
  - other goals as needed
  - the ultimate goal: the computer can never lose (i.e., the worst
  it will do is tie) */

char board[3][3];
void game_init();
void display();

void human_input();

//d before the bot input, it would check whether the game is tie. If it is, then end
void bot_input();
char check_rule();

//*****TO PROVE *****
int check_bot_valid(int,int); //a
int check_human_valid(int,int); //b
void check_winner(char); //c
//the bot ai that never loses
void bot_smart_move(int i,int j);
void bot_sub_move(int i,int j);
//*******************

void game_init()
{
	int i, j;
	//assign all board space with ' '
	for(i=0; i<3; i++)
		for(j=0; j<3; j++) board[i][j] = ' ';
}

//this function checks and accepts player's input
void human_input()
{
	int x, y;
	int valid;
	printf("Enter your next X,Y coordinate on board: ");
	scanf("%d%*c%d", &x, &y);
	x--; y--;//to match up with the index range from 1-3 to 0-2

	valid=check_human_valid(x,y);
	if(valid==1){
		human_input();
	}
	else board[x][y] = 'X';
}

//function that reject an invalid move from the user
int check_human_valid(int x,int y)
{
	if(board[x][y]!= ' '){
	printf("Your move is invalid, try another move.\n");
	return 1;
	}
	else return 0;
}

//this function generates the bot's input
void bot_input()
{
	int i, j;
	int valid;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++)
			if(board[i][j]==' ') break;
		if(board[i][j]==' ') break;
	}

	if(i*j==9) {
	printf("tie\n");
	exit(0);
	}
	else
	{
		//check the default bot move board[i][j]
		valid=check_bot_valid(i,j);
		if(valid==1){
			bot_input();
		}
	else bot_smart_move(i,j);
	}
}

void bot_smart_move(int i,int j)
{
	if(board[1][1]!=' '){
		if(board[1][1]=='X'){
			if(board[0][0]=='X'){
				if(board[2][2]!=' '){
					board[2][2]='O';
					return;
				}
				else bot_sub_move(i,j);
			}
			else if(board[0][2]=='X'){
				if(board[2][0]!=' '){
					board[2][0]='O';
					return;
				}
				else bot_sub_move(i,j);
			}
			else if(board[2][0]=='X'){
				if(board[0][2]!=' '){
					board[0][2]='O';
					return;
				}
				else bot_sub_move(i,j);
			}
			else if(board[2][2]=='X'){
				if(board[0][0]!=' '){
					board[0][0]='O';
					return;
				}
				else bot_sub_move(i,j);
			}
			else bot_sub_move(i,j);
		bot_sub_move(i,j);
		}
		else bot_sub_move(i,j);
	}
	else board[1][1] = 'O';
}

void bot_sub_move(int i,int j)
{
	//check cornor (4 total)
	if(board[0][0]=='X' && board[0][2]=='X' && board[0][1] == ' '){
		board[0][1]='O';
		return;}
	else if(board[0][0]=='X' && board[2][0]=='X' && board[1][0] == ' '){
		board[1][0]='O';
		return;}
	else if(board[2][2]=='X' && board[2][0]=='X' && board[2][1] == ' '){
		board[2][1]='O';
		return;}
	else if(board[2][2]=='X' && board[0][2]=='X' && board[1][2] == ' '){
		board[1][2]='O';
		return;}

	//check center (4 total)
	else if(board[1][1]=='X' && board[0][0]=='X' && board[2][2] == ' '){
		board[2][2]='O';
		return;}
	else if(board[1][1]=='X' && board[2][2]=='X' && board[0][0] == ' '){
		board[0][0]='O';
		return;}
	else if(board[1][1]=='X' && board[2][0]=='X' && board[0][2] == ' '){
		board[0][2]='O';
		return;}
	else if(board[1][1]=='X' && board[0][2]=='X' && board[2][0] == ' '){
		board[2][0]='O';
		return;}

	//check center (4 total)
	else if(board[1][1]=='X' && board[1][0]=='X' && board[1][2] == ' '){
		board[1][2]='O';
		return;}
	else if(board[1][1]=='X' && board[1][2]=='X' && board[1][0] == ' '){
		board[1][0]='O';
		return;}
	else if(board[1][1]=='X' && board[0][1]=='X' && board[2][1] == ' '){
		board[2][1]='O';
		return;}
	else if(board[1][1]=='X' && board[2][1]=='X' && board[0][1] == ' '){
		board[0][1]='O';
		return;}
	//check edges (8 total)
	else if(board[0][0]=='X' && board[0][1]=='X' && board[0][2] == ' '){
		board[0][2]='O';
		return;}
	else if(board[0][0]=='X' && board[1][0]=='X' && board[2][0] == ' '){
		board[2][0]='O';
		return;}
	else if(board[0][2]=='X' && board[0][1]=='X' && board[0][0] == ' '){
		board[0][0]='O';
		return;}
	else if(board[0][2]=='X' && board[1][2]=='X' && board[2][2] == ' '){
		board[2][2]='O';
		return;}
	else if(board[2][0]=='X' && board[1][0]=='X' && board[0][0] == ' '){
		board[0][0]='O';
		return;}
	else if(board[2][0]=='X' && board[2][1]=='X' && board[2][2] == ' '){
		board[2][2]='O';
		return;}
	else if(board[2][2]=='X' && board[2][1]=='X' && board[2][0] == ' '){
		board[2][0]='O';
		return;}
	else if(board[2][2]=='X' && board[1][2]=='X' && board[0][2] == ' '){
		board[0][2]='O';
		return;}
	//use the default move
	else board[i][j]='O';
}

int check_bot_valid(int i,int j)
{
	if(board[i][j]!= ' '){
		printf("Bot made an invalid move, it's trying again\n");
		//This should not happen
		return 1;
	}
	else return 0;
}

//call to display the board
void display()
{
	int t;
	for(t=0; t<3; t++) {
		printf(" %c | %c | %c ",board[t][0],
		board[t][1], board[t][2]);

		if(t!=2) printf("\n---|---|---\n");
	}
	printf("\n");
}

//check the rule for game ending or not
char check_rule()
{
	int i;
	for(i=0; i<3; i++)

		if(board[i][0]==board[i][1] && board[i][0]==board[i][2]) 
		return board[i][0];

	for(i=0; i<3; i++) 

		if(board[0][i]==board[1][i] && board[0][i]==board[2][i]) 
		return board[0][i];

	if(board[0][0]==board[1][1] && board[1][1]==board[2][2])
	return board[0][0];

	if(board[0][2]==board[1][1] && board[1][1]==board[2][0])
	return board[0][2];

	return ' ';
}

//check who is the winner
void check_winner(char flag)
{
	display();
	if(flag=='X') printf("You won the game\n");
	else printf("Bot won the game\n");
}

//main function
int main()
{
	char flag;
	printf("Thanks for playing this dumb game\n");
	flag = ' ';
	game_init();

	do {
		display();
		human_input();
		flag = check_rule();
		if(flag!= ' ') break;
		bot_input();
		flag = check_rule();
	} while(flag== ' ');

	check_winner(flag);
	return 0;
}