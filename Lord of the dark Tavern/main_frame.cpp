#include "main_frame.hpp"

main_frame::main_frame(const std::string &path) :
	main_path(path.substr(0, path.length() - 27))
{
	p_data = new main_data(main_path);

	p_memory_allocator = new JNR::main_base(main_path);

	
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.antialiasingLevel = 1;
	contextSettings.majorVersion = 4;
	contextSettings.minorVersion = 5;

	pRenderWindow = new sf::RenderWindow(sf::VideoMode(main.x,main.y, 64), "Lord of the dark Travern",sf::Style::Default);
	pRenderWindow->setFramerateLimit(60);
	pRenderWindow->setVerticalSyncEnabled(true);
	pMainEvent	  = new sf::Event;
	pClock        = new sf::Clock;
	pFont = new sf::Font;
	pFont->loadFromFile(main_path + "DATA/resource/dungeon.ttf");
	pText.setFont(*pFont);
	pText.setPosition(0, 0);
	pText.setString("");

	pBackground = new sf::Texture;
	//pBackground->loadFromFile(main_path + "DATA/resource/bg.png");
	pBackground->loadFromMemory(&p_memory_allocator->get_memory_data("backg")[0], p_memory_allocator->get_memory_data("backg").size());
	pSprite = new sf::Sprite;
	pSprite->setTexture(*pBackground);
	pSprite->setScale(2.67f, 2.85f);

	/// Tavern 

	pTextureTaverne = new sf::Texture;
	pTextureTaverne->loadFromMemory(&p_memory_allocator->get_memory_data("taver")[0], p_memory_allocator->get_memory_data("taver").size());
	pTaverne = new sf::Sprite;
	pTaverne->setTexture(*pTextureTaverne);
	pTaverne->setPosition(tavern_coords[0], tavern_coords[1]);
	pTaverne->setScale(2.67f, 2.85f);

	tavern_coords[2] = pTextureTaverne->getSize().x*2.67f + tavern_coords[0];
	tavern_coords[3] = pTextureTaverne->getSize().y*2.85f + tavern_coords[1];



	//Hover Tavern/////////////////////

	pImageTavern_Hover = new sf::Image;
	pImageTavern_Hover->loadFromFile(main_path + "DATA/resource/hover_tavern.png");
	pImageTavern_Hover->createMaskFromColor(sf::Color(0, 0, 10, 20));
	pTextureTaverne_Hover = new sf::Texture;
	pTextureTaverne_Hover->loadFromImage(*pImageTavern_Hover);
	pTaverne_Hover = new sf::Sprite;
	pTaverne_Hover->setTexture(*pTextureTaverne_Hover);
	pTaverne_Hover->setPosition(tavern_coords[0]+95.f, tavern_coords[1]+105.f);
	pTaverne_Hover->setScale(2.67f, 2.85f);
	////////////////////////////////////

	//Sky and Clouds

	pSky_Texture = new sf::Texture;
	pClouds_Texture = new sf::Texture;
	pSky = new sf::Sprite;
	pClouds = new sf::Sprite;
	pClouds2 = new sf::Sprite;

	//pSky_Texture->loadFromFile(main_path + "DATA/resource/sky.png");
	pSky_Texture->loadFromMemory(&p_memory_allocator->get_memory_data("skybb")[0], p_memory_allocator->get_memory_data("skybb").size());
	pClouds_Texture->loadFromFile(main_path + "DATA/resource/clouds.png");

	pSky->setTexture(*pSky_Texture);
	pSky->setScale(2.67f, 2.85f);
	pClouds->setTexture(*pClouds_Texture);
	pClouds->setScale(1.5f, 1.2f);

	pClouds2->setTexture(*pClouds_Texture);
	pClouds2->setScale(1.5f, 1.2f);
	pClouds2->setPosition(0-1200,0);


	// Enviroment Loader ///
	pEnviromentLoader = new enviroment_loader(main_path);



	// Dungeon Portal //
	pDungeonProtal_T = new sf::Texture;
	pDungeonPortal = new sf::Sprite;

	pDungeonProtal_T->loadFromFile(main_path + "DATA/resource/portal.png");

	pDungeonPortal->setTexture(*pDungeonProtal_T);
	pDungeonPortal->setOrigin(pDungeonProtal_T->getSize().x / 2.f, pDungeonProtal_T->getSize().y / 2.f);
	pDungeonPortal->setPosition(portal_coords[0], portal_coords[1]);
	pDungeonPortal->setScale(0.5, 0.5);

	portal_coords[2] = pDungeonProtal_T->getSize().x*0.20f + portal_coords[0];
	portal_coords[3] = pDungeonProtal_T->getSize().y*0.19f + portal_coords[1];

	// Dungeon Portal Hover //

	pPortal_T_Hover = new sf::Texture;
	pPortal_T_Hover->loadFromFile(main_path + "DATA/resource/portal_hover.png");
	pPortal_Sky_Hover = new sf::Texture;
	pPortal_Sky_Hover->loadFromFile(main_path + "DATA/resource/sky_hover.png");

	// Option BTNS
	for (auto i = 0; i < 3; i++)
	{
		pBtn[i] = new sf::Sprite;
		pBtn_T[i] = new sf::Texture;
		pBtn_T[i]->loadFromMemory(&p_memory_allocator->get_memory_data("btn", i + 100)[0], p_memory_allocator->get_memory_data("btn", i + 100).size());
		pBtn[i]->setTexture(*pBtn_T[i]);
		pBtn[i]->setPosition(btn[i], btn[3]);
		pBtn[i]->setScale(1.7f, 1.7f);
	}
	// Dungeon Browser Menu //
	create_dungeon_browser();
	/////


	

	m_scale = 800.f / main.x;

	p_tavern = new tavern_main(main_path, p_memory_allocator,main);


	pLoader = new re_loader(main_path);


}

