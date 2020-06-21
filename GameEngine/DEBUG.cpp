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
		Frame* Wow = new Frame();
		Wow->ClipsDescendants = true;
		Wow->Size = Udim2(0.5,0,0,50);
		main->AddChild(Wow);
		Frame* Tab = new Frame();
		Tab->Size = Udim2(0.5, 0, 0, 30);
		Tab->Name = "Tab Frame";
		Tab->BackgroundColor = Color(0, 51, 153);
		Wow->AddChild(Tab);
		Frame* Body = new Frame();
		Tab->AddChild(Body);
		Body->BackgroundColor = Color(77, 136, 255);
		Body->Size = Udim2(1, 0, 0, 300);
		Body->Position = Udim2(0,15,1,-15);
		bool shouldDrag = false;
		Vector2 offset;
		std::function<void()> MouseDown = [Tab, &shouldDrag, &offset]() mutable
		{
			Tab->ClipsDescendants = true;
			offset.x = Enum.Mouse.Position.x - Tab->_body.getPosition().x;
			offset.y = Enum.Mouse.Position.y - Tab->_body.getPosition().y;
			shouldDrag = true;
		};
		std::function<void()> MouseUp = [Tab, &shouldDrag, &offset]() mutable
		{
			Tab->ClipsDescendants = false;
			shouldDrag = false;
		};
		std::function<void()> MouseMove = [Tab, &shouldDrag, &offset]() mutable
		{
			if (shouldDrag == true)
			{
				Tab->Position = Udim2(0, Enum.Mouse.Position.x - offset.x, 0, Enum.Mouse.Position.y - offset.y);
			}
		};
		Tab->HookEvent("MouseButton1Down", MouseDown);
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
