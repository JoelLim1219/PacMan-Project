/*PACMAN Assignmnet for Fundamental of Programming June Sem 2023*/
// https://github.com/JoelLim1219/MyStuffs.git

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <cctype>
using namespace std;

void main_menu();
void run_game();
void make_map();
bool display(int t_p_x, int t_p_y, int p_x, int p_y, int g_x, int g_y, int score, int duration, int scale, bool finish);
void e_display(int p_x, int p_y, int g_x, int g_y);
void edit_map();
void arrow_key_movement(int& x, int& y, char key);
void edit_arrow_key_movement(int& x, int& y, char key);
void ghost_movement(int p_x, int p_y, int& g_x, int& g_y);
bool compare_score(SCOREBOARD a, SCOREBOARD b);
void scoreboard(int score, int duration);
void view_scoreboard();

struct INFO_COORDS
{
	bool is_wall;
	bool p_pass;
};

struct INFO_COORDS map[20][40];

struct SCOREBOARD
{
	char name[50];
	int score;
	int duration;
	double compare_score;
};

struct SCOREBOARD player[100];

int main()
{
	main_menu();
	return 0;

}

void main_menu()
{
	char option = '0';
	while (option != 27)
	{
		system("cls");
		cout << "\tPPPPPP     A        CCCCCC   MM      MM       A       NN     N     =======      =======    " << endl;
		cout << "\tP    PP   A A      CC        M M    M M      A A      N N    N   ===========   == +== +==  " << endl;
		cout << "\tPPPPP    A   A     C         M  M  M  M     A   A     N  N   N  ==========     ==  ==  ==  " << endl;
		cout << "\tP       AAAAAAA    C         M   MM   M    AAAAAAA    N   N  N  ======         ==========  " << endl;
		cout << "\tP      A       A   CC        M        M   A       A   N    N N   ===========   ==========  " << endl;
		cout << "\tP     A         A   CCCCCC   M        M  A         A  N     NN     =======     == = = = =  " << endl;
		cout << endl;
		cout << "\t\t\t\t\tPress '1' to start game.\n\n\t\t\t\t\tPress '2' to edit level.\n\n\t\t\t\t\tPress '3' to view scoreboard.\n\n\t\t\t\t\tPress 'Esc' to escape.\n";

		unsigned char option = _getch();

		if (option == '1')
		{
			make_map();
			run_game();
		}

		else if (option == '2')
		{
			make_map();
			edit_map();
		}

		else if (option == '3')
		{
			view_scoreboard();
		}

		else if (option == 27)
			break;

		else
		{
			cout << "Enter a valid option.\n";
			Sleep(200);
		}

	}
}

void run_game()
{
	int t_p_x = 0, t_p_y = 0;
	int player_x = 0, player_y = 0;
	int ghost_x = 39, ghost_y = 19;
	unsigned char key = 0;
	int score = -1;
	int start_time = time(NULL);
	int playing_time, duration;
	int scale = 0;
	int difficulty = 2;
	bool finish = 1;
	
	do
	{
		system("cls");
		cout << "How much do you want to scale up the game? (1 - 3) : ";
		cin >> scale;

		if (scale < 1 || scale > 3)
		{
			cout << "Please enter a valid scale value." << endl;
			Sleep(400);
		}

	} while (scale < 1 || scale > 3 );

	do
	{
		system("cls");
		cout << "Choose your difficulty level [1 - 3] (1 - Hardest / 3 - Easiest) : ";
		cin >> difficulty;

		if (difficulty < 1 || difficulty > 3)
		{
			cout << "Please enter a valid scale value." << endl;
			Sleep(400);
		}

	} while (difficulty < 1 || difficulty > 3);

	for (int count = 0; true; count++) // infinity loop
	{
		system("cls");
		playing_time = time(NULL);
		duration = playing_time - start_time;
		finish = display(t_p_x, t_p_y, player_x, player_y, ghost_x, ghost_y, score, duration, scale, finish);
		if (count % difficulty == 0) // depend on difficulty
			ghost_movement(player_x, player_y, ghost_x, ghost_y);

		if (_kbhit())
		{
			key = _getch();
			if (key == 224)
				key = _getch();

			else if (key == 27) //esc
				break;
		}

		t_p_x = player_x;
		t_p_y = player_y;
		arrow_key_movement(player_x, player_y, key);
		
		if (map[player_y][player_x].p_pass == 0)
		{
			map[player_y][player_x].p_pass = 1;
			score++;
		}

		if (ghost_x == player_x && ghost_y == player_y)
		{
			cout << "GAME OVER!";
			Sleep(500);
			break;
		}

		else if (finish == 1)
		{
			cout << "Congratz! You won! Thanks for playing!";
			Sleep(500);
			break;
		}

		Sleep(50);
	}

	if (key != 27)
		scoreboard(score, duration);
}

