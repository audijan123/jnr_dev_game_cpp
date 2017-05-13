#include "main_frame.hpp"

main_frame::main_frame(std::string const &path) :
	main_path(path.substr(0, path.length() - 27))
{
	p_data = new main_data(main_path);

	p_memory_allocator = new JNR::main_base(main_path);

	
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.antialiasingLevel = 1;
	contextSettings.majorVersion = 4;
	contextSettings.minorVersion = 5;

	pRenderWindow = new sf::RenderWindow(sf::VideoMode(main_x, main_y, 64), "Lord of the dark Travern",sf::Style::Default);
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
	pSprite->setScale(2.67, 2.85);

	/// Tavern 

	pTextureTaverne = new sf::Texture;
	pTextureTaverne->loadFromMemory(&p_memory_allocator->get_memory_data("taver")[0], p_memory_allocator->get_memory_data("taver").size());
	pTaverne = new sf::Sprite;
	pTaverne->setTexture(*pTextureTaverne);
	pTaverne->setPosition(tavern_coords[0], tavern_coords[1]);
	pTaverne->setScale(2.67, 2.85);

	tavern_coords[2] = pTextureTaverne->getSize().x*2.67 + tavern_coords[0];
	tavern_coords[3] = pTextureTaverne->getSize().y*2.85 + tavern_coords[1];



	//Hover Tavern/////////////////////

	pImageTavern_Hover = new sf::Image;
	pImageTavern_Hover->loadFromFile(main_path + "DATA/resource/hover_tavern.png");
	pImageTavern_Hover->createMaskFromColor(sf::Color(0, 0, 10, 20));
	pTextureTaverne_Hover = new sf::Texture;
	pTextureTaverne_Hover->loadFromImage(*pImageTavern_Hover);
	pTaverne_Hover = new sf::Sprite;
	pTaverne_Hover->setTexture(*pTextureTaverne_Hover);
	pTaverne_Hover->setPosition(tavern_coords[0]+95, tavern_coords[1]+105);
	pTaverne_Hover->setScale(2.67, 2.85);
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
	pSky->setScale(2.67, 2.85);
	pClouds->setTexture(*pClouds_Texture);
	pClouds->setScale(1.5, 1.2);

	pClouds2->setTexture(*pClouds_Texture);
	pClouds2->setScale(1.5, 1.2);
	pClouds2->setPosition(0-1200,0);


	// Enviroment Loader ///
	pEnviromentLoader = new enviroment_loader(main_path);



	// Dungeon Portal //
	pDungeonProtal_T = new sf::Texture;
	pDungeonPortal = new sf::Sprite;

	pDungeonProtal_T->loadFromFile(main_path + "DATA/resource/portal.png");

	pDungeonPortal->setTexture(*pDungeonProtal_T);
	pDungeonPortal->setOrigin(pDungeonProtal_T->getSize().x / 2, pDungeonProtal_T->getSize().y / 2);
	pDungeonPortal->setPosition(portal_coords[0], portal_coords[1]);
	pDungeonPortal->setScale(0.5, 0.5);

	portal_coords[2] = pDungeonProtal_T->getSize().x*0.20 + portal_coords[0];
	portal_coords[3] = pDungeonProtal_T->getSize().y*0.19 + portal_coords[1];

	// Dungeon Portal Hover //

	pPortal_T_Hover = new sf::Texture;
	pPortal_T_Hover->loadFromFile(main_path + "DATA/resource/portal_hover.png");
	pPortal_Sky_Hover = new sf::Texture;
	pPortal_Sky_Hover->loadFromFile(main_path + "DATA/resource/sky_hover.png");




	// Option BTNS
	pBtn[0] = new sf::Sprite;
	pBtn[1] = new sf::Sprite;
	pBtn[2] = new sf::Sprite;

	pBtn_T[0] = new sf::Texture;
	pBtn_T[1] = new sf::Texture;
	pBtn_T[2] = new sf::Texture;


	pBtn_T[0]->loadFromFile(main_path + "DATA/resource/btn/btn_exit.png");
	pBtn_T[1]->loadFromFile(main_path + "DATA/resource/btn/btn_settings.png");
	pBtn_T[2]->loadFromFile(main_path + "DATA/resource/btn/btn_patrons.png");

	pBtn[0]->setTexture(*pBtn_T[0]);
	pBtn[1]->setTexture(*pBtn_T[1]);
	pBtn[2]->setTexture(*pBtn_T[2]);

	pBtn[0]->setPosition(btn[0], btn[3]);
	pBtn[1]->setPosition(btn[1], btn[3]);
	pBtn[2]->setPosition(btn[2], btn[3]);

	pBtn[0]->setScale(1.7, 1.7);
	pBtn[1]->setScale(1.7, 1.7);
	pBtn[2]->setScale(1.7, 1.7);


	// Dungeon Browser Menu //
	create_dungeon_browser();


	

	m_scale = 800 / main_x;

	p_tavern = new tavern_main(main_path);


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

		//enviroment //
		tavern_hover();
		//life_clouds();
		//dungeon_rotate();

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
	}
}

