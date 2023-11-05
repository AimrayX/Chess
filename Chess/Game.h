#pragma once
#include <string>
#include <vector>


class Game
{
public:
	Game();
	~Game();

	std::vector<std::vector<int>> getCurrentPosition()
	{
		
		return currentPosition;
	}

	void updatePosition(std::vector<std::vector<int>> pos)
	{
		
		currentPosition = pos;
	}

private:

	std::vector<std::vector<int>> currentPosition;

};