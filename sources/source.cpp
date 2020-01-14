// Copyright 2019 Fedorov james.sayfer2015@yandex.ru

#include "../include/header.hpp"


File::File(std::string pam, std::string fin): broker(pam), account(fin.substr(8, 8)), num(1), date(fin.substr(17, 8))
{

}

bool date(int year, int month, int day)
{
    if (day < 0)
	{
		return true;
	}
	if ((month > 12) || (month < 0))
	{
		return true;
	}
    if ((year < 1970) || (year > 2019))
	{
		return true;
	}
    if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
	{
        if (day > 30)
		{
			return true;
		}
    }
	if (month == 2 && (month != ((month == 4) || (month == 6) || (month == 9) || (month == 11))))
	{
        if ((year % 4) == 0)
		{
            if (day > 29)
			{
				return true;
			}
        }
		if ((year % 4) != 0)
		{
            if (day > 28)
			{
				return true;
			}
        }
    }
	else
	{
        if (day > 31)
		{
			return true;
		}
    }
    return false;
}

bool name(std::string fileName)
{
    if (fileName.substr(0, 8) != "balance_")
	{
        return true;
    }
    if (fileName.length() != 29)
	{
        return true;
    }
    if (fileName[16] != '_')
	{
        return true;
    }
    if (fileName[25] != '.')
	{
        return true;
    }
	size_t i = 8;
	while (i < 16)
	{
		if ((fileName[i] > '9') || (fileName[i] < '0'))
		{
			return true;
		}
		i = i + 1;
	}
	size_t j = 17;
	while (j < 25)
	{
		if ((fileName[i] > '9') || (fileName[i] < '0'))
		{
			return true;
		}
		j = j + 1;
	}
    return false;
}


void repository(const path& p, std::vector<File>& pam)
{
    if (!exists(p))
	{
		std::cout << "Not exist";
		std::cout << p;
        exit(-1);
    }
    for (auto& x : directory_iterator{ p })
	{
        if (boost::filesystem::is_directory(x.path()))
		{
            repository(x.path(), pam);
        }
        if (boost::filesystem::is_regular_file(x.path()))
		{
            std::string fileName = x.path().fileName().string();
            if (name(fileName))
			{
				continue;
			}
            int day = 10 * (fileName[23] - 48) + fileName[24] - 48;
            int month = 10 * (fileName[21] - 48) + fileName[22] - 48;
            int year = 1000 * (fileName[17] - 48) + 10 * (fileName[18] - 48) + 10 * (fileName[19] - 48) + fileName[20] - 48;
            if (date(year, month, day))
			{
				continue;
			}
			std::cout << p.fileName().string();
			std::cout << " ";
			std::cout << fileName;
			std::cout << "    ";
            
			File newFile(p.fileName().string(), fileName);
            bool fl = false;
            for (auto& cur : pam)
			{
                if (cur.broker == newFile.broker)
				{
                    if (cur.account == newFile.account)
					{
                        fl = true;
                        cur.date = cur.date > newFile.date ? cur.date : newFile.date;
                        cur.num=cur.num+1;
                    }
                }
            }
            if (!fl)
			{
                pam.push_back(newFile);
            }
        }
    }
}


int mainVirt(int argc, char* argv[])
{
    const boost::filesystem::path p(boost::filesystem::current_path());
    if (argc == 2)
	{
        const boost::filesystem::path p(argv[1]);
    }
    std::vector<File> files;
    repository(p, files);
    for (auto cur : files)
	{
		std::cout << "   ";
		std::cout << cur;
   }
    return 0;
}


std::ostream& operator<<(std::ostream& out, const File& file)
{
	out << "broker:  " << file.broker << "  account:  " << file.account << "  files:  " << file.num << "  lastdate:  " << file.date;
    return out;
}
