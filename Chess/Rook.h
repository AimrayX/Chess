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
		generatePiece();
	}

	char getID()
	{
		return id;
	}

private:
	int value = 5;
};

