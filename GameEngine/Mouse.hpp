#pragma once
#include "InputManager.hpp"
#include "SFMLEventHandler.hpp"
#include "DataTypes.hpp"
#include <functional>
namespace Solar
{
	struct Mouse
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
		Button_Bools _Buttons;
		Vector2 _Position;
		bool _InWindow;
		std::map<int, EventStruct> EventQueue;

	public:
		const Vector2* Position = &_Position;
		const Button_Bools* Buttons = &_Buttons;
		const bool* InsideWindow = &_InWindow;

		void HookEvent(std::string Event, std::function<void()> function);
		void FireEvent(std::string Event);
	};
}

