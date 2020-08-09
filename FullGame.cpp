#include <iostream>
#include <Windows.h>
#include <fstream>


using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

//variables needed
//starting size of snake
int snake_length = 1;
//used to control sound
bool soundon = true;
//max size a snake can be is 100 at the moment
int x[100];
int y[100];
//check if the game is over or not
bool endgame = false;
// used to print out the layout
char map[20][40];
//used to reset a space to its default
char previous_spot =' ';
//used to hold food location x being the first in the array then y second
int foodposition[2];
//used to hol the direction of the snake
int speeddirection;
//set difficulty of game
int difficulty;
int dif = 0;
//file that stores the highscore data
fstream file;
//name of previous highscore holder
string names;
//name of current player
string currentname;
//previously set highscore
int highestscore;

//set cursor position
void cursor_position(int x , int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	
}
//play sound effects
void play_sound()
{
	if (soundon == true)
	{
		cout << "\a";
	}
}
//function for spawning food at different locations;
void spawn_food()
{
	bool food_located = false;
	int xx;
	int yy;

	while (food_located == false)
	{
		for (int index_snake = 0; index_snake < snake_length; index_snake++)
		{
			xx = rand() % 16 + 2;
			yy = rand() % 16 + 2;
			//making sure the food location aligns on the grid
			int modx = xx % 2;
			int mody = yy % 2;
			if (xx != x[index_snake] && yy != y[index_snake] && modx == 0 && mody==0 )
			{
				SetConsoleTextAttribute(h, 10);
				cursor_position(yy, xx);
				cout << "=" << endl;
				foodposition[0] = xx;
				foodposition[1] = yy;
				food_located = true;
				break;
			}
		}
	}
}

