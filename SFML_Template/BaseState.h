#pragma once
#include "Window.h"
#include <SFML/Graphics.hpp>
#include "EventManager.h"

class BaseState
{
	friend class StateManager;

public:
	BaseState(StateManager* l_stateManager) :m_stateMgr(l_stateManager), m_transparent(false),m_transcendent(false){}
	virtual ~BaseState() {}

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void Activate() = 0;
	virtual void Deactivate() = 0;

	virtual void Update(const sf::Time& l_time) = 0;
	virtual void Draw() = 0;

protected:
	StateManager* m_stateMgr;
	bool m_transparent;
	bool m_transcendent;
};

