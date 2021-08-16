#pragma once
#include "windows.h"
#include "Figure.h"
#include <vector>
#include <memory>

//Field -- класс, который только хранит "стакан".умеет прибавлять фигуру, удалять,
//сдвигать ниже, выше и проч.

class Field
{
public:
	Field(int, int);
	void move_right(std::shared_ptr<Figure>, int, int);
	void move_left(std::shared_ptr<Figure>, int, int);
	void move_down(std::shared_ptr<Figure>, int, int);
	void move_up(std::shared_ptr<Figure>, int, int);
	void rotate(std::shared_ptr<Figure>, int, int);

	bool can_insert_element(std::shared_ptr<Figure>, int x, int y);
	void insert_element(std::shared_ptr<Figure>, int x, int y);
	void delete_element(std::shared_ptr<Figure>, int x, int y);

	void draw_field();
	void clear_field();
	void row_burning_check();

private:
	int cols; 
	int rows;
	std::vector<std::vector<char>> cells;
};

