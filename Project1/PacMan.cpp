/*PACMAN Assignmnet for Fundamental of Programming June Sem 2023*/
// https://github.com/JoelLim1219/MyStuffs.git

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;

void main_menu();
void run_game();
void arrow_key_movement(int& x, int& y, char key);
void edit_arrow_key_movement(int& x, int& y, char key);
void display(int t_p_x, int t_p_y, int p_x, int p_y, int g_x, int g_y);
void make_map();
void ghost_movement(int p_x, int p_y, int& g_x, int& g_y);
void edit_map();

struct INFO_COORDS
{
	bool is_wall;
	bool p_pass;
};

INFO_COORDS map[20][40];

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
		cout << "Press '1' to start game.\nPress '2' to edit level.\nPress 'Esc' to escape.\n";

		unsigned char option = _getch();

		if (option == '1')
		{
			make_map();
			run_game();
		}

		else if (option == '2')
		{
			edit_map();
		}

		else if (option == 27)
			break;

		else
			cout << "Enter a valid option.\n";

	}
}

void run_game()
{
	int t_p_x = 0, t_p_y = 0;
	int player_x = 0, player_y = 0;
	int ghost_x = 39, ghost_y = 19;
	unsigned char key = 0;
	for (int count = 0; true; count++) // infinity loop
	{
		system("cls");
		display(t_p_x, t_p_y, player_x, player_y, ghost_x, ghost_y);
		if (count % 3 == 0) // every 3 loop
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
		map[player_y][player_x].p_pass = 1;

		Sleep(20);
	}
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

void display(int t_p_x, int t_p_y, int p_x, int p_y, int g_x, int g_y)
{
	COORD coord = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //set cursor at top left

	int scale = 2;

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
						cout << ".";
					else if (map[row][column].is_wall == 1)
						cout << "#";
				}
			}
			cout << endl;
		}
	}
}

void arrow_key_movement(int& x, int& y, char key)
{
	if (key == 72)
	{
		if (y > 0 && y <= 19 && map[x][y - 1].is_wall == 0)
		{
			y--;
		}

		else if (y == 0 && map[x][y + 19].is_wall == 0)
		{
			y += 19;
		}
	}

	else if (key == 80)
	{
		if (y >= 0 && y < 19 && map[x][y + 1].is_wall == 0)
		{
			y++;
		}
		else if (y == 19 && map[x][y - 19].is_wall == 0)
			y -= 19;
	}

	else if (key == 75)
	{
		if (x > 0 && x <= 39 && map[x - 1][y].is_wall == 0)
		{
			x--;
		}
		else if (x == 0 && map[x + 39][y].is_wall == 0)
			x += 39;
	}

	else if (key == 77)
	{
		if (x >= 0 && x < 39 && map[x + 1][y].is_wall == 0)
		{
			x++;
		}

		else if (x == 39 && map[x - 39][y].is_wall == 0)
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
	int previous_g_x = g_x, previous_g_y = g_y;
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

void e_display(int p_x, int p_y, int g_x, int g_y)
{
	COORD coord = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //set cursor at top left

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 40; column++)
		{
				if (row == p_y && column == p_x)
					cout << "X";
				else if (row == g_y && column == g_x)
					cout << "G";
				else if (map[column][row].is_wall == 0 && map[column][row].p_pass == 1)
					cout << " ";
				else if (map[column][row].is_wall == 0 && map[column][row].p_pass == 0)
					cout << ".";
				else if (map[column][row].is_wall == 1)
					cout << "#";
		}
		cout << endl;
	}
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
					map[e_y][e_x].is_wall = 1;
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
		
		Sleep(200);
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

