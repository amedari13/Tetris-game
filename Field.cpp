#include "Field.h"
Field::Field()
{
	COLS = 12;
	ROWS = 25;
	coords.resize(25);
	for (size_t i = 0; i < coords.size(); ++i)
	{
		coords[i].resize(12);
	}
}

void Field::createRandomFigure()
{
	// обычно, в таких случаях передаётся не ссылка, а указатель
	const Field &ref = *this;

	// нет такого поля current_element, это как бы функция у тебя
	current_element = *new Figure(ref);

	// и, кстати, есть вопрос с архитектурой
	// класс Figure не должен по идее иметь нималейшего понятия о размере поля, а ты зачем-то
	// передаёшь указатель на класс Field и только для того, чтобы Figure полезла своими грязными
	// ручками во внутренности класса Field.

	// У тебя должен быть класс фигуры, которы умеет скажем только сообщать форму элемента
	// т.е. это что-то битового поля
	// .#.
	// .#.
	// .##
	// Как реализовано хранение этих полей это внутреннее дело класса Figure
	// А что делать с информацией -- это внутреннее дело класса Field.
	// Т.е. код в моём представлении должен выглядеть так
	//
	// auto f = Fugure::random();
	// a.rotate_left(); // к примеру вращаем
	// a.rotate_left(); // ещё раз
	// field->add(f, x, y); //добавляем фигуру
	// field->sub(f, x, y); //удаляем фигуру



}

bool Field::canInsertElement()
{
	for (int r = 0; r < 3; ++r)
	{
		for (int c = 0; c < 3; ++c)
		{
			int rr = r + current_element.current_row;
			int cc = c + current_element.current_col;

			if (current_element.symbol[r][c] == 0)
				continue;

			// проверяем, что координаты в пределах экрана
			if (rr < 0 || rr >= ROWS)
				return false;
			if (cc < 0 || cc >= COLS)
				return false;

			// проверяем, что ячейка не занята
			if (coords[rr][cc])
				return false;
		}
	}
	return true;
}
void Field::insertElement()
{
	for (int r = 0; r < 3; ++r)
	{
		for (int c = 0; c < 3; ++c)
		{
			int rr = r + current_element.current_row;
			int cc = c + current_element.current_col;

			if (current_element.symbol[r][c])
				coords[rr][cc] = 1;
		}
	}
}
void Field::deleteElement()
{
	for (int r = 0; r < 3; ++r)
	{
		for (int c = 0; c < 3; ++c)
		{
			int rr = r + current_element.current_row;
			int cc = c + current_element.current_col;

			if (current_element.symbol[r][c])
				coords[rr][cc] = 0;
		}
	}
}
void Field::clearField()
{
	for (int r = 0; r < ROWS; ++r)
		for (int c = 0; c < COLS; ++c)
			coords[r][c] = 0;
}
void Field::drawField()
{
	// получаем хэндл консоли
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// запоминаем результаты
	COORD crds{ 35, 0 };

	for (int r = 0; r < ROWS; ++r)
	{
		crds.Y = r;
		// устанавливаем курсор в нужную позицию
		SetConsoleCursorPosition(hConsole, crds);


		printf("\xB3"); // левая граница стакана
		for (int c = 0; c < COLS; ++c)
		{
			if (coords[r][c] == 0)
				// выводим пустой квадратик
				printf("  ");
			else
				// выводим заполненный квадратик
				printf("\xDB\xDB");
		}
		printf("\xB3"); // правая граница стакана
	}

	crds.Y = ROWS;
	// устанавливаем курсор в нужную позицию
	SetConsoleCursorPosition(hConsole, crds);

	// выводим нижнюю границу
	printf("\xC0");
	for (int c = 0; c < COLS; ++c)
		printf("\xC4\xC4");
	printf("\xD9");
}
