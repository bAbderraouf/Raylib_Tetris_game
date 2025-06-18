#pragma once

#include "Game.h"
#include "Grid.h"
#include "Piece.h"
#include "raylib.h"
#include "Position.h"
#include <ctime>
#include <string>


class Tetris : public Game
{
public :
	Tetris(int w, int h, int fps, int nRows, int nCols, int cSize);
	~Tetris();

	//----------------------
	// principal functions
	//----------------------
	void Init();  // setup()
	void Input();
	void Update(); // logic
	void Draw();	// render

	//----------------------
	// additional functions
	//----------------------
	void setGameFPS(int fps);
	Piece* getRandomPiece(void);
	void movePiece(Position step);
	void RotatePiece();
	bool checkBoundaries(Position newPos);
	bool checkColision(Piece& nextPieceState);
	void ErasePieceFromGrid(Piece & piece, Grid & grid);
	int DeleteFullLines(Grid & grid);
	int GetIndexOfFirstNotEmptyLine(Grid &grid);
	bool CheckIfLineIsFull(Grid& grid, int lineIndex);
	bool PieceArrived();
	double GetDeltaTime();
	void RestartGame();
	void DrawText();
	Music GetGameMusic();
	void InitGameSounds();
	
private:
	Grid *grid, *nextPieceGrid;
	Piece *piece , *nextPiece;

	//window
	int windowWidth, windowHeigh;
	int gameFps; 

	//grid
	int numRows;
	int numCols;
	int cellSize;


	// game
	int score;
	std::string strScoreTitle, strScoreValue;
	Font font;
	Music gameMusic;
	Sound gameOverSound, rotateSound, deleteLineSound;

	//piece
	int rotStat;
	bool flag_moveLeft,
		flag_moveRight,
		flag_moveDown,
		flag_rotate,
		flag_pieceArrived,
		flag_gameOver;


};