#pragma once
#include "Window.h"
#include "EventManager.h"

enum class StateType
{
	Intro = 1, MainMenu, Game, Paused, GameOver, Credits
};


struct SharedContext {
	SharedContext() :m_window(nullptr), m_eventManager(nullptr) {}
	Window* m_window;
	EventManager* m_eventManager;
};

class BaseState
{
	friend class StateManager;

public:
	BaseState(StateManager* l_stateManager) :m_stateManager(l_stateManager), m_transparent(false),m_transcendent(false){}
	virtual ~BaseState() {}

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void Activate() = 0;
	virtual void Deactivate() = 0;

	virtual void Update(const sf::Time& l_time) = 0;
	virtual void Draw() = 0;
};

