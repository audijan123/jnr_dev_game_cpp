#include "tavern_main.hpp"


tavern_main::tavern_main(std::string const &path, const JGE::main_base* pbase,const sf::Vector2f &main) :
	m_path(path),p_memory_allocator(*pbase),main(main)
{
	pfont = new sf::Font;
	pfont->loadFromFile(m_path + "DATA/resource/dungeon.ttf");

	item_gen = new gen_item;

	create_main();
	create_mage();
	create_sellman();
	create_safe();


}

tavern_main::~tavern_main()
{


}

void tavern_main::create_main()
{
	bg_tavern = new sf::Texture;
	bg_tavern->loadFromFile(m_path + "DATA/taverne/bg_1.png");

	floor_tavern = new sf::Texture;
	floor_tavern->loadFromFile(m_path + "DATA/taverne/floor_1.png");

	counter_tavern = new sf::Texture;
	counter_tavern->loadFromFile(m_path + "DATA/taverne/counter_1.png");

	for (auto k = 0; k < 4; k++)
	{
		sell_man_t[k] = new sf::Texture;
		sell_man_t[k]->loadFromMemory(&p_memory_allocator.get_memory_data("sale" + std::to_string(k + 1))[0], p_memory_allocator.get_memory_data("sale" + std::to_string(k + 1)).size());
		mage_t[k] = new sf::Texture;
		mage_t[k]->loadFromMemory(&p_memory_allocator.get_memory_data("mage" + std::to_string(k + 1))[0], p_memory_allocator.get_memory_data("mage" + std::to_string(k + 1)).size());
	}


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

void tavern_main::create_safe()
{
	for (auto i = 0; i < 7; i++)
	{
		banking_t[i] = new sf::Texture;
		banking_t[i]->loadFromMemory(&p_memory_allocator.get_memory_data("bank" + std::to_string(i + 1))[0], p_memory_allocator.get_memory_data("bank" + std::to_string(i + 1)).size());
		p_banking[i] = new sf::Sprite;
		p_banking[i]->setTexture(*banking_t[i]);

		if (i != 6)
		{
			safe_t[i] = new sf::Texture;
			p_safe[i] = new sf::Sprite;
			safe_t[i]->loadFromMemory(&p_memory_allocator.get_memory_data("safe" + std::to_string(i + 1))[0], p_memory_allocator.get_memory_data("safe" + std::to_string(i + 1)).size());
			p_safe[i]->setTexture(*safe_t[i]);
			p_safe[i]->setScale(scale);
			if (i == 0)
			{
				p_safe[i]->setPosition(120, 325);
			}
			else
			{
				float y_buffer = (safe_t[i]->getSize().y*scale.y) - (safe_t[0]->getSize().y*scale.y);
				p_safe[i]->setPosition(120, 325 - y_buffer);
			}
		}

	}

	// BANKING POSI
	p_banking[0]->setScale(0.85f, 1.5f);
	p_banking[1]->setScale(1.2f, 1.f);
	p_banking[0]->setOrigin(banking_t[0]->getSize().x / 2.f, banking_t[0]->getSize().y / 2.f);
	p_banking[0]->setPosition(main.x / 2.f, main.y / 2.f);
	p_banking[1]->setPosition(p_banking[0]->getPosition().x - 200.f*0.8f, p_banking[0]->getPosition().y);
	p_banking[2]->setPosition(p_banking[1]->getPosition());
	p_banking[3]->setScale(1.f, 0.8f);
	p_banking[3]->setPosition(p_banking[0]->getPosition().x - 1.f + (banking_t[0]->getSize().x / 2)*0.85f - banking_t[3]->getSize().x, p_banking[0]->getPosition().y - 92.f);
	p_banking[4]->setPosition(p_banking[1]->getPosition().x + banking_t[1]->getSize().x*0.9f, p_banking[1]->getPosition().y + 40);
	p_banking[6]->setPosition(p_banking[1]->getPosition().x + banking_t[1]->getSize().x*1.08f, p_banking[4]->getPosition().y);
	p_banking[5]->setPosition(p_banking[1]->getPosition().x + banking_t[1]->getSize().x*1.08f, p_banking[4]->getPosition().y);
	banking_text.setFont(*pfont);
	current_gold.setFont(*pfont);
	set_gold.setFont(*pfont);
	set_gold.setString("");

	banking_text.setPosition(p_banking[1]->getPosition().x, p_banking[1]->getPosition().y - 25);
	banking_text.setString("Current Gold");
	banking_text.setCharacterSize(20);
	current_gold.setPosition(p_banking[1]->getPosition().x + 35, p_banking[1]->getPosition().y - 11);
	current_gold.setString("1000000M");
	current_gold.setCharacterSize(44);
	current_gold.setFillColor(sf::Color::Black);
	set_gold.setPosition(p_banking[1]->getPosition().x + 35, p_banking[1]->getPosition().y - 11);
	set_gold.setFillColor(sf::Color::Black);
	set_gold.setCharacterSize(44);
}

void tavern_main::create_sellman()
{

	item_list = item_gen->items(main_data::item_class::WEAPON);

	std::cout << "TEST: "<< item_list[2].i_texture << " SIZE OF VECTOR " << item_list.size() << std::endl;

	p_sell_man = new sf::Sprite;
	p_sell_man->setTexture(*sell_man_t[0]);
	p_sell_man->setScale(2.67f, 2.85f);
	p_sell_man->setPosition(650, 100);

	for (auto i = 0; i < 12; i++)
	{
		item_shop_texture[i] = new sf::Texture;
		if (i < 10)
		{
			item_shop_texture[i]->loadFromMemory(&p_memory_allocator.get_memory_data("itsh" + std::to_string(i))[0], p_memory_allocator.get_memory_data("itsh" + std::to_string(i)).size());
		}
		else
		{
			item_shop_texture[i]->loadFromMemory(&p_memory_allocator.get_memory_data("its" + std::to_string(i))[0], p_memory_allocator.get_memory_data("its" + std::to_string(i)).size());
		}
		item_shop_sprites[i] = new sf::Sprite;
		item_shop_sprites[i]->setTexture(*item_shop_texture[i]);
	}
	for (auto i = 1; i < 5; i++)
	{
		item_shop_sprites[i]->setPosition((main.x / 2 - item_shop_texture[1]->getSize().x*1.5f / 2), main.y / 2 - item_shop_texture[1]->getSize().y*1.5f / 2);
		item_shop_sprites[i]->setScale(1.5f, 1.5f);
	}

	item_shop_sprites[0]->setPosition(item_shop_sprites[1]->getPosition().x + item_shop_texture[1]->getSize().x*1.44f, item_shop_sprites[1]->getPosition().y+29);
	item_shop_sprites[0]->setScale(0.78f, 1.58f);
	item_shop_sprites[11]->setPosition(item_shop_sprites[1]->getPosition().x + 650, item_shop_sprites[1]->getPosition().y + 190);
	item_shop_sprites[8]->setPosition(item_shop_sprites[1]->getPosition().x-8, item_shop_sprites[1]->getPosition().y + 70);


	for (auto i = 0; i < 3; i++)
	{
		item_sprite_t[i] = new sf::Texture;
		item_sprite_t[i]->loadFromMemory(&p_memory_allocator.get_memory_data("item" + std::to_string(i))[0], p_memory_allocator.get_memory_data("item" + std::to_string(i)).size());
	}
	for (auto i = 0; i < 30; i++)
	{
		item_sprite[i] = new sf::Sprite;
		if (i < 15)
		{
			item_sprite[i]->setTexture(*item_sprite_t[0]);
		}
		else
		{
			item_sprite[i]->setTexture(*item_sprite_t[2]);
		}
	}

	item_sprite[30] = new sf::Sprite;
	item_sprite[30]->setTexture(*item_sprite_t[1]);
	item_sprite[0]->setPosition(item_shop_sprites[1]->getPosition().x + 65, item_shop_sprites[1]->getPosition().y+110);
	item_sprite[5]->setPosition(item_shop_sprites[1]->getPosition().x + 65, item_shop_sprites[1]->getPosition().y + 182);
	item_sprite[10]->setPosition(item_shop_sprites[1]->getPosition().x + 65, item_shop_sprites[1]->getPosition().y + 254);

	for (auto i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			for (auto p = 1; p < 5; p++)
			{
				item_sprite[p]->setPosition(item_sprite[p - 1]->getPosition().x + 60, item_sprite[0]->getPosition().y);
			}
		}
		else if (i == 1)
		{
			for (auto p = 6; p < 10; p++)
			{
				item_sprite[p]->setPosition(item_sprite[p - 1]->getPosition().x + 60, item_sprite[5]->getPosition().y);
			}
		}
		else if (i == 2)
		{
			for (auto p = 11; p < 15; p++)
			{
				item_sprite[p]->setPosition(item_sprite[p - 1]->getPosition().x + 60, item_sprite[10]->getPosition().y);
			}
		}
	}
	for (auto i = 0; i < 15; i++)
	{
		item_sprite[i]->setScale(0.15f, 0.3f);
		item_sprite[i]->setOrigin(item_sprite_t[0]->getSize().x / 2.f, item_sprite_t[0]->getSize().y / 2.f);
		item_sprite[i + 15]->setOrigin(item_sprite_t[2]->getSize().x / 2.f, item_sprite_t[2]->getSize().y / 2.f);
		item_sprite[i + 15]->setPosition(item_sprite[i]->getPosition());
	}

	item_sprite[30]->setOrigin(item_sprite_t[1]->getSize().x / 2.f, item_sprite_t[1]->getSize().y / 2.f);
	item_sprite[30]->setPosition(item_sprite[0]->getPosition());
	item_sprite[30]->setScale(1.2f, 1.7f);

	item_shop_sprites[12] = new sf::Sprite;
	item_shop_sprites[12]->setTexture(*item_sprite_t[2]);
	item_shop_sprites[12]->setPosition(645, 235);

	rectangle[0].setPosition(310, 200);
	rectangle[1].setPosition(378, 200);
	rectangle[2].setPosition(446, 200);
	rectangle[3].setPosition(516, 200);

	for (auto i = 0; i < 4; i++)
	{
		rectangle[i].setSize(sf::Vector2f(50, 45));
	}

	item_shop_sprites[5]->setPosition(315, 480);
	item_shop_sprites[6]->setPosition(578, item_shop_sprites[5]->getPosition().y);
	item_shop_sprites[5]->setScale(1.5f, 1.5f);
	item_shop_sprites[6]->setScale(item_shop_sprites[5]->getScale());
	site.setFont(*pfont);
	site.setPosition(item_shop_sprites[5]->getPosition().x + 50, item_shop_sprites[5]->getPosition().y+3);
	site.setCharacterSize(25);
	site.setString("Seite 1 von " +std::to_string(max));
}

