#pragma once
#include <SFML/Graphics.hpp>


using MessageContainer = std::vector<std::string>;

class TextBox
{
public:
	// tiene 2 constructores.
	TextBox();
	TextBox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);

	~TextBox();

	void Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
	void Add(std::string l_message);
	void ClearText();

	void Render(sf::RenderWindow& l_window);

private:
	MessageContainer m_messages;
	int m_numVisible;

	sf::RectangleShape m_backdrop;
	sf::Font m_font;
	sf::Text m_content;
};
