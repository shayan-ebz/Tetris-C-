#include "Block.h"
#include <iostream>

Block::Block()
	: m_blockGridCellSize{ 30 }, m_rotationState{ 0 }, m_blockColors{ CreatCellColors() },
		m_rowOffset{0}, m_columnOffset{0}, m_id{0}
{

}

void Block::Draw(int offsetX, int offsetY)
{
	std::vector<FCellPoition> tiles = GetCurrentCellPositions();

	//std::cout << tiles[0].m_row << " , column: " << tiles[0].m_column << std::endl;


	for (const auto& tile : tiles)
	{
		DrawRectangle(tile.m_column * m_blockGridCellSize + offsetX, tile.m_row * m_blockGridCellSize + offsetY, m_blockGridCellSize - 1,
			m_blockGridCellSize - 1, m_blockColors[m_id]);
	}
}

void Block::Move(int rowOffset, int columnOffset)
{
	m_rowOffset += rowOffset;
	m_columnOffset += columnOffset;
}

std::vector<FCellPoition> Block::GetCurrentCellPositions()
{
	// get cell's current position 
	std::vector<FCellPoition> currentTiles = m_blockGrid[m_rotationState];
	std::vector<FCellPoition> movedTiles;
	//std::cout << currentTiles[0].m_row << ", column :: " << currentTiles[0].m_column << std::endl;
	// move the tiles of the blocks based on the offsets

	//std::cout << "m_rowOffset = " << m_rowOffset << " ;:::::: m_columnOffset = " << m_columnOffset << std::endl;
	for (auto tile : currentTiles)
	{
		FCellPoition newPosition = { tile.m_row + m_rowOffset, tile.m_column + m_columnOffset };
		//std::cout << " New Position m_rowOffset = " << newPosition.m_row << " ;:::::: m_columnOffset = " << newPosition.m_column << std::endl;
		movedTiles.push_back(newPosition);
	}
	//std::cout << movedTiles[0].m_row << ", column :: " << movedTiles[0].m_column << std::endl;
	return movedTiles;
}

void Block::Rotate()
{
	//todo:: should we explicitly put the value back to 0??? is it essential for our game to make it back to 0?
	
	m_rotationState = (m_rotationState + 1) % 4; // will always go from 0 to 3 [0,3]
	std::cout << m_rotationState << " ::::Rotate \n";
}

void Block::UndoRotate()
{
	--m_rotationState; 
	
	// this happens at state number 3, the rotate method adds to the data and it becomes 0 again and we decreament it here so it becomes -1
	if (m_rotationState < 0)
	{
		// back to the max state
		m_rotationState = static_cast<int>(m_blockGrid.size() - 1); // or in hard coded state  = 3
	}
	std::cout << m_rotationState << " ::::UndoRotate state \n";
}


LBlock::LBlock() : Block()
{
	m_id = 1;
	
	m_blockGrid[0] = { {0, 2}, {1, 0}, {1, 1}, {1, 2} }; // implicit conversion {0, 2} -> FCellPosition(0,2)
	m_blockGrid[1] = { {0, 1}, {1, 1}, {2, 1}, {2, 2} };
	m_blockGrid[2] = { {1, 0}, {1, 1}, {1, 2}, {2, 0} };
	m_blockGrid[3] = { {0, 0}, {0, 1}, {1, 1}, {2, 1} };

	// Move the block to spawn at the top-center of the grid
	Move(0, 3);
}

JBlock::JBlock() : Block()
{
	m_id = 2;

	m_blockGrid[0] = { {0, 0}, {1, 0}, {1, 1}, {1, 2} };
	m_blockGrid[1] = { {0, 1}, {0, 2}, {1, 1}, {2, 1} };
	m_blockGrid[2] = { {1, 0}, {1, 1}, {1, 2}, {2, 2} };
	m_blockGrid[3] = { {0, 1}, {1, 1}, {2, 0}, {2, 1} };

	// Move the block to spawn at the top-center of the grid
	Move(0, 3);
}

IBlock::IBlock() : Block()
{
	m_id = 3;

	m_blockGrid[0] = { {1, 0}, {1, 1}, {1, 2}, {1, 3} };
	m_blockGrid[1] = { {0, 2}, {1, 2}, {2, 2}, {3, 2} };
	m_blockGrid[2] = { {2, 0}, {2, 1}, {2, 2}, {2, 3} };
	m_blockGrid[3] = { {0, 1}, {1, 1}, {2, 1}, {3, 1} };

	// Move the block to spawn at the top-center of the grid
	Move(-1, 3);
}

OBlock::OBlock() : Block()
{
	m_id = 4;

	//todo:: do optimization for OBlock later
	m_blockGrid[0] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
	m_blockGrid[1] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
	m_blockGrid[2] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
	m_blockGrid[3] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };

	// Move the block to spawn at the top-center of the grid
	Move(0, 4);
}

SBlock::SBlock() : Block()
{
	m_id = 5;

	m_blockGrid[0] = { {0, 1}, {0, 2}, {1, 0}, {1, 1} };
	m_blockGrid[1] = { {0, 1}, {1, 1}, {1, 2}, {2, 2} };
	m_blockGrid[2] = { {1, 1}, {1, 2}, {2, 0}, {2, 1} };
	m_blockGrid[3] = { {0, 0}, {1, 0}, {1, 1}, {2, 1} };

	// Move the block to spawn at the top-center of the grid
	Move(0, 3);
}

TBlock::TBlock() : Block()
{
	m_id = 6;

	m_blockGrid[0] = { {0, 1}, {1, 0}, {1, 1}, {1, 2} };
	m_blockGrid[1] = { {0, 1}, {1, 1}, {1, 2}, {2, 1} };
	m_blockGrid[2] = { {1, 0}, {1, 1}, {1, 2}, {2, 1} };
	m_blockGrid[3] = { {0, 1}, {1, 0}, {1, 1}, {2, 1} };

	// Move the block to spawn at the top-center of the grid
	Move(0, 3);
}

ZBlock::ZBlock() : Block()
{
	m_id = 7;

	m_blockGrid[0] = { {0, 0}, {0, 1}, {1, 1}, {1, 2} };
	m_blockGrid[1] = { {0, 2}, {1, 1}, {1, 2}, {2, 1} };
	m_blockGrid[2] = { {1, 0}, {1, 1}, {2, 1}, {2, 2} };
	m_blockGrid[3] = { {0, 1}, {1, 0}, {1, 1}, {2, 0} };

	// Move the block to spawn at the top-center of the grid
	Move(0, 3);
}
