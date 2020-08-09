#include <iostream>
#include <Windows.h>

using namespace std;

char map[20][40];
int player_x = 1;
int player_y = 1;
bool gameover = false;

//use this function to set the position of the cursor
void cursor_position(int y, int x)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void movement()
{
	//Used to tell if the key has been pressed 
	if (GetAsyncKeyState(VK_UP))
	{
		int control = 0;
		//while the key is down we want to carry out some tasks
		while(GetAsyncKeyState(VK_UP))
		{ 
			//this variable is used to ensure that the movement occurs only once per button press
			if (control < 1)
			{
				if (player_x > 1)
				{
					//clear out the previous position of the player
					cursor_position(player_x, player_y);
					cout << " " << endl;

					//change the position of the players location according to the direction to be travelled
					player_x--;

					//print out the new position of the player
					cursor_position(player_x, player_y);
					cout << "@" << endl;

				}
				control++;
			}
		}
	}
	else
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			int control = 0;
			while (GetAsyncKeyState(VK_DOWN))
			{
				if (control < 1)
				{
					if (player_x < 18)
					{
						cursor_position(player_x, player_y);
						cout << " " << endl;

						player_x++;

						cursor_position(player_x, player_y);
						cout << "@" << endl;
					}
					control++;
				}
			}
		}
		else
		{
			if (GetAsyncKeyState(VK_RIGHT))
			{
				int control = 0;
				while (GetAsyncKeyState(VK_RIGHT))
				{
					if (control < 1)
					{
						if (player_y < 38)
						{
							cursor_position(player_x, player_y);
							cout << " " << endl;

							player_y++;

							cursor_position(player_x, player_y);
							cout << "@" << endl;
						}
						control++;
					}
				}
			}
			else
			{
				if (GetAsyncKeyState(VK_LEFT))
				{
					int control = 0;
					while (GetAsyncKeyState(VK_LEFT))
					{
						if (control < 1)
						{
							if (player_y > 1)
							{
								cursor_position(player_x, player_y);
								cout << " " << endl;

								player_y--;

								cursor_position(player_x, player_y);
								cout << "@" << endl;
							}
							control++;
						}
					}
				}
			}

		}
	}
	
}

void display()
{
	//used to display the border of the game by using the map two dimensional array declared above
	map[player_x][player_y] = '@';
	for (int rows = 0; rows < 20; rows++)
	{
		for (int columns = 0; columns < 40; columns++)
		{
			cout << map[rows][columns];
		}
		cout << endl;
	}
	
}

int main()
{
	//set border values to what we want to display as our border
	for (int index = 0; index< 20; index++)
	{
		map[index][0] = '#';
		map[index][39] = '#';
	}
	for (int index = 0; index < 40; index++)
	{
		map[19][index] = '#';
		map[0][index] = '#';
	}
	

	//print out the map after we initialize the border
	display();


	//this is the gameloop that decides whether the game goes on or not
	while (gameover == false)
	{
		movement();
		//this allows the user to end the game by pressing the escape key
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			gameover = true;
		}
	}
	//set the position of the cursor to right below the map so that the return statement is printed below it 
	cursor_position(21, 0);
	return 0;
}