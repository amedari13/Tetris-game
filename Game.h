#pragma once
#include "Field.h"
#include <map>
#include <functional>
#include <memory>

//Game -- класс, который взаимодействует с пользователем, обрабатывает клавиатуру
//помнит текущую фигуру и что в данный момент происходит
//помнит местоположение текущей фигуры
//Создаёт поле Field, причём указывает его размер
//field = std::make_shared<Field>(10, 25);

class Game
{
public:
	Game();
	void Start();

private:
	std::shared_ptr<Field> field;

	std::shared_ptr<Figure> current_figure;
	int cx;//текущие координаты
	int cy;

	bool gameOver = false;
	bool inserted = 0; // опускается ли в данный момент фигура



	/*std::map<int, std::function<void()>> Keys
	{
		  {32, [&]() {Rotate();	  }}
		, {75, [&]() {StepLeft(); }}
		, {80, [&]() {StepDown(); }}
		, {77, [&]() {StepRight(); }}
	};*/
};
