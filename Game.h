#pragma once
#include "Field.h"
#include <map>
#include <functional>
#include <memory>

//Game -- класс, который взаимодействует с пользователем, обрабатывает клавиатуру
//помнит текущую фигуру и что в данный момент происходит
//помнит местоположение текущей фигуры

class Game
{
public:
	Game();
	void Start();
	void Proccess(int);
	void calc_cycle();

private:
	std::shared_ptr<Field> field;
	std::shared_ptr<Figure> current_figure;

	int cx;
	int cy;

	bool gameOver = false;

	void rotate_figure();
	void move_right();
	void move_left();
	void move_down();


	std::map<int, std::function<void()>> keys
	{
		  {32, [&]() {rotate_figure(); }}
		, {77, [&]() {move_right();    }}
		, {75, [&]() {move_left();     }}
		, {80, [&]() {move_down();     }}
	};
};
