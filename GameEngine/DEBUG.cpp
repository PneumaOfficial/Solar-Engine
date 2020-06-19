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
		std::cout << Serialize(main) << std::endl;
		std::function<void()> Click1 = [testing]() mutable
		{
			testing->BackgroundColor = Color(255, 102, 0);
		};
		std::function<void()> Click2 = [testing]() mutable
		{
			testing->BackgroundColor = Color(255, 0, 0);
		};

		std::function<void()> scroll1 = [testing]() mutable
		{
			testing->Size = Udim2(testing->Size.x.scale, testing->Size.x.offset, testing->Size.y.scale, testing->Size.y.offset + 15);
		};
		std::function<void()> scroll2 = [testing]() mutable
		{
			testing->Size = Udim2(testing->Size.x.scale, testing->Size.x.offset, testing->Size.y.scale, testing->Size.y.offset - 15);
		};
		testing->HookEvent("MouseButton1Down", Click2);
		testing->HookEvent("MouseButton1Up", Click1);
		Enum.data.input.HookEvent("ScrollUp", scroll2);
		Enum.data.input.HookEvent("ScrollDown", scroll1);
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
