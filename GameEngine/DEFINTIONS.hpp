#pragma once
#define local static

#include <unordered_map>
#include "DEBUG.hpp"
#include "AssetManager.hpp"
#include "StateMachine.hpp"
#include "InputManager.hpp"
#include "Mouse.hpp"
#include "Instance.hpp"
#include "SFMLEventHandler.hpp"
#include <typeinfo>
#include <memory>

#define nil NULL
namespace Solar
{
	//Structs
	struct FontsDir
	{
		const char* Arial = "Resources/fonts/arial.ttf";
	};

	struct WindowProperties
	{
		int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;
		int SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;
	};

	struct Framework 
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
		sf::View DefaultView;
	};

	enum x_Status
	{
		Visible,
		Invisible,
		Active,
		Inactive,
		Enabled,
		Disabled,
	};
	enum x_Result
	{
		Success,
		Failure
	};
	//Define
	struct Enums
	{
		//Structs
		WindowProperties Window;
		FontsDir FontDir;
		Framework data;
		std::unordered_map<int, std::unique_ptr<Instance>> Game;
		MOUSE Mouse;
		DEBUG Debug;
		SFMLEventHandler SFMLEVENTS;
		//Enums
		x_Status Status;
		x_Result Result;
	};

}