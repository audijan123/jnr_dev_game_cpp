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

	sell_man_t[0] = new sf::Texture;
	sell_man_t[1] = new sf::Texture;
	sell_man_t[2] = new sf::Texture;
	sell_man_t[0]->loadFromFile(m_path + "DATA/taverne/salesman/salesman_1.png");
	sell_man_t[1]->loadFromFile(m_path + "DATA/taverne/salesman/salesman_2.png");
	sell_man_t[2]->loadFromFile(m_path + "DATA/taverne/salesman/salesman_3.png");
	
	p_sell_man = new sf::Sprite;
	p_sell_man->setTexture(*sell_man_t[0]);
	p_sell_man->setScale(2.67f, 2.85f);
	p_sell_man->setPosition(650, 100);

	mage_t[0] = new sf::Texture;
	mage_t[1] = new sf::Texture;
	mage_t[2] = new sf::Texture;
	mage_t[3] = new sf::Texture;
	mage_t[0]->loadFromFile(m_path + "DATA/taverne/wizard/wizard_1.png");
	mage_t[1]->loadFromFile(m_path + "DATA/taverne/wizard/wizard_2.png");
	mage_t[2]->loadFromFile(m_path + "DATA/taverne/wizard/wizard_3.png");
	mage_t[3]->loadFromFile(m_path + "DATA/taverne/wizard/wizard_4.png");
	p_mage = new sf::Sprite;
	p_mage->setTexture(*mage_t[0]);
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

	safe_t[0] = new sf::Texture;
	safe_t[1] = new sf::Texture;
	safe_t[2] = new sf::Texture;
	safe_t[3] = new sf::Texture;
	safe_t[4] = new sf::Texture;
	safe_t[5] = new sf::Texture;

	safe_t[0]->loadFromFile(m_path + "DATA/taverne/safe/safelvl1.png");
	safe_t[1]->loadFromFile(m_path + "DATA/taverne/safe/safelvl2.png");
	safe_t[2]->loadFromFile(m_path + "DATA/taverne/safe/safelvl3.png");
	safe_t[3]->loadFromFile(m_path + "DATA/taverne/safe/safelvl4.png");
	safe_t[4]->loadFromFile(m_path + "DATA/taverne/safe/safelvl5.png");
	safe_t[5]->loadFromFile(m_path + "DATA/taverne/safe/safelvl6.png");

	main_sprites[3] = new sf::Sprite; //safe
	main_sprites[3]->setTexture(*safe_t[0]);
	main_sprites[3]->setScale(2.67f, 2.85f);
	main_sprites[3]->setPosition(973, 330);


}

tavern_main::~tavern_main()
{



}


void tavern_main::test_func()
{
	main_sprites[3]->setTexture(*safe_t[test]);
	test++;
}



void tavern_main::update(float const &m_time)
{

}

void tavern_main::render(sf::RenderWindow *rw)
{
	for (short i = 0; i < 4; i++)
	{
		rw->draw(*main_sprites[i]);
	}
	rw->draw(*p_sell_man);
	rw->draw(*p_mage);

}