#include "DEBUG.hpp"
#include "DEFINTIONS.hpp"
#include "Serialization.hpp"
namespace Solar
{
	extern struct Enums Enum;
	Folder* main;
	void DEBUG::Init()
	{
		//Main GUI
		main = new Folder();
		main->Name = "GUI";
		Enum.Game.find(2)->second->AddChild(main);

		Frame* testing = new Frame();
		testing->Size = Udim2(0.5, 0, 0.5, 0);
		testing->Transparency = 255;
		testing->Name = "Testing Frame";
		main->AddChild(testing);
		testing->AddChild(new Frame());
		bool shouldDrag = false;
		Vector2 offset;
		//std::cout << Serialize(main) << std::endl;
		std::function<void()> MouseDown = [testing, &shouldDrag, &offset]() mutable
		{
			offset.x = Enum.Mouse.Position.x - testing->_body.getPosition().x;
			offset.y = Enum.Mouse.Position.y - testing->_body.getPosition().y;
			shouldDrag = true;
		};
		std::function<void()> MouseUp = [testing, &shouldDrag, &offset]() mutable
		{
			shouldDrag = false;
		};
		std::function<void()> MouseMove = [testing, &shouldDrag, &offset]() mutable
		{
			if (shouldDrag == true)
			{
				testing->Position = Udim2(0, Enum.Mouse.Position.x - offset.x, 0, Enum.Mouse.Position.y - offset.y);
			}
		};
		testing->HookEvent("MouseButton1Down", MouseDown);
		Enum.Mouse.HookEvent("LeftUp", MouseUp);
		Enum.Mouse.HookEvent("MouseMoved", MouseMove);
	}
	void DEBUG::HandleEvents()
	{
		Enum.Game.find(2)->second->HandleEvents();
	}
	void DEBUG::Tick(float dt)
	{

		Enum.Game.find(2)->second->Tick(dt);
	}
	void DEBUG::Render(float dt)
	{


		Enum.Game.find(2)->second->Render(dt);
	}
}
