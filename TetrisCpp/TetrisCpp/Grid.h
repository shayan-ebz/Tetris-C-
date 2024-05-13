#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
///////////////////// data 
private:
	// number of rows and columns in the grid
	int m_numCol;
	int m_numRow;
	// size of the grid cell in pixels (the size of width and height of the cell)
	int m_cellSize; 

	//todo:: can this be implemented in the block class?
	// vector that is holding colors. we have 7 colors for blocked cells and an empty color for the empty cells (overall 8 colors)
	std::vector<Color> m_colors;


public:
	// the grid 2D array
	int m_gridCells[20][10];



///////////////////// methods 
public:

	//////////////
	/// \brief default constructor to initialize the data members
	//////////////
	Grid();

	//////////////
	/// \brief we initialize the grid cells to 0
	//////////////
	void InitializeGrid();

	//////////////
	/// \brief [Developer use only] this method prints the values in the grid. e.g. 0 for an empty cell and 1 for the green ...
	//////////////
	void PrintGrid_Helper() const;

	//////////////
	/// \brief Draws each cell of the grid with a specific color [empty cell is darkgray,...]
	//////////////
	void Draw();
	

	//////////////
	/// \brief checks to see if the block is out of the grid (does a simple check on the tile coordinates to check the boundaries)
	/// \param blockRow: block's row coordinate
	/// \param blockColumn: block's column coordinate
	/// \return true if the block is out of the grid
	//////////////
	bool IsBlockOutFromGrid(int blockRow, int blockColumn);

	//////////////
	/// \brief checks to see if grid in the given coordinate is empty (has value of 0)
	/// \param gridRow: grid cell's row
	/// \param gridColumn: grid cell's column
	/// \return true if the cell is empty (has value of 0) and false otherwise 
	//////////////
	bool IsCellEmpty(int gridRow, int gridColumn);

	//////////////
	/// \brief checks ALL the rows from the bottom to the top to see there is any full rows
	/// \return number of the full rows from the bottom to top
	//////////////
	int ClearFullRows();

private:

	//////////////
	/// \brief checks grid row values to see if the row is full or not
	/// \return true if the row is full
	//////////////
	bool IsRowFull(int gridRow);

	//////////////
	/// \brief clears the given row by making all the cell values back to 0
	/// \param grid's row coordinate
	//////////////
	void ClearRow(int gridRow);


	//////////////
	/// \brief shifts down all row values based on the given parameters (this is when a row is completed and vanishes, so the rows
	/// \brief above it would be shifted down to fill the empty places 
	/// \param row: grid's row coordinate
	/// \param numRowsToMoveDown: is how many rows have been completed so the row should shift down based on that
	//////////////
	void MoveRowDown(int row, int numRowsToMoveDown);

};

