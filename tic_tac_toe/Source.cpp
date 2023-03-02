#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>

char board[3][3]
{
	{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'}
};

char turn = 'X';
bool draw = false;
bool game_over();
void display_board();
void player_turn();

void display_board()
{
	std::cout << "       |       |       " << std::endl;
	std::cout << "   " << board[0][0] << "   |   " << board[0][1] << "   |   " << board[0][2] << "  " << std::endl;
	std::cout << "_______|_______|_______" << std::endl;
	std::cout << "       |       |       " << std::endl;
	std::cout << "   " << board[1][0] << "   |   " << board[1][1] << "   |   " << board[1][2] << "  " << std::endl;
	std::cout << "_______|_______|_______" << std::endl;
	std::cout << "       |       |       " << std::endl;
	std::cout << "   " << board[2][0] << "   |   " << board[2][1] << "   |   " << board[2][2] << "  " << std::endl;
	std::cout << "       |       |       " << std::endl;
}

bool check_validity(char arr[3][3],std::string s)
{
	char x;
	if (s.length() == 1  && std::all_of(s.begin(), s.end(), ::isdigit))
	{
		std::stringstream ss(s);
		ss >> x;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (arr[i][j] == x)
				{
					return true;
				}
			}
		}
		std::cout << "box already filled! Please re-enter";
		return false;
	}
	else
	{
		std::cout << "Invalid! Please re-enter ";
		return false;
	}
}

void update_board(char arr[3][3], std::string y, char turn)
{
	char x;
	std::stringstream ss(y);
	ss >> x;
	char position = '1';
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (x == position)
			{
				if (turn == 'X')
				{
					arr[i][j] = 'X';
					return;
				}
				else if (turn == 'O')
				{
					arr[i][j] = 'O';
					return;
				}
			}
			++position;
		}
	}
}

bool game_over()
{	//checking for horizontal and vertical rows
	for (int i = 0; i < 3; i++)
	{
		if ((board[i][0] == board[i][1] && board[i][0] == board[i][2]) || (board[0][i] == board[1][i] && board[0][i] == board[2][i]))
		{
			return false;
		}
	}
	// checking for diagonal win
	if ((board[0][0] == board[1][1] && board[0][0] == board[2][2]) || (board[0][2] == board[1][1] && board[0][2] == board[2][0]))
	{
		return false;
	}
	//checking if the game is in continue mode 
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] != 'X' && board[i][j] != 'O')
			{
				return true;
			}
		}
	}
	// checking for draw
	draw = true;
	return false;
}

void player_turn()
{
	std::string key;
	std::cout << "Player turn " << turn << ":";
	if (turn == 'X') 
	{
		do 
		{
			std::getline(std::cin, key);
		}while (check_validity(board, key) == false);
		update_board(board, key, turn = 'X');
		turn = 'O';
	}
	else if (turn == 'O')
	{
		do
		{
			std::getline(std::cin, key);
		}while (check_validity(board, key) == false);
		update_board(board, key, turn = 'O');
		turn = 'X';
	}
}


int main()
{
	while (game_over()) 
	{
		display_board();
		player_turn();
		game_over();
	}
	if (turn == 'X' && draw == false) {
		std::cout << "Congratulations! Player with O has won the game";
	}
	else if (turn == 'O' && draw == false) {
		std::cout << "Congratulations! Player with X has won the game";
	}
	else
	{
		std::cout << "Game Drawn";
	}
}

