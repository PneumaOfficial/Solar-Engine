#pragma once
//Types of supported serials
#include "Folder.hpp"
#include "Frame.hpp"
#define local static;

namespace Solar
{
	struct Serialization
	{
		//Overloads
		std::string Serialize(Frame parent);
		std::string Serialize(Folder parent);


	};
}