void make_map()
{
	int row, column;
	ifstream in_file("map.txt");

	in_file >> row >> column;
	while (in_file)
	{
		in_file >> row >> column;
		map[row][column].is_wall = 1;
	}

	in_file.close();

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 40; column++)
		{
			map[row][column].p_pass = 0;
		}
	}
}

bool display(int t_p_x, int t_p_y, int p_x, int p_y, int g_x, int g_y, int score, int duration, int scale, bool finish)
{
	COORD coord = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //set cursor at top left

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = true;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);

	for (int row = 0; row < 20; row++)
	{
		for (int j = 0; j < scale; j++)
		{
			for (int column = 0; column < 40; column++)
			{
				for (int i = 0; i < scale; i++)
				{
					if (row == p_y && column == p_x)
					{
						if (t_p_x == p_x && t_p_y == p_y)
							cout << "X";
						else if (t_p_x < p_x && t_p_y == p_y)
							cout << ">";
						else if (t_p_x > p_x && t_p_y == p_y)
							cout << "<";
						else if (t_p_x == p_x && t_p_y < p_y)
							cout << "v";
						else if (t_p_x == p_x && t_p_y > p_y)
							cout << "^";

					}
					else if (row == g_y && column == g_x)
						cout << "G";
					else if (map[row][column].is_wall == 0 && map[row][column].p_pass == 1)
						cout << " ";
					else if (map[row][column].is_wall == 0 && map[row][column].p_pass == 0)
					{
						cout << ".";
						finish = 0;
					}
					else if (map[row][column].is_wall == 1)
						cout << "#";
				}
			}
			cout << endl;
		}
	}

	cout << "Score\t:\t" << score << endl;
	cout << "Time\t:\t" << duration << endl;
	return finish;
}

void e_display(int p_x, int p_y, int g_x, int g_y)
{
	COORD coord = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //set cursor at top left

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = true;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 40; column++)
		{
				if (row == p_y && column == p_x)
					cout << "X";
				else if (row == g_y && column == g_x)
					cout << "G";
				else if (map[row][column].is_wall == 0 && map[row][column].p_pass == 1)
					cout << " ";
				else if (map[row][column].is_wall == 0 && map[row][column].p_pass == 0)
					cout << ".";
				else if (map[row][column].is_wall == 1)
					cout << "#";
		}
		cout << endl;
	}

	cout << "Press 'C' to place wall.\nPress 'X' to remove wall." << endl;
}

void edit_map()
{
	ofstream out_file("map.txt");

	int e_x = 0, e_y = 0;
	int e_g_x = 39, e_g_y = 19;
	unsigned char key = 0;
	for (;;)
	{
		system("cls");
		make_map();
		e_display(e_x, e_y, e_g_x, e_g_y);
		if (_kbhit())
		{
			key = _getch();

			if (key == 224)
			{
				key = _getch();
				edit_arrow_key_movement(e_x, e_y, key);
			}

			else if (key == 'C' || key == 'c')
			{
				if (map[e_y][e_x].is_wall == 0)
				{
					if (e_y == 0 && e_x == 0)
						cout << "Cannot place wall at spawn point";
					else if (e_y == e_g_y && e_x == e_g_x)
						cout << "Cannot place wall at ghost spawn point";
					else
						map[e_y][e_x].is_wall = 1;
				}
				
				else if (map[e_y][e_x].is_wall == 1)
					cout << "A wall is already made here!" << endl;
			}

			else if (key == 'X' || key == 'x')
			{
				if (map[e_y][e_x].is_wall == 1)
					map[e_y][e_x].is_wall = 0;
				else if (map[e_y][e_x].is_wall == 0)
					cout << "No wall is here to be removed!" << endl;
			}

			else if (key == 27)
				break;

		}
		
		Sleep(50);
	}

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 40; column++)
		{
			if (map[row][column].is_wall == 1)
				out_file << row << " " << column << endl;
		}
	}

	out_file.close();
}

