#include "tavern_main.hpp"


tavern_main::tavern_main(std::string const &path, const JNR::main_base* pbase,const sf::Vector2f &main) :
	m_path(path),p_memory_allocator(*pbase),main(main)
{
	pfont = new sf::Font;
	pfont->loadFromFile(m_path + "DATA/resource/dungeon.ttf");

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
	
	
	p_sell_man = new sf::Sprite;
	p_sell_man->setTexture(*sell_man_t[0]);
	p_sell_man->setScale(2.67f, 2.85f);
	p_sell_man->setPosition(650, 100);

	
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
	p_banking[0]->setPosition(main.x /2.f , main.y /2.f );
	p_banking[1]->setPosition(p_banking[0]->getPosition().x - 200.f*0.8f, p_banking[0]->getPosition().y);
	p_banking[2]->setPosition(p_banking[1]->getPosition());
	p_banking[3]->setScale(1.f, 0.8f);
	p_banking[3]->setPosition(p_banking[0]->getPosition().x-1.f + (banking_t[0]->getSize().x/2)*0.85 - banking_t[3]->getSize().x, p_banking[0]->getPosition().y-92.f);
	p_banking[4]->setPosition(p_banking[1]->getPosition().x + banking_t[1]->getSize().x*0.9f, p_banking[1]->getPosition().y + 40);
	p_banking[6]->setPosition(p_banking[1]->getPosition().x+banking_t[1]->getSize().x*1.08f, p_banking[4]->getPosition().y);
	p_banking[5]->setPosition(p_banking[1]->getPosition().x + banking_t[1]->getSize().x*1.08f, p_banking[4]->getPosition().y);
	banking_text.setFont(*pfont);
	current_gold.setFont(*pfont);
	set_gold.setFont(*pfont);
	set_gold.setString("");

	banking_text.setPosition(p_banking[1]->getPosition().x, p_banking[1]->getPosition().y - 25);
	banking_text.setString("Current Gold");
	banking_text.setCharacterSize(20);
	current_gold.setPosition(p_banking[1]->getPosition().x + 35, p_banking[1]->getPosition().y-11);
	current_gold.setString("1000000M");
	current_gold.setCharacterSize(44);
	current_gold.setColor(sf::Color::Black);
	set_gold.setPosition(p_banking[1]->getPosition().x + 35, p_banking[1]->getPosition().y - 11);
	set_gold.setColor(sf::Color::Black);
	set_gold.setCharacterSize(44);
}

tavern_main::~tavern_main()
{



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

}

void tavern_main::check_sellman()
{
	if (m_pos.x >= p_sell_man->getPosition().x && m_pos.x <= p_sell_man->getPosition().x + sell_man_t[0]->getSize().x*scale.x - 50 && m_pos.y >= p_sell_man->getPosition().y && m_pos.y <= p_sell_man->getPosition().y + sell_man_t[0]->getSize().y*scale.y && !banking)
	{
		std::cout << "sellman test" << std::endl;
	}

}

void tavern_main::check_mage()
{
	if (m_pos.x >= p_mage->getPosition().x+50 && m_pos.x <= p_mage->getPosition().x + mage_t[0]->getSize().x*scale.x && m_pos.y >= p_mage->getPosition().y && m_pos.y <= p_mage->getPosition().y + mage_t[0]->getSize().y*scale.y && !banking)
	{
		std::cout << "mage test" << std::endl;
	}
}

void tavern_main::check_safe()
{
	if (m_pos.x >= p_safe[activ_safe]->getPosition().x && m_pos.x <= p_safe[activ_safe]->getPosition().x + safe_t[activ_safe]->getSize().x*scale.x && m_pos.y >= p_safe[activ_safe]->getPosition().y && m_pos.y <= p_safe[activ_safe]->getPosition().y + safe_t[activ_safe]->getSize().y*scale.y )
	{
		banking = true;
		u_menu = true;
	}
	else if (banking)
	{
		if (m_pos.x >= p_banking[3]->getPosition().x && m_pos.x <= p_banking[3]->getPosition().x + banking_t[3]->getSize().x && m_pos.y >= p_banking[3]->getPosition().y && m_pos.y <= p_banking[3]->getPosition().y + banking_t[3]->getSize().y*0.8f)
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
		else if (m_pos.x >= p_banking[4]->getPosition().x && m_pos.x <= p_banking[4]->getPosition().x + banking_t[4]->getSize().x && m_pos.y >= p_banking[4]->getPosition().y && m_pos.y <= p_banking[4]->getPosition().y + banking_t[4]->getSize().y&& !edit_gold)
		{
			status = negativ;
			banking_text.setString("Wieviel willst du haben?");
			edit_gold = true;
		}
		else if (m_pos.x >= p_banking[6]->getPosition().x && m_pos.x <= p_banking[6]->getPosition().x + banking_t[6]->getSize().x && m_pos.y >= p_banking[6]->getPosition().y && m_pos.y <= p_banking[6]->getPosition().y + banking_t[6]->getSize().y && !edit_gold)
		{
			status = positiv;
			banking_text.setString("Wieviel willst du einzahlen?");
			edit_gold = true;
		}
		else if (m_pos.x >= p_banking[5]->getPosition().x && m_pos.x <= p_banking[5]->getPosition().x + banking_t[5]->getSize().x && m_pos.y >= p_banking[5]->getPosition().y && m_pos.y <= p_banking[5]->getPosition().y + banking_t[5]->getSize().y && edit_gold)
		{
			if (status = positiv)
			{
				// player money - and bank money +
				// saverange
			}
			else if (status = negativ)
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