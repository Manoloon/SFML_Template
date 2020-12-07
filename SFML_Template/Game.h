#pragma once
#include "Window.h"
#include "Textbox.h"

class Game
{
public:
	Game();
	~Game();
	void Update();
	void Render();
	float GetTimeElapsed();
	void RestartClock();

	Window* GetWindow();

private:

	Window m_window;
	sf::Clock m_clock;
	float m_timeElapsed;
	TextBox m_textbox;
};

