#pragma once

#include <iostream>
#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Piece.h"
#include "Position.h"
#include <chrono>
#include <thread>

class Grid
{
public:
	Grid(int nRows, int nCols, int cSize);
	void Initialize();
	void AddPieceToGrid(Piece& const piece);
	void EreasePieceFromGrid(Piece& const piece);
	void PrintValues();
	void Draw();
	void DrawOneCell(int x, int y, int w, int h, Color color);
	int getNumRows();
	int getNumCols();
	void SetMargins(int left, int top);
	int grid[20][10]; // 20 rows and 10 collumns

private:
	int numRows;  // columns number
	int numCols;
	int cellSize;

	// draw margins
	int leftMargin,
		topMargin;
	
	std::vector<Color> cellColorsList; // the list of different colors
	std::vector<Color> getCellColorsList(); // init the list of colors

};