main_frame::~main_frame()
{
}


void main_frame::run()
{
	while (m_run)
	{
		update();
		tavern_hover();
		update_diffi();

		handleEvents();
		render();
		m_frametime();
		quit();
	}
}

void main_frame::quit()
{
	if (!m_run)
	{
		pRenderWindow->close();
		exit(0x001996);
	}
}

void main_frame::update()
{
	if (m_pause == false)
	{
		a_frametime = static_cast<int>(1.f / m_frame_time);
		pText.setString(std::to_string(a_frametime));

		m_pos = { sf::Mouse::getPosition().x - 8.f - pRenderWindow->getPosition().x ,sf::Mouse::getPosition().y - 32.f - pRenderWindow->getPosition().y };

		p_tavern->update(m_pos);
	}


}
void main_frame::handleEvents()
{
	while (pRenderWindow->pollEvent(*pMainEvent))
	{
		if (pMainEvent->type == sf::Event::Closed)
		{
			m_run = false;
		}
		if (pMainEvent->type == sf::Event::KeyPressed && pRenderWindow->hasFocus())
		{
			p_tavern->event_get_key(pMainEvent);
			if (pMainEvent->key.code == sf::Keyboard::A)
			{
				std::cout << "event " << std::endl;
			}
			else if (pMainEvent->key.code == sf::Keyboard::F1)
			{
				p_tavern->test_func();
			}
			else if (pMainEvent->key.code == sf::Keyboard::F5)
			{
				exit_dungeon();
			}

			
		}
		if (pMainEvent->type == sf::Event::MouseButtonPressed)
		{
			if (pMainEvent->key.code == sf::Mouse::Button::Left)
			{
				if (hover_tavern && !m_dungeon && !m_tavern)
				{
					m_tavern = true;
					m_dungeon = false;
					m_screen = false;
				}			
				else if (m_dungeon_browser && !m_dungeon && !m_tavern)
				{
					hardcore_btn();
					diffi_btn();
					btn_exit_dungeon();
					btn_go_dungeon();
				}
				else if (m_tavern)
				{
					p_tavern->event();
				}
				exit_btn();
			}
		}
	}
}

