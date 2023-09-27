#include <map>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include <ctime>
#include <stdio.h>
#include <cstdlib>

struct e_yyyymmdd
{
	int		y;
	int		m;
	int		d;
};

void	display_today_date(void)
{
    time_t      rawtime;
    struct  tm  *time_ptr;
    char        buffer[80];
    time (&rawtime);
    time_ptr = localtime(&rawtime);
    strftime (buffer, 80, "%Y-%m-%d", time_ptr);
    std::cout << buffer << std::endl;
}

// date comp use it date1 is older than date2 returns true
bool	compareDates(std::string const &str1, std::string const &str2)
{
	e_yyyymmdd		d1, d2;
	std::sscanf(str1.c_str(), "%d-%d-%d", &d1.y, &d1.m, &d1.d);
	std::sscanf(str2.c_str(), "%d-%d-%d", &d2.y, &d2.m, &d2.d);
	if (d2.y > d1.y)
		return true;
	else if (d2.y == d1.y)
	{
		if (d2.m > d1.m)
			return true;
		else if (d2.m == d1.m)
			{
				if (d2.d >= d1.d)
					return true;
			}		
	}
	return false;
}
bool	checkDate(std::string const &date)
{
	if (date.length() != 10)
		return false;
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7) 
		{
			if (date[i] != '-')
				return false;
		}
		else if (!isdigit(date[i]))
			return false; 
	}
	int		year, month, day;
	std::sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
	if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	return true;
}

/*
https://stackoverflow.com/questions/11213326/how-to-convert-a-string-variable-containing-time-to-time-t-type-in-c

			when.tm_year = YY - 1900; //Years from 1900
			when.tm_mon = MM - 1; //0-based
			when.tm_mday = DD; //1 based

			when.tm_hour = hh;
			when.tm_min = mm;
			when.tm_sec = ss;

			//Make sure the daylight savings is same as current timezone.
			time_t now = time(0);
			when.tm_isdst = std::localtime(&now)->tm_isdst;

			//Convert the tm struct to the Linux epoch
			time_t converted;
			converted = mktime(&when);
*/

int     main(int argc, char **argv)
{
	display_today_date();
	if (argc == 1)
		return 0;
	std::string     mdate = "";
	std::string		db_date = "2017-06-15";
	mdate.append(argv[1]);
	if (checkDate(mdate))
		std::cout << "date is ok" << std::endl;
	else
		std::cout << "date is invalid" << std::endl;
	if (compareDates(db_date, mdate))
		std::cout << db_date << " is older than " << mdate << " (true)\n";
	else
		std::cout << db_date << " is more recent than " << mdate << " (false)\n";
	return 0;
}