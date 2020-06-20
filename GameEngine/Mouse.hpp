#pragma once
#include "InputManager.hpp"
#include "SFMLEventHandler.hpp"
#include "DataTypes.hpp"
#include <functional>
namespace Solar
{
	struct MOUSE
	{
		friend InputManager;
		friend SFMLEventHandler;
	private:
		struct EventStruct
		{
			std::string EventName;
			std::function<void()> StoredFunction;
		};
		struct Button_Bools
		{
			bool Left;
			bool Right;
			bool Middle;
		};
		Button_Bools _buttons;
		Vector2 _position;
		bool _inWindow;
		std::map<int, EventStruct> EventQueue;

	public:
		const Vector2& Position = _position;
		const Button_Bools& Buttons = _buttons;
		const bool& InsideWindow = _inWindow;

		void HookEvent(std::string Event, std::function<void()> function);
		void FireEvent(std::string Event);
	};
}