void movement(int index)
{
	
	if (GetAsyncKeyState(VK_LEFT))
	{
		//set direction of snake
		speeddirection = 1;

		if (y[index] > 2)
		{
			// makes sure the button click is only registered once per click
			int add = 0;
			while (GetAsyncKeyState(VK_LEFT))
			{
				if (add < 1)
				{
					
					if ( y[1] != ( y[0] - 2))
					{
						int previous_1 = y[0];
						int previous_1x = x[0];
						cursor_position(y[0], x[0]);
						cout << " " << endl;
						y[index] -= 2;

						//check to see if the head of the snake has collided with a body part
						for (int ss = 1; ss < snake_length ; ss++)
						{
							if (y[index] == y[ss] && x[index] == x[ss])
							{
							    endgame = true;
							}
						}

						//check if snake ate food
						if (x[index] == foodposition[0] && y[index] == foodposition[1])
						{
							snake_length++;
							play_sound();
							spawn_food();
						}

						//print out the head of the snake
						SetConsoleTextAttribute(h, 12);
						cursor_position(y[index], x[index]);
						cout << '@' << endl;

						//update the position of all body parts relative to the movement of the snakes head
						for (int sl = 1; sl < snake_length; sl++)
						{
							int previous_2 = y[sl];
							cursor_position(y[sl], x[sl]);
							cout << " " << endl;
							
							y[sl] = previous_1;
							previous_1 = previous_2;

							int previous_2x = x[sl];
							x[sl] = previous_1x;
							previous_1x = previous_2x;

							//print out body
							int mod = sl % 15;
							if(mod == 0)
							{ 
								SetConsoleTextAttribute(h, sl % 15 + 1);
							}
							else
							{
								SetConsoleTextAttribute(h, sl % 15);
							}
							cursor_position(y[sl], x[sl]);
							cout << 'O' << endl;
						}
					}
				}
				add++;
			}
			
			
			
		}
		else
		{
			endgame = true;
		}
		
	}
	else
	{
		if (GetAsyncKeyState(VK_RIGHT))
		{
			//set direction of snake
			speeddirection = 2;
			if (y[index] < 38)
			{
				// makes sure the button click is only registered once per click
				int add = 0;
				while (GetAsyncKeyState(VK_RIGHT))
				{
					if (add < 1)
					{
					
						if (y[1] != (y[0] + 2))
						{
							int previous_1 = y[0];
							int previous_1x = x[0];
							cursor_position(y[0], x[0]);
							cout << " " << endl;
							y[index] += 2;

							//check to see if the head of the snake has collided with a body part
							for (int ss = 1; ss < snake_length; ss++)
							{
								if (y[index] == y[ss] && x[index] == x[ss])
								{
									endgame = true;
								}
							}

							//check if snake ate food
							if (x[index] == foodposition[0] && y[index] == foodposition[1])
							{
								snake_length++;
								play_sound();
								spawn_food();
							}

							//print out the head of the snake
							SetConsoleTextAttribute(h, 12);
							cursor_position(y[index], x[index]);
							cout << '@' << endl;

							//update the position of all body parts relative to the movement of the snakes head
							for (int sl = 1; sl < snake_length; sl++)
							{
								int previous_2 = y[sl];
								cursor_position(y[sl], x[sl]);
								cout << " " << endl;

								y[sl] = previous_1;
								previous_1 = previous_2;

								int previous_2x = x[sl];
								x[sl] = previous_1x;
								previous_1x = previous_2x;

								//print out body
								int mod = sl % 15;
								if (mod == 0)
								{
									SetConsoleTextAttribute(h, sl % 15 + 1);
								}
								else
								{
									SetConsoleTextAttribute(h, sl % 15);
								}
								cursor_position(y[sl], x[sl]);
								cout << 'O' << endl;
							}
						}
					}
					add++;
				}

			}
			else
			{
				endgame = true;
			}
		}
		else
		{
			if (GetAsyncKeyState(VK_DOWN))
			{
				//set direction of snake
				speeddirection = 3;
				if (x[index] < 18)
				{
					// makes sure the button click is only registered once per click
					int add = 0;
					while (GetAsyncKeyState(VK_DOWN))
					{
						if (add < 1)
						{
						
							if (x[1] != (x[0] + 1))
							{
								int previous_1 = y[0];
								int previous_1x = x[0];
								cursor_position(y[0], x[0]);
								cout << " " << endl;
								++x[index];

								//check to see if the head of the snake has collided with a body part
								for (int ss = 1; ss < snake_length; ss++)
								{
									if (y[index] == y[ss] && x[index] == x[ss])
									{
										endgame = true;
									}
								}

								//check if snake ate food
								if (x[index] == foodposition[0] && y[index] == foodposition[1])
								{
									snake_length++;
									play_sound();
									spawn_food();
								}

								//print out the head of the snake
								SetConsoleTextAttribute(h, 12);
								cursor_position(y[index], x[index]);
								cout << '@' << endl;

								//update the position of all body parts relative to the movement of the snakes head
								for (int sl = 1; sl < snake_length; sl++)
								{
									int previous_2 = y[sl];
									cursor_position(y[sl], x[sl]);
									cout << " " << endl;

									y[sl] = previous_1;
									previous_1 = previous_2;

									int previous_2x = x[sl];
									x[sl] = previous_1x;
									previous_1x = previous_2x;

									//print out body
									int mod = sl % 15;
									if (mod == 0)
									{
										SetConsoleTextAttribute(h, sl % 15 + 1);
									}
									else
									{
										SetConsoleTextAttribute(h, sl % 15);
									}
									cursor_position(y[sl], x[sl]);
									cout << 'O' << endl;
								}
							}
							add++;
						}
					}
					
					
				}
				else
				{
					endgame = true;
				}
				
			}
			else
			{
				if (GetAsyncKeyState(VK_UP))
				{
					//set direction of snake
					speeddirection = 4;
					if ( x[index] > 1)
					{
						// makes sure the button click is only registered once per click
						int add = 0;
						while (GetAsyncKeyState(VK_UP))
						{
							if (add < 1)
							{
							
								if (x[1] != (x[0] - 1))
								{
									int previous_1 = y[0];
									int previous_1x = x[0];
									cursor_position(y[0], x[0]);
									cout << " " << endl;
									--x[index];

									//check to see if the head of the snake has collided with a body part
									for (int ss = 1; ss < snake_length; ss++)
									{
										if (y[index] == y[ss] && x[index] == x[ss])
										{
											endgame = true;
										}
									}

									//check if snake ate food
									if (x[index] == foodposition[0] && y[index] == foodposition[1])
									{
										snake_length++;
										play_sound();
										spawn_food();
									}

									//print out the head of the snake
									SetConsoleTextAttribute(h, 12);
									cursor_position(y[index], x[index]);
									cout << '@' << endl;

									//update the position of all body parts relative to the movement of the snakes head
									for (int sl = 1; sl < snake_length; sl++)
									{
										int previous_2 = y[sl];
										cursor_position(y[sl], x[sl]);
										cout << " " << endl;

										y[sl] = previous_1;
										previous_1 = previous_2;

										int previous_2x = x[sl];
										x[sl] = previous_1x;
										previous_1x = previous_2x;

										//print out body
										int mod = sl % 15;
										if (mod == 0)
										{
											SetConsoleTextAttribute(h, sl % 15 + 1);
										}
										else
										{
											SetConsoleTextAttribute(h, sl % 15);
										}
										cursor_position(y[sl], x[sl]);
										cout << 'O' << endl;
										
									}
								}
							}
							add++;
						}
						
					}
					else
					{
						endgame = true;
					}
					
				}
			}
		}
	}

	
}

