// Tetris.cpp: определяет точку входа для консольного приложения.
//

//#include <stdafx.h>
#include<iostream>
#include "stdlib.h"
#include "time.h"

#include "conio.h"

#include "windows.h"

const int COLS = 12;
const int ROWS = 25;
char field[ROWS][COLS] = { 0 };

int num_sym, num_pov;// номер фигуры и номер поворота

char symbols[][4][4] = {
	{{0,1,0,0},
	{0,1,0,0},
	{0,1,1,0},
	{0,0,0,0}},//правая L 0
{
	{0,0,1,0},// 1
	{1,1,1,0},
	{0,0,0,0},
	{0,0,0,0}
},
{
	{0,1,1,0},//2
	{0,0,1,0},
	{0,0,1,0},
	{0,0,0,0}
},
{
	{1,0,0,0},//3
	{1,1,1,0},
	{0,0,0,0},
	{0,0,0,0}
},

{
	{0,0,1,0},// L левая 4 
	{0,0,1,0},
	{0,1,1,0},
	{0,0,0,0}
},
{
	{1,0,0,0},//5
	{1,1,1,0},
	{0,0,0,0},
	{0,0,0,0}
},
{
	{1,1,0,0},//6
	{1,0,0,0},
	{1,0,0,0},
	{0,0,0,0}
},
{
	{1,1,1,0},//7
	{0,0,1,0},
	{0,0,0,0},
	{0,0,0,0}
},
{
	{0,1,0,0},//для T 8
	{1,1,1,0},
	{0,0,0,0},
	{0,0,0,0}
},
{
	{0,1,0,0},//9
	{0,1,1,0},
	{0,1,0,0},
	{0,0,0,0}
},
{
	{1,1,1,0},//10
	{0,1,0,0},
	{0,0,0,0},
	{0,0,0,0}
},
{
	{0,1,0,0},//11
	{1,1,0,0},
	{0,1,0,0},
	{0,0,0,0}
},
{
	{0,1,1,0},// куб 12
	{0,1,1,0},
	{0,0,0,0},
	{0,0,0,0}
},
{
	{0,1,0,0},// Z 13
	{0,1,1,0},
	{0,0,1,0},
	{0,0,0,0}
},
{
	{0,1,1,0},//14
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0}
},
{
	{1,0,0,0},//15
	{1,1,0,0},
	{0,1,0,0},
	{0,0,0,0}
},
{
	{0,1,1,0},//16
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0}
},
{
	{0,0,1,0},// Z обратная 17
	{0,1,1,0},
	{0,1,0,0},
	{0,0,0,0}
},
{
	{1,1,0,0},//18
	{0,1,1,0},
	{0,0,0,0},
	{0,0,0,0}
},
{
	{0,1,0,0},//19
	{0,1,1,0},
	{0,0,1,0},
	{0,0,0,0}
},
{
	{0,1,1,0},//20
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0}
},
{
	{0,0,1,0},// палка 21
	{0,0,1,0},
	{0,0,1,0},
	{0,0,1,0}
},
{
	{1,1,1,1},//22
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
} };

char elementDataIndex[7][4] =
{ {0, 1, 2, 3}, // правая L 
  {4, 5, 6, 7}, // левая L
  {8, 9, 10, 11}, // фигура T
  {12, -1, -1, -1}, // блок
  {13, 14, 15, 16}, // z
  {17, 18, 19, 20}, // z обратная
  {21, 22, -1, -1}, // прямая
};

void RandomMix() {//рандомная выборка фигур
	srand((unsigned)time(NULL));
	num_pov = 0;
	num_sym = rand() % 7;
};

// эти координаты определяют место, где находится падающий элемент
int currentRow = 0;
int currentCol = (COLS / 2) - 2;

bool canInsertElement()
{
	int symbolIndex = elementDataIndex[num_sym][num_pov];
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			int rr = r + currentRow;
			int cc = c + currentCol;

			if (symbols[symbolIndex][r][c] == 0)
				continue;

			// проверяем, что координаты в пределах экрана
			if (rr < 0 || rr >= ROWS)
				return false;
			if (cc < 0 || cc >= COLS)
				return false;

			// проверяем, что ячейка не занята
			if (field[rr][cc])
				return false;
		}
	}
	return true;
}

void insertElement()
{
	int symbolIndex = elementDataIndex[num_sym][num_pov];
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			int rr = r + currentRow;
			int cc = c + currentCol;

			if (symbols[symbolIndex][r][c])
				field[rr][cc] = 1;
		}
	}
}

