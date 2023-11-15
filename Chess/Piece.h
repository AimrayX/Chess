#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Piece
{
public:
	Piece(std::pair<int, int> textureCoord, std::vector<std::vector<sf::RectangleShape>> board, std::pair<int, int> arrPosition)
	{
		arrayIndex = arrPosition;
		currentSquare = board[arrPosition.first][arrPosition.second];
		piece.setSize(sf::Vector2f(115.0f, 115.0f));
		piece.setOrigin(piece.getSize().x / 2, piece.getSize().y / 2);
		piece.setPosition(currentSquare.getPosition());
		piecesTexture.loadFromFile("pieces.png");
		piece.setTexture(&piecesTexture);
		sf::Vector2u textureSize = piecesTexture.getSize();
		textureSize.x /= 6;
		textureSize.y /= 2;
		piece.setTextureRect(sf::IntRect(textureSize.x * textureCoord.first, textureSize.y * textureCoord.second, textureSize.x, textureSize.y));
	}
	~Piece()
	{

	}

	sf::RectangleShape getCurrentSquare()
	{
		return currentSquare;
	}

	void setCurrentSquare(sf::RectangleShape square) {
		currentSquare = square;
	}

	std::pair<int, int> getArrayIndex()
	{
		return arrayIndex;
	}

	void setArrayIndex(int xIndex, int yIndex)
	{
		arrayIndex = { xIndex, yIndex };
	}

	char id = 0;
	sf::RectangleShape piece;
	short value;
	bool diagonalMovement = false;
	bool linearMovement = false;
	bool horsing = false;
	bool isKing = false;
	int color;
	std::vector<sf::RectangleShape> emptySquares;
	std::vector<sf::RectangleShape> takingSquares;

private:
	float squareSize = 812.0f / 8;
	sf::Texture piecesTexture;
	std::vector<std::pair<float, float>> legalMoves;
	std::pair<int, int> arrayIndex;
	sf::RectangleShape currentSquare;
	
	
};

