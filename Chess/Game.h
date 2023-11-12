#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Rook.h"
#include "Piece.h"
#include <cmath>
#include <unordered_map>

//Information about the game
class Game
{
public:
	Game(std::vector<std::vector<sf::RectangleShape>> board)
		:rw1({3, 1}, board[0][0], {0,0}, 0), rw2({1, 0}, board[4][4], { 4,4 }, 0)
	{
		alivePieces = { rw1, rw2 };
		gBoard = board;
	}

	~Game()
	{

	}
	 
	void linearSearch()
	{
		//go over these squares on by one an check the above conditions
		int y = activePiece->getArrayIndex().second;
		int x = activePiece->getArrayIndex().first;
		result.clear();
		//horizontal search
		for (int i = 0; i < 8; i++)
		{
			if (i == x)
			{
				continue;
			}
			//check all pieces and see if one has the current square we are looking at

			std::vector<Piece>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{

				sf::Vector2f hall = gBoard[i][y].getPosition();
				sf::Vector2f sall = it->getCurrentSquare().getPosition();
				if (gBoard[i][y].getPosition() == it->getCurrentSquare().getPosition())
				{
					std::cout << "enemy on square " << i << " " << y << std::endl;
					pieceFound = true;
					continue;
				}

			}
			if (!pieceFound)
			{
				result.push_back(gBoard[i][y]);
			}
		}
		//vertical search
		for (int i = 0; i < 8; i++)
		{
			if (i == y)
			{
				continue;
			}
			//check all pieces and see if one has the current square we are looking at
			std::vector<Piece>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end() && pieceFound == false; it++)
			{


				sf::Vector2f hall = gBoard[x][i].getPosition();
				sf::Vector2f sall = it->getCurrentSquare().getPosition();
				if (gBoard[x][i].getPosition() == it->getCurrentSquare().getPosition())
				{
					std::cout << "enemy on square " << i << " " << y << std::endl;
					pieceFound = true;
					continue;
				}

			}
			if (!pieceFound)
			{
				result.push_back(gBoard[x][i]);
			}

		}
	}
	
	bool isLegalMove(sf::RectangleShape goal)
	{
		// check if that square is accessible by the type of activePiece
		
		// maybe make a couple of attributes that are called can move vertical and so on

		// code a switch statment which calculates all possible squares depending on those attributes
		// while it is doing the calculation in each direction on given attributes it should stop with further calculating in that direction
		// and if its not friendly include that square otherwise -1 in that direction
		// but before that check if the piece has the attribute: "Jumping=true" in that case calculate further
		bool finished = false;
		
		if (activePiece->diagonalMovement && activePiece->linearMovement)
		{
			
		}
		else if (activePiece->diagonalMovement)
		{

		}
		else if (activePiece->linearMovement)
		{
			//gives free spaces in a linear fashion until the edge of the board
			linearSearch();
			
		}
		else if (activePiece->horsing)
		{

		}
		
		//compare input move and possible moves
		std::vector<sf::RectangleShape>::iterator it;
		for (it = result.begin(); it != result.end(); it++)
		{
			if (it->getPosition() == goal.getPosition()) 
			{
				return 1;
			}
		}
		return 0;
	}
	
	void release(sf::Vector2i mousePos, std::vector<std::vector<sf::RectangleShape>> board)
	{
		bool initiateNewMove = false;
		int i=0;
		for (rowR = board.begin(); rowR != board.end() && !isDragging && !initiateNewMove; rowR++, i++)
		{
			int j=0;
			for (colR = rowR->begin(); colR != rowR->end() && !isDragging && !initiateNewMove; colR++, j++)
			{
				if (colR->getGlobalBounds().contains(sf::Vector2f(mousePos)) && !isLegalMove(*colR))
				{
					activePiece->piece.setPosition(posX, posY);
					initiateNewMove = true;
				}
				else if (colR->getGlobalBounds().contains(sf::Vector2f(mousePos)) && isLegalMove(*colR))
				{
					activePiece->piece.setPosition(colR->getPosition());
					activePiece->setArrayIndex(i, j);
				}
			}
		}
	}

	void move(sf::Vector2i mousePos, const sf::RenderWindow& window)
	{
		for (col = alivePieces.begin(); col != alivePieces.end() && !isDragging; col++)
		{
			float dx = col->piece.getPosition().x - mousePos.x;
			float dy = col->piece.getPosition().y - mousePos.y;
			float distance = std::sqrt(dx * dx + dy * dy);

			if (col->piece.getGlobalBounds().contains(sf::Vector2f(mousePos)) && distance < 45.0f)
			{
				activePiece = col;
				isDragging = true;
				break;
			}
		}

		if (col != alivePieces.end())
		{
			if (!setter)
			{
				posX = activePiece->piece.getPosition().x;
				posY = activePiece->piece.getPosition().y;
				std::cout << "pos : " << posX << " " << posY << std::endl;
				setter = true;
			}
			activePiece->piece.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
		}
	}

	std::vector<Piece> getPieces()
	{
		return alivePieces;
	}

	void setCurrentPosition(short row, short col)
	{
		//Take FEN string and convert it to the position

		//currentPosition[row][col] = rw1.Piece::generatePiece();
	}
	
	Rook rw1;
	Rook rw2;

	bool isDragging;
	bool setter;
	std::vector<sf::RectangleShape> result;

private:
	std::vector<std::vector<sf::RectangleShape>> gBoard;

	std::vector<Piece>::iterator activePiece;
	std::vector<Piece> alivePieces;
	std::vector<Piece>::iterator col;
	std::vector<sf::RectangleShape>::iterator colR;
	std::vector<std::vector<sf::RectangleShape>>::iterator rowR;

	float dx = 0.0f;
	float dy = 0.0f;
	float distance = 0.0f;
	float posX;
	float posY;
};