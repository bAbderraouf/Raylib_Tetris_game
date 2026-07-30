#include "Tetris.h"


Tetris::Tetris(int w, int h, int fps, int nRows, int nCols, int cSize)
{
	// game window
	windowWidth = w;
	windowHeigh = h;
	gameFps = fps;

	//grid
	numRows = nRows;
	numCols = nCols;
	cellSize = cSize;

	// init widow + grid + piece
	Init();
}

Tetris::~Tetris()
{
	delete piece;
	delete grid;
	UnloadFont(font);
	//audio
	CloseAudioDevice();
	//music 
	UnloadMusicStream(gameMusic);
	//sounds
	UnloadSound(rotateSound);
	UnloadSound(deleteLineSound);
	UnloadSound(gameOverSound);
}

void Tetris::Init()
{
	// Game window
	InitWindow(windowWidth, windowHeigh, "Raouf's Tetris");
	setGameFPS(gameFps);	// frames per second

	//grid
	grid = new Grid(numRows, numCols, cellSize);
	grid->SetMargins(140, 10);

	nextPieceGrid = new Grid(4, 4, 20);
	nextPieceGrid->SetMargins(25, 50);

	//current piece 
	piece = getRandomPiece();
	rotStat = piece->getRotationState();
	
	//next piece
	nextPiece = getRandomPiece();
	nextPiece->setPosition(Position(1,1));
	nextPieceGrid->AddPieceToGrid(*nextPiece);

	//game
	font = LoadFont("assets/fonts/TechnoRaceItalic-eZRWe.otf");
	if (font.texture.id == 0) {
		std::cout << "Font failed to load!" << std::endl;
	}
	score = 0;

	// init audio 
	InitGameSounds();
	

	//flags
	flag_moveLeft = false;
	flag_moveRight = false;
	flag_moveDown = false;
	flag_rotate = false;
	flag_pieceArrived = false;
	flag_gameOver = false;
}

void Tetris::Input()
{
	int keyPressed = GetKeyPressed();

	// rotation requested
	if (keyPressed == KEY_R)
		flag_rotate = true;
		
	//move right
	if (keyPressed == KEY_RIGHT)
		flag_moveRight = true;

	//move left
	if (keyPressed ==KEY_LEFT)
		flag_moveLeft = true;

	//move down quickly
	if (IsKeyDown(KEY_DOWN))
		flag_moveDown = true;

	
	// restart the game after gameOver "pres N"
	if (flag_gameOver && keyPressed == KEY_N)
	{
		flag_gameOver = false;
		RestartGame();
	}
}

void Tetris::Update()
{
	
		Position stepRight(1, 0), stepLeft(-1, 0), 
				stepDown(0, 1), stepDownSpeed(0, 2);

		//-------------
		// postDraw
		//-------------
		
		if(flag_pieceArrived)
		{
			flag_pieceArrived = false;

			if (flag_gameOver == false)
			{
				score += 2;

				// create next piece
				delete piece;
				piece = NULL;
				piece = nextPiece->Clone();
				piece->setPosition(Position(4, 0));

				//next piece update
				ErasePieceFromGrid(*nextPiece, *nextPieceGrid);
				nextPiece = getRandomPiece();
				nextPiece->setPosition(Position(1,1));

				//check if game is over
				if (checkColision(*piece))
				{
					flag_gameOver = true;
					// pause music
					StopMusicStream(gameMusic);
					// play sound
					PlaySound(gameOverSound);
				}
			}
			
		}
		else
		{
			ErasePieceFromGrid(*piece, *grid);
			movePiece(stepDown);
			
		}
		
		//-------------------
		// check input cases
		//-------------------

		if (flag_rotate)
		{
			flag_rotate = false;
			RotatePiece();
		}
		if (flag_moveLeft)
		{
			flag_moveLeft = false;
			movePiece(stepLeft);
		}
		if (flag_moveRight)
		{
			flag_moveRight = false;
			movePiece(stepRight);
		}
		if (flag_moveDown)
		{
			flag_moveDown = false;
			movePiece(stepDownSpeed);
		}
		//-------------------------------------
		// Delete full lines from the grid
		//-------------------------------------

		int numLineDeleted = DeleteFullLines(*grid);
		score += 100 * numLineDeleted;

		//-----------------------
		// check if piece arrived
		//------------------------
		if (PieceArrived())
			flag_pieceArrived = true;

		//--------------
		// fill grid
		//--------------
		grid->AddPieceToGrid(*piece);
		nextPieceGrid->AddPieceToGrid(*nextPiece);
}

