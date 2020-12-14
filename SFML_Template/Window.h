#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "EventManager.h"

class Window
{
public:
	Window();
	Window(const std::string& l_title, const sf::Vector2u& size);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone();
	bool IsFullscreen();

	sf::Vector2u GetWindowSize();
	void ToggleFullscreen(EventDetails* l_details);
	void Draw(sf::Drawable& l_Drawable);
	sf::RenderWindow* GetRenderWindow();

	// event manager
	bool IsFocused();
	EventManager* GetEventManager();
	void Close(EventDetails* l_details=nullptr);
	

private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Create();

	// Variables
	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;

	// Event Manager
	EventManager m_eventManager;
	bool bIsFocused;

};