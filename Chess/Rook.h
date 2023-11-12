#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(std::pair<int, int> textureCoord, sf::RectangleShape square, std::pair<int, int> arrPosition, int x) : Piece(textureCoord, square, arrPosition)
	{
		value = 5;
		diagonalMovement = false;
		horsing = false;
		linearMovement = true;
		color = x;
	}

	char getID()
	{
		return id;
	}

private:
	
};

