#include "resource_loader.hpp"


re_loader::re_loader(std::string m_path)
{

	sf::Image image;
	std::string dev2 = "/";
	std::string dev1 = "\\";
	for (int i = 0; i < m_path.length(); i++)
	{
		if (m_path[i] == dev1[0])
		{
			m_path[i] = dev2[0];
		}
	}



	while (c_ord != 6)
	{
		if (c_ord == 0)
		{
			work_dir = m_path + "DATA/mob/cave/*";
		}
		else if (c_ord == 1)
		{
			work_dir = m_path + "DATA/mob/fire/*";
		}
		else if (c_ord == 2)
		{
			work_dir = m_path + "DATA/mob/ice/*";
		}
		else if (c_ord == 3)
		{
			work_dir = m_path + "DATA/mob/void/*";
		}
		else if (c_ord == 4)
		{
			work_dir = m_path + "DATA/mob/water/*";
		}
		else if (c_ord == 5)
		{
			work_dir = m_path + "DATA/symbols/*";
		}

		//std::cout << work_dir << std::endl;

		std::wstring stemp = s2ws(work_dir);
		LPCWSTR result = stemp.c_str();


		fHandle = FindFirstFile(result, &wfd);

		do
		{
			// Eintrag nur behandeln, wenn es nicht . oder .. ist (werden nur bei Unterverzeichnissen mit zurückgeliefert) 
			// hier könnte man z.B. auch mit lstrcmp auf . und .. vergleichen, was allerdings nicht ganz so effizient ist 
			if (!((wfd.cFileName[0] == '.') && ((wfd.cFileName[1] == '.' && wfd.cFileName[2] == 0) || wfd.cFileName[1] == 0)))
			{
				//MessageBox(0, wfd.cFileName, LPCWSTR(L"Folgende Datei gefunden:"), 0);

				std::wstring ws(wfd.cFileName);
				std::string str_dev(ws.begin(), ws.end());
				//std::cout << work_dir.substr(0, work_dir.size() - 1) + str_dev << std::endl;
				mob_data.push_back(new sf::Image);
				mob_data[p]->loadFromFile(work_dir.substr(0, work_dir.size() - 1) + str_dev);
				p++;

			}
		} while (FindNextFile(fHandle, &wfd));
		FindClose(fHandle);
		c_ord++;
	}
}

re_loader::~re_loader()
{
}


std::wstring re_loader::s2ws(const std::string& s)
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