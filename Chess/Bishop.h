#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(std::pair<int, int> textureCoord, std::vector<std::vector<sf::RectangleShape>> board, std::pair<int, int> arrPosition, int x) : Piece(textureCoord, board, arrPosition)
	{
		value = 3;
		diagonalMovement = true;
		color = x;
	}

private:

};

