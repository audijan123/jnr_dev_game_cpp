#include "dungeon_mob.hpp"


mob::mob(uint16_t position, const sf::Image Image, int diffi, int m_class, const sf::Font *pfont , const sf::Image hp_Image)
{

	p_texture = new sf::Texture();
	if (!p_texture->loadFromImage(Image, sf::IntRect(0, 0, Image.getSize().x / 2, Image.getSize().y)))
	{
		std::cout << "Error" << std::endl;
	}
	
	m_life = m_life*diffi;

	p_life.setFont(*pfont);

	p_life.setString(std::to_string(m_life));

	p_sprite = new sf::Sprite();
	p_sprite->setTexture(*p_texture);


	p_texture_life = new sf::Texture();
	p_texture_life->loadFromImage(hp_Image);

	p_sprite_life = new sf::Sprite();
	p_sprite_life->setTexture(*p_texture_life);


	//92 x 89,7
	double x_scale = 100 / (Image.getSize().x / 2);
	double y_scale = 60 / (Image.getSize().y / 2);

	//std::cout << x_scale << "x : y" << y_scale << std::endl;

	p_sprite->setScale(x_scale, y_scale);

	//std::cout << "MOB:"<< position << std::endl;

	if (position == 0)
	{
		p_sprite->setPosition(650,280);
	}
	if (position == 1)
	{
		p_sprite->setPosition(650, 440);
	}
	if (position == 2)
	{
		p_sprite->setPosition(650, 600);
	}
	if (position == 3)
	{
		p_sprite->setPosition(790, 280);
	}
	if (position == 4)
	{
		p_sprite->setPosition(790, 440);
	}
	if (position == 5)
	{
		p_sprite->setPosition(790, 600);
	}
	if (position == 6)
	{
		p_sprite->setPosition(930, 280);
	}
	if (position == 7)
	{
		p_sprite->setPosition(930, 440);
	}
	if (position == 8)
	{
		p_sprite->setPosition(930, 600);
	}

	p_life.setPosition(p_sprite->getPosition().x + 10, p_sprite->getPosition().y - 20);
	p_sprite_life->setPosition(p_life.getPosition().x - 15, p_life.getPosition().y+15);
}

mob::~mob()
{
	delete p_sprite_life;
	delete p_sprite;
	delete p_texture;
	delete p_texture_life;

	p_sprite_life = nullptr;
	p_sprite = nullptr;
	p_texture = nullptr;
	p_texture_life = nullptr;

}


void mob::attack()
{

}

void mob::render(sf::RenderWindow *rw)
{
	rw->draw(*p_sprite);
	rw->draw(p_life);
	rw->draw(*p_sprite_life);
}