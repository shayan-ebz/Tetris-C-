#pragma once
#include <map>
#include <vector>
#include <utility>
#include "Colors.h"


//////////////
/// \brief this struct holds two integers: row and column position 
//////////////
struct FCellPoition
{
	int m_row{0};
	int m_column{ 0 };
};



class Block
{
	
///////////////////// data 
private:
	int m_blockGridCellSize;
	int m_rotationState;
	std::vector<Color> m_blockColors;

	int m_rowOffset;
	int m_columnOffset;

public:
	int m_id;
	std::map<int, std::vector<FCellPoition>> m_blockGrid;



///////////////////// methods 
public:

	//////////////
	/// \brief default constructor to initialize the data members
	//////////////
	Block();

	//////////////
	/// \brief draws the block on the screen using raylib DrawRectangle(...)
	//////////////
	void Draw(int offsetX, int offsetY);

	//////////////
	/// \brief modifies the rowOffset and columnOffset for the blocks
	/// \param rowOffset: offset of the row
	/// \param columnOfsset: offset of the column 
	//////////////
	void Move(int rowOffset, int columnOffset);


	//////////////
	/// \brief calculates the current cell position after the movement(the offsetting part) by adding the updated offsets to the current position
	/// \return a vector of cell position (row, column) after the movement
	//////////////
	std::vector<FCellPoition> GetCurrentCellPositions();


	//////////////
	/// \brief simply updates m_rotationState member variable and checks the validation of the data
	//////////////
	void Rotate();

	//////////////
	/// \brief undo the rotation if the boundary check fails. when rotating close to the walls there is possiblity of rotating outside
	/// \brief of the bounds.
	//////////////
	void UndoRotate();


};


class LBlock : public Block
{
public:
	LBlock();

};

class JBlock : public Block
{
public:
	JBlock();

};

class IBlock : public Block
{
public:
	IBlock();

};

class OBlock : public Block
{
public:
	OBlock();

};

class SBlock : public Block
{
public:
	SBlock();

};

class TBlock : public Block
{
public:
	TBlock();

};

class ZBlock : public Block
{
public:
	ZBlock();

};
