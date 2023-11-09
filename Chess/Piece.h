#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Piece
{
public:
	Piece()
	{

	}
	~Piece()
	{

	}

	short value = 0;

	void Draw(sf::RenderWindow window);

	long long checkLegalMoves()
	{
		//check for legal moves
		long long legalMoves = 0b00001;

		return legalMoves;
	}
	
	void move()
	{
		
	}

	
	
	sf::RectangleShape generatePiece()
	{
		/*
		Piece Identifiers
		K = 0
		Q = 1
		R1 = 2
		R2 = 3
		B1 = 4
		B2 = 5
		N1 = 6
		N2 = 7
		P1 = 8
		P2 = 9
		P3 = 10
		P4 = 11
		P5 = 12
		P6 = 13
		P7 = 14
		P8 = 15

		k = 16
		q = 17
		r1 = 18
		r2 = 19
		b1 = 20
		b1 = 21
		n2 = 22
		n2 = 23
		p1 = 24
		p2 = 25
		p3 = 26
		p4 = 27
		p5 = 28
		p6 = 29
		p7 = 30
		p8 = 31
		*/
		

		switch (id)
		{
		case 0:
			positionX = 0;
			positionY = 0;
		case 1:
			positionX = 0;
			positionY = 0;
		case 2:
			positionX = 710.5;
			positionY = 710.5;
			x = 5;
			y = 1;
		case 3:
			positionX = 101.5;
			positionY = 101.5;
		case 4:
		case 5:
			positionX = 0;
			positionY = 0;
		case 6:
		case 7:
			positionX = 0;
			positionY = 0;
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:		
		case 14:
		case 15:
			positionX = 0;
			positionY = 0;
		case 16:
			positionX = 0;
			positionY = 0;
		case 17:
			positionX = 0;
			positionY = 0;
		case 18:
		case 19:
			positionX = 0;
			positionY = 0;
			x = 5;
			y = 2;
		case 20:
		case 21:
			positionX = 0;
			positionY = 0;
		case 22:
		case 23:
			positionX = 0;
			positionY = 0;
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
			positionX = 0;
			positionY = 0;
		}

		sf::RectangleShape piece(sf::Vector2f(100, 100));
		sf::Texture piecesTexture;
		piece.setOrigin(originX, originY);
		piece.setPosition(positionX, positionY);
		piecesTexture.loadFromFile("pieces.png");
		
		sf::Vector2u textureSize = piecesTexture.getSize();
		textureSize.x /= 6;
		textureSize.y /= 2;
		piece.setTextureRect(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
		return piece;
	}
	char id;
private:
	sf::RectangleShape body;
	
	float originX = 256;
	float originY = 256;
	float positionX = 0;
	float positionY = 0;
	short x = 0;
	short y = 0;
	
};

