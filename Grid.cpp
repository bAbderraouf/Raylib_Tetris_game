#include "Grid.h"

Grid::Grid(int nRows, int nCols, int cSize)
{
	// rand
	std::srand(std::time(nullptr));

	numRows = nRows;
	numCols = nCols;
	cellSize = cSize; // pixels

	//draw grid margins
	leftMargin = 0;
	topMargin = 0;

	Initialize(); // set grid to 0
	cellColorsList = getCellColorsList();
}

void Grid::Initialize()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			grid[i][j] = 0; //rand() % 9;

		}
	}

}

void Grid::AddPieceToGrid(Piece & const piece)
{
	// grid = last state + new state (new piece)
	Position pos = piece.getPosition();
	
	for (int row = 0; row < piece.getSize(); row++) //rows
	{
		for (int col = 0; col < piece.getSize(); col++) // columns
		{
			if(row + pos.row < numRows  && col + pos.col < numCols)
				if (piece.block[row][col] > 0) // only for not empty cases block
					grid[row + pos.row ][col + pos.col] = piece.block[row][col] ; 
				
		}
				
	}
}

void Grid::EreasePieceFromGrid(Piece& const piece) 
{
	Position pos = piece.getPosition();

	for (int row = 0; row < piece.getSize(); row++) //rows
	{
		for (int col = 0; col < piece.getSize(); col++) // columns
		{
				if (piece.block[row][col] > 0)
					grid[row + pos.row][col + pos.col] = 0;
		}

	}
}

void Grid::PrintValues()
{
	std::cout <<"=======================" << std::endl;
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Grid::Draw()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			int cellValue = grid[row][col];
			DrawOneCell( col*cellSize+1 , row * cellSize+1, cellSize -1, cellSize-1, cellColorsList[cellValue]);
		}
	}
}

void Grid::DrawOneCell(int x , int y, int w , int h, Color color)
{
	DrawRectangle(leftMargin + x, topMargin + y, w, h, color);
}

int Grid::getNumRows()
{
	return numRows;
}

int Grid::getNumCols()
{
	return numCols;
}

std::vector<Color> Grid::getCellColorsList()
{
	Color orange = { 255, 102, 0, 255 };
	Color green = { 128, 255, 0 , 255 };
	Color red = { 255, 64, 0 , 255 };
	Color yellow = { 255, 255, 0, 255 };
	Color cyan = { 0, 255, 255, 255 };
	Color blue = { 0, 0, 255, 255 };
	Color magenta = { 255, 0, 255 , 255 };
	Color brown = { 165, 42, 42 , 255 };
	Color black = { 0, 0, 0  , 255 };
	Color lightGreen = { 0, 255, 0, 255 };
	Color lightBlue = { 0,  255, 255, 255 };
	Color white = { 255, 255, 255 , 255 };
	Color pink = { 255, 0, 102, 255 };
	Color purple = { 153, 0, 204 , 255 };

	std::vector<Color> colorsList = { black, red ,blue,yellow , lightGreen, white,pink,purple,orange,lightBlue
									,green, cyan  };
	return colorsList;
}



void Grid::SetMargins(int left, int top)
{
	leftMargin = left;
	topMargin = top;
}