void tavern_main::create_mage()
{
	p_mage = new sf::Sprite;
	p_mage->setTexture(*mage_t[0]);
	p_mage->setScale(2.67f, 2.85f);
	p_mage->setPosition(1000, 100);
}







void tavern_main::test_func()
{
	if(activ_safe < 5)
	{
		activ_safe++;
	}
	else
	{
		osm::call("Max safe erreicht");
	}
}



void tavern_main::update(const sf::Vector2f &m_posi)
{
	m_pos = m_posi;
	set_gold.setString(bank_Set_gold);

}

void tavern_main::event()
{
	check_mage();
	check_sellman();
	check_safe();
}

void tavern_main::event_get_key(sf::Event *pollevent)
{
	if (pollevent->key.code >= 26 && pollevent->key.code <= 35 && edit_gold)
	{
		if (bank_Set_gold.length() == 0 && pollevent->key.code == 26)
		{
			osm::call("Die erstezahl kann keine Null sein!");
		}
		else
		{
			bank_Set_gold.push_back(static_cast<char>(pollevent->key.code + 22));
		}	
	}
	else if (pollevent->key.code == 59 && bank_Set_gold.length() > 0)
	{
		bank_Set_gold.pop_back();
	}



}

void tavern_main::render(sf::RenderWindow *rw)
{
	for (auto i = 0; i < 3; i++)
	{
		rw->draw(*main_sprites[i]);
	}
	rw->draw(*p_sell_man);
	rw->draw(*p_safe[activ_safe]);
	rw->draw(*p_mage);
	if (banking)
	{
		rw->draw(*p_banking[0]);
		rw->draw(*p_banking[1]);
		rw->draw(*p_banking[2]);
		rw->draw(*p_banking[3]);
		if (!edit_gold)
		{
			rw->draw(*p_banking[4]);
			rw->draw(*p_banking[6]);
			rw->draw(current_gold);
		}
		else
		{
			rw->draw(*p_banking[5]);
			rw->draw(set_gold);
		}
		rw->draw(banking_text);
	}
	else if (item_shop)
	{
		if (bonus_memu)
		{
			rw->draw(*item_shop_sprites[0]);
		}
		
		rw->draw(*item_shop_sprites[1]);
		rw->draw(*item_shop_sprites[11]);
		rw->draw(*item_shop_sprites[8]);
		rw->draw(*item_shop_sprites[12]);
		rw->draw(*item_shop_sprites[5]);
		rw->draw(*item_shop_sprites[6]);
		rw->draw(site);


		for (auto i = 0; i < 31; i++)
		{
			rw->draw(*item_sprite[i]);
		}
	}

}

