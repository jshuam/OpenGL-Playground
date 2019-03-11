#pragma once

#include <vector>
#include <sstream>

class Utils
{
public:
	static std::vector<std::string> split( std::string& string, char delimiter = ' ' )
	{
		std::istringstream iss( string );
		std::string token;
		std::vector<std::string> result;
		while( std::getline( iss, token, delimiter ) )
		{
			result.push_back( token );
		}

		return result;
	}
};

