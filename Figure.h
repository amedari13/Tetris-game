#pragma once
#include "memory"
#include "vector"

//Figure -- класс который исключительно хранит форму фигур.Тут можно использовать
//через указатель либо по значению.В принципе должно быть так, чтобы внутри фигура могла
//быть любого размера хоть 5х5, а не стандартные 3х3 и всё чтобы при этом продолжало работать.
//В этом случае лучше через указатель(умный), например shared_ptr<>
//
//figure = Figure::random();
//figure.rotate()

enum class Symbols
{
	right_l = 0,
	left_l,
	t_shaped,
	cube,
	right_z,
	left_z,
	line
};

class Figure
{
public:
	Figure();
	void random();

	int get_width();
	int get_length();
	std::vector<std::pair<int, int>> get_form();
	
	std::vector<std::pair<int, int>> rotate();//вращает фигуру
	std::vector<std::pair<int, int>> reverse_rotate();//вращает фигуру в обратную сторону

private:
	std::vector<std::pair<int, int>> form_coords;
};
