#pragma once
#include "Piece.h"

class Rook : private Piece
{
public:
	Rook()
	{
		value = 5;
	}

	std::string getPieceTextureFile()
	{
		return pieceTextureFile;
	}

private:
	std::string pieceTextureFile = "";

};

