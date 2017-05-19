#pragma once

#include <iostream>
#include <string>
#include <boost/random.hpp>
#include <ctime>
#include <cstdint>
#include <SFML\Graphics.hpp>
#include <Vector>
#include "main_base.hpp"
#include "enviroment_loader.hpp"


class dungeon_manager
{
public:
	dungeon_manager(const int &m_power,const std::string &path,const JGE::main_base* pbase);
	~dungeon_manager();


	bool check_dungeon() { return dungeon_atkiv; };
	int enviroment_id() { return enviro_id; };


	void render(sf::RenderWindow *rw) const;


private:


	void fill_dungeon();
	

	int diffculty = 1;
	int floors = 0;
	int floor_a = 0;
	int enviro_id = 0;
	bool dungeon_atkiv = false;

	JGE::main_base p_memory_allocator;


	//Hintergrund Lader
	enviroment_loader	*pHintergrundLader;

	sf::Font *pfont;
	struct mob
	{
		sf::Sprite *p_sprite = new sf::Sprite;
		sf::Vector2f scale;
		sf::Sprite *p_life = new sf::Sprite;

		sf::Text *text = new sf::Text;

		int life = 10;
		int dmg = 10;
	};

	std::string m_path;

	std::time_t now;
	sf::Texture *p_life_t;
	sf::Texture *p_texture_t;
	sf::Image *image;
	std::vector<sf::Texture*> p_texture;
	std::vector<struct mob> mob_this_dungeons;


	std::vector<int> mob_per_floor;



};