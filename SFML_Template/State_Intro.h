#pragma once
#include "BaseState.h"
class State_Intro :
    public BaseState
{
public:
    void Continue(EventDetails* l_details);

    virtual void OnCreate() override;
    virtual void OnDestroy() override;
    virtual void Update(const sf::Time& l_time) override;
    virtual void Draw() override;
    virtual void Activate() override;
    virtual void Deactivate() override;

private:
    sf::Texture m_introTexture;
    sf::Sprite m_IntroSprite;
    sf::Text m_text;
    sf::Font m_font;
    float m_timePassed;
 

};

