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

int Field::get_cols()
{
	return cols;
}

int Field::get_rows()
{
	return rows;
}

void Field::set(int x, int y, char elem)
{
	cells[y][x] = elem;
}

bool Field::is_empty(int x, int y)
{
	return cells[y][x] == 0 ? true : false;
}

bool Field::can_insert_element(std::shared_ptr<Figure> figure, int cx, int cy)
{
	for (std::pair<int, int> pair : figure->get_form())
	{
		int cc = pair.first + cx;
		int rr = pair.second + cy;
		// проверяем, что координаты в пределах экрана
		if (cc < 0 || cc >= cols)
			return false;
		if (rr < 0 || rr >= rows)
			return false;

		if (!is_empty(cc, rr))
			return false;
	}
	return true;
}

void Field::insert_element(std::shared_ptr<Figure> figure, int cx, int cy)
{
	for (std::pair<int, int> pair : figure->get_form())
	{
		set(pair.first + cx, pair.second + cy, 1);
	}
}

void Field::erase_element(std::shared_ptr<Figure> figure, int cx, int cy)
{
	for (std::pair<int, int> pair : figure->get_form())
	{
		set(pair.first + cx, pair.second + cy, 0);
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

void Field::clear_field()
{
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
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
			//вот тут вставленно новое
			r++;
		}z = 0;
	}
}
