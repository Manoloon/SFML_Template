#pragma once
#include "Window.h"
#include "EventManager.h"
#include "Textbox.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();
	void Update();
	void Render();
	sf::Time GetTimeElapsed();
	void RestartClock();

	Window* GetWindow();

	void MoveSprite(EventDetails* l_details);

private:

	Window m_window;
	sf::Clock m_clock;	
	TextBox m_textbox;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};

