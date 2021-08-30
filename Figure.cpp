#include "Figure.h"
#define _USE_MATH_DEFINES
#include <math.h>

Figure::Figure() 
{
	form_coords.resize(5);
	random();
}

void Figure::random()
{
	//выбирает фигуру
	//возвращает все в координатах
	Symbols current_symbol = static_cast<Symbols>(rand() % 7);
	//теперь эти данные надо преобразовать в вектор пар кординат
	//сначала символ
	switch (current_symbol)
	{
	case Symbols::t_shaped:  form_coords = { {0,0}, {1,0}, {2,0}, {1,1} }; break;
	case Symbols::right_l:   form_coords = { {0,0}, {1,0}, {0,1}, {0,2} }; break;
	case Symbols::right_z:   form_coords = { {0,0}, {1,0}, {1,1}, {2,1} }; break;
	case Symbols::left_l:    form_coords = { {0,0}, {0,1}, {0,2}, {1,2} }; break;
	case Symbols::left_z:    form_coords = { {0,1}, {1,1}, {1,0}, {2,0} }; break;
	case Symbols::cube:      form_coords = { {0,0}, {0,1}, {1,0}, {1,1} }; break;
	case Symbols::line:      form_coords = { {0,0}, {0,1}, {0,2}, {0,3} }; break;
	default: form_coords = { {0,0}, {0,1}, {0,2}, {0,3} }; break;
	}
}

int Figure::get_width()
{
	int max_x = form_coords[0].first;
	for (auto pair : form_coords)
		max_x = pair.first > max_x ? pair.first : max_x;
	return max_x;
}

int Figure::get_length()
{
	int max_y = form_coords[0].second;
	for (auto pair : form_coords)
		max_y = pair.second > max_y ? pair.second : max_y;
	return max_y;
}

std::vector<std::pair<int, int>> Figure::get_form()
{
	return form_coords;
}

std::vector<std::pair<int, int>> Figure::rotate()
{
	//x' = x*cos(a) - y*sin(a)
	//y' = x*sin(a) + y*cos(a)
	//получаем вектор х и у и возвращаем повернутый на 90 градусов
	int min_x = 0, min_y = 0;
	for (auto& pair : form_coords) 
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
		for (auto& pair : form_coords) 
		{
			pair.first -= min_x;
			pair.second -= min_y;
		}
	}
	return form_coords;
}

std::vector<std::pair<int, int>> Figure::reverse_rotate()
{
	//x' = x*cos(a) - y*sin(a)
	//y' = x*sin(a) + y*cos(a)
	//получаем вектор х и у и возвращаем повернутый на 90 градусов
	int min_x = 0, min_y = 0;
	for (auto& pair : form_coords)
	{
		pair.first = static_cast<int>(
			-pair.second * sin(-90 * M_PI / 180.)
			);
		if (pair.first < 0 && pair.first < min_x) min_x = pair.first;

		pair.second = static_cast<int>(
			pair.first * sin(-90 * M_PI / 180.)
			);

		if (pair.second < 0 && pair.second < min_y) min_y = pair.second;
	}
	if (min_x < 0 || min_y < 0) //если нашли отрицательные числа-- сдвигаем фигуру
	{
		for (auto& pair : form_coords)
		{
			pair.first -= min_x;
			pair.second -= min_y;
		}
	}
	return form_coords;
}
