#include "dungeon_manager.hpp"


dungeon_manager::dungeon_manager(const int &m_power,const std::string &path, const JNR::main_base* pbase) :
	p_memory_allocator(*pbase)
{

	m_path = path;
	load_dungeon();

	/// Random Dungeon Generator
	now = std::time(0);
	boost::random::mt19937 rng{ static_cast<std::uint32_t>(now) };;
	/// Dungeon Range Floor länge für LevelGrad
	if (m_power == 1)
	{
		floors = rng() % 20 + 10; ////  10 - 30
	}
	else if (m_power == 2)
	{
		floors = rng() % 50 + 30; //// 30 - 80
	}
	else if (m_power == 3)
	{
		floors = rng() % 120 + 60; //// 60 - 180
	}
	else if (m_power > 3)
	{
		floors = rng() % 120 + 60+ 30*(m_power-2); //// 60 - 180
	}
	
	diffculty = m_power;
	/// Enviroment Auswürfeln und setzen 

	enviro_id = rng() % 12;
	fill_dungeon();
	dungeon_atkiv = true;
}


dungeon_manager::~dungeon_manager()
{
	for (int t = mob_this_dungeons.size(); t != 0 ; t--)
	{
		delete mob_this_dungeons[t-1].p_sprite;
		mob_this_dungeons[t-1].p_sprite = nullptr;

		delete mob_this_dungeons[t-1].image;
		mob_this_dungeons[t-1].image = nullptr;

		delete mob_this_dungeons[t-1].text;
		mob_this_dungeons[t-1].text = nullptr;

		delete mob_this_dungeons[t-1].p_life_t;
		mob_this_dungeons[t-1].p_life_t = nullptr;

		delete mob_this_dungeons[t - 1].p_life;
		mob_this_dungeons[t - 1].p_life = nullptr;

		delete mob_this_dungeons[t-1].p_texture;
		mob_this_dungeons[t-1].p_texture = nullptr;

	}
	mob_this_dungeons.clear();

	delete pfont;
	pfont = nullptr;
}

void dungeon_manager::load_dungeon()
{

}

void dungeon_manager::fill_dungeon()
{
	pfont = new sf::Font;
	pfont->loadFromFile(m_path + "DATA/resource/dungeon.ttf");

	int mobs_ebene = 0;
	for (int i = 0; i <= floors; i++)
	{
		std::time_t times = std::time(0);
		boost::random::mt19937 dev{ static_cast<std::uint32_t>(times) };;
		mobs_ebene = dev()*(i+1) % 9 + 1;

		for (uint16_t u = mobs_ebene; u != 0; u--)
		{
			now = std::time(0);
			boost::random::mt19937 dev_test{ static_cast<std::uint32_t>(now) };;
			//uint16_t rnd = dev_test()*u % (image.capacity()-2);
			//mob_ebene_1.push_back(new mob(u-1,*image[rnd], diffculty, 0, pfont, *image[image.capacity()-1]));
			struct mob dev = {};
			dev.image->loadFromMemory(&p_memory_allocator.get_memory_data("mobaa")[0], p_memory_allocator.get_memory_data("mobaa").size());
			dev.p_texture->loadFromImage(*dev.image,sf::IntRect(0, 0, dev.image->getSize().x / 2, dev.image->getSize().y));
			dev.p_sprite->setTexture(*dev.p_texture);
			if (u == 1)
			{
				dev.p_sprite->setPosition(650, 280);
			}
			else if (u == 2)
			{
				dev.p_sprite->setPosition(650, 440);
			}
			else if (u == 3)
			{
				dev.p_sprite->setPosition(650, 600);
			}
			else if (u == 4)
			{
				dev.p_sprite->setPosition(790, 280);
			}
			else if (u == 5)
			{
				dev.p_sprite->setPosition(790, 440);
			}
			else if (u == 6)
			{
				dev.p_sprite->setPosition(790, 600);
			}
			else if (u == 7)
			{
				dev.p_sprite->setPosition(930, 280);
			}
			else if (u == 8)
			{
				dev.p_sprite->setPosition(930, 440);
			}
			else if (u == 9)
			{
				dev.p_sprite->setPosition(930, 600);
			}

			dev.p_life_t->loadFromMemory(&p_memory_allocator.get_memory_data("leben")[0], p_memory_allocator.get_memory_data("leben").size());
			dev.p_life->setTexture(*dev.p_life_t);
			dev.text->setFont(*pfont);
			dev.text->setString(std::to_string(dev.life*diffculty));
			dev.p_sprite->setScale((100 / (dev.image->getSize().x / 2)), 50 / (dev.image->getSize().y / 2));
			dev.text->setPosition(dev.p_sprite->getPosition().x + 10, dev.p_sprite->getPosition().y - 20);
			dev.p_life->setPosition(dev.text->getPosition().x - 15, dev.text->getPosition().y + 15);

			mob_this_dungeons.push_back(dev);

		}
		mob_per_floor.push_back(mobs_ebene);		
	}



}




void dungeon_manager::render(sf::RenderWindow *rw) const
{
	if (dungeon_atkiv)
	{
		for (int i_p = 0; i_p < mob_per_floor[floor_a]; i_p++)
		{
			rw->draw(*mob_this_dungeons[i_p].p_sprite);
			rw->draw(*mob_this_dungeons[i_p].p_life);
			rw->draw(*mob_this_dungeons[i_p].text);
		}
	}
}
