#pragma once
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>

#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"


//Information about the game
class Game
{
public:
	Game(std::vector<std::vector<sf::RectangleShape>> board)
		:rb1({4, 1}, board, {0,0}, 1), rb2({ 4, 1 }, board, { 7, 0 }, 1), rw1({ 4, 0 }, board, { 0,7 }, 0), rw2({4, 0}, board, { 7,7 }, 0), 
		bw1({ 2, 0 }, board, { 2,7 }, 0), bw2({ 2, 0 }, board, { 5,7 }, 0), bb1({ 2, 1 }, board, { 2,0 }, 1), bb2({ 2, 1 }, board, { 5,0 }, 1),
		qw({ 1, 0 }, board, { 3,7 }, 0), qb({ 1, 1 }, board, { 3,0 }, 1),
		kw({ 0, 0 }, board, { 4,7 }, 0), kb({ 0, 1 }, board, { 4,0 }, 1)
	{
		alivePieces = { kw, kb, rb1, rb2, rw1, rw2, bw1, bw2, bb1, bb2, qw, qb};
		gBoard = board;
	}

	~Game()
	{

	}
	 
	void diagonalSearch()
	{
		int y = activePiece->getArrayIndex().second;
		int x = activePiece->getArrayIndex().first;
		//diagonal down to the right search right
		for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++)
		{
			std::vector<Piece>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				sf::Vector2f hall = gBoard[i][j].getPosition();
				sf::Vector2f sall = it->getCurrentSquare().getPosition();
				if (gBoard[i][j].getPosition() == it->getCurrentSquare().getPosition())
				{
					std::cout << "something on square stopping :" << i << " " << j << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && it->color != activePiece->color)
			{
				result.push_back(gBoard[i][j]);
				break;
			}
			else if (pieceFound && it->color == activePiece->color)
			{
				break;
			}
			else if (!pieceFound)
			{
				result.push_back(gBoard[i][j]);
			}
		}
		//diagonal up to the right search right
		for (int i = x + 1, j = y - 1; i < 8 && j > -1; i++, j--)
		{
			std::vector<Piece>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				sf::Vector2f hall = gBoard[i][j].getPosition();
				sf::Vector2f sall = it->getCurrentSquare().getPosition();
				if (gBoard[i][j].getPosition() == it->getCurrentSquare().getPosition())
				{
					std::cout << "something on square stopping :" << i << " " << j << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && it->color != activePiece->color)
			{
				result.push_back(gBoard[i][j]);
				break;
			}
			else if (pieceFound && it->color == activePiece->color)
			{
				break;
			}
			else if (!pieceFound)
			{
				result.push_back(gBoard[i][j]);
			}
		}
		//diagonal up to the left search right
		for (int i = x - 1, j = y - 1; i > -1 && j > -1; i--, j--)
		{
			std::vector<Piece>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				sf::Vector2f hall = gBoard[i][j].getPosition();
				sf::Vector2f sall = it->getCurrentSquare().getPosition();
				if (gBoard[i][j].getPosition() == it->getCurrentSquare().getPosition())
				{
					std::cout << "something on square stopping :" << i << " " << j << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && it->color != activePiece->color)
			{
				result.push_back(gBoard[i][j]);
				break;
			}
			else if (pieceFound && it->color == activePiece->color)
			{
				break;
			}
			else if (!pieceFound)
			{
				result.push_back(gBoard[i][j]);
			}
		}
		//diagonal down to the left search right
		for (int i = x - 1, j = y + 1; i > -1 && j < 8; i--, j++)
		{
			std::vector<Piece>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				sf::Vector2f hall = gBoard[i][j].getPosition();
				sf::Vector2f sall = it->getCurrentSquare().getPosition();
				if (gBoard[i][j].getPosition() == it->getCurrentSquare().getPosition())
				{
					std::cout << "something on square stopping :" << i << " " << j << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && it->color != activePiece->color)
			{
				result.push_back(gBoard[i][j]);
				break;
			}
			else if (pieceFound && it->color == activePiece->color)
			{
				break;
			}
			else if (!pieceFound)
			{
				result.push_back(gBoard[i][j]);
			}
		}
	}


	void linearSearch()
	{
		int y = activePiece->getArrayIndex().second;
		int x = activePiece->getArrayIndex().first;
		//horizontal search right
		for (int i = x+1; i < 8; i++)
		{
			std::vector<Piece>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				sf::Vector2f hall = gBoard[i][y].getPosition();
				sf::Vector2f sall = it->getCurrentSquare().getPosition();
				if (gBoard[i][y].getPosition() == it->getCurrentSquare().getPosition())
				{
					std::cout << "something on square stopping :" << i << " " << y << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && it->color != activePiece->color)
			{
				result.push_back(gBoard[i][y]);
				break;
			}
			else if (pieceFound && it->color == activePiece->color)
			{
				break;
			}
			else if (!pieceFound)
			{
				result.push_back(gBoard[i][y]);
			}
		}
		//horizontal search left
		for (int i = x-1; i > -1; i--)
		{
			std::vector<Piece>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				sf::Vector2f hall = gBoard[i][y].getPosition();
				sf::Vector2f sall = it->getCurrentSquare().getPosition();
				if (gBoard[i][y].getPosition() == it->getCurrentSquare().getPosition())
				{
					std::cout << "something on square stopping :" << i << " " << y << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && it->color != activePiece->color)
			{
				result.push_back(gBoard[i][y]);
				break;
			}
			else if (pieceFound && it->color == activePiece->color)
			{
				break;
			}
			else if (!pieceFound)
			{
				result.push_back(gBoard[i][y]);
			}
		}
		//vertical search down
		for (int i = y+1; i < 8; i++)
		{
			std::vector<Piece>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end() && pieceFound == false; it++)
			{
				sf::Vector2f hall = gBoard[x][i].getPosition();
				sf::Vector2f sall = it->getCurrentSquare().getPosition();
				if (gBoard[x][i].getPosition() == it->getCurrentSquare().getPosition())
				{
					std::cout << "something on square " << x << " " << i << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && it->color != activePiece->color)
			{
				result.push_back(gBoard[x][i]);
				break;
			}
			else if (pieceFound && it->color == activePiece->color)
			{
				break;
			}
			else if (!pieceFound)
			{
				result.push_back(gBoard[x][i]);
			}
		}
		//vertical search up
		for (int i = y - 1; i > -1; i--)
		{
			std::vector<Piece>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end() && pieceFound == false; it++)
			{
				sf::Vector2f hall = gBoard[x][i].getPosition();
				sf::Vector2f sall = it->getCurrentSquare().getPosition();
				if (gBoard[x][i].getPosition() == it->getCurrentSquare().getPosition())
				{
					std::cout << "something on square " << x << " " << i << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && it->color != activePiece->color)
			{
				result.push_back(gBoard[x][i]);
				break;
			}
			else if (pieceFound && it->color == activePiece->color)
			{
				break;
			}
			else if (!pieceFound)
			{
				result.push_back(gBoard[x][i]);
			}
		}
	}

	void kingSearch() {
		int y = activePiece->getArrayIndex().second;
		int x = activePiece->getArrayIndex().first;
		//horizontal search right
		bool pieceFound = false;
		std::vector<Piece>::iterator it;
		for (it = alivePieces.begin(); it != alivePieces.end(); it++)
		{
			if (gBoard[x+1][y].getPosition() == it->getCurrentSquare().getPosition())
			{
				std::cout << "something on square stopping :" << x+1 << " " << y << std::endl;
				if (it->color != activePiece->color)
				{
					result.push_back(gBoard[x + 1][y]);
				}
				pieceFound = true;
				break;
			}
			
		}
		if (!pieceFound)
		{
			result.push_back(gBoard[x+1][y]);
		}
		pieceFound = false;
		for (it = alivePieces.begin(); it != alivePieces.end(); it++)
		{
			if (gBoard[x+1][y+1].getPosition() == it->getCurrentSquare().getPosition())
			{
				std::cout << "something on square stopping :" << x + 1 << " " << y << std::endl;
				if (it->color != activePiece->color)
				{
					result.push_back(gBoard[x + 1][y+1]);
				}
				pieceFound = true;
				break;
			}

		}
		if (!pieceFound)
		{
			result.push_back(gBoard[x + 1][y+1]);
		}
		pieceFound = false;
		for (it = alivePieces.begin(); it != alivePieces.end(); it++)
		{
			if (gBoard[x][y+1].getPosition() == it->getCurrentSquare().getPosition())
			{
				std::cout << "something on square stopping :" << x + 1 << " " << y << std::endl;
				if (it->color != activePiece->color)
				{
					result.push_back(gBoard[x][y+1]);
				}
				pieceFound = true;
				break;
			}

		}
		if (!pieceFound)
		{
			result.push_back(gBoard[x][y+1]);
		}
		pieceFound = false;
		for (it = alivePieces.begin(); it != alivePieces.end(); it++)
		{
			if (gBoard[x-1][y+1].getPosition() == it->getCurrentSquare().getPosition())
			{
				std::cout << "something on square stopping :" << x + 1 << " " << y << std::endl;
				if (it->color != activePiece->color)
				{
					result.push_back(gBoard[x - 1][y+1]);
				}
				pieceFound = true;
				break;
			}

		}
		if (!pieceFound)
		{
			result.push_back(gBoard[x - 1][y+1]);
		}
		pieceFound = false;
		for (it = alivePieces.begin(); it != alivePieces.end(); it++)
		{
			if (gBoard[x-1][y].getPosition() == it->getCurrentSquare().getPosition())
			{
				std::cout << "something on square stopping :" << x + 1 << " " << y << std::endl;
				if (it->color != activePiece->color)
				{
					result.push_back(gBoard[x-1][y]);
				}
				pieceFound = true;
				break;
			}

		}
		if (!pieceFound)
		{
			result.push_back(gBoard[x-1][y]);
		}
		pieceFound = false;
		for (it = alivePieces.begin(); it != alivePieces.end(); it++)
		{
			if (gBoard[x-1][y-1].getPosition() == it->getCurrentSquare().getPosition())
			{
				std::cout << "something on square stopping :" << x + 1 << " " << y << std::endl;
				if (it->color != activePiece->color)
				{
					result.push_back(gBoard[x-1][y-1]);
				}
				pieceFound = true;
				break;
			}

		}
		if (!pieceFound)
		{
			result.push_back(gBoard[x-1][y-1]);
		}
		pieceFound = false;
		for (it = alivePieces.begin(); it != alivePieces.end(); it++)
		{
			if (gBoard[x][y-1].getPosition() == it->getCurrentSquare().getPosition())
			{
				std::cout << "something on square stopping :" << x + 1 << " " << y << std::endl;
				if (it->color != activePiece->color)
				{
					result.push_back(gBoard[x][y-1]);
				}
				pieceFound = true;
				break;
			}

		}
		if (!pieceFound)
		{
			result.push_back(gBoard[x][y-1]);
		}
		pieceFound = false;
		for (it = alivePieces.begin(); it != alivePieces.end(); it++)
		{
			if (gBoard[x+1][y-1].getPosition() == it->getCurrentSquare().getPosition())
			{
				std::cout << "something on square stopping :" << x + 1 << " " << y << std::endl;
				if (it->color != activePiece->color)
				{
					result.push_back(gBoard[x+1][y-1]);
				}
				pieceFound = true;
				break;
			}

		}
		if (!pieceFound)
		{
			result.push_back(gBoard[x+1][y-1]);
		}
	}
	
	bool isLegalMove(sf::RectangleShape goal)
	{
		// check if that square is accessible by the type of activePiece
		// while it is doing the calculation in each direction on given attributes it should stop with further calculating in that direction
		// and if its not friendly include that square otherwise -1 in that direction
		bool finished = false;
		if (activePiece != alivePieces.end())
		{
			if (activePiece->diagonalMovement && activePiece->linearMovement)
			{
				result.clear();
				diagonalSearch();
				linearSearch();

			}
			else if (activePiece->diagonalMovement)
			{
				result.clear();
				diagonalSearch();
			}
			else if (activePiece->linearMovement)
			{
				result.clear();
				linearSearch();

			}
			else if (activePiece->isKing)
			{
				result.clear();
				kingSearch();
			}
			else if (activePiece->horsing)
			{
				result.clear();
			}
			else
			{
				result.clear();

			}
		}
		
		
		//compare input move and possible moves
		std::vector<sf::RectangleShape>::iterator it;
		contr = false;
		
		for (it = result.begin(); it != result.end(); it++)
		{
			
			std::vector<Piece>::iterator it2;
			for (it2 = alivePieces.begin(); it2 != alivePieces.end(); it2++)
			{
				if (it->getPosition() == goal.getPosition() && it2->getCurrentSquare().getPosition() == goal.getPosition())
				{
					pieceToBeTaken = it2;
					contr = true;
					return 1;
				}
				
			}
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
		std::vector<sf::RectangleShape>::iterator colR;
		std::vector<std::vector<sf::RectangleShape>>::iterator rowR;

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
				else if (contr && !initiateNewMove && colR->getGlobalBounds().contains(sf::Vector2f(mousePos)))
				{
					activePiece->piece.setPosition(colR->getPosition());
					activePiece->setCurrentSquare(*colR);
					activePiece->setArrayIndex(i, j);
					alivePieces.erase(pieceToBeTaken);
					initiateNewMove = true;
				}
				else if (!initiateNewMove && colR->getGlobalBounds().contains(sf::Vector2f(mousePos)))
				{
					activePiece->piece.setPosition(colR->getPosition());
					activePiece->setArrayIndex(i, j);
					activePiece->setCurrentSquare(*colR);
					initiateNewMove = true;

				}
			}
		}
		
	}

	void move(sf::Vector2i mousePos, const sf::RenderWindow& window)
	{
		std::vector<Piece>::iterator col;
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
	
	King kw;
	King kb;

	Rook rb1;
	Rook rb2;
	Rook rw1;
	Rook rw2;

	Bishop bw1;
	Bishop bw2;
	Bishop bb1;
	Bishop bb2;

	Queen qw;
	Queen qb;

	bool contr;
	bool isDragging;
	bool setter;
	std::vector<sf::RectangleShape> result;

private:
	std::vector<std::vector<sf::RectangleShape>> gBoard;
	std::vector<Piece>::iterator activePiece;
	std::vector<Piece> alivePieces;
	std::vector<Piece>::iterator pieceToBeTaken;
	float dx = 0.0f;
	float dy = 0.0f;
	float distance = 0.0f;
	float posX;
	float posY;
};