void main_frame::render()
{
	pRenderWindow->clear();
	if (m_dungeon)
	{
		if (!pDungeonManager->check_dungeon()) {
			pRenderWindow->draw(*pSky);
			if (!hover_portal) {
				pRenderWindow->draw(*pClouds);
				pRenderWindow->draw(*pClouds2);
			}
			pRenderWindow->draw(*pSprite);
			pRenderWindow->draw(*pTaverne);
			pRenderWindow->draw(*pDungeonPortal);
			if (hover_tavern)
			{
				pRenderWindow->draw(*pTaverne_Hover);
			}
		}
		else if (pDungeonManager->check_dungeon())
		{
			pEnviromentLoader->render_enviro(pDungeonManager->enviroment_id(), pRenderWindow);
			if(!m_screen)
				pDungeonManager->render(pRenderWindow);
		}
	}
	else if (m_screen)
	{
		pRenderWindow->draw(*pSky);
		if (!hover_portal) {
			pRenderWindow->draw(*pClouds);
			pRenderWindow->draw(*pClouds2);
		}
		pRenderWindow->draw(*pSprite);
		pRenderWindow->draw(*pTaverne);
		pRenderWindow->draw(*pDungeonPortal);
		if (hover_tavern)
		{
			pRenderWindow->draw(*pTaverne_Hover);
		}
	}
	else if (m_tavern)
	{
		p_tavern->render(pRenderWindow);
	}
	ui_render();
	pRenderWindow->draw(pText);
	pRenderWindow->display();
}

void main_frame::ui_render()
{
	pRenderWindow->draw(*pBtn[0]);
	pRenderWindow->draw(*pBtn[1]);
	pRenderWindow->draw(*pBtn[2]);

	if (m_dungeon_browser && !m_dungeon && !m_tavern)
	{
		pRenderWindow->draw(*p_Dungeon_Browser[5]);
		pRenderWindow->draw(*p_Dungeon_Browser[2]);
		pRenderWindow->draw(*p_Dungeon_Browser_Title);
		//pRenderWindow->draw(*p_Dungeon_Browser[5]);
		pRenderWindow->draw(*p_Dungeon_Browser[0]);
		pRenderWindow->draw(*p_Dungeon_Browser[1]);
		pRenderWindow->draw(*p_Dungeon_Browser[3]);
		pRenderWindow->draw(*p_Dungeon_Browser[4]);
		pRenderWindow->draw(*p_Dungeon_Browser_Diffi);
		pRenderWindow->draw(*p_Dungeon_Browser_EmpowerdText);
	}


}

void main_frame::m_frametime()
{
	m_frame_time = pClock->getElapsedTime().asSeconds();
	pClock->restart();
}

void main_frame::tavern_hover()
{
	if (m_pos.x > tavern_coords[0] && m_pos.x <= tavern_coords[2] && !m_dungeon_browser && !m_tavern)
		{
		if (m_pos.y >= tavern_coords[1] && m_pos.y <= tavern_coords[3])
		{
			hover_tavern = true;
		}
		else
		{
			hover_tavern = false;
		}
	}
	else
	{
		hover_tavern = false;
	}
}

void main_frame::life_clouds()
{
	if (pClouds->getPosition().x >= main.x)
	{
		pClouds->setPosition(0- main.x, pClouds->getPosition().y);
	}
	else if (pClouds->getPosition().x <  main.x)
	{
		pClouds->setPosition(pClouds->getPosition().x + 30 * m_frame_time, pClouds->getPosition().y);
	}
	if (pClouds2->getPosition().x >= main.x)
	{
		pClouds2->setPosition(0 - main.x, pClouds2->getPosition().y);
	}
	else if (pClouds2->getPosition().x < main.x)
	{
		pClouds2->setPosition(pClouds2->getPosition().x + 30 * m_frame_time, pClouds2->getPosition().y);
	}
}

