#include "Animation.h"

Animation::Animation(sf::RenderWindow * window, sf::Texture &t, int column, int line, int width, int height, float speed, int count, sf::Vector2f position)
{
	this->m_window = window;
    this->m_speed = speed;
    this->m_Frame = 0;

    for (int i = 0; i < count; i++)
        this->m_Frames.push_back(sf::IntRect(column + width*i, line, width, height));
    this->m_sprite.setTexture(t);
    this->m_sprite.setScale(0.4, 0.4);
    this->m_sprite.setOrigin(width / 2, height / 2);
    this->m_sprite.setPosition(position.x, position.y);
    this->m_sprite.setTextureRect(this->m_Frames[0]);
}

void Animation::update()
{
	this->m_Frame += this->m_speed;
    int n = this->m_Frames.size();
    if (this->m_Frame > n)
        this->m_Frame -= n;
    this->m_sprite.setTextureRect(this->m_Frames[int(this->m_Frame)]);
    //std::cout << int(this->m_Frame) << "\n";
}

void Animation::draw()
{
	this->m_window->draw(this->m_sprite);
}

bool Animation::checkEnd()
{
    return this->m_Frame + this->m_speed >= this->m_Frames.size();
}

void Animation::setPosition(sf::Vector2f position)
{
    this->m_sprite.setPosition(position.x, position.y);
}