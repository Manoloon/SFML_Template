#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
	void ToggleFullscreen();
	void Draw(sf::Drawable& l_Drawable);
	sf::RenderWindow* GetRenderWindow();

private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Destroy();
	void Create();

	// Variables
	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;


};