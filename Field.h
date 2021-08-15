#pragma once
#include "windows.h"
#include <vector>
#include "Figure.h"

//Field -- класс, который только хранит "стакан".умеет прибавлять фигуру, удалять,
//сдвигать ниже, выше и проч.
//
//if (field->can_add(figure, x, y) { ... }
//
//field->add(figure, x, y);
//field->sub(figure, x, y);
class Field
{
public:
	Field();
	//Figure current_element(Field*); // неиспользуемая функция, хотя по коду должна быть такая переменная

	// эти переменные почему-то не private
	int COLS; // большие буквы обычно используются для макросов
	int ROWS;
	std::vector<std::vector<char>> coords;

	Figure currentElement; // добавил 

	void createRandomFigure();
	bool canInsertElement();
	void insertElement();
	void deleteElement();
	void clearField();
	void drawField();
};

