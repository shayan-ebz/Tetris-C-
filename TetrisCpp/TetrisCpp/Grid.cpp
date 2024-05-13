#include "Grid.h"
#include <iostream>//todo:: delete this header at the cooking process
#include "Colors.h"

Grid::Grid()
	:m_numRow{20}, m_numCol{10}, m_cellSize{30}
{
	InitializeGrid();
	m_colors = CreatCellColors();
}

void Grid::InitializeGrid()
{
	// zero initializing the grid
	for (int i = 0; i < m_numRow; ++i)
	{
		for (int j = 0; j < m_numCol; ++j)
		{
			m_gridCells[i][j] = 0;
		}
	}
}

void Grid::Draw()
{
	for (int row = 0; row < m_numRow; ++row)
	{
		for (int col = 0; col < m_numCol; ++col)
		{
			// get the value of the cell
			int cellValue{ m_gridCells[row][col] };

			// draw a square for the each cell of the grid with correct color (based on the cellValue, e.g. empty cell's value == 0 => darkgray
			DrawRectangle(col * m_cellSize + 10 , row * m_cellSize + 10, m_cellSize - 1, m_cellSize - 1, m_colors[cellValue]);
		}
	}
}

bool Grid::IsBlockOutFromGrid(int blockRow, int blockColumn)
{
	// valid state for the block cell
	if (blockRow >= 0 && blockRow < m_numRow && blockColumn >= 0 && blockColumn < m_numCol)
	{
		return false;
	}

	return true;
}

bool Grid::IsCellEmpty(int gridRow, int gridColumn)
{
	// grid cell is empty
	if (m_gridCells[gridRow][gridColumn] == 0)
	{
		return true;
	}

	// grid cell is not empty
	return false;
}

int Grid::ClearFullRows()
{
	int completed = 0;

	for (int row = m_numRow - 1; row >= 0; --row) // row == 19; row >= 0; --row;
	{
		if (IsRowFull(row))
		{
			ClearRow(row);
			completed++;
		}
		else if (completed > 0)
		{
			MoveRowDown(row, completed);
		}
	}

	return completed;
}

bool Grid::IsRowFull(int gridRow)
{
	for (int colum = 0; colum < m_numCol; ++colum)
	{
		if (m_gridCells[gridRow][colum] == 0)
		{
			return false;
		}
	}

	return true;
}

void Grid::ClearRow(int gridRow)
{
	for (int colum = 0; colum < m_numCol; ++colum)
	{
		m_gridCells[gridRow][colum] = 0;
	}
}

void Grid::MoveRowDown(int row, int numRowsToMoveDown)
{
	for (int column = 0; column < m_numCol; ++column)
	{
		// shift the up row values to down by the factor of numRows(number of full rows)
		m_gridCells[row + numRowsToMoveDown][column] = m_gridCells[row][column];

		// reset the shifted rows to 0
		m_gridCells[row][column] = 0;
	}
}

void Grid::PrintGrid_Helper() const
{
	for (int i = 0; i < m_numRow; ++i)
	{
		for (int j = 0; j < m_numCol; ++j)
		{
			std::cout << m_gridCells[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


