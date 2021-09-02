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
		Proccess(counter);
		field->draw_field();

		if (!_kbhit() || gameOver)
		{
			Sleep(100);
			continue;
		}

		if (current_figure) 
		{
			int c = _getch();
			if (keys[c] || static_cast<int>(c) == -32)
				keys[c]();
		}
	}
}

void Game::Proccess(int counter)
{
	if (!gameOver && counter % 10 == 0)
	{
		if (current_figure)
		{
			calc_cycle();
		}
		else
		{
			current_figure = std::make_shared<Figure>();

			cx = field->get_cols() / 2;
			cy = 0;

			if (field->can_insert_element(current_figure, cx, cy))
			{
				field->insert_element(current_figure, cx, cy);
			}
			else
			{
				gameOver = true;
				printf("\n\t\t\t\t\tGame Over, Loser!");
			}
		}
	}
}

void Game::calc_cycle()
{
	field->erase_element(current_figure, cx, cy);
	
	if (field->can_insert_element(current_figure, cx, 1 + cy))
	{
		field->insert_element(current_figure, cx, ++cy);
	}
	else
	{
		field->insert_element(current_figure, cx, cy);
		field->row_burning_check();
		current_figure.reset();
	}
}

void Game::rotate_figure()
{
	field->erase_element(current_figure, cx, cy);
	current_figure->rotate();

	if (field->can_insert_element(current_figure, cx, cy))
	{
		field->insert_element(current_figure, cx, cy);
	}
	else
	{
		current_figure->reverse_rotate();
		field->insert_element(current_figure, cx, cy);
	}
}

void Game::move_right()
{
	field->erase_element(current_figure, cx, cy);

	if (field->can_insert_element(current_figure, cx + 1, cy))
	{
		field->insert_element(current_figure, ++cx, cy);
	}
	else
	{
		field->insert_element(current_figure, cx, cy);
	}
}

void Game::move_left()
{
	field->erase_element(current_figure, cx, cy);
	
	if (field->can_insert_element(current_figure, cx - 1, cy))
	{
		field->insert_element(current_figure, --cx, cy);
	}
	else
	{
		field->insert_element(current_figure, cx, cy);
	}
}

void Game::move_down()
{
	field->erase_element(current_figure, cx, cy);

	if (field->can_insert_element(current_figure, cx, cy + 1))
	{
		field->insert_element(current_figure, cx, ++cy);
	}
	else
	{
		field->insert_element(current_figure, cx, cy);
	}
}