void Tetris::Draw()
{
	grid->Draw();
	nextPieceGrid->Draw();
	DrawText();
}

void Tetris::setGameFPS(int fps)
{
	gameFps = fps;
	SetTargetFPS(gameFps);
}

Piece* Tetris::getRandomPiece(void)
{
	// rand
	std::srand(std::time(nullptr));
	int randomIndex = rand() % 6;

	switch (randomIndex)
	{
	case 0: return new L_piece();
	case 1: return new I_piece();
	case 2: return new Z_piece();
	case 3: return new S_piece();
	case 4: return new O_piece();
	case 5: return new T_piece();
	default: return nullptr;
	}

}

void Tetris::movePiece(Position step)
{
	if (flag_gameOver == false)
	{
		Position oldPos = piece->getPosition();
	
		// new state
		Position newPos(oldPos.col + step.col, oldPos.row + step.row);
		Piece* nextPieceState = piece->Clone();
		nextPieceState->setPosition(newPos);

		if( !checkColision(*nextPieceState)  && !checkBoundaries(newPos))
			piece->setPosition(newPos);
	}

}

void Tetris::RotatePiece()
{
	if (flag_gameOver == false)
	{
		if (piece->id == 5) // piece O (1state)
			return;

		rotStat++;
		if (rotStat == 5)
			rotStat = 1;

		Piece* nextPieceState = piece->Clone();
		nextPieceState->setRotationState(rotStat);
		Position newPos = nextPieceState->getPosition();

		if (!checkColision(*nextPieceState) && !checkBoundaries(newPos))
		{
			//rotate the piece
			piece->setRotationState(rotStat);
			// play sound
			PlaySound(rotateSound);
		}
	}
}

bool Tetris::checkBoundaries(Position newPos)
{
	// return true if colision exist
	bool cond1 = ((newPos.row + piece->getDownBound() + 1) > grid->getNumRows());
	bool cond2 = (newPos.row < 0);
	bool cond3 = ((newPos.col + piece->getRigtBound() + 1) > grid->getNumCols());
	bool cond4 = (newPos.col + piece->getLeftBound() < 0);

	if ( cond1 || cond2 || cond3 || cond4)
		return true;
	else
		return false;

}

bool Tetris::checkColision(Piece &nextPieceState)
{
	// return true if colision exist

	Position pos = nextPieceState.getPosition();

	for (int row = 0; row < nextPieceState.getSize(); row++) //rows
	{
		for (int col = 0; col < nextPieceState.getSize(); col++) // columns
		{
			if (row + pos.row < numRows && col + pos.col < numCols)
			{
				int gridRow = row + pos.row,
					gridCol = col + pos.col;
				int gridValue = grid->grid[gridRow][gridCol];
				int pieceValue = nextPieceState.block[row][col];

				if (gridValue != 0 && pieceValue != 0)
					return true;
			}
				
		}
	}
	return false;
}

void Tetris::ErasePieceFromGrid(Piece& piece, Grid& grid)
{
	grid.EreasePieceFromGrid(piece);
}

int Tetris::DeleteFullLines(Grid& grid)
{
	int numberOfLinesDeleted = 0;
	int indexLinetoDelete = 0;
	int indexFirstLineNotEmpty = GetIndexOfFirstNotEmptyLine(grid);

	if (indexFirstLineNotEmpty != -1)
	{
	// calculate indexLineToDelete

		for (int row = 0; row < numRows; row++) // each line
		{
			if (CheckIfLineIsFull(grid , row))
			{
				indexLinetoDelete = row;
				std::this_thread::sleep_for(std::chrono::milliseconds(750));
				numberOfLinesDeleted++;
				// play sound
				PlaySound(deleteLineSound);

				// delete the line 
				if (indexLinetoDelete != 0) // game over case
				{
					for (int row = indexLinetoDelete; row >= indexFirstLineNotEmpty; row--) // each line
					{
						for (int col = 0; col < numCols; col++)
						{
							int upperValue = grid.grid[row - 1][col];
							grid.grid[row][col] = upperValue;
						}
					}
				}
			}
		}
	}

	return numberOfLinesDeleted;

}