void tavern_main::check_sellman()
{
	if (osm::sprite_pressed(p_sell_man,m_pos) && !banking && !item_shop)
	{
		// sellman to do
		item_shop = true;
	}
	else if (item_shop)
	{
		for (auto i = 0; i < 15; i++)
		{
			if (osm::sprite_pressed(item_sprite[i],m_pos))
			{
				item_sprite[30]->setPosition(item_sprite[i]->getPosition());
				item_shop_sprites[12]->setTexture(*item_sprite[i+15]->getTexture());
			}
		}

		for (auto i = 0; i < 4; i++)
		{
			if (rectangle[i].getGlobalBounds().contains(m_pos) && item_shop_sprites[1]->getTexture() != item_shop_texture[i+1])
			{
				if (!cap_menu)
				{
					item_shop_sprites[1]->setTexture(*item_shop_texture[i + 1]);
					item_sprite[30]->setPosition(item_sprite[0]->getPosition());
				}
				else if (cap_menu)
				{
					item_shop_sprites[1]->setTexture(*item_shop_texture[i + 1]);
					item_sprite[30]->setPosition(item_sprite[0]->getPosition());
				}
			}
		}

		if (item_shop_sprites[8]->getGlobalBounds().contains(m_pos) && !cap_menu)
		{
			item_shop_sprites[1]->setTexture(*item_shop_texture[1]);
			item_shop_sprites[8]->setTexture(*item_shop_texture[9]);
			item_sprite[30]->setPosition(item_sprite[0]->getPosition());
			cap_menu = true;
		}
		else if (item_shop_sprites[8]->getGlobalBounds().contains(m_pos) && cap_menu)
		{
			item_shop_sprites[8]->setTexture(*item_shop_texture[8]);
			item_shop_sprites[1]->setTexture(*item_shop_texture[1]);
			item_sprite[30]->setPosition(item_sprite[0]->getPosition());
			cap_menu = false;
		}
		else if (item_shop_sprites[11]->getGlobalBounds().contains(m_pos))
		{
			if (item_shop_sprites[11]->getScale().x == -1.f)
			{
				item_shop_sprites[11]->setPosition(item_shop_sprites[11]->getPosition().x - 29, item_shop_sprites[11]->getPosition().y);
				item_shop_sprites[11]->setScale(1.f, 1);
			}
			else
			{
				item_shop_sprites[11]->setPosition(item_shop_sprites[11]->getPosition().x + 29, item_shop_sprites[11]->getPosition().y);
				item_shop_sprites[11]->setScale(-1.f, 1);
			}
			
			bonus_memu = !bonus_memu;
		}

	}

}

