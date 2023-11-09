#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook()
	{

	}

	Rook(char idIn)
	{
		id = idIn;
		pieceTextureFile = "rook/" + std::to_string(static_cast<short>(id));
		generatePiece();
	}

	char getID()
	{
		return id;
	}

	std::string getPieceTextureFile()
	{

		return pieceTextureFile;
	}

private:
	std::string pieceTextureFile = "rook/"+id;
	int value = 5;
};

