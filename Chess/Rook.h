#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(std::pair<int, int> textureCoord, std::vector<std::vector<sf::RectangleShape>> board, std::pair<int, int> arrPosition, int x) : Piece(textureCoord, board, arrPosition)
	{
		value = 5;
		linearMovement = true;
		color = x;
	}

private:
	
};

