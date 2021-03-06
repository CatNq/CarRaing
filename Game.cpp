#include "Game.h"

Game::Game(sf::RenderWindow* window) : m_score(10)
{
    this->m_window = window;

    this->m_player = new Player(this->m_window);

    this->m_texture_threat_1.loadFromFile("Assets/Texture/Car_1.png");
    this->m_texture_threat_1.setSmooth(true);

    this->m_texture_threat_2.loadFromFile("Assets/Texture/Car_2.png");
    this->m_texture_threat_2.setSmooth(true);

    this->m_texture_threat_3.loadFromFile("Assets/Texture/Car_3.png");
    this->m_texture_threat_3.setSmooth(true);



    this->m_texture_road.loadFromFile("Assets/Texture/Road.png");
    this->m_texture_road.setSmooth(true);
    this->m_sprite_road.setTexture(this->m_texture_road);

    this->m_threat.push_back(Threat(this->m_window, this->m_texture_threat_1));

    this->m_font.loadFromFile("Assets/Font/MarkerFelt.ttf");
    this->m_text.setFont(this->m_font);
    this->m_text.setString("Score: ");
    this->m_text.setCharacterSize(15);
    this->m_text.setPosition(200, 0);
}

Game::~Game()
{
    delete this->m_player;
}


bool Game::update()
{
    this->m_player->update();

	//explosion()

    if (this->m_threat.size() > 0)
    {
        for (std::list<Threat>::iterator it = this->m_threat.begin(); it != this->m_threat.end(); it++)
        {
            it->update();
        }

        for (std::list<Threat>::iterator it = this->m_threat.begin(); it != this->m_threat.end(); it++)
        {

            int x = abs(this->m_player->getPosition().x - it->getPosition().x);
            int y = abs(this->m_player->getPosition().y - it->getPosition().y);

            int check_x = (this->m_player->getPosition().x < it->getPosition().x) ? this->m_player->getPosition().x : it->getPosition().x;
            int check_y = (this->m_player->getPosition().y < it->getPosition().y) ? this->m_player->getPosition().y : it->getPosition().y;

            if (x <= 45 && y <= 95)
            {
                //std::cout << "Va cham";
                this->m_threat.erase(it);
				this->m_player->getCountHeart()--;
                break;
            }
        }
        
        if (this->m_threat.size() > 0 && this->m_threat.begin()->getPosition().y >= 550)
        {
            this->m_threat.pop_front();
			this->m_score += 10;
        }
    }
    std::cout << "Score: " << this->m_score << std::endl;
    this->m_time = this->m_clock.getElapsedTime();

    if (this->m_time.asSeconds() > 0.9)
    {
        switch (std::rand() % 3)
        {
        case 0:
            this->m_threat.push_back(Threat(this->m_window, this->m_texture_threat_1));
            break;
        case 1:
            this->m_threat.push_back(Threat(this->m_window, this->m_texture_threat_2));
            break;
        case 2:
            this->m_threat.push_back(Threat(this->m_window, this->m_texture_threat_1));
            break;
        }
        
        this->m_clock.restart();
    }

    this->m_text.setString("Score: " + std::to_string(this->m_score));

    if (this->m_player->getCountHeart() >= 0)
        return true;
}

void Game::draw()
{
    this->m_window->draw(this->m_sprite_road);
    if (this->m_threat.size() > 0)
    {
        for (std::list<Threat>::iterator it = this->m_threat.begin(); it != this->m_threat.end(); it++)
        {
            it->draw();
        }
    }

    this->m_player->draw();

    if (this->m_explosion.size() > 0)
    {
        for (std::list<Animation>::iterator it = this->m_explosion.begin(); it != this->m_explosion.end(); it++)
            it->draw();
    }

    this->m_window->draw(this->m_text);
}