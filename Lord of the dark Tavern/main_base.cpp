#include "main_base.hpp"

namespace JNR
{
	main_base::main_base(std::string path)
		: main_path(path)
	{
		std::string path1 = path;
		std::string dev2 = "/";
		std::string dev1 = "\\";
		for (int i = 0; i < main_path.length(); i++)
		{
			if (main_path[i] == dev1[0])
			{
				main_path[i] = dev2[0];
			}
		}

		std::wstring stemp = s2ws(main_path + "DATA/*");
		LPCWSTR result = stemp.c_str();

		fHandle = FindFirstFile(result, &wfd);

		do
		{
			if (!((wfd.cFileName[0] == '.') && ((wfd.cFileName[1] == '.' && wfd.cFileName[2] == 0) || wfd.cFileName[1] == 0)))
			{
				std::wstring ws(wfd.cFileName);
				std::string str_dev(ws.begin(), ws.end());

				if (str_dev.length() > 4)
				{
					std::string buffer_ending = str_dev.substr(str_dev.length() - 4, str_dev.length());

					if (buffer_ending == ".jnr")
					{
						std::ifstream texture_file{ path1 + "DATA/" + str_dev, std::ifstream::binary };
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

						struct memory_data d_memory_data;
						buffer.erase(buffer.begin());
						d_memory_data.t = buffer;
						char buffer_char[5] = {};
						bool found = false;
						short i = 0;
						short u_k = 0;
						while (!found)
						{
							if (buffer[buffer.size() - i] == '#')
							{
							for (short k = sec_integer; k > 0; k--)
								{
									if (static_cast<int>(buffer[buffer.size() - (i + k)]) >= 97 && static_cast<int>(buffer[buffer.size() - (i + k)]) <= 122)
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
						std::cout << dev_buffer << std::endl;
						d_memory_data.name = dev_buffer;
						d_data.push_back(d_memory_data);
						buffer.clear();
					}
				}
			}
		} while (FindNextFile(fHandle, &wfd));
		FindClose(fHandle);
	}

	main_base::~main_base()
	{
	}

	std::vector<char> main_base::get_memory_data(std::string name) const
	{
		for (int i = 0; i < d_data.size(); i++)
		{
			if (d_data[i].name == name)
			{
				return d_data[i].t;
			}
		}
	}

	std::wstring main_base::s2ws(const std::string& s)
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