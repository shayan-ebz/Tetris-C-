#include "Game.h"
#include <random>
#include <iostream>


Game::Game()
{
	m_grid = Grid();
	m_blocks = GetAllBlocks();

	m_currentBlock = GetRandomBlock();
	m_nextBlock = GetRandomBlock();

	bGameOver = false;	

	m_Score = 0;
}

Block Game::GetRandomBlock()
{
	// if the vector of blocks is empty, refill it
	if (m_blocks.empty())
	{
		m_blocks = GetAllBlocks();
	}

	int randomIndex = rand() % m_blocks.size(); // a number between 0 and vector size  [0 , 6] or [0, 7)

	Block block = m_blocks[randomIndex];

	//now remove the selected block from the vector so the next time it wont be selected repeatedly (tetris works this way)
	m_blocks.erase(m_blocks.begin() + randomIndex);

	return block;
}

std::vector<Block> Game::GetAllBlocks() const
{
	std::vector<Block> blocks = { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
	
	return blocks;
}

void Game::Draw()
{
	m_grid.Draw();
	m_currentBlock.Draw(10,10);

	// draw the next shape on the screen
	m_nextBlock.Draw(270, 270);
}

void Game::HandleInput()
{
	int pressedKeyCode = GetKeyPressed();

	// player pressed any key to restart the game
	if (bGameOver && pressedKeyCode)
	{
		bGameOver = false;
		Reset();
	}


	switch (pressedKeyCode)
	{
		case KEY_LEFT: // KEY_LEFT is an enum at raylib which holds the value of 263
			MoveBlockLeft();
			break;
		case KEY_RIGHT:
			MoveBlockRight();
			break;
		case KEY_DOWN:
			MoveBlockDown();
			UpdateScore(0, 1);
			break;
		case KEY_UP:
			RotateBlock();
			break;
		default:
			break;
	}

}

void Game::MoveBlockLeft()
{
	if (bGameOver)
	{
		return;
	}

	m_currentBlock.Move(0, -1);

	// check to see if the block is in the boundaries
	if (IsBlockOutside() || !IsBlockFits())
	{
		m_currentBlock.Move(0, 1);
	}
}

void Game::MoveBlockRight()
{
	if (bGameOver)
	{
		return;
	}

	m_currentBlock.Move(0, 1);

	// check to see if the block is in the boundaries
	if (IsBlockOutside() || !IsBlockFits())
	{
		m_currentBlock.Move(0, -1);
	}
}

void Game::MoveBlockDown()
{
	if (bGameOver)
	{
		return;
	}

	m_currentBlock.Move(1, 0);

	// check to see if the block is in the boundaries
	if (IsBlockOutside() || !IsBlockFits())
	{
		// undo the move and lock the block in place and proceed with the next block
		m_currentBlock.Move(-1,0);
		LockBlock();
	}
}

void Game::RotateBlock()
{
	if (bGameOver)
	{
		return;
	} 

	m_currentBlock.Rotate();

	if (IsBlockOutside() || !IsBlockFits())
	{
		m_currentBlock.UndoRotate();
	}
}

bool Game::IsBlockOutside()
{
	// get hold of all the block tiles 
	std::vector<FCellPoition> tiles = m_currentBlock.GetCurrentCellPositions();
	for (auto tile : tiles)
	{
		if (m_grid.IsBlockOutFromGrid(tile.m_row, tile.m_column))
		{
			return true;
		}
	}

	// tiles of blocks are inside the bounds
	return false;
}


void Game::LockBlock()
{
	// get a vector of cell positions of the tiles 
	std::vector<FCellPoition> tiles = m_currentBlock.GetCurrentCellPositions();
	
	// set the values of locked grid cells (to be the id of current block)
	for (auto tile : tiles)
	{
		// set the value of the grid cells to be equal to the block id value (at the beginning all grid values are 0)
		m_grid.m_gridCells[tile.m_row][tile.m_column] = m_currentBlock.m_id;
	}

	// get the next shape and spawn it from the top center
	m_currentBlock = m_nextBlock;

	m_nextBlock = GetRandomBlock();
	
	if (!IsBlockFits())
	{
		bGameOver = true;
	}

	int numRowsCleared = m_grid.ClearFullRows();
	UpdateScore(numRowsCleared, 0);


	//m_grid.PrintGrid_Helper();
}

bool Game::IsBlockFits()
{
	std::vector<FCellPoition> tiles = m_currentBlock.GetCurrentCellPositions();

	for (auto tile : tiles)
	{
		// if the grid is not empty in the tile's position
		if (!m_grid.IsCellEmpty(tile.m_row, tile.m_column))
		{
			return false;
		}
	}

	// yes block fits
	return true;
}

void Game::Reset()
{
	m_grid.InitializeGrid();
	m_blocks = GetAllBlocks();
	m_currentBlock = GetRandomBlock();
	m_nextBlock = GetRandomBlock();
	m_Score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared)
	{
	case 1:
		m_Score += 100;
		break;
	case 2:
		m_Score += 300;
		break;
	case 3:
		m_Score += 500;
		break;
	default:
		break;
	}

	m_Score += moveDownPoints;
}

