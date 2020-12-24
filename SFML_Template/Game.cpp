#include "Game.h"

Game::Game() : m_window("Sfml Template",sf::Vector2u(800,600)),m_stateManager(&m_context)
{
	m_clock.restart();
	srand(time(nullptr));
// 	m_texture.loadFromFile("Images/Nes_Items.png");
// 	m_sprite.setTexture(m_texture);
// 	m_sprite.setOrigin(m_texture.getSize().x / 2.0f, m_texture.getSize().y / 2.0f);
// 	m_sprite.setPosition(0, 0);
// 	m_window.GetEventManager()->AddCallback("Move", &Game::MoveSprite, this);

	m_context.m_window = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game(){}

void Game::Update()
{
	m_window.Update();
	m_stateManager.Update(m_timeElapsed);
}

void Game::Render()
{
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.GetRenderWindow()->draw(m_sprite);
	m_window.EndDraw();
}

sf::Time Game::GetTimeElapsed()
{
	return m_clock.getElapsedTime();
}

void Game::RestartClock()
{
	m_clock.restart();
}

void Game::LateUpdate()
{
	m_stateManager.ProcessRequest();
	RestartClock();
}

Window* Game::GetWindow()
{
	return &m_window;
}

 void Game::MoveSprite(EventDetails* l_details)
 {
 	sf::Vector2i mousePos = m_window.GetEventManager()->GetMousePos(m_window.GetRenderWindow());
 	m_sprite.setPosition(mousePos.x, mousePos.y);
 	std::cout << "moving sprite to: " << mousePos.x << ":" << mousePos.y << std::endl;
 }
