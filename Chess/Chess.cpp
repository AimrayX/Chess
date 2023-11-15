#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include "Game.h"

static const int VIEW_HEIGHT = 812;

std::vector<std::vector<sf::RectangleShape> > losition{ {},{ } };

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void render(sf::RenderWindow& window, sf::View view, std::vector<std::vector<sf::RectangleShape>> board, std::vector<Piece> pieces)
{
	window.clear();
	window.setView(view);
	
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			window.draw(board[i][j]);
		}
	}

	std::vector<Piece>::iterator col;
	for (col = pieces.begin(); col != pieces.end(); col++) {
		window.draw(col->piece);
	}
	window.display();
}

int main()
{
	//init Game
    sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_HEIGHT), "Chess", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(VIEW_HEIGHT/2, VIEW_HEIGHT/2), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	
	float squareSize = window.getSize().x / 8.0f;
	std::vector<std::vector<sf::RectangleShape>> board(8, std::vector<sf::RectangleShape>(8));

	sf::Color customColorB(118, 74, 152, 255);
	sf::Color customColorW(255, 250, 245, 255);
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			board[i][j].setSize(sf::Vector2f(squareSize, squareSize));
			board[i][j].setPosition(i * squareSize + squareSize / 2.0f, j * squareSize + squareSize / 2.0f);
			board[i][j].setOrigin(squareSize / 2.0f, squareSize / 2.0f);

			if ((i + j) % 2 == 0)
			{
				board[i][j].setFillColor(customColorW);
			}
			else
			{
				board[i][j].setFillColor(customColorB);
			}
		}
	}

	Game game(board);
	game.isDragging = false;



	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			case sf::Event::MouseButtonReleased:
				if (game.isDragging)
				{
					game.isDragging = false;
					game.setter = false;
					game.release(sf::Mouse::getPosition(window), board);
					break;
				}
			}
		}
		

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			game.move(sf::Mouse::getPosition(window), window);
		}
		
		render(window, view, board, game.getPieces());	

	}
    return 0;
}