void main_frame::dungeon_rotate()
{
	pDungeonPortal->rotate(0.5);

	if (m_pos.x > portal_coords[0] - 100 && m_pos.x <= portal_coords[2] && !m_tavern || m_dungeon_browser)
	{
		if (m_pos.y >= portal_coords[1] * 1.5 - pDungeonProtal_T->getSize().y / 2 && m_pos.y <= portal_coords[3] || m_dungeon_browser)
		{
			hover_portal = true;
			pSprite->setTexture(*pPortal_T_Hover);
			pSky->setTexture(*pPortal_Sky_Hover);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				m_dungeon_browser = true;
			}
		}
		else
		{
			hover_portal = false;
			pSprite->setTexture(*pBackground);
			pSky->setTexture(*pSky_Texture);
		}
	}
	else
	{
		hover_portal = false;
		pSprite->setTexture(*pBackground);
		pSky->setTexture(*pSky_Texture);
	}

}

void main_frame::exit_dungeon()
{
	m_dungeon = false;
	delete pDungeonManager;
	pDungeonManager = nullptr;
	m_screen = true;
}

void main_frame::exit_btn()
{
	if (osm::sprite_pressed(pBtn[0], m_pos))
	{
		if (m_dungeon)
		{
			exit_dungeon();
		}
		else if (m_screen)
		{
			m_run = false;
		}
		else if (m_tavern && !p_tavern->o_menu())
		{
			m_tavern = false;
			m_screen = true;
		}
	}
}

void main_frame::hardcore_btn()
{
	if (osm::sprite_pressed(p_Dungeon_Browser[4], m_pos))
		{
		if (m_dungeon_hardcore)
		{
			m_dungeon_hardcore = false;
			p_Dungeon_Browser[4]->setTexture(*p_Dungeon_Browser_T[4]);
		}
		else if (!m_dungeon_hardcore)
		{
			m_dungeon_hardcore = true;
			p_Dungeon_Browser[4]->setTexture(*p_Dungeon_Browser_T[3]);
		}
		}
}

void main_frame::diffi_btn()
{
	//p_Dungeon_Browser[1]
	if (osm::sprite_pressed(p_Dungeon_Browser[0],m_pos) && difficulty > 1)
	{
		difficulty--;
	}
	else if (osm::sprite_pressed(p_Dungeon_Browser[1], m_pos))
	{
		difficulty++;
	}
}

void main_frame::update_diffi()
{
	if (difficulty == 1)
	{
		p_Dungeon_Browser_Diffi->setString("Leicht");
	}
	else if (difficulty == 2)
	{
		p_Dungeon_Browser_Diffi->setString("Normal");
	}
	else if (difficulty == 3)
	{
		p_Dungeon_Browser_Diffi->setString("Schwer");
	}
	else if (difficulty == 4)
	{
		p_Dungeon_Browser_Diffi->setString("Mystisch");
	}
	else if (difficulty > 4)
	{
		p_Dungeon_Browser_Diffi->setString("Mystisch " + std::to_string(difficulty-4));
	}
}

void main_frame::btn_exit_dungeon()
{
	if (osm::sprite_pressed(p_Dungeon_Browser[2], m_pos))
	{
		m_dungeon_browser = false;
	}
}

void main_frame::btn_go_dungeon()
{
	if (osm::sprite_pressed(p_Dungeon_Browser[3], m_pos))
	{
		m_dungeon_browser = false;
		pDungeonManager = new dungeon_manager(difficulty, main_path, p_memory_allocator);
		m_dungeon = true;
		m_screen = false;
	}
}

