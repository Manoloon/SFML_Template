#include "State_Intro.h"
#include "StateManager.h"

void State_Intro::Continue(EventDetails* l_details)
{
	if(m_timePassed>=5.0f)
	{
		m_stateMgr->SwitchTo(StateType::MainMenu);
		m_stateMgr->Remove(StateType::Intro);
	}
}

void State_Intro::OnCreate()
{
	m_timePassed = 0.0f;

	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->GetSize();

	m_introTexture.loadFromFile("images/intro.png");
	m_IntroSprite.setTexture(m_introTexture);
	m_IntroSprite.setOrigin(m_introTexture.getSize().x / 2.0f, m_introTexture.getSize() / 2.0f);
	
	m_IntroSprite.setPosition(windowSize.x / 2.0f, 0.0f);

	m_font.loadFromFile("AtariSmall.ttf");
	m_text.setFont(m_font);
	m_text.setString({ "Press Space to Continue" });
	m_text.setCharacterSize(15);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	EventManager* m_eventMgr = m_stateMgr->GetContext()->m_eventManager;

	m_eventMgr->AddCallback(StateType::Intro, "Intro_Continue", &State_Intro::Continue, this);
	
}

void State_Intro::OnDestroy()
{
	EventManager* m_eventMgr = m_stateMgr->GetContext()->m_eventManager;
	m_eventMgr->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void State_Intro::Update(const sf::Time& l_time)
{
	if(m_timePassed < 5.0f)
	{
		m_timePassed += l_time.asSeconds();
		m_IntroSprite.setPosition(m_IntroSprite.getPosition().x, m_IntroSprite.getPosition().y + (48 * l_time.asSeconds()));
	}
}

void State_Intro::Draw()
{
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_window->GetRenderWindow();

	window->draw(m_IntroSprite);
	if (m_timePassed >= 5.0f) 
	{
		window->draw(m_text);
	}
}

void State_Intro::Activate()
{

}

void State_Intro::Deactivate()
{

}