void speed()
{
	switch (speeddirection)
	{
		case 1: {
			int index = 0;
			if (y[index] > 2)
			{
				if (y[1] != (y[0] - 2))
				{
					int previous_1 = y[0];
					int previous_1x = x[0];
					cursor_position(y[0], x[0]);
					cout << " " << endl;
					y[index] -= 2;

					//check to see if the head of the snake has collided with a body part
					for (int ss = 1; ss < snake_length; ss++)
					{
						if (y[index] == y[ss] && x[index] == x[ss])
						{
							endgame = true;
						}
					}

					//check if snake ate food
					if (x[index] == foodposition[0] && y[index] == foodposition[1])
					{
						snake_length++;
						play_sound();
						spawn_food();
					}

					//print out the head of the snake
					SetConsoleTextAttribute(h, 12);
					cursor_position(y[index], x[index]);
					cout << '@' << endl;

					//update the position of all body parts relative to the movement of the snakes head
					for (int sl = 1; sl < snake_length; sl++)
					{
						int previous_2 = y[sl];
						cursor_position(y[sl], x[sl]);
						cout << " " << endl;

						y[sl] = previous_1;
						previous_1 = previous_2;

						int previous_2x = x[sl];
						x[sl] = previous_1x;
						previous_1x = previous_2x;

						//print out body
						int mod = sl % 15;
						if (mod == 0)
						{
							SetConsoleTextAttribute(h, sl % 15 + 1);
						}
						else
						{
							SetConsoleTextAttribute(h, sl % 15);
						}
						cursor_position(y[sl], x[sl]);
						cout << 'O' << endl;
					}
				}
			}
			else
			{
				endgame = true;
			}
			break;
		}
		case 2: {
			int index = 0;
			if (y[index] < 38)
			{
				if (y[1] != (y[0] + 2))
				{
					int previous_1 = y[0];
					int previous_1x = x[0];
					cursor_position(y[0], x[0]);
					cout << " " << endl;
					y[index] += 2;

					//check to see if the head of the snake has collided with a body part
					for (int ss = 1; ss < snake_length; ss++)
					{
						if (y[index] == y[ss] && x[index] == x[ss])
						{
							endgame = true;
						}
					}

					//check if snake ate food
					if (x[index] == foodposition[0] && y[index] == foodposition[1])
					{
						snake_length++;
						play_sound();
						spawn_food();
					}

					//print out the head of the snake
					SetConsoleTextAttribute(h, 12);
					cursor_position(y[index], x[index]);
					cout << '@' << endl;

					//update the position of all body parts relative to the movement of the snakes head
					for (int sl = 1; sl < snake_length; sl++)
					{
						int previous_2 = y[sl];
						cursor_position(y[sl], x[sl]);
						cout << " " << endl;

						y[sl] = previous_1;
						previous_1 = previous_2;

						int previous_2x = x[sl];
						x[sl] = previous_1x;
						previous_1x = previous_2x;

						//print out body
						int mod = sl % 15;
						if (mod == 0)
						{
							SetConsoleTextAttribute(h, sl % 15 + 1);
						}
						else
						{
							SetConsoleTextAttribute(h, sl % 15);
						}
						cursor_position(y[sl], x[sl]);
						cout << 'O' << endl;
					}
				}
			}
			else
			{
				endgame = true;
			}
			break;
		}
	    case 3: {
			int index = 0;
			if (x[index] < 18)
			{
				if (x[1] != (x[0] + 1))
				{
					int previous_1 = y[0];
					int previous_1x = x[0];
					cursor_position(y[0], x[0]);
					cout << " " << endl;
					++x[index];

					//check to see if the head of the snake has collided with a body part
					for (int ss = 1; ss < snake_length; ss++)
					{
						if (y[index] == y[ss] && x[index] == x[ss])
						{
							endgame = true;
						}
					}

					//check if snake ate food
					if (x[index] == foodposition[0] && y[index] == foodposition[1])
					{
						snake_length++;
						play_sound();
						spawn_food();
					}

					//print out the head of the snake
					SetConsoleTextAttribute(h, 12);
					cursor_position(y[index], x[index]);
					cout << '@' << endl;

					//update the position of all body parts relative to the movement of the snakes head
					for (int sl = 1; sl < snake_length; sl++)
					{
						int previous_2 = y[sl];
						cursor_position(y[sl], x[sl]);
						cout << " " << endl;

						y[sl] = previous_1;
						previous_1 = previous_2;

						int previous_2x = x[sl];
						x[sl] = previous_1x;
						previous_1x = previous_2x;

						//print out body
						int mod = sl % 15;
						if (mod == 0)
						{
							SetConsoleTextAttribute(h, sl % 15 + 1);
						}
						else
						{
							SetConsoleTextAttribute(h, sl % 15);
						}
						cursor_position(y[sl], x[sl]);
						cout << 'O' << endl;
					}
				}
			}
			else
			{
				endgame = true;
			}
			break;
		}
    	case 4: {
			int index = 0;
			if (x[index] > 1)
			{
				if (x[1] != (x[0] - 1))
				{
					int previous_1 = y[0];
					int previous_1x = x[0];
					cursor_position(y[0], x[0]);
					cout << " " << endl;
					--x[index];

					//check to see if the head of the snake has collided with a body part
					for (int ss = 1; ss < snake_length; ss++)
					{
						if (y[index] == y[ss] && x[index] == x[ss])
						{
							endgame = true;
						}
					}

					//check if snake ate food
					if (x[index] == foodposition[0] && y[index] == foodposition[1])
					{
						snake_length++;
						play_sound();
						spawn_food();
					}

					//print out the head of the snake
					SetConsoleTextAttribute(h, 12);
					cursor_position(y[index], x[index]);
					cout << '@' << endl;

					//update the position of all body parts relative to the movement of the snakes head
					for (int sl = 1; sl < snake_length; sl++)
					{
						int previous_2 = y[sl];
						cursor_position(y[sl], x[sl]);
						cout << " " << endl;

						y[sl] = previous_1;
						previous_1 = previous_2;

						int previous_2x = x[sl];
						x[sl] = previous_1x;
						previous_1x = previous_2x;

						//print out body
						int mod = sl % 15;
						if (mod == 0)
						{
							SetConsoleTextAttribute(h, sl % 15 + 1);
						}
						else
						{
							SetConsoleTextAttribute(h, sl % 15);
						}
						cursor_position(y[sl], x[sl]);
						cout << 'O' << endl;

					}
				}
			}
			else
			{
				endgame = true;
			}
	    }
	}
}

