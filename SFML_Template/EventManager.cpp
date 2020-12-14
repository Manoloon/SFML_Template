#include "EventManager.h"

EventManager::EventManager() : m_bHasFocus(true) { LoadBindings(); }

EventManager::~EventManager()
{
	for (auto &itr : m_bindings)
	{
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::AddBinding(Binding* l_binding)
{
	if(m_bindings.find(l_binding->m_name) != m_bindings.end())
	{
		return false;
	}
	return m_bindings.emplace(l_binding->m_name, l_binding).second;
}

bool EventManager::RemoveBinding(std::string l_name)
{
	auto itr = m_bindings.find(l_name);
	if (itr == m_bindings.end()) { return false; }
	
	delete itr->second;
	m_bindings.erase(itr);
	return true;
}

void EventManager::SetFocus(const bool& l_focus)
{
	m_bHasFocus = l_focus;
}

void EventManager::HandleEvent(sf::Event& l_event)
{
	// handling SFML events
	for(auto &b_itr : m_bindings)
	{
		Binding* bind = b_itr.second;
		for (auto &e_itr : bind->m_events)
		{
			EventType sfmlEvent = (EventType)l_event.type;
			if(e_itr.first != sfmlEvent){continue; }
			if(sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
			{
				if (e_itr.second.m_code == l_event.mouseButton.button)
				{
					bind->m_details.m_mouse.x = l_event.mouseButton.x;
					bind->m_details.m_mouse.y = l_event.mouseButton.y;

					if (bind->m_details.m_keyCode != 1)
					{
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
			} 
			else 
			{
				if (sfmlEvent == EventType::MouseWheel)
				{
					bind->m_details.m_mouseWheelDelta = l_event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized)
				{
					bind->m_details.m_size.x = l_event.size.width;
					bind->m_details.m_size.y = l_event.size.height;
				}
				else if(sfmlEvent == EventType::TextEntered) 
				{
					bind->m_details.m_textEntered = l_event.text.unicode;
				}
				++(bind->c);
			}
		}
	}
}

void EventManager::Update()
{
	if (!m_bHasFocus) { return; }
	for(auto &b_itr : m_bindings)
	{
	
		Binding* bind = b_itr.second;
		for(auto &e_itr : bind->m_events)
		{
			switch(e_itr.first)
			{
			case(EventType::Keyboard):
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code)))
				{
					if(bind->m_details.m_keyCode != -1)
					{
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
				}
			break;
			case(EventType::Mouse):
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code)))
				{
					if(bind->m_details.m_keyCode !=-1)
					{
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
				}
			break;
			case (EventType::Joystick): 
				// a expandir
			break;
			}
		}

		if(bind->m_events.size() == bind->c)
		{
			auto callItr = m_callbacks.find(bind->m_name);
			if(callItr != m_callbacks.end())
			{
				callItr->second(&bind->m_details);
			}
		}
		bind->c = 0;
		bind->m_details.Clear();
	}
}

void EventManager::LoadBindings()
{
	std::string delimiter = ":";
	std::ifstream bindings;
	
	bindings.open("inputs.cfg");
	if(!bindings.is_open())
	{
		std::cout << "Failed to open inputs.cfg" << std::endl;
		return;
	}
	std::string line;
	while(std::getline(bindings,line))
	{
		std::stringstream keyStream(line);
		std::string callbackName;
		keyStream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while(!keyStream.eof())
		{
			std::string keyVal;
			keyStream >> keyVal;
			int start = 0;
			int end = keyVal.find(delimiter);
			if (end == std::string::npos)
			{
				delete bind;
				bind = nullptr;
				break;
			}
			EventType type = EventType(stoi(keyVal.substr(start, end - start)));
			int code = stoi(keyVal.substr(end + delimiter.length(),
				keyVal.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo.m_code = code;
			bind->BindEvent(type, eventInfo);
		}
		if (!AddBinding(bind)) { delete bind; }
		bind = nullptr;
	}
	bindings.close();
}

