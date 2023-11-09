#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Rook.h"
#include "Piece.h"

//Information about the game
class Game
{
public:
	Game()
		:rw1(2), rw2(3)
	{
		std::vector<std::vector<sf::RectangleShape> > currentPosition
		{ 
			{rw1.Piece::generatePiece(), rw2.Piece::generatePiece()},
			{}, 
			{}, 
			{}, 
			{}, 
			{}, 
			{},
			{}
		};
		
	}

	~Game()
	{

	}


	std::vector<std::vector<sf::RectangleShape>> getCurrentPosition()
	{
		return currentPosition;
	}

	void setPosition(short row, short col)
	{
		//Take FEN string and convert it to the position

		currentPosition[row][col] = rw1.Piece::generatePiece();
	}

	

private:
	Rook rw1;
	Rook rw2;
	std::vector<std::vector<sf::RectangleShape>> currentPosition;

};