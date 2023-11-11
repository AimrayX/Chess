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

void render(sf::RenderWindow& window, sf::View view,sf::RectangleShape board, std::vector<std::vector<Piece>> currentPosition)
{
	window.setView(view);
	window.clear();
	window.draw(board);
	
	std::vector< std::vector<Piece> >::iterator row;
	std::vector<Piece>::iterator col;
	for (row = currentPosition.begin(); row != currentPosition.end(); row++) {
		for (col = row->begin(); col != row->end(); col++) {
			window.draw(col->piece);
		}
	}
	window.display();
}

int main()
{
	//init Game
    sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_HEIGHT), "Chess", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(VIEW_HEIGHT/2, VIEW_HEIGHT/2), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	
	sf::RectangleShape board(sf::Vector2f(static_cast<sf::Vector2i>(window.getSize())));
	board.setOrigin(0, 0);
	board.setPosition(0, 0);
	sf::Texture boardTexture;
	boardTexture.loadFromFile("chessBoard.png");
	board.setTexture(&boardTexture);


	Game game;
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
				game.isDragging = false;
				game.release(sf::Mouse::getPosition(window));
				break;
			}

		}
		

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			game.move(sf::Mouse::getPosition(window), window);
		}
		
		render(window, view, board, game.getCurrentPosition());	

	}
    return 0;
}
