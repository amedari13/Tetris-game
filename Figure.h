#pragma once
#include "memory"
#include "vector"

//Figure -- класс который исключительно хранит форму фигур.

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
	
	std::vector<std::pair<int, int>> rotate();
	std::vector<std::pair<int, int>> reverse_rotate();

private:
	std::vector<std::pair<int, int>> form_coords;
};
