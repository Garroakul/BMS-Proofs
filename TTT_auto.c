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

void game_init(); //game board init
void display(); //graphic support

char check_rule(); //main function checking who wins, proved
void check_winner(char); //just a printing functuon

void human_input(); //takes human input (keyboard input commented, now using auto number generaotr)
int input_generator(); //generates a move for human, including valid & invalid moves
int check_human_valid(int,int); //check human input valid, proved

void bot_input(); //check wether bot should input
int check_bot_valid(int,int); //check bot input valid, proved the dafault condition
void bot_smart_move(int,int); //secondary func for bot move
void bot_sub_move(int,int); //sub func for smart_move

//graphic display for the board
void display()
{
	int i;
	for(i=0; i<3; i++) {
		printf(" %c | %c | %c ",board[i][0],
		board[i][1], board[i][2]);

		if(i!=2) printf("\n---|---|---\n");
	}
	printf("\n");
}

//fill the board with empty space
void game_init()
{
	int i, j;
	//assign all board space with ' '

	for(i=0; i<3; i++){

		for(j=0; j<3; j++){ board[i][j] = ' '; }

	}
}

//check the rule for game ending or not

/*@ predicate verticalLine(integer i) =
    (board[0][i] == board[1][i] == board[2][i]);
    
    predicate horizontalLine(integer i) =
    (board[i][0] == board[i][1] == board[i][2]);
    
    predicate diagonalLine(integer i) =
    (board[0][0] == board[i][i] == board[2][2]) || (board[0][2] == board[i][i] == board[2][0]);
 */

 /*@requires \valid(board + (0..2));
  requires \valid(board[0] + (0..2));
  requires \valid(board[1] + (0..2));
  requires \valid(board[2] + (0..2));
  requires \forall int i,j; (0 <= i <= 2 && 0 <= j <= 2) ==> (board[i][j] == 'X' || board[i][j] == 'O' || board[i][j] == ' ');
    behavior VertOne:
    	assumes verticalLine(0) ;
		ensures \result == board[0][0];
    behavior VertTwo:
    	assumes verticalLine(1) && !(verticalLine(0));
		ensures \result == board[1][1];
    behavior VertThree:
    	assumes verticalLine(2) && !(verticalLine(0) || verticalLine(1));
		ensures \result == board[2][2];
    behavior HorOne:
    	assumes horizontalLine(0) && !(verticalLine(0) || verticalLine(1) || verticalLine(2));
		ensures \result == board[0][0];
    behavior HorTwo:
    	assumes horizontalLine(1)&& !(verticalLine(0) || verticalLine(1) || verticalLine(2) || horizontalLine(0));
		ensures \result == board[1][1];
    behavior HorThree:
    	assumes horizontalLine(2) && !(verticalLine(0) || verticalLine(1) || verticalLine(2) || horizontalLine(0) || horizontalLine(1));
		ensures \result == board[2][2];
    behavior Diag:
    	assumes diagonalLine(1) && !(verticalLine(0) || verticalLine(1) || verticalLine(2) || horizontalLine(0) || horizontalLine(1) || horizontalLine(2));
		ensures \result == board[1][1];
    behavior none:
    	assumes !(verticalLine(0) || verticalLine(1) || verticalLine(2) || horizontalLine(0) || horizontalLine(1) || horizontalLine(2) || diagonalLine(1));
		ensures \result == ' ';
    complete behaviors VertOne, VertTwo, VertThree, HorOne, HorTwo, HorThree, Diag, none;
    disjoint behaviors VertOne, VertTwo, VertThree, HorOne, HorTwo, HorThree, Diag, none;
 */
char check_rule()
{
	// Vertical checks.
	
	if(board[0][0]==board[0][1] && board[0][0]==board[0][2]) 
	return board[0][0];
	
	if(board[1][0]==board[1][1] && board[1][0]==board[1][2]) 
	return board[1][0];

	if(board[2][0]==board[2][1] && board[2][0]==board[2][2]) 
	return board[2][0];
	
	// Horizontal checks.
	
	if(board[0][0]==board[1][0] && board[0][0]==board[2][0]) 
	return board[0][0];

	if(board[0][1]==board[1][1] && board[0][1]==board[2][1]) 
	return board[0][1];

	if(board[0][2]==board[1][2] && board[0][2]==board[2][2]) 
	return board[0][2];
	
	// Diagonal checks.
	
	if(board[0][0]==board[1][1] && board[1][1]==board[2][2])
	return board[0][0];
	
	if(board[0][2]==board[1][1] && board[1][1]==board[2][0])
	return board[0][2];

	return ' ';
}

//just a print function
void check_winner(char flag)
{
	display();
	if(flag=='X') printf("You won the game\n");
	else printf("Bot won the game\n");
}

//this function accepts generator's input
void human_input()
{
	int x, y;
	int valid;
	//printf("Enter your next X,Y coordinate on board: ");
	//scanf("%d%*c%d", &x, &y);

	x=input_generator();
	y=input_generator();
	x--; y--;//to match up with the index range from 1-3 to 0-2

	valid=check_human_valid(x,y);
	if(valid==1){
        printf("Your move is invalid, try another move.\n");
		human_input();
	}
	else board[x][y] = 'X';
}

/*@ ensures \result>=1 && \result<=4;
 */
int input_generator()
{
	int r=rand()%4+1;
	return r;
}

//function that reject an invalid move from the user

/*@ requires 0<=x<3 && 0<=y<3;
    behavior is_valid:
    	assumes board[x][y]==' ';
		ensures \result == 0;
    behavior not_valid:
    	assumes board[x][y]!=' ';
		ensures \result == 1;
    complete behaviors is_valid, not_valid;
    disjoint behaviors is_valid, not_valid;
 */
int check_human_valid(int x,int y)
{
	if(board[x][y]!= ' '){
	return 1;
	}
	else return 0;
}

//this function generates the bot's input
void bot_input()
{
	//check wether there is still space on board
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
		//if still space available
		//check the default bot move board[i][j] (first available spot)
		valid=check_bot_valid(i,j);
		if(valid==1){
            printf("Bot made an invalid move, it's trying again\n");
			bot_input();
		}
	else bot_smart_move(i,j);
	}
}

//bot AI part I
void bot_smart_move(int i,int j)
{
	if(board[1][1]!=' '){
		if(board[1][1]=='X'){
			if(board[0][0]=='X' && board[2][2]==' '){
				board[2][2]='O';
				return;}

			else if(board[0][2]=='X' && board[2][0]==' '){
				board[2][0]='O';
				return;}

			else if(board[2][0]=='X' && board[0][2]==' '){
				board[0][2]='O';
				return;
			}
			else if(board[2][2]=='X' && board[0][0]==' '){
				board[0][0]='O';
				return;}

			else bot_sub_move(i,j);
		}
		else bot_sub_move(i,j);
	}
	else board[1][1] = 'O';
}

//bot AI part II
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

	//check center-diag (4 total)
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

/*@ requires 0<=i<3 && 0<=j<3;
    behavior is_valid:
    	assumes board[i][j]==' ';
	ensures \result == 0;
    behavior not_valid:
    	assumes board[i][j]!=' ';
	ensures \result == 1;
    complete behaviors is_valid, not_valid;
    disjoint behaviors is_valid, not_valid;
 */

int check_bot_valid(int i,int j)
{
	if(board[i][j]!= ' '){
		//This should not happen
		return 1;
	}
	else return 0;
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
