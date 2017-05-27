#include "dungeon_manager.hpp"
extern sf::Font	*pFont;
extern JGE::SpriteGen *pSpriteErsteller;

dungeon_manager::dungeon_manager(const int &iPower,const std::vector<sf::Texture>& vMobTexture)
	:	p_texture(vMobTexture) , diffculty(iPower)
{
	p_life_t = pSpriteErsteller->erstelle_texture("leben");

	// Hintergrundbilder Laden ///
	pHintergrundLader = new enviroment_loader();

	/// Random Dungeon Generator
	now = std::time(0);
	boost::random::mt19937 rng{ static_cast<std::uint32_t>(now) };;

	/// Dungeon Range Floor länge für LevelGrad
	switch (iPower)
	{
	case 1:
		floors = rng() % 20 + 10; ////  10 - 30
		break;
	case 2:
		floors = rng() % 50 + 30; //// 30 - 80
		break;
	case 3:
		floors = rng() % 120 + 60; //// 60 - 180
		break;
	default:
		floors = rng() % 120 + 60 + 30 * (iPower - 2); //// 60 - 180
		break;
	}

	/// Enviroment Auswürfeln und setzen 

	enviro_id = rng() % 12;
	fill_dungeon();
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
	mob_this_dungeons.clear();

	delete pHintergrundLader;
	pHintergrundLader = nullptr;
}


void dungeon_manager::fill_dungeon()
{
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
			uint16_t rnd = (dev_test()*u) % (static_cast<uint16_t>(p_texture.size())-1);
			GAMESTRUCTS::mob dev_s = {};
			dev_s.p_sprite->setTexture(p_texture[rnd]);
			dev_s.scale = { 50.f / (p_texture[rnd].getSize().x / 2),50.f / (p_texture[rnd].getSize().y / 2) };
			dev_s.life *= diffculty;
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

			dev_s.p_life->setTexture(p_life_t);
			dev_s.text->setFont(*pFont);
			dev_s.text->setString(std::to_string(dev_s.life));
			dev_s.p_sprite->setScale(dev_s.scale);
			dev_s.text->setPosition(dev_s.p_sprite->getPosition().x + 10, dev_s.p_sprite->getPosition().y - 20);
			dev_s.p_life->setPosition(dev_s.text->getPosition().x - 15, dev_s.text->getPosition().y + 15);

			mob_this_dungeons.push_back(dev_s);
		}
		mob_per_floor.push_back(mobs_ebene);	
	}

}

void dungeon_manager::render(sf::RenderWindow *rw)
{
	pHintergrundLader->render_enviro(enviro_id, rw);
	for (auto i_p = 0; i_p < mob_per_floor[floor_a]; i_p++)
	{
		rw->draw(*mob_this_dungeons[i_p].p_sprite);
		rw->draw(*mob_this_dungeons[i_p].p_life);
		rw->draw(*mob_this_dungeons[i_p].text);
	}
}