void main_frame::create_dungeon_browser()
{
	for (auto i_l = 0; i_l < 7; i_l++)
	{
		p_Dungeon_Browser_T[i_l] = new sf::Texture;
		p_Dungeon_Browser_T[i_l]->loadFromMemory(&p_memory_allocator->get_memory_data("dbtn" + std::to_string(i_l + 1))[0], p_memory_allocator->get_memory_data("dbtn" + std::to_string(i_l + 1)).size());
		p_Dungeon_Browser[i_l] = new sf::Sprite;
	}



	p_Dungeon_Browser[0]->setTexture(*p_Dungeon_Browser_T[0]); // Diffi Pfeil
	p_Dungeon_Browser[1]->setTexture(*p_Dungeon_Browser_T[0]); // Diffi Pfeil Andere Reichtung
	p_Dungeon_Browser[1]->setScale(1.3f, -1.f);
	p_Dungeon_Browser[2]->setTexture(*p_Dungeon_Browser_T[1]); // close btn
	p_Dungeon_Browser[3]->setTexture(*p_Dungeon_Browser_T[2]); // start btn
	p_Dungeon_Browser[4]->setTexture(*p_Dungeon_Browser_T[4]); // check true
	p_Dungeon_Browser[5]->setTexture(*p_Dungeon_Browser_T[5]); //bg
	p_Dungeon_Browser[6]->setTexture(*p_Dungeon_Browser_T[6]); // bg text


	p_Dungeon_Browser_Title = new sf::Text;
	p_Dungeon_Browser_Diffi = new sf::Text;
	p_Dungeon_Browser_MenuText = new sf::Text;
	p_Dungeon_Browser_EmpowerdText = new sf::Text;

	p_Dungeon_Browser_Title->setFont(*pFont);
	p_Dungeon_Browser_Diffi->setFont(*pFont);
	p_Dungeon_Browser_MenuText->setFont(*pFont);
	p_Dungeon_Browser_EmpowerdText->setFont(*pFont);


	p_Dungeon_Browser[5]->setOrigin(p_Dungeon_Browser_T[5]->getSize().x / 2.f, p_Dungeon_Browser_T[5]->getSize().y / 2.f);
	p_Dungeon_Browser[5]->setPosition(main.x / 2.f, main.y / 2.f);
	p_Dungeon_Browser[5]->setScale(1.5f, 1.5f);

	p_Dungeon_Browser_Title->setPosition(p_Dungeon_Browser[5]->getPosition().x - 82.f, p_Dungeon_Browser[5]->getPosition().y - 130.f);
	p_Dungeon_Browser_Title->setCharacterSize(21);
	p_Dungeon_Browser_Title->setString("Dungeon Browser");

	p_Dungeon_Browser_Diffi->setPosition(p_Dungeon_Browser[5]->getPosition().x - 127.f, p_Dungeon_Browser[5]->getPosition().y - 50.f);
	p_Dungeon_Browser_Diffi->setCharacterSize(21);
	p_Dungeon_Browser_Diffi->setString("Leicht");

	p_Dungeon_Browser[1]->setPosition(p_Dungeon_Browser[5]->getPosition().x - 167.f, p_Dungeon_Browser[5]->getPosition().y - 50.f);
	p_Dungeon_Browser[0]->setPosition(p_Dungeon_Browser[1]->getPosition().x, p_Dungeon_Browser[1]->getPosition().y + 30.f);
	p_Dungeon_Browser[0]->setScale(1.3f, 1.f);

	p_Dungeon_Browser[2]->setPosition(p_Dungeon_Browser[5]->getPosition().x + 155.f, p_Dungeon_Browser[5]->getPosition().y - 132.f);

	p_Dungeon_Browser[3]->setPosition(p_Dungeon_Browser[5]->getPosition().x - 75.f, p_Dungeon_Browser[5]->getPosition().y + 70.f);

	p_Dungeon_Browser_EmpowerdText->setPosition(p_Dungeon_Browser[5]->getPosition().x + 15.f, p_Dungeon_Browser[5]->getPosition().y - 90.f);
	p_Dungeon_Browser_EmpowerdText->setCharacterSize(21);
	p_Dungeon_Browser_EmpowerdText->setString("Hardcore Mode");

	p_Dungeon_Browser[4]->setPosition(p_Dungeon_Browser_EmpowerdText->getPosition().x + 50.f, p_Dungeon_Browser_EmpowerdText->getPosition().y + 30.f);
}





/////Enviroment SYSTEM Thread 1 //////////

void main_frame::enviroment()
{
	osm::t_s_ms(20);
	life_clouds();
	dungeon_rotate();
}



/////DATENBANK SYSTEM Thread 2 //////////


void main_frame::datenbank()
{
	p_data->run();
}