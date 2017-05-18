#include "dungeon_manager.hpp"


dungeon_manager::dungeon_manager(const int &m_power,const std::string &path, const JGE::main_base* pbase) :
	p_memory_allocator(*pbase)
{

	m_path = path;
	p_life_t = new sf::Texture;
	p_life_t->loadFromMemory(&p_memory_allocator.get_memory_data("leben")[0], p_memory_allocator.get_memory_data("leben").size());


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

	for (auto mob_size = p_memory_allocator.get_mob_size_short()-1; mob_size != 0; mob_size--)
	{
		image = new sf::Image;
		image->loadFromMemory(&p_memory_allocator.get_memory_data("mob", mob_size + 99)[0], p_memory_allocator.get_memory_data("mob", mob_size + 99).size());
		p_texture_t = new sf::Texture;
		p_texture_t->loadFromImage(*image, sf::IntRect(0, 0, image->getSize().x / 2, image->getSize().y));
		p_texture.push_back(p_texture_t);
		delete image;
	}


	/// Enviroment Auswürfeln und setzen 

	enviro_id = rng() % 12;
	fill_dungeon();
	dungeon_atkiv = true;
}


dungeon_manager::~dungeon_manager()
{
	for (auto t = mob_this_dungeons.size(); t != 0 ; t--)
	{
		delete mob_this_dungeons[t-1].p_sprite;
		mob_this_dungeons[t-1].p_sprite = nullptr;

		delete mob_this_dungeons[t-1].text;
		mob_this_dungeons[t-1].text = nullptr;

		delete mob_this_dungeons[t - 1].p_life;
		mob_this_dungeons[t - 1].p_life = nullptr;
	}
	for (auto i = p_texture.size(); i != 0; i--)
	{
		delete p_texture[i-1];
		p_texture[i-1] = nullptr;
	}
	p_texture.clear();
	mob_this_dungeons.clear();

	image = nullptr;

	delete pfont;
	pfont = nullptr;

	delete p_life_t;
	p_life_t = nullptr;
}


void dungeon_manager::fill_dungeon()
{
	pfont = new sf::Font;
	pfont->loadFromFile(m_path + "DATA/resource/dungeon.ttf");

	int mobs_ebene = 0;
	for (auto i = 0; i <= floors; i++)
	{
		std::time_t times = std::time(0);
		boost::random::mt19937 dev{ static_cast<std::uint32_t>(times) };;
		mobs_ebene = dev()*(i+1) % 9 + 1;

		for (auto u = mobs_ebene; u != 0; u--)
		{
			now = std::time(0);
			boost::random::mt19937 dev_test{ static_cast<std::uint32_t>(now) };;
			uint16_t rnd = (dev_test()*u % (p_memory_allocator.get_mob_size_short()-1));
			struct mob dev_s = {};
			dev_s.p_sprite->setTexture(*p_texture[rnd]);
			dev_s.scale = { 50.f / (p_texture[rnd]->getSize().x / 2),50.f / (p_texture[rnd]->getSize().y / 2) };
			if (u == 1)
			{
				dev_s.p_sprite->setPosition(650, 280);
			}
			else if (u == 2)
			{
				dev_s.p_sprite->setPosition(650, 440);
			}
			else if (u == 3)
			{
				dev_s.p_sprite->setPosition(650, 600);
			}
			else if (u == 4)
			{
				dev_s.p_sprite->setPosition(790, 280);
			}
			else if (u == 5)
			{
				dev_s.p_sprite->setPosition(790, 440);
			}
			else if (u == 6)
			{
				dev_s.p_sprite->setPosition(790, 600);
			}
			else if (u == 7)
			{
				dev_s.p_sprite->setPosition(930, 280);
			}
			else if (u == 8)
			{
				dev_s.p_sprite->setPosition(930, 440);
			}
			else if (u == 9)
			{
				dev_s.p_sprite->setPosition(930, 600);
			}

			dev_s.p_life->setTexture(*p_life_t);
			dev_s.text->setFont(*pfont);
			dev_s.text->setString(std::to_string(dev_s.life*diffculty));
			dev_s.p_sprite->setScale(dev_s.scale);
			dev_s.text->setPosition(dev_s.p_sprite->getPosition().x + 10, dev_s.p_sprite->getPosition().y - 20);
			dev_s.p_life->setPosition(dev_s.text->getPosition().x - 15, dev_s.text->getPosition().y + 15);

			mob_this_dungeons.push_back(dev_s);
		}
		mob_per_floor.push_back(mobs_ebene);	
	}

}




void dungeon_manager::render(sf::RenderWindow *rw) const
{
	if (dungeon_atkiv)
	{
		for (auto i_p = 0; i_p < mob_per_floor[floor_a]; i_p++)
		{
			rw->draw(*mob_this_dungeons[i_p].p_sprite);
			rw->draw(*mob_this_dungeons[i_p].p_life);
			rw->draw(*mob_this_dungeons[i_p].text);
		}
	}
}
