#include <map>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include <ctime>

int     main(void)
{
	std::map<std::string, double>  data;
	data["2017-12-28"] = 231.4;
	data["2017-12-28"] = 242.42; // updates previous
	data["2018-01-28"] = 128.90;
	data["2018-07-04"] = 180.23;
	data["2017-02-28"] = 23.9;
	data["2019-09-13"] = 1431.12;
	data["2018-04-28"] = 831.50;
	//access elements
	for (std::map<std::string, double>::iterator it = data.begin(); it != data.end(); it++)
		std::cout << it->first << " = " << it->second << "; ";
	std::cout << std::endl;
	// find existing key
	std::string  key1 = "2017-12-28";
	std::cout << "key1 " << data.find(key1)->second << std::endl;
	std::string  key3 = "2019-09-13";
	std::cout << "key3 " << data.find(key3)->second << std::endl;
	// find non-existing key
	std::map<std::string, double>::iterator it;
	std::string  key2 = "2017-12-29";
	it = data.find (key2);
	if (it != data.end())
	{
		data.erase (it);
		std::cout << "key2 " << data.find(key2)->second << std::endl;
	}
	else
		std::cout << "key2 not found" << std::endl;
	return 0;
}