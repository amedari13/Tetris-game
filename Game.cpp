#include "Game.h"
#include <ctime>
#include <conio.h>

Game::Game()
{
	field.clearField();
}

void Game::Start()
{
	for (int counter = 0;; counter++)
	{
		if (!gameOver && counter % 10 == 0)
		{
			// если элемент существует двигаем его
			if (inserted) 
			{
				field.deleteElement(); // удаляем элемент

				// вот это многоуровневое обращение как бы намекает
				// что функция занимается не своими делами
				// то есть текущий класс Game обращается
				// к Field который обращается к Figure который почему то помнит
				// текущий ряд
				field.current_element.current_row++; // смещаем его на одну строчку вниз
				if (!field.canInsertElement()) 
				{  
					field.current_element.current_row--;
					field.insertElement();
					inserted = false; 

					//проверка на сжигание ряда
					for (int r = field.ROWS - 1; r >= 0; --r) {
						int z = 0;
						for (int c = 0; c < field.COLS; ++c)
							if (field.coords[r][c] == 1)
								z++;
						if (z == field.COLS) {
							for (int c = 0; c < field.COLS; ++c)
								field.coords[r][c] = 0;
							for (int r0 = r; r0 > 0; r0--)
								for (int c = 0; c < field.COLS; ++c)
									field.coords[r0][c] = field.coords[r0 - 1][c];
						}z = 0;
					}
					continue;
				}
				else
				{
					field.insertElement();
				}
			}
			else 
			{
				field.createRandomFigure(); 

				if (field.canInsertElement()) 
				{
					field.insertElement();
					inserted = true;
				}
				else 
				{
					gameOver = true;
					printf("\n\t\t\t\t\tGame Over, Loser!");
					break;
				}
			}
		}
		field.drawField();

		if (!_kbhit() || gameOver)
		{
			Sleep(100);
			continue;
		}

		int c = _getch();///////доделать
		Keys[c]();
	}
}
void Game::StepRight()
{
	field.deleteElement();
	field.current_element.current_col++;
	if (!field.canInsertElement())
	{
		field.current_element.current_col--;
		field.insertElement();
	}
	else
		field.insertElement();
}
void Game::StepLeft()
{
	field.deleteElement();
	field.current_element.current_col--;
	if (!field.canInsertElement()) {
		field.current_element.current_col++;
		field.insertElement();
	}
	else
		field.insertElement();
}
void Game::StepDown()
{
	field.deleteElement();
	field.current_element.current_row++;
	if (!field.canInsertElement()) {
		field.current_element.current_row--;
		field.insertElement();
	}
	else
		field.insertElement();
}
void Game::Rotate()
{
	field.deleteElement();
	int prev = field.current_element.current_rotation;
	field.current_element.current_rotation = 
		static_cast<Rotations>((field.current_element.current_rotation + 1) % 4);

	if (!field.canInsertElement()) 
	{
		////num_pov = prev;
		//не уверена что в верном порядке
		field.insertElement();
	}
	else 
	{
		MatrixRotate();
		field.insertElement();
	}
}

void Game::MatrixRotate() {
	size_t size = field.current_element.symbol.size();
	auto symbol = field.current_element.symbol;

	for (int i = 0; i < size/ 2; i++)
		std::swap(symbol[i], symbol[size - 1 - i]);
	
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size / 2; j++)
			std::swap(symbol[i][j], symbol[i][size - 1 - j]);
	field.current_element.symbol = symbol;
}