void display()
{
	SetConsoleTextAttribute(h, 13);
	//system("CLS");
//	map[x][y] = 'O';
	for (int i = 0; i < 20; i++)
	{
		for (int ii = 0; ii < 40; ii++)
		{
			cursor_position(ii, i);
			cout << map[i][ii];
		}
		if (i == 10)
		{
			//print out difficulty
			string mode;
			switch (difficulty)
			{
			case 1: mode = "EASY";
			case 2: mode = "MEDIUM";
			case 3: mode = "HARD";
			}

			cursor_position(42, i - 8);
			cout << "                    HIGH SCORE : " << highestscore << " by " << names << endl;
			cout << endl << endl;

			cursor_position(42, i - 6);
			cout << "                    DIFFICULTY : " << mode << endl;
			cout << endl << endl;

			cursor_position(42, i );

			cout << "                  CREATED BY DAVID MUNGAI" << endl;
			cout << endl << endl;
			cursor_position(42, i + 3);
			cout << "  USE THE ARROW KEYS TO CONTROL THE SNAKE" << endl;
			cursor_position(42, i + 4);
			cout << "  DO NOT COLLIDE WITH THE SIDES" << endl;
			cursor_position(42, i + 5);
			cout << "  TO PAUSE THE GAME PRESS THE ARROW KEY OPPOSITE TO THE DIRECTION OF THE SNAKE" << endl;
			cursor_position(42, i + 6);
			cout << "  TO CONTINUE PRESS ANY OTHER DIRECTION THAN THE ONE USED TO PAUSE" << endl;
			cursor_position(42, i + 7);
			cout << "  TO PAUSE THE GAME MOMENTARILLY HOLD ON THE DIRECTION OF THE SNAKE" << endl;
			cursor_position(42, i + 8);
			cout << "  WHEN YOU LET GO THE GAME WILL CONTINUE" << endl;
			cursor_position(42, i + 9);
			cout << "  TO QUIT THE GAME PRESS THE ESCAPE KEY" << endl;
			cursor_position(42, i + 10);
			cout << "  TOGGLE THE MUSIC ON AND OFF BY PRESSING THE CONTROL KEY" << endl;
		}

		
	}
	SetConsoleTextAttribute(h, 12);
	cursor_position(y[0],x[0]);
	cout << "@" << endl;
}

