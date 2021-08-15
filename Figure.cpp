#include "Figure.h"
#define _USE_MATH_DEFINES
#include <math.h>

Figure::Figure()
{
	//random(); сделать рандомное вращение?
}

std::vector<std::vector<char>> Figure::get_form()
{
	int max_x = form_coords[0].first;//ищем максимальные значения по x и у для постройки матрицы тетрино
	int max_y = form_coords[0].second;
	for (auto pair : form_coords) 
	{
		max_x = pair.first > max_x ? pair.first : max_x;
		max_y = pair.second > max_y ? pair.second : max_y;
	}
	std::vector<std::vector<char>> form;
	//задаем рзмерность массива и заполняем нулями
	form.resize(max_x);
	for (int i = 0; i < max_x; ++i)
		form[i].resize(max_y, 0);
	
	for (auto pair : form_coords) //по координатам из пары находим в новой матрице квадратик и закрашиваем
	{
		form[pair.first][pair.second] = 1;
	}
	return form;
}

std::vector<std::pair<int, int>> Figure::rotate()
{
	//x' = x*cos(a) - y*sin(a)
	//y' = x*sin(a) + y*cos(a)
	//получаем вектор х и у и возвращаем повернутый на 90 градусов
	int min_x = 0, min_y = 0;
	for (auto pair : form_coords) 
	{
		pair.first = static_cast<int>(
			 - pair.second * sin(90 * M_PI / 180.)
			);
		if (pair.first < 0 && pair.first < min_x) min_x = pair.first;

		pair.second = static_cast<int>(
			pair.first * sin(90 * M_PI / 180.)
			);

		if (pair.second < 0 && pair.second < min_y) min_y = pair.second;
	}
	if (min_x < 0 || min_y < 0) //если нашли отрицательные числа-- сдвигаем фигуру
	{
		for (auto pair : form_coords) 
		{
			pair.first -= min_x;
			pair.second -= min_y;
		}
	}
	return form_coords;// нужен сдвиг для избежания отрицательных чисел
}

std::vector<std::pair<int, int>> Figure::random()
{
	//выбирает фигуру
	//возвращает все в координатах
	Symbols current_symbol = static_cast<Symbols>(rand() % 7);
	//теперь эти данные надо преобразовать в вектор пар кординат
	//сначала символ
	switch (current_symbol)
	{
	case t_shaped:  form_coords = { {0,0}, {1,0}, {2,0}, {1,1} }; break;
	case right_l:   form_coords = { {0,0}, {1,0}, {0,1}, {0,2} }; break;
	case right_z:   form_coords = { {0,0}, {1,0}, {1,1}, {2,1} }; break;
	case left_l:    form_coords = { {0,0}, {0,1}, {0,2}, {1,2} }; break;
	case left_z:    form_coords = { {0,1}, {1,1}, {1,0}, {2,0} }; break;
	case cube:      form_coords = { {0,0}, {0,1}, {1,0}, {1,1} }; break;
	case line:      form_coords = { {0,0}, {0,1}, {0,2}, {0,3} }; break;
	default: throw _EXCEPTION_;
	}
	return form_coords;//тут чета странное
}
enum Symbols
{
	right_l = 0,
	left_l,
	t_shaped,
	cube,
	right_z,
	left_z,
	line
};
