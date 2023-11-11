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
		currentPosition = 
		{ 
			{rw1, rw2},
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

	
	void release(sf::Vector2i mousePos)
	{
		if (shortest < 50.0f && !isDragging)
		{
			float snapToPositionX = 0.0f;
			float snapToPositionY = 0.0f;

			float closest = 10000.0f;
			for (int i = 1; i < 9; i++) {
				dx = (possiblePosition * i - 812/16) - mousePos.x;
				for (int j = 1; j < 9; j++) {
					dy = (possiblePosition * j- 812 / 16) - mousePos.y;
					distance = std::sqrt(dx * dx + dy * dy);
					if (closest > distance)
					{
						closest = distance;
						snapToPositionX = possiblePosition * i - 812 / 16;
						snapToPositionY = possiblePosition * j - 812 / 16;
					}
				}
			}

			closestPiece->piece.setPosition(static_cast<float>(snapToPositionX), static_cast<float>(snapToPositionY));

		}
	}

	void move(sf::Vector2i mousePos, const sf::RenderWindow& window)
	{
		if (!isDragging)
		{
			shortest = 100000.0f;
		}
		for (row = currentPosition.begin(); row != currentPosition.end() && shortest != 0 && !isDragging; row++) {
			for (col = row->begin(); col != row->end() && shortest != 0; col++) {
				dx = col->piece.getPosition().x - mousePos.x;
				dy = col->piece.getPosition().y - mousePos.y;
				distance = std::sqrt(dx * dx + dy * dy);
				if (shortest > distance)
				{
					shortest = distance;
					closestPiece = col;
					
				}
			}
			isDragging = true;
		}

		
		if(shortest < 50.0f)
			closestPiece->piece.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

		
		
		//setPosition();
	}

	std::vector<std::vector<Piece>> getCurrentPosition()
	{
		return currentPosition;
	}

	void setCurrentPosition(short row, short col)
	{
		//Take FEN string and convert it to the position

		//currentPosition[row][col] = rw1.Piece::generatePiece();
	}

	Rook rw1;
	Rook rw2;
	bool isDragging;

private:
	//std::vector<Piece>::iterator col;
	
	std::vector<Piece>::iterator closestPiece;
	std::vector<std::vector<Piece>> currentPosition;
	std::vector< std::vector<Piece> >::iterator row;
	std::vector<Piece>::iterator col;
	bool released = true;
	float dx = 0.0f;
	float dy = 0.0f;
	float distance = 0.0f;
	float shortest = 100000.0f;
	float possiblePosition = 812.0f/8;
	
};