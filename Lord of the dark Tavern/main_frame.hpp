#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "dungeon_manager.hpp"
#include "enviroment_loader.hpp"
#include "resource_loader.hpp"
#include <thread>
#include <chrono>
#include "datenbank_main.hpp"
#include "tavern_main.hpp"
#include "main_base.hpp"

class main_frame
{
public:
	sf::Vector2f main = { 1280.f,768.f };

	main_frame(std::string const &path);
	~main_frame();
	void run();
	void enviroment();
	void datenbank();

	double get_main_scale() { return m_scale; };

private:

	std::string main_path;
	sf::Vector2f m_pos;

	void quit();
	void render();
	void update();
	void handleEvents();
	void tavern_hover();
	void ui_render();
	void m_frametime();
	void life_clouds();
	void dungeon_rotate();
	void exit_dungeon();
	void exit_btn();
	void hardcore_btn();
	void diffi_btn();
	void update_diffi();
	void btn_exit_dungeon();
	void btn_go_dungeon();
	void create_dungeon_browser();


	float m_frame_time;

	float m_scale = 1;

	int a_frametime;

	int difficulty = 1;


	sf::RenderWindow *pRenderWindow;
	sf::Event		 *pMainEvent;
	sf::Clock		 *pClock;
	sf::Texture		 *pBackground;
	sf::Sprite		 *pSprite;
	sf::Font		 *pFont;

	sf::Text		  pText;


	//// Taverne Render //////
	sf::Image *pImageTavern;
	sf::Sprite *pTaverne;
	sf::Texture *pTextureTaverne;


	//// Taverne Render Hover //////

	sf::Image *pImageTavern_Hover;
	sf::Sprite *pTaverne_Hover;
	sf::Texture *pTextureTaverne_Hover;


	/// Umwelt /////

	sf::Texture *pSky_Texture;
	sf::Texture *pClouds_Texture;
	sf::Sprite *pSky;
	sf::Sprite *pClouds;
	sf::Sprite *pClouds2;


	/// Dungeon /////
	sf::Sprite *pDungeonPortal;
	sf::Texture *pDungeonProtal_T;
	sf::Texture *pPortal_T_Hover;
	sf::Texture *pPortal_Sky_Hover;

	dungeon_manager *pDungeonManager;
	enviroment_loader *pEnviromentLoader;



	/// OPT BTNS ///
	sf::Sprite *pBtn[10];
	sf::Texture *pBtn_T[10];



	/// Dungeon Browser ///

	sf::Texture *p_Dungeon_Browser_T[7];
	sf::Sprite *p_Dungeon_Browser[7];

	sf::Text *p_Dungeon_Browser_Title;
	sf::Text *p_Dungeon_Browser_Diffi;
	sf::Text *p_Dungeon_Browser_MenuText;
	sf::Text *p_Dungeon_Browser_EmpowerdText;


	main_data *p_data;



	/// REsource Loader ///
	re_loader *pLoader;


	/// Taverne ///
	tavern_main *p_tavern;


	JNR::main_base *p_memory_allocator;



	bool m_run = true;
	bool m_screen = true;
	bool m_pause = false;
	bool m_dungeon = false;
	bool m_tavern = false;

	bool m_dungeon_browser = false;


	bool m_dungeon_hardcore = false;

	float tavern_coords[10] = {0,230};

	float portal_coords[10] = { 1100, 390 };


	float btn[10] = { main.x - 50.f,main.x - 100.f,main.x - 150.f,0.f,50.f };

	bool hover_tavern = false;
	bool hover_portal = false;

	

};