void deleteElement()
{
	int symbolIndex = elementDataIndex[num_sym][num_pov];
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			int rr = r + currentRow;
			int cc = c + currentCol;

			if (symbols[symbolIndex][r][c])
				field[rr][cc] = 0;
		}
	}
}

// функция очищает поле
void clearField()
{
	for (int r = 0; r < ROWS; ++r)
		for (int c = 0; c < COLS; ++c)
			field[r][c] = 0;
}

// рисуем поле
void drawField()
{
	// получаем хэндл консоли
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// запоминаем результаты
	COORD crds{ 35, 0 };

	for (int r = 0; r < ROWS; ++r)
	{
		crds.Y = r;
		// устанавливаем курсор в нужную позицию
		SetConsoleCursorPosition(hConsole, crds);


		printf("\xB3"); // левая граница стакана
		for (int c = 0; c < COLS; ++c)
		{
			if (field[r][c] == 0)
				// выводим пустой квадратик
				printf("  ");
			else
				// выводим заполненный квадратик
				printf("\xDB\xDB");
		}
		printf("\xB3"); // правая граница стакана
	}

	crds.Y = ROWS;
	// устанавливаем курсор в нужную позицию
	SetConsoleCursorPosition(hConsole, crds);

	// выводим нижнюю границу
	printf("\xC0");
	for (int c = 0; c < COLS; ++c)
		printf("\xC4\xC4");
	printf("\xD9");
}

void Rotation() {
	deleteElement();
	int prev = num_pov;
	num_pov = (num_pov + 1) % 4;;
	if (elementDataIndex[num_sym][num_pov] == -1)
		num_pov = 0;
	if (!canInsertElement()) {
		num_pov = prev;
		insertElement();
	}
	else {
		insertElement();
	}
}



int main()
{
	clearField();

	bool gameOver = false;
	bool inserted = 0; // опускается ли в данный момент фигура
	for (int counter = 0;; counter++)
	{
		if (!gameOver && counter % 10 == 0)
		{
			if (inserted) // если элемент существует
			{
				// удаляем элемент
				deleteElement();

				// смещаем его на одну строчку вниз
				currentRow++;

				// проверяем можно ли вставить в новом положении
				if (!canInsertElement())
				{   // если нельзя, вовзращаем обратно
					currentRow--;
					insertElement();

					// превращаем фигуру в часть стакана
					inserted = false;

					//проверка на сжигание ряда
					for (int r = ROWS - 1; r >= 0; --r) {
						int z = 0;
						for (int c = 0; c < COLS; ++c)
							if (field[r][c] == 1)
								z++;
						if (z == COLS) {
							for (int c = 0; c < COLS; ++c)
								field[r][c] = 0;
							for (int r0 = r; r0 > 0; r0--)
								for (int c = 0; c < COLS; ++c)
									field[r0][c] = field[r0 - 1][c];
						}z = 0;
					}

					// запускаем цикл заново
					continue;
				}
				else {
					insertElement();
				}
			}
			else {
				RandomMix();  // вставляем новую фигуру
				currentRow = 0;
				currentCol = (COLS / 2) - 2;

				// пытаемся вставить новую фигуру
				if (canInsertElement()) {
					insertElement();
					inserted = true;
				}
				else {
					// если не сумели вставить, значит стакан заполнен
					gameOver = true;
					printf("\n\t\t\t\t\tGame Over, Loser!");
					break;
				}
			}
		}
		drawField();

		if (!_kbhit() || gameOver)
		{
			Sleep(100);
			continue;
		}

		int c = _getch();
		if (c == 'q')
			break;
		else  if (inserted && c == 32) { // пробел
			Rotation();
		}
		else if (inserted && c == 224) // нажата специальная клавиша
		{
			while (c == 224) c = _getch();

			if (c == 77) { // стрелка вправо
				deleteElement();
				currentCol++;
				if (!canInsertElement())
				{
					currentCol--;
					insertElement();
				}
				else
					insertElement();
			}
			else if (c == 75) // стрелка влево
			{
				deleteElement();
				currentCol--;
				if (!canInsertElement()) {
					currentCol++;
					insertElement();
				}
				else
					insertElement();
			}
			else  if (c == 80) // стрелка вниз
			{
				deleteElement();
				currentRow++;
				if (!canInsertElement()) {
					currentRow--;
					insertElement();
				}
				else
					insertElement();
			}

		}

	}
	return 0;
}
 