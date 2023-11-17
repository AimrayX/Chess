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
		alivePieces = { &rb1, &rb2, &rw1, &rw2, &bw1, &bw2, &bb1, &bb2, &qw, &qb, &kw, &kb };
		gBoard = board;
		updateLegalMoves();
	}

	~Game()
	{

	}
	 
	void diagonalSearch()
	{
		int y = (*activePiece)->getArrayIndex().second;
		int x = (*activePiece)->getArrayIndex().first;
		//diagonal down to the right search right
		for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++)
		{
			std::vector<Piece*>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[i][j].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					std::cout << "something on square stopping :" << i << " " << j << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && (*it)->color != (*activePiece)->color)
			{
				takingResult.push_back(gBoard[i][j]);
				break;
			}
			else if (pieceFound && (*it)->color == (*activePiece)->color)
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
			std::vector<Piece*>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[i][j].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					std::cout << "something on square stopping :" << i << " " << j << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && (*it)->color != (*activePiece)->color)
			{
				takingResult.push_back(gBoard[i][j]);
				break;
			}
			else if (pieceFound && (*it)->color == (*activePiece)->color)
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
			std::vector<Piece*>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[i][j].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					std::cout << "something on square stopping :" << i << " " << j << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && (*it)->color != (*activePiece)->color)
			{
				takingResult.push_back(gBoard[i][j]);
				break;
			}
			else if (pieceFound && (*it)->color == (*activePiece)->color)
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
			std::vector<Piece*>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[i][j].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					std::cout << "something on square stopping :" << i << " " << j << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && (*it)->color != (*activePiece)->color)
			{
				takingResult.push_back(gBoard[i][j]);
				break;
			}
			else if (pieceFound && (*it)->color == (*activePiece)->color)
			{
				break;
			}
			else if (!pieceFound)
			{
				result.push_back(gBoard[i][j]);
			}
		}
		(*activePiece)->emptySquares = result;
		(*activePiece)->takingSquares = takingResult;
		if ((*activePiece)->color == 0)
		{
			attackedSquaresByWhite.insert(attackedSquaresByWhite.end(), takingResult.begin(), takingResult.end());
			attackedSquaresByWhite.insert(attackedSquaresByWhite.end(), result.begin(), result.end());
		}
		else if ((*activePiece)->color == 1)
		{
			attackedSquaresByBlack.insert(attackedSquaresByBlack.end(), takingResult.begin(), takingResult.end());
			attackedSquaresByBlack.insert(attackedSquaresByBlack.end(), result.begin(), result.end());
		}
	}

	void linearSearch()
	{
		int y = (*activePiece)->getArrayIndex().second;
		int x = (*activePiece)->getArrayIndex().first;
		//horizontal search right
		for (int i = x+1; i < 8; i++)
		{
			std::vector<Piece*>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[i][y].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					std::cout << "something on square stopping :" << i << " " << y << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && (*it)->color != (*activePiece)->color)
			{
				takingResult.push_back(gBoard[i][y]);
				break;
			}
			else if (pieceFound && (*it)->color == (*activePiece)->color)
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
			std::vector<Piece*>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[i][y].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					std::cout << "something on square stopping :" << i << " " << y << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && (*it)->color != (*activePiece)->color)
			{
				takingResult.push_back(gBoard[i][y]);
				break;
			}
			else if (pieceFound && (*it)->color == (*activePiece)->color)
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
			std::vector<Piece*>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end() && pieceFound == false; it++)
			{
				if (gBoard[x][i].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					std::cout << "something on square " << x << " " << i << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && (*it)->color != (*activePiece)->color)
			{
				takingResult.push_back(gBoard[x][i]);
				break;
			}
			else if (pieceFound && (*it)->color == (*activePiece)->color)
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
			std::vector<Piece*>::iterator it;
			bool pieceFound = false;
			for (it = alivePieces.begin(); it != alivePieces.end() && pieceFound == false; it++)
			{
				if (gBoard[x][i].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					std::cout << "something on square " << x << " " << i << std::endl;
					pieceFound = true;
					break;
				}
			}
			if (pieceFound && (*it)->color != (*activePiece)->color)
			{
				takingResult.push_back(gBoard[x][i]);
				break;
			}
			else if (pieceFound && (*it)->color == (*activePiece)->color)
			{
				break;
			}
			else if (!pieceFound)
			{
				result.push_back(gBoard[x][i]);
			}
		}
		(*activePiece)->emptySquares = result;
		(*activePiece)->takingSquares = takingResult;
		if ((*activePiece)->color == 0)
		{
			attackedSquaresByWhite.insert(attackedSquaresByWhite.end(), takingResult.begin(), takingResult.end());
			attackedSquaresByWhite.insert(attackedSquaresByWhite.end(), result.begin(), result.end());
		}
		else if ((*activePiece)->color == 1)
		{
			attackedSquaresByBlack.insert(attackedSquaresByBlack.end(), takingResult.begin(), takingResult.end());
			attackedSquaresByBlack.insert(attackedSquaresByBlack.end(), result.begin(), result.end());
		}
	}

	void kingSearch() {
		int y = (*activePiece)->getArrayIndex().second;
		int x = (*activePiece)->getArrayIndex().first;
		//horizontal search right
		
		std::vector<sf::RectangleShape>::iterator itR;
		std::vector<Piece*>::iterator it;
		bool skip = false;

		switch ((*activePiece)->color)
		{
		case 0:
			
			for (itR = attackedSquaresByBlack.begin(); x + 1 < 8 && itR != attackedSquaresByBlack.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x + 1][y].getPosition())
				{
					skip = true;
				}
			}
			break;

		case 1:
			for (itR = attackedSquaresByWhite.begin(); x + 1 < 8 && itR != attackedSquaresByWhite.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x + 1][y].getPosition())
				{
					skip = true;
				}
			}
			break;
		}
		
		bool pieceFound = false;
		if (x + 1 < 8 && !skip)
		{
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[x + 1][y].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					if ((*it)->color != (*activePiece)->color)
					{
						takingResult.push_back(gBoard[x + 1][y]);
					}
					pieceFound = true;
					break;
				}

			}
			if (!pieceFound)
			{
				result.push_back(gBoard[x + 1][y]);
			}
		}
		skip = false;
		switch ((*activePiece)->color)
		{
		case 0:

			for (itR = attackedSquaresByBlack.begin(); x + 1 < 8 && y + 1 < 8 && itR != attackedSquaresByBlack.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x + 1][y + 1].getPosition())
				{
					skip = true;
				}
			}
			break;

		case 1:
			for (itR = attackedSquaresByWhite.begin(); x + 1 < 8 && y + 1 < 8 && itR != attackedSquaresByWhite.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x + 1][y + 1].getPosition())
				{
					skip = true;
				}
			}
			break;
		}
		pieceFound = false;
		if (x + 1 < 8 && y + 1 < 8 && !skip)
		{
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[x + 1][y + 1].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					if ((*it)->color != (*activePiece)->color)
					{
						takingResult.push_back(gBoard[x + 1][y + 1]);
					}
					pieceFound = true;
					break;
				}

			}
			if (!pieceFound)
			{
				result.push_back(gBoard[x + 1][y + 1]);
			}
		}
		skip = false;
		switch ((*activePiece)->color)
		{
		case 0:

			for (itR = attackedSquaresByBlack.begin(); y + 1 < 8 && itR != attackedSquaresByBlack.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x][y + 1].getPosition())
				{
					skip = true;
				}
			}
			break;

		case 1:
			for (itR = attackedSquaresByWhite.begin(); y + 1 < 8 && itR != attackedSquaresByWhite.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x][y + 1].getPosition())
				{
					skip = true;
				}
			}
			break;
		}
		pieceFound = false;
		if (y + 1 < 8 && !skip)
		{
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[x][y + 1].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					if ((*it)->color != (*activePiece)->color)
					{
						takingResult.push_back(gBoard[x][y + 1]);
					}
					pieceFound = true;
					break;
				}

			}
			if (!pieceFound)
			{
				result.push_back(gBoard[x][y + 1]);
			}
		}
		skip = false;
		switch ((*activePiece)->color)
		{
		case 0:

			for (itR = attackedSquaresByBlack.begin(); x - 1 > -1 && y + 1 < 8 && itR != attackedSquaresByBlack.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x - 1][y + 1].getPosition())
				{
					skip = true;
				}
			}
			break;

		case 1:
			for (itR = attackedSquaresByWhite.begin(); x - 1 > -1 && y + 1 < 8 && itR != attackedSquaresByWhite.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x - 1][y + 1].getPosition())
				{
					skip = true;
				}
			}
			break;
		}
		pieceFound = false;
		if (x - 1 > -1 && y + 1 < 8 && !skip)
		{
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[x - 1][y + 1].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					if ((*it)->color != (*activePiece)->color)
					{
						takingResult.push_back(gBoard[x - 1][y + 1]);
					}
					pieceFound = true;
					break;
				}

			}
			if (!pieceFound)
			{
				result.push_back(gBoard[x - 1][y + 1]);
			}
		}
		skip = false;
		switch ((*activePiece)->color)
		{
		case 0:

			for (itR = attackedSquaresByBlack.begin(); x - 1 > -1 && itR != attackedSquaresByBlack.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x - 1][y].getPosition())
				{
					skip = true;
				}
			}
			break;

		case 1:
			for (itR = attackedSquaresByWhite.begin(); x - 1 > -1 && itR != attackedSquaresByWhite.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x - 1][y].getPosition())
				{
					skip = true;
				}
			}
			break;
		}
		pieceFound = false;
		if (x - 1 > -1 && !skip)
		{
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[x - 1][y].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					if ((*it)->color != (*activePiece)->color)
					{
						takingResult.push_back(gBoard[x - 1][y]);
					}
					pieceFound = true;
					break;
				}

			}
			if (!pieceFound)
			{
				result.push_back(gBoard[x - 1][y]);
			}
		}
		skip = false;
		switch ((*activePiece)->color) {
		case 0:

			for (itR = attackedSquaresByBlack.begin(); x - 1 > -1 && y - 1 > -1 && itR != attackedSquaresByBlack.end(); itR++) {
				if (itR->getPosition() == gBoard[x - 1][y - 1].getPosition()) {
					skip = true;
				}
			}
			break;

		case 1:
			for (itR = attackedSquaresByWhite.begin(); x - 1 > -1 && y - 1 > -1 && itR != attackedSquaresByWhite.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x - 1][y - 1].getPosition())
				{
					skip = true;
				}
			}
			break;
		}
		pieceFound = false;
		if (x - 1 > -1 && y - 1 > -1 && !skip)
		{
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[x - 1][y - 1].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					if ((*it)->color != (*activePiece)->color)
					{
						takingResult.push_back(gBoard[x - 1][y - 1]);
					}
					pieceFound = true;
					break;
				}

			}
			if (!pieceFound)
			{
				result.push_back(gBoard[x - 1][y - 1]);
			}
		}
		skip = false;
		switch ((*activePiece)->color)
		{
		case 0:

			for (itR = attackedSquaresByBlack.begin(); y - 1 > -1 && itR != attackedSquaresByBlack.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x][y - 1].getPosition())
				{
					skip = true;
				}
			}
			break;

		case 1:
			for (itR = attackedSquaresByWhite.begin(); y - 1 > -1 && itR != attackedSquaresByWhite.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x][y - 1].getPosition())
				{
					skip = true;
				}
			}
			break;
		}
		pieceFound = false;
		if (y - 1 > -1 && !skip)
		{
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[x][y - 1].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					if ((*it)->color != (*activePiece)->color)
					{
						takingResult.push_back(gBoard[x][y - 1]);
					}
					pieceFound = true;
					break;
				}

			}
			if (!pieceFound)
			{
				result.push_back(gBoard[x][y - 1]);
			}
		}
		skip = false;
		switch ((*activePiece)->color)
		{
		case 0:

			for (itR = attackedSquaresByBlack.begin(); x + 1 < 8 && y - 1 > -1 && itR != attackedSquaresByBlack.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x + 1][y - 1].getPosition())
				{
					skip = true;
				}
			}
			break;

		case 1:
			for (itR = attackedSquaresByWhite.begin(); x + 1 < 8 && y - 1 > -1 && itR != attackedSquaresByWhite.end(); itR++)
			{
				if (itR->getPosition() == gBoard[x + 1][y - 1].getPosition())
				{
					skip = true;
				}
			}
			break;
		}
		pieceFound = false;
		if (x + 1 < 8 && y - 1 > -1 && !skip)
		{
			for (it = alivePieces.begin(); it != alivePieces.end(); it++)
			{
				if (gBoard[x + 1][y - 1].getPosition() == (*it)->getCurrentSquare().getPosition())
				{
					if ((*it)->color != (*activePiece)->color)
					{
						takingResult.push_back(gBoard[x + 1][y - 1]);
					}
					pieceFound = true;
					break;
				}

			}
			if (!pieceFound)
			{
				result.push_back(gBoard[x + 1][y - 1]);
			}
		}
		if ((*activePiece)->color == 0)
		{
			attackedSquaresByWhite.insert(attackedSquaresByWhite.end(), takingResult.begin(), takingResult.end());
			attackedSquaresByWhite.insert(attackedSquaresByWhite.end(), result.begin(), result.end());
		}
		else if ((*activePiece)->color == 1)
		{
			attackedSquaresByBlack.insert(attackedSquaresByBlack.end(), takingResult.begin(), takingResult.end());
			attackedSquaresByBlack.insert(attackedSquaresByBlack.end(), result.begin(), result.end());
		}
		
	}
	
	void updateLegalMoves()
	{
		bool avoidKingSearch = false;
		attackedSquaresByBlack.clear();
		attackedSquaresByWhite.clear();
		for (activePiece = alivePieces.begin(); activePiece != alivePieces.end(); activePiece++)
		{
			result.clear();
			takingResult.clear();
			if ((*activePiece)->diagonalMovement && (*activePiece)->linearMovement)
			{
				diagonalSearch();
				linearSearch();
			}
			else if ((*activePiece)->diagonalMovement)
			{
				diagonalSearch();
			}
			else if ((*activePiece)->linearMovement)
			{
				linearSearch();
			}
			else if ((*activePiece)->isKing && !avoidKingSearch)
			{
				kingSearch();
			}
			else if ((*activePiece)->horsing)
			{

			}
			else
			{

			}
			(*activePiece)->emptySquares = result;
			(*activePiece)->takingSquares = takingResult;
		}
		//check if the king has any emptysquares to go to and if yes than check if that position would be attacked if he moved there
		std::vector<Piece*>::iterator it4;
		for (it4 = alivePieces.begin(); it4 != alivePieces.end(); it4++)
		{
			std::cout << "Piece empty Squares:" << std::endl;
			std::vector<sf::RectangleShape>::iterator it5;
			for (it5 = (*it4)->emptySquares.begin(); it5 != (*it4)->emptySquares.end(); it5++)
			{
				std::cout << it5->getPosition().x << " " << it5->getPosition().y << std::endl;
			}
			
		}
		std::cout << "King white empty Squares:" << std::endl;
		std::vector<sf::RectangleShape>::iterator it5;
		for (it5 = kw.emptySquares.begin(); it5 != kw.emptySquares.end(); it5++)
		{
			std::cout << it5->getPosition().x << " " << it5->getPosition().y << std::endl;
		}
		std::cout << "King black empty Squares:" << std::endl;
		for (it5 = kb.emptySquares.begin(); it5 != kb.emptySquares.end(); it5++)
		{
			std::cout << it5->getPosition().x << " " << it5->getPosition().y << std::endl;
		}
		if (kw.emptySquares.size() == 0) {
			std::cout << "check mate!" << std::endl;
			exit;
		}
		if (kw.emptySquares.size() == 1)
		{
			avoidKingSearch = true;
			sf::RectangleShape tempCurrentSquare = kw.getCurrentSquare();
			std::pair<int, int> tempArrayIndex = kw.getArrayIndex();

			kw.piece.setPosition(kw.emptySquares[0].getPosition());
			kw.setCurrentSquare(kw.emptySquares[0]);
			kw.setArrayIndex(std::floor((kw.emptySquares[0].getPosition().x/100)), std::floor((kw.emptySquares[0].getPosition().y/100)));
			updateLegalMoves();
			std::vector<sf::RectangleShape>::iterator it3;
			for (it3 = attackedSquaresByBlack.begin(); it3 != attackedSquaresByBlack.end(); it3++)
			{
				if (kw.emptySquares[0].getPosition() == it3->getPosition())
				{
					std::cout << "check mate!" << std::endl;
					exit;
				}
			}
			kw.piece.setPosition(tempCurrentSquare.getPosition());
			kw.setCurrentSquare(tempCurrentSquare);
			kw.setArrayIndex(tempArrayIndex.first, tempArrayIndex.second);	
		}
		if (kb.emptySquares.size() == 1)
		{
			avoidKingSearch = true;
			avoidKingSearch = true;
			sf::RectangleShape tempCurrentSquare = kw.getCurrentSquare();
			std::pair<int, int> tempArrayIndex = kw.getArrayIndex();

			kb.piece.setPosition(kb.emptySquares[0].getPosition());
			kb.setCurrentSquare(kb.emptySquares[0]);
			kb.setArrayIndex((std::floor(kb.emptySquares[0].getPosition().x/100)), std::floor((kb.emptySquares[0].getPosition().y/100)));
			updateLegalMoves();
			std::vector<sf::RectangleShape>::iterator it3;
			for (it3 = attackedSquaresByWhite.begin(); it3 != attackedSquaresByWhite.end(); it3++)
			{
				if (kb.emptySquares[0].getPosition() == it3->getPosition())
				{
					std::cout << "check mate!" << std::endl;
					exit;
				}
			}
			kw.piece.setPosition(tempCurrentSquare.getPosition());
			kw.setCurrentSquare(tempCurrentSquare);
			kw.setArrayIndex(tempArrayIndex.first, tempArrayIndex.second);
		}
	}

	bool isLegalMove(sf::RectangleShape goal)
	{
		//compare input move and possible moves
		//compare if after the king has moved to escape a check the new square he moved to is not being attacked by the attacking piece again
		std::vector<sf::RectangleShape>::iterator it;
		contr = false;
		for (it = (*activePiece)->emptySquares.begin(); it != (*activePiece)->emptySquares.end(); it++)
		{
			if (it->getPosition() == goal.getPosition())
			{
				
				return 1;
			}
		}
		for (it = (*activePiece)->takingSquares.begin(); it != (*activePiece)->takingSquares.end(); it++) {
			if (it->getPosition() == goal.getPosition()) {
				std::vector<Piece*>::iterator it2;
				for (it2 = alivePieces.begin(); it2 != alivePieces.end(); it2++) {
					if ((*it2)->getCurrentSquare().getPosition() == goal.getPosition()) {
						pieceToBeTaken = it2;
						contr = true;
						return 1;
					}
				}
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
					(*activePiece)->piece.setPosition(posX, posY);
					initiateNewMove = true;
				}
				else if (contr && !initiateNewMove && colR->getGlobalBounds().contains(sf::Vector2f(mousePos)) && isLegalMove(*colR))
				{
					(*activePiece)->piece.setPosition(colR->getPosition());
					(*activePiece)->setCurrentSquare(*colR);
					(*activePiece)->setArrayIndex(i, j);
					alivePieces.erase(pieceToBeTaken);
					initiateNewMove = true;
				}
				else if (!initiateNewMove && colR->getGlobalBounds().contains(sf::Vector2f(mousePos)) && isLegalMove(*colR))
				{
					(*activePiece)->piece.setPosition(colR->getPosition());
					(*activePiece)->setArrayIndex(i, j);
					(*activePiece)->setCurrentSquare(*colR);
					initiateNewMove = true;

				}
			}
		}
		updateLegalMoves();
	}

	void move(sf::Vector2i mousePos, const sf::RenderWindow& window)
	{
		std::vector<Piece*>::iterator col;
		for (col = alivePieces.begin(); col != alivePieces.end() && !isDragging; col++)
		{
			float dx = (*col)->piece.getPosition().x - mousePos.x;
			float dy = (*col)->piece.getPosition().y - mousePos.y;
			float distance = std::sqrt(dx * dx + dy * dy);

			if ((*col)->piece.getGlobalBounds().contains(sf::Vector2f(mousePos)) && distance < 45.0f)
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
				posX = (*activePiece)->piece.getPosition().x;
				posY = (*activePiece)->piece.getPosition().y;
				std::cout << "pos : " << posX << " " << posY << std::endl;
				setter = true;
			}
			(*activePiece)->piece.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
		}
	}

	std::vector<Piece> getPieces()
	{
		std::vector<Piece> renderActivePieces;
		for (Piece* piecePtr : alivePieces) {
			renderActivePieces.push_back(*piecePtr);
		}
		return renderActivePieces;
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
	std::vector<sf::RectangleShape> takingResult;

private:
	std::vector<std::vector<sf::RectangleShape>> gBoard;
	std::vector<sf::RectangleShape> attackedSquaresByWhite;
	std::vector<sf::RectangleShape> attackedSquaresByBlack;

	std::vector<std::vector<sf::RectangleShape>> freeSquares;

	std::vector<Piece*>::iterator activePiece;
	std::vector<Piece*> alivePieces;
	std::vector<Piece*>::iterator pieceToBeTaken;

	float posX;
	float posY;
};