#include "Game.h"

int main(int argc,char** argv[])
{
	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}

		Window.clear();
		Window.draw(shape);
		Window.display();
	}

	return 0;
}