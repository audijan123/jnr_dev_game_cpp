#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "main_os_manager.hpp"
#include "main_base.hpp"
#include "main_os_manager.hpp"
#include "datenbank_main.hpp"
#include "generate_items.hpp"


class tavern_main
{
public:
	tavern_main(std::string const &path, const JGE::main_base* pbase, const sf::Vector2f &main);
	~tavern_main();


	void update(const sf::Vector2f &m_posi);

	void render(sf::RenderWindow *rw);
	void event_get_key( sf::Event *pollevent);

	bool o_menu();

	void event();

	void test_func();
	

private:

	enum gold_set
	{
		positiv,
		negativ,
		init
	};

	gen_item *item_gen;
	std::vector<main_data::item_data> item_list;


	uint8_t items_per_site_max = 14;
	uint8_t site_max = 10;

	struct item_site
	{
		uint8_t items_per_site = 0;
		std::vector<main_data::item_data> items;

	};

	gold_set status = init;

	void create_main();
	void create_safe();




	void create_sellman();
	sf::Texture *item_shop_texture[12];
	sf::Sprite *item_shop_sprites[13];
	bool item_shop = false;
	bool bonus_memu = false;

	sf::Text site;
	int max = 10;


	sf::Texture *item_sprite_t[3];
	sf::Sprite *item_sprite[31];


	void create_mage();


	void check_mage();
	void check_sellman();
	void check_safe();

	sf::Vector2f m_pos;
	sf::Vector2f main;

	sf::Font *pfont;
	sf::Text banking_text;
	sf::Text current_gold;


	short buffer = 0;
	std::string bank_Set_gold;
	sf::Text set_gold;

	bool banking = false;
	bool u_menu = false;
	bool edit_gold = false;
	bool cap_menu = false;

	std::string m_path;

	sf::Texture *bg_tavern;
	sf::Texture *floor_tavern;
	sf::Texture *counter_tavern;
	sf::Texture *sell_man_t[4];
	sf::Image test_image;
	sf::Texture *mage_t[4];

	sf::Sprite *p_sell_man;
	sf::Sprite *p_mage;
	
	
	sf::Sprite *p_safe[6];
	sf::Texture *safe_t[6];
	sf::Texture *banking_t[7];
	sf::Sprite *p_banking[7];

	sf::Sprite *main_sprites[4];

	sf::Vector2f scale = { 2.67f,2.85f };
	JGE::main_base p_memory_allocator;

	sf::RectangleShape rectangle[4];

	short activ_safe = 0;

};