void arrow_key_movement(int& x, int& y, char key)
{
	if (key == 72)
	{
		if (y > 0 && y <= 19 && map[y - 1][x].is_wall == 0)
		{
			y--;
		}

		else if (y == 0 && map[y + 19][x].is_wall == 0)
		{
			y += 19;
		}
	}

	else if (key == 80)
	{
		if (y >= 0 && y < 19 && map[y + 1][x].is_wall == 0)
		{
			y++;
		}
		else if (y == 19 && map[y - 19][x].is_wall == 0)
			y -= 19;
	}

	else if (key == 75)
	{
		if (x > 0 && x <= 39 && map[y][x - 1].is_wall == 0)
		{
			x--;
		}
		else if (x == 0 && map[y][x + 39].is_wall == 0)
			x += 39;
	}

	else if (key == 77)
	{
		if (x >= 0 && x < 39 && map[y][x + 1].is_wall == 0)
		{
			x++;
		}

		else if (x == 39 && map[y][x - 39].is_wall == 0)
			x -= 39;
	}

}

void edit_arrow_key_movement(int& x, int& y, char key)
{
	if (key == 72)
	{
		if (y > 0 && y <= 19)
		{
			y--;
		}

		else if (y == 0)
		{
			y += 19;
		}
	}

	else if (key == 80)
	{
		if (y >= 0 && y < 19)
		{
			y++;
		}
		else if (y == 19)
			y -= 19;
	}

	else if (key == 75)
	{
		if (x > 0 && x <= 39)
		{
			x--;
		}
		else if (x == 0)
			x += 39;
	}

	else if (key == 77)
	{
		if (x >= 0 && x < 39)
		{
			x++;
		}

		else if (x == 39)
			x -= 39;
	}

}

void ghost_movement(int p_x, int p_y, int& g_x, int& g_y)
{
	int r_distance = pow(double(abs(g_x + 1 - p_x)), 2) + pow(double(abs(g_y - p_y)), 2);
	int l_distance = pow(double(abs(g_x - 1 - p_x)), 2) + pow(double(abs(g_y - p_y)), 2);
	int d_distance = pow(double(abs(g_x - p_x)), 2) + pow(double(abs(g_y + 1 - p_y)), 2);
	int u_distance = pow(double(abs(g_x - p_x)), 2) + pow(double(abs(g_y - 1 - p_y)), 2);
	int distance[4] = { r_distance,l_distance,d_distance,u_distance };

	for (int i = 0; i < 4; i++)
	{
		for (int j = (i + 1); j < 4; j++)
		{
			if (distance[i] >= distance[j])
			{
				int temp = distance[i];
				distance[i] = distance[j];
				distance[j] = temp;
			}
		}
	}

	if (distance[0] == u_distance && map[g_y - 1][g_x].is_wall == 0) //prioritise up and down
		g_y--;

	else if (distance[0] == d_distance && map[g_y + 1][g_x].is_wall == 0)
		g_y++;

	else if (distance[0] == r_distance && map[g_y][g_x + 1].is_wall == 0)
		g_x++;

	else if (distance[0] == l_distance && map[g_y][g_x - 1].is_wall == 0)
		g_x--;

	else if (distance[1] == u_distance && map[g_y - 1][g_x].is_wall == 0)
		g_y--;

	else if (distance[1] == d_distance && map[g_y + 1][g_x].is_wall == 0)
		g_y++;

	else if (distance[1] == r_distance && map[g_y][g_x + 1].is_wall == 0)
		g_x++;

	else if (distance[1] == l_distance && map[g_y][g_x - 1].is_wall == 0)
		g_x--;

	else if (distance[2] == u_distance && map[g_y - 1][g_x].is_wall == 0)
		g_y--;

	else if (distance[2] == d_distance && map[g_y + 1][g_x].is_wall == 0)
		g_y++;

	else if (distance[2] == r_distance && map[g_y][g_x + 1].is_wall == 0)
		g_x++;

	else if (distance[2] == l_distance && map[g_y][g_x - 1].is_wall == 0)
		g_x--;

	else if (distance[3] == u_distance && map[g_y - 1][g_x].is_wall == 0)
		g_y--;

	else if (distance[3] == d_distance && map[g_y + 1][g_x].is_wall == 0)
		g_y++;

	else if (distance[3] == r_distance && map[g_y][g_x + 1].is_wall == 0)
		g_x++;

	else if (distance[3] == l_distance && map[g_y][g_x - 1].is_wall == 0)
		g_x--;

}

