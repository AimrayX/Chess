#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Piece
{
public:
	Piece();
	~Piece();

	short value = 0;

	void Draw(sf::RenderWindow window);

	long long checkLegalMoves()
	{
		//check for legal moves
		long long legalMoves = 0b00001;

		return legalMoves;
	}
	
	sf::RectangleShape generatePiece(std::string pieceTextureFile)
	{

		sf::RectangleShape piece(sf::Vector2f(100, 100));
		sf::Texture pieceTexture;
		piece.setOrigin(512 / 2, 512 / 2);
		piece.setPosition(0, 0);
		pieceTexture.loadFromFile(pieceTextureFile);
		piece.setTexture(&pieceTexture);
		return piece;
	}


private:
	sf::RectangleShape body;
	
};

