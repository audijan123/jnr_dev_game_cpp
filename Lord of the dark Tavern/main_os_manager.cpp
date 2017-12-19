#include "main_os_manager.hpp"
using namespace std;

namespace osm
{
	

	void call(const string &text)
	{
		cout << text << endl;
	}

	int si(const string &text)
	{
		return stoi(text);
	}

	uint8_t sB(const string &text)
	{
		return static_cast<uint8_t>(stoi(text));
	}

	void t_s_ms(const short &ms)
	{
		this_thread::sleep_for(chrono::milliseconds(ms));
	}

	bool sprite_pressed(const sf::Sprite *sprite,const sf::Vector2f &m)
	{
		return sprite->getGlobalBounds().contains(m);
	}

	int genZufallsZahl()
	{
		std::time_t now;
		now = std::time(0);
		boost::random::mt19937 rng{ static_cast<std::uint32_t>(now) };;
		int buff = rng()*rand();
		return buff;
	}

	int genZufallsZahl(const int& min,const int& rnd)
	{
		std::time_t now;
		now = std::time(0);
		boost::random::mt19937 rng{ static_cast<std::uint32_t>(now) };;
		int buff = rng()*rnd+min;
		return buff;
	}

	int genZufallsZahl(const int& min ,const int& max, const int& rnd)
	{
		std::time_t now;
		now = std::time(0);
		boost::random::mt19937 rng{ static_cast<std::uint32_t>(now) };;
		int buff = (rng()*rnd)%(max-min) + min;
		return buff;
	}

	std::string convertEnumToString(const GAMESTRUCTS::item_rare& r)
	{
		switch (r)
		{
		case GAMESTRUCTS::NORMAL:
			return "{Normal}";
			break;
		case GAMESTRUCTS::BESONDERS:
			return "{Besonders}";
			break;
		case GAMESTRUCTS::SELTEN:
			return "{Selten}";
			break;
		case GAMESTRUCTS::SEHRSELTEN:
			return "{SehrSelten}";
			break;
		case GAMESTRUCTS::EPISCH:
			return "{Episch}";
			break;
		case GAMESTRUCTS::LEGENDAER:
			return "{Legendär}";
			break;
		case GAMESTRUCTS::MYSTISCH:
			return "{Mystisch}";
			break;
		default:
			return "{Normal}";
			break;
		}
	}

	std::wstring s2ws(const std::string& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}
}