#include "Field.h"
#include "memory"
#include <wincrypt.h>
#pragma once

//Figure -- класс который исключительно хранит форму фигур.Тут можно использовать
//через указатель либо по значению.В принципе должно быть так, чтобы внутри фигура могла
//быть любого размера хоть 5х5, а не стандартные 3х3 и всё чтобы при этом продолжало работать.
//В этом случае лучше через указатель(умный), например shared_ptr<>
//
//figure = Figure::random();
//figure.rotate()

class Figure
{
public:
	Figure();
	std::vector<std::vector<char>> get_form();//возвращает форму в виде матрицы
	std::vector<std::pair<int, int>> rotate();//вращает фигуру

private:
	std::vector<std::pair<int, int>> form_coords;//фигура через координаты
	std::vector<std::pair<int, int>> random();//создает рандомную фигуру
};
