#pragma once
#define local static

#include <unordered_map>
#include "DEBUG.hpp"
#include "AssetManager.hpp"
#include "StateMachine.hpp"
#include "InputManager.hpp"
#include "Instance.hpp"
#include "SFMLEventHandler.h"
#include <typeinfo>

#define nil NULL
namespace Solar
{
	//Structs
	local struct Fonts
	{
		const char* Arial = "Resources/fonts/arial.ttf";
	};

	local struct WindowProperties
	{
		int SCREEN_WIDTH = 800;
		int SCREEN_HEIGHT = 600;
	};

	local struct Framework 
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	local enum x_Status
	{
		Visible,
		Invisible,
		Active,
		Inactive,
		Enabled,
		Disabled,
	};
	local enum x_Result
	{
		Success,
		Failure
	};
	//Define
	struct Enums
	{
		//Structs
		WindowProperties Window;
		Fonts Font;
		Framework data;
		std::multimap<int, Instance*> Game;
		DEBUG Debug;
		sf::Mouse Mouse;
		SFMLEventHandler SFMLEVENTS;
		//Enums
		x_Status Status;
		x_Result Result;
	};

}