#include "StateManager.h"

StateManager::StateManager(SharedContext* l_shared) : m_shared(l_shared)
{
	RegisterState(State_Intro)(StateType::Intro);
	RegisterState(State_MainMenu)(StateType::MainMenu);
	RegisterState(State_Paused)(StateType::Paused);
	RegisterState(State_Game)(StateType::Game);
}

StateManager::~StateManager()
{
	for(auto &itr :m_States)
	{
		itr.second->OnDestroy();
		delete itr->second;
	}
}

void StateManager::Update(const sf::Time& l_time)
{
	if (m_States.empty()) { return; }

	if(m_States.back()->second->IsTransparent() && m_States.size() > 1)
	{
		auto itr = m_States.end();
		while(itr != m_States.begin())
		{
			if(itr != m_States.end())
			{
				if(!itr->second->IsTransparent())
				{
					break;
				}
			}
			--itr;
		}
		for (; itr != m_States.end(); itr++)ç
		{
		itr->second->Update(l_time);
		}
	}
	else
	{
		m_States.back().second->Update(l_time);
	}
}

void StateManager::Draw()
{
	if(m_States.empty()){return;}

	if(m_States.back().second->IsTransparent() && m_States.size() >1)
	{
		auto itr = m_States.end();
		while(itr != m_States.begin())
		{
			if(itr != m_States.end())
			{
				if(!itr->second->IsTransparent())
				{
				break;
				}
			}
			--itr;
		}
		for(;itr!=m_States.end();++itr)
		{
			itr->second->Draw();
		}
	} 
	else 
	{
	m_States.back().second->Draw();
	}
}

void StateManager::ProcessRequest()
{
	while(m_toRemove.begin()) != m_toRemove.end())
	{
	RemoveState(*m_toRemove.begin());
	m_toRemove.erase(m_toRemove.begin());
	}
}

SharedContext* StateManager::GetContext()
{

	void StateManager::Remove(const StateType & l_type)
	{
		m_toRemove.push_back(l_type);
	}

	bool StateManager::HasState(const StateType & l_type)
	{
	for(auto itr = m_States.begin();itr !=m_States.end();++itr)
		{
			if(itr->first == l_type)
			{
				auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), l_type);
				if (removed == m_toRemove.end()) { return; }
				return false;
			}
		}
	return false;
	}
}

void StateManager::SwitchTo(const StateType& l_type)
{
	m_shared->m_eventManager->SetCurrentState(l_type);
	for(auto itr = m_States.begin();itr != m_States.end();++itr)
	{
		if(itr->first == l_type)
		{
			m_States.back().second->Deactivate();
			StateType tmp_type = itr->first;
			BaseState* tmp_state = itr->second;
			m_States.erase(itr);
			m_States.emplace_back(tmp_type, tmp_state);
			tmp_state->Activate();
			return;
		}
	}
	if(!m_States.empty())
	{
		m_States.back().second->Deactivate();
	}
	CreateState(l_type);
	m_States.back().second->Activate();
}

void StateManager::CreateState(const StateType& l_type)
{
	auto newstate = m_stateFactory.find(l_type);
	if (newstate == m_stateFactory.end()) { return; }
	BaseState* state = newstate->second();
	m_States.emplace_back(l_type, state);
	state->OnCreate();
}

void StateManager::RemoveState(const StateType& l_type)
{
	for(auto itr = m_States.begin();itr != m_States.end();++itr)
	{
		if(itr->first() == l_type)
		{
			itr->second->OnDestroy();
			delete itr->second;
			m_States.erase(itr);
			return;
		}
	}
}
