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
int check_bot_valid(int,int); //a - Pending
int check_human_valid(int,int); //b - Pending
void check_winner(char); //c - Pending
//the bot ai that never loses
void bot_smart_move(int i,int j);
void bot_sub_move(int i,int j);
//*******************
int input_generator();

/*@ ensures \forall integer i, j; 0<=i<3 && 0<=j<3 => board[i][j] == ' ';
    assigns board;
 */

void game_init()
{
	int i, j;
	//assign all board space with ' '
	
	/*@ loop invariant 0<=i<3;
	    loop invariant \forall integer m, n; 0<=m<i && 0<=n<3 => board[m][n] == ' ';
	    loop variant 3 - i;
	    loop assigns i, board;
	 */
	
	for(i=0; i<3; i++)
		
		/*@ loop invariant 0<=j<3;
		    loop invariant \forall integer n; 0<=n<j => board[i][n] == ' ';
		    loop variant 3 - j;
		    loop assigns j, board;
		 */
		
		for(j=0; j<3; j++) board[i][j] = ' ';
}

int input_generator()
{
	int r=rand()%4+1;
	return r;
}

//this function checks and accepts player's input
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
		human_input();
	}
	else board[x][y] = 'X';
}

//function that reject an invalid move from the user

/*@ requires 0<=x<3 && 0<=y<3;
    behavior is_valid:
    	assumes board[x][y]==' ';
	ensures \return == 0;
    behavior not_valid:
    	assumes board[x][y]!=' ';
	ensures \return == 1;
    complete behaviors is_valid, not_valid;
    disjoint behaviors is_valid, not_valid;
 */

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

/*@ requires 0<=x<3 && 0<=y<3;
    behavior is_valid:
    	assumes board[x][y]==' ';
	ensures \return == 0;
    behavior not_valid:
    	assumes board[x][y]!=' ';
	ensures \return == 1;
    complete behaviors is_valid, not_valid;
    disjoint behaviors is_valid, not_valid;
 */

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

/*@ predicate verticalLine(int i) =
    (board[0][i] == board[1][i] == board[2][i]);
    
    predicate horizontalLine(int i) =
    (board[i][0] == board[i][1] == board[i][2]);
    
    predicate diagonalLine() =
    (board[0][0] == board[1][1] == board[2][2]) || (board[0][2] == board[1][1] == board[2][0]);
    
    behavior 3V1:
    	assumes verticalLine(0);
	ensures \return == board[0][0];
    behavior 3V2:
    	assumes verticalLine(1);
	ensures \return == board[0][1];
    behavior 3V3:
    	assumes verticalLine(2);
	ensures \return == board[0][2];
    behavior 3H1:
    	assumes horizontalLine(0);
	ensures \return == board[0][0];
    behavior 3H2:
    	assumes horizontalLine(1);
	ensures \return == board[1][0];
    behavior 3H3:
    	assumes horizontalLine(2);
	ensures \return == board[2][0];
    behavior 3D:
    	assumes diagonalLine();
	ensures \return == board[1][1];
    behavior none:
    	assumes !verticalLine(0) && !verticalLine(1) && !verticalLine(2) && !horizontalLine(0) && !horizontalLine(1) && !horizontalLine(2) && !diagonalLine();
	ensures \return == ' ';
    complete behaviors 3V1, 3V2, 3V3, 3H1, 3H2, 3H3, 3D, none;
    disjoint behaviors 3V1, 3V2, 3V3, 3H1, 3H2, 3H3, 3D, none;
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

//check who is the winner

//@ requires flag != ' ';

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
