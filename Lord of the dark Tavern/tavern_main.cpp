#include "tavern_main.hpp"



tavern_main::tavern_main(std::string const &path) :
	m_path(path)
{
	bg_tavern = new sf::Texture;
	bg_tavern->loadFromFile(m_path + "DATA/taverne/bg_1.png");

	floor_tavern = new sf::Texture;
	floor_tavern->loadFromFile(m_path + "DATA/taverne/floor_1.png");

	counter_tavern = new sf::Texture;
	counter_tavern->loadFromFile(m_path + "DATA/taverne/counter_1.png");

	sell_man_t = new sf::Texture;
	sell_man_t->loadFromFile(m_path + "DATA/taverne/salesman_1.png");
	p_sell_man = new sf::Sprite;
	p_sell_man->setTexture(*sell_man_t);
	p_sell_man->setScale(2.67f, 2.85f);
	p_sell_man->setPosition(650, 100);

	mage_t = new sf::Texture;
	mage_t->loadFromFile(m_path + "DATA/taverne/wizard_1.png");
	p_mage = new sf::Sprite;
	p_mage->setTexture(*mage_t);
	p_mage->setScale(2.67f, 2.85f);
	p_mage->setPosition(1000, 100);

	main_sprites[0] = new sf::Sprite; //floor
	main_sprites[0]->setTexture(*floor_tavern);
	main_sprites[0]->setScale(2.67f, 2.85f);
	main_sprites[0]->setPosition(0, 366);

	main_sprites[1] = new sf::Sprite; //bg
	main_sprites[1]->setTexture(*bg_tavern);
	main_sprites[1]->setScale(2.67f, 2.85f);

	main_sprites[2] = new sf::Sprite; //counter
	main_sprites[2]->setTexture(*counter_tavern);
	main_sprites[2]->setScale(2.67f, 2.85f);
	main_sprites[2]->setPosition(66, 370);






}

tavern_main::~tavern_main()
{

}



void tavern_main::update()
{

}

void tavern_main::render(sf::RenderWindow *rw)
{
	for (short i = 0; i < 3; i++)
	{
		rw->draw(*main_sprites[i]);
	}
	rw->draw(*p_sell_man);
	rw->draw(*p_mage);

}