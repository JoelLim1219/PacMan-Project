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
void player_control(int& x, int& y, char key);
void display(int p_x, int p_y, int g_x, int g_y);
void make_wall();
void ghost_movement(int p_x, int p_y, int& g_x, int& g_y);
void edit_map();

struct INFO_COORDS
{
	int x_coords;
	int y_coords;
	bool is_wall;
	bool p_pass;
};

INFO_COORDS map[40][20];

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
			make_wall();
			run_game();
		}

		if (option == '2')
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
	int player_x = 0, player_y = 0;
	int ghost_x = 39, ghost_y = 19;
	unsigned char key = 0;
	for (int count = 0; true; count++) // infinity loop
	{
		system("cls");
		display(player_x, player_y, ghost_x, ghost_y);
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

		player_control(player_x, player_y, key);

		Sleep(20);
	}
}

void make_wall()
{
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 40; column++)
		{
			map[column][row].x_coords = column;
			map[column][row].y_coords = row;
			map[column][row].is_wall = 0;
			map[column][row].p_pass = 0;
		}
		
	}

}

void player_control(int& x, int& y, char key)
{
	map[x][y].p_pass = 1;
	if (key == 72)
	{
		if (y > 0 && y <= 19 && map[x][y - 1].is_wall == 0)
			y--;
		else if (y == 0 && map[x][y + 19].is_wall == 0)
			y += 19;
	}

	else if (key == 80)
	{
		if (y >= 0 && y < 19 && map[x][y + 1].is_wall == 0)
			y++;
		else if (y == 19 && map[x][y - 19].is_wall == 0)
			y -= 19;
	}

	else if (key == 75)
	{
		if (x > 0 && x <= 39 && map[x - 1][y].is_wall == 0)
			x--;
		else if (x == 0 && map[x + 39][y].is_wall == 0)
			x += 39;
	}

	else if (key == 77)
	{
		if (x >= 0 && x < 39 && map[x + 1][y].is_wall == 0)
			x++;
		else if (x == 39 && map[x - 39][y].is_wall == 0)
			x -= 39;
	}

}

void display(int p_x, int p_y, int g_x, int g_y)
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



void ghost_movement(int p_x, int p_y, int& g_x, int& g_y)
{
	int previous_g_x = g_x, previous_g_y = g_y;
	int r_distance = pow(abs(g_x + 1 - p_x), 2) + pow(abs(g_y - p_y), 2);
	int l_distance = pow(abs(g_x - 1 - p_x), 2) + pow(abs(g_y - p_y), 2);
	int d_distance = pow(abs(g_x - p_x), 2) + pow(abs(g_y + 1 - p_y), 2);
	int u_distance = pow(abs(g_x - p_x), 2) + pow(abs(g_y - 1 - p_y), 2);
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

	if (distance[0] == u_distance && map[g_x][g_y - 1].is_wall == 0) //prioritise up and down
		g_y--;

	else if (distance[0] == d_distance && map[g_x][g_y + 1].is_wall == 0)
		g_y++;

	else if (distance[0] == r_distance && map[g_x + 1][g_y].is_wall == 0)
		g_x++;

	else if (distance[0] == l_distance && map[g_x - 1][g_y].is_wall == 0)
		g_x--;

	else if (distance[1] == u_distance && map[g_x][g_y - 1].is_wall == 0)
		g_y--;

	else if (distance[1] == d_distance && map[g_x][g_y + 1].is_wall == 0)
		g_y++;

	else if (distance[1] == r_distance && map[g_x + 1][g_y].is_wall == 0)
		g_x++;

	else if (distance[1] == l_distance && map[g_x - 1][g_y].is_wall == 0)
		g_x--;

	else if (distance[2] == u_distance && map[g_x][g_y - 1].is_wall == 0)
		g_y--;

	else if (distance[2] == d_distance && map[g_x][g_y + 1].is_wall == 0)
		g_y++;

	else if (distance[2] == r_distance && map[g_x + 1][g_y].is_wall == 0)
		g_x++;

	else if (distance[2] == l_distance && map[g_x - 1][g_y].is_wall == 0)
		g_x--;

	else if (distance[3] == u_distance && map[g_x][g_y - 1].is_wall == 0)
		g_y--;

	else if (distance[3] == d_distance && map[g_x][g_y + 1].is_wall == 0)
		g_y++;

	else if (distance[3] == r_distance && map[g_x + 1][g_y].is_wall == 0)
		g_x++;

	else if (distance[3] == l_distance && map[g_x - 1][g_y].is_wall == 0)
		g_x--;

}