int Tetris::GetIndexOfFirstNotEmptyLine(Grid &grid)
{
	/* return the index of the 1st not empty line if exists
	*  return -1 otherwise
	*/

	for (int row = 0; row < numRows; row++) // each line
	{
		for (int col = 0; col < numCols; col++)
		{
			if (grid.grid[row][col] != 0)
				return row;
		}
	}
	return -1;
}

bool Tetris::CheckIfLineIsFull(Grid& grid, int lineIndex)
{
	for (int col = 0; col < numCols; col++)
	{
		if (grid.grid[lineIndex][col] == 0)
			return false;
	}
	return true;
}

bool Tetris::PieceArrived()
{
	Position oldPos = piece->getPosition(),
			 stepDown(0, 1);

	// new state
	Position newPos(oldPos.col + stepDown.col, oldPos.row + stepDown.row);
	Piece* nextPieceState = piece->Clone();
	nextPieceState->setPosition(newPos);

	if (checkBoundaries(newPos) || checkColision(*nextPieceState))
		return true;
	return false;
}

double Tetris::GetDeltaTime()
{
	static time_t precedent = time(nullptr);
	time_t now = time(nullptr);

	double deltaTime = now - precedent;
	return deltaTime;
}

void Tetris::RestartGame()
{
	//set grid to empty
	grid->Initialize();

	//play game music
	PlayMusicStream(gameMusic);
}

void Tetris::DrawText()
{
	//	DrawTextEx(	font, text, position, fontSize, spacing, color);

	DrawTextEx(font, "Score :", { 30, 165 }, 25, 1, WHITE);
	DrawTextEx(font, " Next piece ", { 15, 15 }, 25, 1, WHITE);
	std::string scre = std::to_string(score);
	DrawTextEx(font, scre.c_str(), { 30, 190 }, 25, 1, WHITE);
	DrawTextEx(font, "Press [R] to rotate", { 7, 540 }, 14, 1, WHITE);
	DrawTextEx(font, "Press [N] to restart", { 7, 560 }, 14, 1, WHITE);
	DrawTextEx(font, "Press [Arows] to move", { 7, 580 }, 14, 1, WHITE);

	if (flag_gameOver)
	{
		DrawTextEx(font, "Game Over", { 20, 300 }, 29, 1, WHITE);
		DrawTextEx(font, "Press [N]", { 30, 350 }, 22, 1, WHITE);
		DrawTextEx(font, "to restart", { 30, 390 }, 20, 1, WHITE);
	}
}

Music Tetris::GetGameMusic()
{
	return gameMusic;
}

void Tetris::InitGameSounds()
{
	// raylib init audio
	InitAudioDevice();
	
	// music
	gameMusic = LoadMusicStream("assets/sounds/music-for-game-fun-kid-game-163649.ogg");
	if (gameMusic.stream.buffer == nullptr) {
		TraceLog(LOG_ERROR, "Failed to load music!");
	}
	else {
		PlayMusicStream(gameMusic);
	}
	//-------
	//sounds
	rotateSound = LoadSound("assets/sounds/turnpage-99756.wav");

	if (rotateSound.stream.buffer == nullptr)
	{
		std::cout << "Erreur : le son a échoué à se charger." << std::endl;
	}

	//-------
	deleteLineSound = LoadSound("assets/sounds/success-340660.wav");

	if (deleteLineSound.stream.buffer == nullptr)
	{
		std::cout << "Erreur : le son a échoué à se charger." << std::endl;
	}

	//-------
	gameOverSound = LoadSound("assets/sounds/8-bit-game-over-sound-effect-331435.wav");

	if (gameOverSound.stream.buffer == nullptr)
	{
		std::cout << "Erreur : le son a échoué à se charger." << std::endl;
	}
}
