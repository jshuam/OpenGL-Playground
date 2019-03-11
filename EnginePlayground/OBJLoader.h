#pragma once

#include <string>
#include "Loader.h"
#include "RawModel.h"

class OBJLoader
{
public:
	static RawModel loadObjModel( std::string filename, Loader loader );
};