void tavern_main::check_mage()
{
	if (osm::sprite_pressed(p_mage,m_pos) && !banking)
	{
		std::cout << "mage test" << std::endl;
	}
}

void tavern_main::check_safe()
{
	if (osm::sprite_pressed(p_safe[activ_safe], m_pos))
	{
		banking = true;
		u_menu = true;
	}
	else if (banking)
	{
		if (osm::sprite_pressed(p_banking[3], m_pos))
		{
			if (edit_gold)
			{
				edit_gold = false;
				set_gold.setString("");
				bank_Set_gold.clear();
				banking_text.setString("Current Gold");
				status = init;
			}
			else
			{
				banking = false;
				u_menu = false;
			}
		}
		else if (osm::sprite_pressed(p_banking[4], m_pos) && !edit_gold)
		{
			status = negativ;
			banking_text.setString("Wieviel willst du haben?");
			edit_gold = true;
		}
		else if (osm::sprite_pressed(p_banking[6], m_pos) && !edit_gold)
		{
			status = positiv;
			banking_text.setString("Wieviel willst du einzahlen?");
			edit_gold = true;
		}
		else if (osm::sprite_pressed(p_banking[5], m_pos) && edit_gold)
		{
			if (status == positiv)
			{
				// player money - and bank money +
				// saverange
			}
			else if (status == negativ)
			{
				// player money + and bank money -
				// player cant get money out of range
			}
			else
			{
				osm::call("Error: Banking System Status");
			}
			edit_gold = false;
			bank_Set_gold.clear();
			status = init;
			banking_text.setString("Current Gold");
		}
	}
}

bool tavern_main::o_menu()
{
	if (banking)
	{
		if (edit_gold)
		{
			set_gold.setString("");
			bank_Set_gold.clear();
			banking_text.setString("Current Gold");
			status = init;
			edit_gold = false;
		}
		else
		{
			banking = false;
			u_menu = false;
		}
		return true;
	}
	else
	{
		return u_menu;
	}

}