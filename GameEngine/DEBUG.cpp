#include "DEBUG.hpp"
#include "DEFINTIONS.hpp"
#include "Serialization.hpp"
#include "TextLabel.hpp"
#include "Sound.hpp"
namespace Solar
{
	extern struct Enums Enum;
	sf::Image img;
	sf::Texture texture;
	sf::Sprite sprite;
	void DEBUG::Init()
	{
		img.loadFromFile("Resources/testing.png");
		texture.loadFromImage(img);
		sprite.setTexture(texture, true);

		//Main GUI
		auto main = CreateFolder();
		main->Name = "GUI";
		main->setParent(std::move(Enum.Game.find(2)->second));
		auto Wow = CreateFrame();
		//Wow->Visible = false;
		Wow->Size = Udim2(0.5,0,0.5,0);
		Wow->Position = Udim2(0.2,0,0.2,0);
		Wow->BackgroundColor = Color(77, 121, 255);
		Wow->ClipsDescendants = true;
		Wow->setParent(std::move(main));

		auto Tab = CreateFrame();
		Tab->Size = Udim2(1, 0, 0, 25);
		Tab->Name = "Tab Frame";
		Tab->BackgroundColor = Color(38, 38, 38);
		Tab->BackgroundTransparency = 0.2;
		auto sound = CreateSound();
		sound->FilePath = "Resources/audio/TestingAudio.wav";
		sound->Name = "SoundEffect";
		sound->setParent(std::move(Tab));
		TextLabel* label = new TextLabel();
		
		label->Size = Udim2(0,50, 1,0);
		label->Position = Udim2(0, 5, 0, 0);
		label->TextColor = Color(255, 255, 255);
		label->TextSize = 20;
		label->Font = "OpenSans/SemiBold";
		label->setParent(std::move(Tab));

		auto Body = CreateFrame();
		Body->BackgroundTransparency = 0.3;
		Body->Position = Udim2(0,0,0,25);
		Body->BackgroundColor = Color(0,0,0);
		Body->Size = Udim2(1, 0, 0, 350);

		auto Border = CreateFrame();
		Border->BlurBackground = true;
		Border->Size = Udim2(0,420,0,375);
		Border->Position = Udim2(0, 0, 0, 0);
		Border->BackgroundTransparency = 1;
		Border->BorderSize = 1;
		Border->BorderColor = Color(255,255,255);
		Border->BlurOffsets.x = 0.002f;
		Border->BlurOffsets.y = 0.002f;
		//Border->ClipsDescendants = true;

		Body->setParent(std::move(Border));
		Tab->setParent(std::move(Border));
		//Border->Trapped = true;
		Border->setParent(std::move(Wow));
		
		bool shouldDrag = false;
		Vector2 offset;
		std::function<void()> MouseDown = [&Tab, &shouldDrag, &offset]() mutable
		{
			
			auto sound = (SoundHandler*)Tab->FindFirstChild("SoundEffect")->get();
			sound->Play();
			
			offset.x = Enum.Mouse.Position.x - Tab->_body.getPosition().x;
			offset.y = Enum.Mouse.Position.y - Tab->_body.getPosition().y;
			shouldDrag = true;
		};
		std::function<void()> MouseUp = [&Tab, &shouldDrag, &offset]() mutable
		{
			shouldDrag = false;
		};
		std::function<void()> MouseMove = [&Border, &shouldDrag, &offset, &Wow]() mutable
		{
			float xOffset = Wow->_body.getPosition().x - Enum.Mouse.Position.x;
			float yOffset = Wow->_body.getPosition().y - Enum.Mouse.Position.y;
			std::cout << "UDim2 X: " << xOffset << std::endl;
			std::cout << "UDim2 Y: " << yOffset << std::endl;
			if (shouldDrag == true)
			{
				Border->Position = Udim2(0, (xOffset + offset.x), 0, yOffset + offset.y);
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

	void DEBUG::Render(float dt, sf::RenderTexture* target)
	{
		target->draw(sprite);
		Enum.Game.find(2)->second->Render(dt, target);
	}
}
