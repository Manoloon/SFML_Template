#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool AddBinding(Binding* l_binding);
	bool RemoveBinding(std::string l_name);

	void SetFocus(const bool& l_focus);

	// Template -> necesita ser declarado en el header.
	template<class T>
	bool AddCallback(const std::string& l_name,
					void(T::*l_func) (EventDetails*),
					T* l_instance)
	{
		auto temp = std::bind(l_func, l_instance, std::placeholders::_1);
		return m_callbacks.emplace(l_name, temp).second;
	}
	void RemoveCallback(const std::string& l_name)
	{
		m_callbacks.erase(l_name);
	}

	void HandleEvent(sf::Event& l_event);
	void Update();

	sf::Vector2i GetMousePos(sf::RenderWindow* l_window = nullptr)
	{
		return (l_window ? sf::Mouse::getPosition(*l_window) : sf::Mouse::getPosition());			
	}


private:
	void LoadBindings();
	Bindings m_bindings;
	Callbacks m_callbacks;
	bool m_bHasFocus;
};

