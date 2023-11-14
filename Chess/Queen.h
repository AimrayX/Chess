#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(std::pair<int, int> textureCoord, std::vector<std::vector<sf::RectangleShape>> board, std::pair<int, int> arrPosition, int x) : Piece(textureCoord, board, arrPosition)
	{
		value = 9;
		diagonalMovement = true;
		linearMovement = true;
		color = x;
	}
};

