#include "generate_items.hpp"

extern JGE::SpriteGen *pSpriteErsteller;

gen_item::gen_item()
{
}

gen_item::~gen_item()
{
}

std::vector<GAMESTRUCTS::item_data> gen_item::items(GAMESTRUCTS::item_class t)
{
	std::time_t times = std::time(0);
	boost::random::mt19937 dev{ static_cast<std::uint32_t>(times) };;
	std::cout << item_list.size() << "=SIZE";
	int t_rnd = dev()*osm::genZufallsZahl(std::time(0),100000,rand()) % 50 +5;
	for (auto i = 0; i < t_rnd; i++)
	{
		GAMESTRUCTS::item_data buff = {};

		buff.i_rare = get_rare(i,t_rnd);
		buff.cItemColor = GetItemNameColorByRare(buff.i_rare);
		buff.i_class = t;
		buff.i_name = "TEST";
		buff.ItemTexture = get_out_list(t_rnd, i ,osm::genZufallsZahl(1,1000,t_rnd),t);
		buff.i_dmg = get_rnd_number(t_rnd*i, i+ osm::genZufallsZahl(), osm::genZufallsZahl(1, 1000, t_rnd))+10;
		buff.i_leben = get_rnd_number(t_rnd, i, osm::genZufallsZahl(1, 1000, t_rnd))+10;
		buff.i_magie = get_rnd_number(i+osm::genZufallsZahl(), t_rnd, osm::genZufallsZahl(1, 1000, t_rnd)) + 10;
		item_list.push_back(buff);
	}
	return item_list;

}

sf::Texture gen_item::get_out_list(const uint8_t& a,const uint8_t& b , const uint8_t& c,const GAMESTRUCTS::item_class& ItemKlasse)
{
	std::time_t times = std::time(0);
	boost::random::mt19937 dev{ static_cast<std::uint32_t>(times) };;
	std::string sbuff;
	GAMESTRUCTS::ItemTextureBereichsGroeﬂe BereichGroeﬂe = {};
	short ibuff;
	switch (ItemKlasse)
	{
	case GAMESTRUCTS::item_class::ARMOR:
		sbuff = "itp";
		ibuff = BereichGroeﬂe.iR¸stungsGroeﬂe;
		break;
	case GAMESTRUCTS::item_class::WEAPON:
		sbuff = "itw";
		ibuff = BereichGroeﬂe.iWaffenGroeﬂe;
		break;
	case GAMESTRUCTS::item_class::SCHILD:
		sbuff = "its";
		ibuff = BereichGroeﬂe.iSchildGroeﬂe;
		break;
	case GAMESTRUCTS::item_class::SPECIAL:
		sbuff = "ita";
		ibuff = BereichGroeﬂe.iSpezialGroeﬂe;
		break;
	default:
		sbuff = "XXX";
		ibuff = BereichGroeﬂe.iDefault;
		break;
	} 

	long rnd = a*dev()*b*c % ibuff;
	if (rnd < 10)
	{
		return pSpriteErsteller->erstelle_texture(sbuff +"0" + std::to_string(rnd));
	}
	else if (rnd == 0)
	{
		return pSpriteErsteller->erstelle_texture(sbuff+"00");
	}
	else
	{
		return pSpriteErsteller->erstelle_texture(sbuff + std::to_string(rnd));
	}
}

int gen_item::get_rnd_number(const uint8_t& a, const uint8_t& b, const uint8_t& c)
{
	std::time_t times = std::time(0);
	boost::random::mt19937 dev{ static_cast<std::uint32_t>(times) };;

	return (a*dev()*b*c) % 100;

}

GAMESTRUCTS::item_rare gen_item::get_rare(const uint8_t& a, const uint8_t& b)
{
	uint8_t int_buffer = (a*get_rnd_number(osm::genZufallsZahl(),a,b)*b) % 7;
	if (int_buffer == 0)
	{
		return GAMESTRUCTS::item_rare::NORMAL;
	}
	else if (int_buffer == 1)
	{
		return GAMESTRUCTS::item_rare::BESONDERS;
	}
	else if (int_buffer == 2)
	{
		return GAMESTRUCTS::item_rare::SELTEN;
	}
	else if (int_buffer == 3)
	{
		return GAMESTRUCTS::item_rare::SEHRSELTEN;
	}
	else if (int_buffer == 4)
	{
		return GAMESTRUCTS::item_rare::EPISCH;
	}
	else if (int_buffer == 5)
	{
		return GAMESTRUCTS::item_rare::LEGENDAER;
	}
	else if (int_buffer == 6)
	{
		return GAMESTRUCTS::item_rare::MYSTISCH;
	}
	return GAMESTRUCTS::item_rare::NORMAL;
}

sf::Color gen_item::GetItemNameColorByRare(const GAMESTRUCTS::item_rare& r)
{
	GAMESTRUCTS::ItemNameColor ItemColor = {};
	switch (r)
	{
	case GAMESTRUCTS::NORMAL:
		return	ItemColor.Weiﬂ; //White
		break;
	case GAMESTRUCTS::BESONDERS:
		return	ItemColor.hBlau; //hblau
		break;
	case GAMESTRUCTS::SELTEN:
		return	ItemColor.dBlau; //DBlau
		break;
	case GAMESTRUCTS::SEHRSELTEN:
		return	ItemColor.Rot;  //red
		break;
	case GAMESTRUCTS::EPISCH:
		return	ItemColor.Gr¸n; //gr¸n
		break;
	case GAMESTRUCTS::LEGENDAER:
		return	ItemColor.Orange; // Orange
		break;
	case GAMESTRUCTS::MYSTISCH:
		return	ItemColor.hPink; //pink
		break;
	default:
		break;
	}
}
