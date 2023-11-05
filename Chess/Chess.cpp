#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

static const float VIEW_HEIGHT = 512;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void render(sf::RenderWindow window, sf::RectangleShape board, std::vector<std::vector<sf::RectangleShape>> pos)
{
	window.clear();
	window.draw(board);
	std::vector< std::vector<sf::RectangleShape> >::iterator row;
	std::vector<sf::RectangleShape>::iterator col;
	for (row = pos.begin(); row != pos.end(); row++) {
		for (col = row->begin(); col != row->end(); col++) {
			window.draw(col);
		}
	}
	
	window.display();
}

int main()
{
	//init Game
    sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_HEIGHT), "Chess", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	
	sf::RectangleShape board(sf::Vector2f(static_cast<sf::Vector2i>(window.getSize())));
	board.setOrigin(512/2, 512/2);
	board.setPosition(0, 0);
	sf::Texture boardTexture;
	boardTexture.loadFromFile("chessBoard.jpg");
	board.setTexture(&boardTexture);

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
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//get piece and position

			//drag it
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			//player.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
		}

		//render
		window.setView(view);
		render();
		

	}
    return 0;
}
