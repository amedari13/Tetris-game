#include "Field.h"
Field::Field(int col, int row)
{
	cols = col;
	rows = row;
	cells.resize(rows);
	for (size_t i = 0; i < cells.size(); ++i)
	{
		cells[i].resize(cols);
	}
}

void Field::delete_element(std::shared_ptr<Figure> figure, int cx, int cy)
{
	for (int len = 0; len < figure->get_length(); ++len)
	{
		for (int wid = 0; wid < figure->get_width(); ++wid)
		{
			int rr = len + cy;
			int cc = wid + cx;

			if (figure->get_form()[len][wid])
				cells[rr][cc] = 0;
		}
	}
}

//готовые 
void Field::clear_field()
{
	for (int r = 0; r < rows; ++r)
		for (int c = 0; c < cols; ++c)
			cells[r][c] = 0;
}

void Field::row_burning_check()//переделать логику --> пропускает некоторые ряды из-за сдвига вниз
{
	for (int r = rows - 1; r >= 0; --r) {
		//проверяем ряды на заполенность
		int z = 0;
		for (int c = 0; c < cols; ++c)
			if (cells[r][c] == 1)
				z++;
		//если нашли ряд то сжигаем его и сдвигаем все содержимое вниз
		if (z == cols) {
			for (int c = 0; c < cols; ++c)
				cells[r][c] = 0;
			for (int r0 = r; r0 > 0; r0--)
				for (int c = 0; c < cols; ++c)
					cells[r0][c] = cells[r0 - 1][c];
		}z = 0;
	}
}
void Field::draw_field()
{
	// получаем хэндл консоли
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// запоминаем результаты
	COORD crds{ 35, 0 };

	for (int r = 0; r < rows; ++r)
	{
		crds.Y = r;
		// устанавливаем курсор в нужную позицию
		SetConsoleCursorPosition(hConsole, crds);


		printf("\xB3"); // левая граница стакана
		for (int c = 0; c < cols; ++c)
		{
			if (cells[r][c] == 0)
				// выводим пустой квадратик
				printf("  ");
			else
				// выводим заполненный квадратик
				printf("\xDB\xDB");
		}
		printf("\xB3"); // правая граница стакана
	}

	crds.Y = rows;
	// устанавливаем курсор в нужную позицию
	SetConsoleCursorPosition(hConsole, crds);

	// выводим нижнюю границу
	printf("\xC0");
	for (int c = 0; c < cols; ++c)
		printf("\xC4\xC4");
	printf("\xD9");
}

//под вопросом
bool Field::can_insert_element(std::shared_ptr<Figure> figure, int cx, int cy)
{
	for (int len = 0; len < figure->get_length(); ++len)//проходим по матрице тетрино
	{
		for (int wid = 0; wid < figure->get_width(); ++wid)
		{
			int rr = len + cy;//границы тетрино
			int cc = wid + cx;

			if (figure->get_form()[len][wid] == 0)
				continue;

			// проверяем, что координаты в пределах экрана
			if (rr < 0 || rr >= rows)
				return false;
			if (cc < 0 || cc >= cols)
				return false;

			// проверяем, что ячейка не занята
			if (cells[rr][cc])
				return false;
		}
	}
	return true;
}

void Field::move_right(std::shared_ptr<Figure> figure, int cx, int cy)
{
	delete_element(figure, cx, cy);//удаляем ис прошлого места
	cx++;//увеличиваем текущие координаты по столбцу на 1
	if (!can_insert_element(figure, cx, cy))
	{
		cx--;
		insert_element(figure, cx, cy);
	}
	else
		insert_element(figure, cx, cy);
}

void Field::move_left(std::shared_ptr<Figure> figure, int cx, int cy)
{
	delete_element(figure, cx, cy);
	cx--;
	if (!can_insert_element(figure, cx, cy)) {
		cx++;
		insert_element(figure, cx, cy);
	}
	else
		insert_element(figure, cx, cy);

}

void Field::move_down(std::shared_ptr<Figure> figure, int cx, int cy)
{
	delete_element(figure, cx, cy);
	cy++;
	if (!can_insert_element(figure, cx, cy)) {
		cy--;
		insert_element(figure, cx, cy);
	}
	else
		insert_element(figure, cx, cy);
}

void Field::move_up(std::shared_ptr<Figure> figure, int cx, int cy)
{
	delete_element(figure, cx, cy);
	cy--;
	if (!can_insert_element(figure, cx, cy)) {
		cy++;
		insert_element(figure, cx, cy);
	}
	else
		insert_element(figure, cx, cy);
}

void Field::rotate(std::shared_ptr<Figure> figure, int cx, int cy)
{
	delete_element(figure, cx, cy);
	figure->rotate();
	if (!can_insert_element(figure, cx, cy))
	{
		figure->reverse_rotate();
		insert_element(figure, cx, cy);
	}
	else
	{
		insert_element(figure, cx, cy);
	}
}

void Field::insert_element(std::shared_ptr<Figure> figure, int cx, int cy)
{
	for (int len = 0; len < figure->get_length(); ++len)
	{
		for (int wid = 0; wid < figure->get_width(); ++wid)
		{
			int rr = len + cy;
			int cc = wid + cx;

			if (figure->get_form()[len][wid])
				cells[rr][cc] = 1;
		}
	}
}