bool compare_score(SCOREBOARD a, SCOREBOARD b)
{
	return a.score > b.score;
}

void scoreboard(int score, int duration)
{
	int count = 0;

	ifstream in_file("scoreboard.txt");

	do
	{
		system("cls");
		cout << "Player name (4 words only) [insert '0' if do not wish to record stats]: ";
		cin >> player[count].name;

	} while (strlen(player[count].name) > 4);

	if (strcmp(player[count].name, "0") == 0)
		return;

	player[count].score = score;
	player[count].duration = duration;
	player[count].compare_score = player[count].score / player[count].duration;
	
	count++;
	
	in_file >> player[count].name >> player[count].score >> player[count].duration;
	player[count].compare_score = 1.0 * player[count].score / player[count].duration;
	while (in_file)
	{
		count++;
		in_file >> player[count].name >> player[count].score >> player[count].duration;
		player[count].compare_score = 1.0*player[count].score / player[count].duration;
	}

	in_file.close();

	//arrange it in descending order according to score
	sort(std::begin(player), std::end(player), &compare_score);

	ofstream out_file("scoreboard.txt");

	system("cls");

	cout << "The more you score and the less time you take the higher you are in the board!\n" << endl;
	cout << "===============================================================================" << endl;
	cout << "\t\t\t\tLEADERBOARD" << endl;
	cout << "===============================================================================\n" << endl;
	cout << "\t\t\tNo\tName\tScore\tDuration" << endl;

	for (int i = 0; i < count; i++)
	{
		cout << "\t\t\t" << i + 1 << "\t" << player[i].name << "\t" << player[i].score << "\t" << player[i].duration << endl;
		out_file << player[i].name << " " << player[i].score << " " << player[i].duration << endl;
	}

	out_file.close();
	_getch();
}

void view_scoreboard()
{
	int count = 0;
	system("cls");

	cout << "The more you score and the less time you take the higher you are in the board!\n" << endl;
	cout << "===============================================================================" << endl;
	cout << "\t\t\t\tLEADERBOARD" << endl;
	cout << "===============================================================================\n" << endl;
	cout << "\t\t\tNo\tName\tScore\tDuration" << endl;

	ifstream in_file("scoreboard.txt");

	in_file >> player[count].name >> player[count].score >> player[count].duration;
	cout << "\t\t\t" << (count + 1) << "\t" << player[count].name << "\t" << player[count].score << "\t" << player[count].duration << endl;
	while (in_file)
	{
		count++;
		in_file >> player[count].name >> player[count].score >> player[count].duration;

		if (!in_file)
			break;
		else 
			cout << "\t\t\t" << (count + 1) << "\t" << player[count].name << "\t" << player[count].score << "\t" << player[count].duration << endl;
	}

	in_file.close();

	_getch();
}
