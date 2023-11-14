#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King(std::pair<int, int> textureCoord, std::vector<std::vector<sf::RectangleShape>> board, std::pair<int, int> arrPosition, int x) : Piece(textureCoord, board, arrPosition)
	{
		value = 10;
		isKing = true;
		color = x;
	}
	
};

