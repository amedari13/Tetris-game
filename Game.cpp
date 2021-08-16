#include "Game.h"
#include <ctime>
#include <conio.h>


Game::Game()
{
	field = std::make_shared<Field>(12, 25);
}

void Game::Start()
{
	field->clear_field();

	for (int counter = 0;; counter++)
	{
		if (!gameOver && counter % 10 == 0)
		{
			// если элемент существует двигаем его
			if (inserted)
			{
				field->delete_element(current_figure, cx, cy); // удаляем элемент

				// вот это многоуровневое обращение как бы намекает
				// что функция занимается не своими делами
				// то есть текущий класс Game обращается
				// к Field который обращается к Figure который почему то помнит
				// текущий ряд
				field->move_down(current_figure, cx, cy); // смещаем его на одну строчку вниз
				if (!field->can_insert_element(current_figure, cx, cy))
				{
					field->move_up(current_figure, cx, cy);
					field->insert_element(current_figure, cx, cy);
					inserted = false;//превращаем в часть стакана

					field->row_burning_check();
					continue;
				}
				else
				{
					field->insert_element(current_figure, cx, cy);
				}
			}
			else
			{
				current_figure = std::make_shared<Figure>();

				if (field->can_insert_element(current_figure, cx, cy))
				{
					field->insert_element(current_figure, cx, cy);
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
		field->draw_field();

		if (!_kbhit() || gameOver)
		{
			Sleep(100);
			continue;
		}

		int c = _getch();///////доделать
		//Keys[c]();а вот тут уже фиг знает шо
	}
}