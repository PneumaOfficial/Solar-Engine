#pragma once
#include <iostream>
#include "Frame.hpp"
#include "Folder.hpp"

namespace Solar
{
	std::string Serialize(Frame* dt);
	std::string Serialize(Folder* dt);
}
