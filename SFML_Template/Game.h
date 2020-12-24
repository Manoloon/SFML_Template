#pragma once
#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"
#include "SharedContext.h"
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

	void LateUpdate();

	Window* GetWindow();

	void MoveSprite(EventDetails* l_details);

private:
	void RestartClock();

	Window m_window;
	sf::Clock m_clock;	
	TextBox m_textbox;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	StateManager m_stateManager;
	SharedContext m_context;
	sf::Time m_timeElapsed;
};

