#include <exception>
#include "CSVReader.hpp"

int main(int argc, char** argv)
{
	try
	{
		std::ifstream	file("data.csv");
		for (const auto& row : CSVRange(file))
		{
			std::cout << row[1] << std::endl;
		}
	}
	catch(std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