void main_frame::update()
{
	if (m_pause == false)
	{
		a_frametime = 1.f / m_frame_time;
		pText.setString(std::to_string(a_frametime));

		mouse_x = sf::Mouse::getPosition().x-8-pRenderWindow->getPosition().x;
		mouse_y = sf::Mouse::getPosition().y-32-pRenderWindow->getPosition().y;
		p_tavern->update(m_frame_time);
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
				exit_btn();
				if (m_dungeon_browser && !m_dungeon && !m_tavern)
				{
					hardcore_btn();
					diffi_btn();
					btn_exit_dungeon();
					btn_go_dungeon();
				}
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
		pRenderWindow->draw(*p_Dungeon_Browser[6]);
		pRenderWindow->draw(*p_Dungeon_Browser[2]);
		pRenderWindow->draw(*p_Dungeon_Browser_Title);
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
	if (mouse_x > tavern_coords[0] && mouse_x <= tavern_coords[2] && !m_dungeon_browser && !m_tavern)
		{
		if (mouse_y >= tavern_coords[1] && mouse_y <= tavern_coords[3])
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
	if (pClouds->getPosition().x >= main_x)
	{
		pClouds->setPosition(0- main_x, pClouds->getPosition().y);
	}
	else if (pClouds->getPosition().x <  main_x)
	{
		pClouds->setPosition(pClouds->getPosition().x + 30 * m_frame_time, pClouds->getPosition().y);
	}
	if (pClouds2->getPosition().x >= main_x)
	{
		pClouds2->setPosition(0 - main_x, pClouds2->getPosition().y);
	}
	else if (pClouds2->getPosition().x < main_x)
	{
		pClouds2->setPosition(pClouds2->getPosition().x + 30 * m_frame_time, pClouds2->getPosition().y);
	}
}

void main_frame::dungeon_rotate()
{
	pDungeonPortal->rotate(0.5);

	if (mouse_x > portal_coords[0] - 100 && mouse_x <= portal_coords[2] && !m_tavern || m_dungeon_browser)
	{
		if (mouse_y >= portal_coords[1] * 1.5 - pDungeonProtal_T->getSize().y / 2 && mouse_y <= portal_coords[3] || m_dungeon_browser)
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
	if (mouse_x > btn[0] && mouse_x <= btn[0] + 50)
	{
		if (mouse_y >= btn[3] && mouse_y <= btn[3] + 55)
		{
			if (m_dungeon)
			{
				exit_dungeon();
			}
			else if (m_screen)
			{
				m_run = false;
			}
			else if (m_tavern)
			{
				m_tavern = false;
				m_screen = true;
			}
		}
	}
}

void main_frame::hardcore_btn()
{
	if (mouse_x > p_Dungeon_Browser[4]->getPosition().x && mouse_x <= p_Dungeon_Browser[4]->getPosition().x + 50)
	{
		if (mouse_y >= p_Dungeon_Browser[4]->getPosition().y && mouse_y <= p_Dungeon_Browser[4]->getPosition().y + 55)
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
}

void main_frame::diffi_btn()
{
	//p_Dungeon_Browser[1]

	if (mouse_x > p_Dungeon_Browser[1]->getPosition().x+10 && mouse_x <= p_Dungeon_Browser[1]->getPosition().x + 130)
	{
		if (mouse_y >= p_Dungeon_Browser[1]->getPosition().y+30 && mouse_y <= p_Dungeon_Browser[1]->getPosition().y + 55 && difficulty > 1)
		{
			difficulty--;
		}
		if (mouse_y <= p_Dungeon_Browser[1]->getPosition().y - 7 && mouse_y >= p_Dungeon_Browser[1]->getPosition().y - 37)
		{
			difficulty++;
		}
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
	if (mouse_x > p_Dungeon_Browser[2]->getPosition().x&& mouse_x <= p_Dungeon_Browser[2]->getPosition().x + 27)
	{
		if (mouse_y >= p_Dungeon_Browser[2]->getPosition().y && mouse_y <= p_Dungeon_Browser[2]->getPosition().y + 27)
		{
			m_dungeon_browser = false;
		}
	}
}

void main_frame::btn_go_dungeon()
{
	if (mouse_x > p_Dungeon_Browser[3]->getPosition().x&& mouse_x <= p_Dungeon_Browser[3]->getPosition().x + 168)
	{
		if (mouse_y >= p_Dungeon_Browser[3]->getPosition().y && mouse_y <= p_Dungeon_Browser[3]->getPosition().y + 50)
		{
			m_dungeon_browser = false;
			pDungeonManager = new dungeon_manager(difficulty, main_path, p_memory_allocator);
			m_dungeon = true;
			m_screen = false;
		}
	}
}

void main_frame::create_dungeon_browser()
{
	p_Dungeon_Browser_T[0] = new sf::Texture;
	p_Dungeon_Browser_T[1] = new sf::Texture;
	p_Dungeon_Browser_T[2] = new sf::Texture;
	p_Dungeon_Browser_T[3] = new sf::Texture;
	p_Dungeon_Browser_T[4] = new sf::Texture;
	p_Dungeon_Browser_T[5] = new sf::Texture;
	p_Dungeon_Browser_T[6] = new sf::Texture;

	p_Dungeon_Browser_T[0]->loadFromFile(main_path + "DATA/dungeon/browser/arrow_level_select.png");
	p_Dungeon_Browser_T[1]->loadFromFile(main_path + "DATA/dungeon/browser/btn_close_small.png");
	p_Dungeon_Browser_T[2]->loadFromFile(main_path + "DATA/dungeon/browser/btn_go.png");
	p_Dungeon_Browser_T[3]->loadFromFile(main_path + "DATA/dungeon/browser/check_checked.png");
	p_Dungeon_Browser_T[4]->loadFromFile(main_path + "DATA/dungeon/browser/check_unchecked.png");
	p_Dungeon_Browser_T[5]->loadFromFile(main_path + "DATA/dungeon/browser/menu_backing_save_files.png");
	p_Dungeon_Browser_T[6]->loadFromFile(main_path + "DATA/dungeon/browser/shadow.png");

	p_Dungeon_Browser[0] = new sf::Sprite;
	p_Dungeon_Browser[1] = new sf::Sprite;
	p_Dungeon_Browser[2] = new sf::Sprite;
	p_Dungeon_Browser[3] = new sf::Sprite;
	p_Dungeon_Browser[4] = new sf::Sprite;
	p_Dungeon_Browser[6] = new sf::Sprite;
	p_Dungeon_Browser[5] = new sf::Sprite;

	p_Dungeon_Browser[0]->setTexture(*p_Dungeon_Browser_T[0]); // Diffi Pfeil
	p_Dungeon_Browser[1]->setTexture(*p_Dungeon_Browser_T[0]); // Diffi Pfeil Andere Reichtung
	p_Dungeon_Browser[1]->setScale(1.3, -1);
	p_Dungeon_Browser[2]->setTexture(*p_Dungeon_Browser_T[1]); // close btn
	p_Dungeon_Browser[3]->setTexture(*p_Dungeon_Browser_T[2]); // start btn
	p_Dungeon_Browser[4]->setTexture(*p_Dungeon_Browser_T[4]); // check true
	p_Dungeon_Browser[6]->setTexture(*p_Dungeon_Browser_T[5]); //bg
	p_Dungeon_Browser[5]->setTexture(*p_Dungeon_Browser_T[6]); // bg text


	p_Dungeon_Browser_Title = new sf::Text;
	p_Dungeon_Browser_Diffi = new sf::Text;
	p_Dungeon_Browser_MenuText = new sf::Text;
	p_Dungeon_Browser_EmpowerdText = new sf::Text;

	p_Dungeon_Browser_Title->setFont(*pFont);
	p_Dungeon_Browser_Diffi->setFont(*pFont);
	p_Dungeon_Browser_MenuText->setFont(*pFont);
	p_Dungeon_Browser_EmpowerdText->setFont(*pFont);


	p_Dungeon_Browser[6]->setOrigin(p_Dungeon_Browser_T[5]->getSize().x / 2, p_Dungeon_Browser_T[5]->getSize().y / 2);
	p_Dungeon_Browser[6]->setPosition(main_x / 2, main_y / 2);
	p_Dungeon_Browser[6]->setScale(1.5, 1.5);

	p_Dungeon_Browser_Title->setPosition(p_Dungeon_Browser[6]->getPosition().x - 82, p_Dungeon_Browser[6]->getPosition().y - 130);
	p_Dungeon_Browser_Title->setCharacterSize(21);
	p_Dungeon_Browser_Title->setString("Dungeon Browser");

	p_Dungeon_Browser_Diffi->setPosition(p_Dungeon_Browser[6]->getPosition().x - 127, p_Dungeon_Browser[6]->getPosition().y - 50);
	p_Dungeon_Browser_Diffi->setCharacterSize(21);
	p_Dungeon_Browser_Diffi->setString("Leicht");

	p_Dungeon_Browser[1]->setPosition(p_Dungeon_Browser[6]->getPosition().x - 167, p_Dungeon_Browser[6]->getPosition().y - 50);
	p_Dungeon_Browser[0]->setPosition(p_Dungeon_Browser[1]->getPosition().x, p_Dungeon_Browser[1]->getPosition().y + 30);
	p_Dungeon_Browser[0]->setScale(1.3, 1);

	p_Dungeon_Browser[2]->setPosition(p_Dungeon_Browser[6]->getPosition().x + 155, p_Dungeon_Browser[6]->getPosition().y - 132);

	p_Dungeon_Browser[3]->setPosition(p_Dungeon_Browser[6]->getPosition().x - 75, p_Dungeon_Browser[6]->getPosition().y + 70);

	p_Dungeon_Browser_EmpowerdText->setPosition(p_Dungeon_Browser[6]->getPosition().x + 15, p_Dungeon_Browser[6]->getPosition().y - 90);
	p_Dungeon_Browser_EmpowerdText->setCharacterSize(21);
	p_Dungeon_Browser_EmpowerdText->setString("Hardcore Mode");

	p_Dungeon_Browser[4]->setPosition(p_Dungeon_Browser_EmpowerdText->getPosition().x + 50, p_Dungeon_Browser_EmpowerdText->getPosition().y + 30);
}




































/////Enviroment SYSTEM Thread 1 //////////

void main_frame::enviroment()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	life_clouds();
	dungeon_rotate();
}



/////DATENBANK SYSTEM Thread 2 //////////


void main_frame::datenbank()
{
	p_data->run();
}