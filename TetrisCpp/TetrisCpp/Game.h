#pragma once
#include "Grid.h"
#include "Block.h"

class Game
{
///////////////////// data 
private:

	// block vector that holds the 7 types of blocks (l-block, z-block,...)
	std::vector<Block> m_blocks;

	Block m_currentBlock;
	Block m_nextBlock;

public:

	// the 20 by 10 grid 
	Grid m_grid;

	bool bGameOver;

	int m_Score;


///////////////////// methods 
public:

	//////////////
	/// \brief default constructor: creates the grid and the 7 blocks
	//////////////
	Game();

	//////////////
	/// \brief gets the input from the player and assigns a proper action to the input
	//////////////
	void Draw();

	//////////////
	/// \brief gets the input from the player and assigns a proper action to the input
	//////////////
	void HandleInput();

	//////////////
	/// \brief calls the move functoin with proper values to move down the tiles and checks certain situation
	/// \brief like if the block has reached the bottom or hit the top of another block
	/// \brief NOTE: this function needs to be public 
	//////////////
	void MoveBlockDown();

private:

	//////////////
	/// \brief constructs and returns all 7 types of the blocks in a vector container
	/// \return a vector of blocks that holds 7 objects of the block types
	//////////////
	std::vector<Block> GetAllBlocks() const;
	
	//////////////
	/// \brief selects a random block from the 7 types of the blocks and returns one randomly 
	/// \brief NOTE: the selection is random but after a block is returned it will be eliminated from the list so it won't be selected
	/// \brief multiple times and other blocks will be selected as well
	/// \return a block object(l-block, z-block...)
	//////////////
	Block GetRandomBlock();

	bool IsBlockOutside();

	void MoveBlockLeft();
	void MoveBlockRight();

	void RotateBlock();

	void LockBlock();

	bool IsBlockFits();

	void Reset();

	void UpdateScore(int linesCleared, int moveDownPoints);
};

