#include "main_base.hpp"

extern JGE::types::SpielString sPfad;


namespace JGE
{
	main_base::main_base()
	{
		JGE::types::SpielString path1 = sPfad;
		for (int i = 0; i < path1.length(); i++)
		{
			if (path1[i] == boost::filesystem::path::preferred_separator)
			{
				path1[i] = boost::filesystem::path::separator;
			}
		}

		JGE::types::SpielWString stemp = osm::s2ws(path1 + "jnr_data/*");
		LPCWSTR result = stemp.c_str();

		fHandle = FindFirstFile(result, &wfd);

		do
		{
			if (!((wfd.cFileName[0] == '.') && ((wfd.cFileName[1] == '.' && wfd.cFileName[2] == 0) || wfd.cFileName[1] == 0)))
			{
				JGE::types::SpielWString ws(wfd.cFileName);
				JGE::types::SpielString str_dev(ws.begin(), ws.end());

				if (str_dev.length() > 4)
				{
					if (str_dev.substr(str_dev.length() - 4, str_dev.length()) == ".jnr")
					{
						JGE::types::DatenInputStream texture_file{ path1 + "jnr_data/" + str_dev, JGE::types::DatenInputStream::binary };
						std::vector<char> buffer;

						if (texture_file) {
							// get length of file:
							texture_file.seekg(0, texture_file.end);
							const auto length = texture_file.tellg();
							if (!length) {
								std::cerr << "Cannot load zero byte texture file" << std::endl;
							}
							buffer.resize(length); // reserve space

							texture_file.seekg(0, texture_file.beg);
							
							auto start = &*buffer.begin();
							texture_file.read(start, length);
							texture_file.close();
						}
						else {
							std::cerr << "Could not open texture file" << std::endl;
						}

						GAMESTRUCTS::memory_data d_memory_data = {};
						buffer.erase(buffer.begin());
						d_memory_data.t = buffer;
						JGE::types::sEinByteChar buffer_char[5] = {};
						found = false;
						JGE::types::uEinByte i = 0;
						JGE::types::uEinByte u_k = 0;
						while (!found)
						{
							if (buffer[buffer.size() - i] == '#')
							{
							for (short k = iMaxCheckRadius; k > 0; k--)
								{
									if (static_cast<int>(buffer[buffer.size() - (i + k)] - 1) >= ASCII::iCharA && static_cast<int>(buffer[buffer.size() - (i + k)] - 1) <= ASCII::iCharZ || static_cast<int>(buffer[buffer.size() - (i + k)]-1) >= ASCII::iChar0 && static_cast<int>(buffer[buffer.size() - (i + k)]-1) <= ASCII::iChar9)
									{
										buffer_char[u_k] = buffer[buffer.size() - (i + k)] - 1;
										u_k++;
									}
								}
								found = true;
							}
							else
							{
								i++;
							}
						}
						std::string dev_buffer(buffer_char);
						d_memory_data.name = dev_buffer;
						d_data.push_back(d_memory_data);
						buffer.clear();
					}
				}
			}
		} while (FindNextFile(fHandle, &wfd));
		FindClose(fHandle);
		
		vSetSizeOfMobData();

	}

	main_base::~main_base()
	{
	}

	std::vector<char> main_base::get_memory_data(const std::string& name) const
	{
		for (int i = 0; i < d_data.size(); i++)
		{
			if (d_data[i].name == name)
			{
				return d_data[i].t;
			}
		}
		return d_data[0].t;
	}

	std::vector<char> main_base::get_memory_data(std::string name,const int& rnd) const
	{
		JGE::types::SpielString buffer_int = std::to_string(rnd);
		name += buffer_int.substr(1,buffer_int.length());
		for (int i = 0; i < d_data.size(); i++)
		{
			if (d_data[i].name == name)
			{
				return d_data[i].t;
			}
		}
		return d_data[0].t;
	}

	inline void main_base::vSetSizeOfMobData()
	{
		for (auto t = d_data.size(); t != 0; t--)
		{
			if (d_data[t-1].name.substr(0, d_data[t-1].name.length() - 2) == "mob")
			{
				iSizeOfMobData++;
			}

		}
	}
}