void savedata(string name , int highscore)
{
	int prevhighscore = highestscore;
	if (highscore > prevhighscore)
	{
		file.open("snakehighscore.txt", ios::out | ios::trunc);
		file << name << " " << highscore << endl;
	}
	file.close();
}

void getdata()
{
	file.open("snakehighscore.txt", ios::in );
	file >> names;
	file >> highestscore;
	file.close();
}

void setdifficulty()
{
	
	if (difficulty == 1)
	{
		dif = 180;
	}
	else
	{
		if (difficulty == 2)
		{
			dif = 150;
		}
		else
		{
			if (difficulty == 3)
			{
				dif = 100;
			}	
		}
	}

}

void update()
{
	speed();
	Sleep(dif);
	movement(0);
	cursor_position(42, 7);
	cout << "                    SCORE : " << snake_length;
}

int main()
{
	getdata();
	cout << "What's your name? " << endl;
	cin >> currentname;
	cout << "Welcome " << currentname << endl;
	cout << "THE DIFFICULTY LEVEL DEFINES THE SPEED OF THE SNAKE" << endl;
	cout << "CHOOSE DIFFICULTY" << endl;
	cout << "Type 1 for easy , 2 for medium and 3 for hard :  ";
	cin >> difficulty;
	
	while (difficulty != 1 && difficulty != 2 && difficulty != 3 && difficulty != 4)
	{
		cout << "CHOOSE A VALID SETTING" << endl;
		cin >> difficulty;
	}

	system("cls");
	x[0] = 10;
	y[0] = 10;

	//initialize map interior
	for (int i = 0; i < 19; i++)
	{
		for (int ii = 0; ii < 19; ii++)
		{
			map[i][ii] = ' ';
		}
	}
	//initialize map border
	for (int i = 0; i < 19; i++)
	{
		
		map[i][0]  = '#';
		
		map[i][39] = '#';
	}
	for (int i = 0; i < 39; i++)
	{
		map[0][i] = '#';
		map[19][i] = '#';
	} 
	display();
	SetConsoleTextAttribute(h, 14);
	spawn_food();

	setdifficulty();
	
	while (GetAsyncKeyState(VK_ESCAPE) == false)
	{
		update();
		if (endgame == true)
		{
			break;
		}

		if (GetAsyncKeyState(VK_CONTROL))
		{
			if (soundon == true)
			{
				soundon = false;
			}
			else
			{
				soundon = true;
			}
		}
	}

	cursor_position(10, 10);
	cout <<" GAME OVER!!!! "<< endl;
	Sleep(100);
	cursor_position(0, 22);
	savedata(currentname , snake_length);
	return 0;
}
