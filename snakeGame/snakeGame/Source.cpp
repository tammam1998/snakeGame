#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <fstream>
#include<stdio.h>
#include <string>
using namespace std;
ofstream fout;
ifstream fin;

bool gameOver;
string user, olduser = "noon";
const int width = 25;
const int height = 25;
int x, y, fruitX, fruitY, score, oldscore, highscore;
int tailX[100], tailY[100];
int nTail;
int BombX[100], BombY[100], nBomb;
char currKey = '*';
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	srand(time(0));
	fruitX = rand() % width;
	fruitY = rand() % height;
	memset(tailX, 0, sizeof(tailX));
	memset(tailY, 0, sizeof(tailY));
	memset(BombX, 0, sizeof(BombX));
	memset(BombY, 0, sizeof(BombY));
	score = 0;
	oldscore = 0;
	nTail = 0;
	nBomb = 5;
	currKey = '*';
	for (int i = 0; i < nBomb; i++) {
		//srand(time(0));
		BombX[i] = rand() % width;
		BombY[i] = rand() % height;
	}
	score = 0;
}
void Draw()
{
	//ios_base::sync_with_stdio(true);
	system("cls");
	for (int i = 0; i < width + 2; i++)
		printf("#");
	printf("\n");

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				printf("#");
			if (i == y && j == x)
				printf("O");
			else if (i == fruitY && j == fruitX)
				printf("*");
			else
			{
				bool print = false;
				for (int k = 0; k < nBomb; k++) {
					if (i == BombY[k] && j == BombX[k]) {
						printf("B");
						print = true;
					}
				}
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						printf("o");
						print = true;
					}
				}
				if (!print)
					printf(" ");
			}


			if (j == width - 1)
				printf("#");
		}
		printf("\n");
	}

	for (int i = 0; i < width + 2; i++)
		printf("#");
	printf("\n");
	printf("score: %d", score);
}
void Input()
{
	if (_kbhit())
	{
		char newKey = _getch();
		if (((newKey == 'a' && currKey == 'd') || (newKey == 'd' && currKey == 'a')
			|| (newKey == 'w' && currKey == 's') || (newKey == 's' && currKey == 'w')) && nTail != 0)
			newKey = currKey;
		else
			currKey = newKey;
		switch (newKey)
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	for (int i = 0; i < nBomb; i++) {
		if (x == BombX[i] && y == BombY[i])
			gameOver = true;
	}
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
	if (oldscore == score - 20) {
		srand(time(0));
		oldscore = score;
		BombX[nBomb] = rand() % width;
		BombY[nBomb] = rand() % height;
		while (abs(BombX[nBomb] - x) <= 1 || abs(BombY[nBomb] - y) <= 1) {
			BombX[nBomb] = rand() % width;
			BombY[nBomb] = rand() % height;
		}
		nBomb++;
		/*for (int i = 0; i < nBomb; i++) {
		BombX[i] = rand() % width;
		BombY[i] = rand() % height;
		}*/

	}
}
int main()
{
	char r = 'r';
	printf("Please Enter Your User Name: ");
	cin >> user;
	user = user + ".txt";
	while (r == 'r') {
		if (ifstream(user)) {
			char stat;
			fin.open(user);
			fin >> highscore;
			if (olduser != user) {
				cout << "Your last highscore was " << highscore << "\nTo reset your highscore press n\nTo start playing press any key\n";
				cin >> stat;
				olduser = user;
				if (stat == 'n') {
					int remove(char *user);
					highscore = 0;
				}
			}
			fin.close();
		}


		Setup();
		while (!gameOver)
		{
			Draw();
			Input();
			Logic();
			if (score < 100)
				Sleep(50 - score/2);
			else
				Sleep(0);
		}
		system("cls");
		printf("    ****         *            *         *      *******\n   *            * *          * *       * *     *\n  *            *   *        *   *     *   *    *******\n  *    ***    *******      *     *   *     *   *******\n   *    *    *       *    *       * *       *  *     \n    ****    *         *  *         *         * *******\n\n");
		printf("      ***    *         *   *******   * * *\n    *     *   *       *    *         *    *\n   *       *   *     *     *******   *    *\n   *       *    *   *      *******   * * *\n    *     *      * *       *         *   *\n      ***         *        *******   *    *\n\n");
		highscore = max(score, highscore);
		printf("Your score is: %d\n", score);
		printf("Your highest score is: %d\n", highscore);
		if (ifstream(user)) {
			int remove(char *user);
			fout.open(user);
			fout << highscore;
			fout.close();
		}
		else {
			fout.open(user);
			fout << highscore;
			fout.close();
		}
		printf("Press r to play again\nPress c to change User\nPress any other key to close the game: ");
		cin >> r;
		if (r == 'c') {
			printf("Please Enter the new Username: ");
			cin >> user;
			user = user + ".txt";
			highscore = 0;
			r = 'r';
		}

	}

	return 0;
}