#include "DEBUG.hpp"
#include "DEFINTIONS.hpp"
#include "Serialization.hpp"
#include "TextLabel.hpp"
#include "Sound.hpp"
namespace Solar
{
	extern struct Enums Enum;
	Folder* main;
	sf::Image img;
	sf::Texture texture;
	sf::Sprite sprite;
	void DEBUG::Init()
	{
		img.loadFromFile("Resources/testing.png");
		texture.loadFromImage(img);
		sprite.setTexture(texture, true);

		//Main GUI
		main = new Folder();
		main->Name = "GUI";
		Enum.Game.find(2)->second->AddChild(main);
		Frame* Wow = new Frame();
		//Wow->Visible = false;
		Wow->Size = Udim2(0.5,0,0.5,0);
		Wow->Position = Udim2(0.2,0,0.2,0);
		Wow->BackgroundColor = Color(77, 121, 255);
		Wow->ClipsDescendants = true;
		main->AddChild(Wow);

		Frame* Tab = new Frame();
		Tab->Size = Udim2(1, 0, 0, 25);
		Tab->Name = "Tab Frame";
		Tab->BackgroundColor = Color(38, 38, 38);
		Tab->BackgroundTransparency = 0.2;
		SoundHandler* sound = new SoundHandler();
		sound->FilePath = "Resources/audio/TestingAudio.wav";
		sound->Name = "SoundEffect";
		Tab->AddChild(sound);
		TextLabel* label = new TextLabel();
		
		label->Size = Udim2(0,50, 1,0);
		label->Position = Udim2(0, 5, 0, 0);
		label->TextColor = Color(255, 255, 255);
		label->TextSize = 20;
		label->Font = "OpenSans/SemiBold";
		Tab->AddChild(label);

		Frame* Body = new Frame();
		Body->BackgroundTransparency = 0.3;
		Body->Position = Udim2(0,0,0,25);
		Body->BackgroundColor = Color(0,0,0);
		Body->Size = Udim2(1, 0, 0, 350);
		Frame* Border = new Frame();
		Border->BlurBackground = true;
		Border->Size = Udim2(0,420,0,375);
		Border->Position = Udim2(0, 0, 0, 0);
		Border->BackgroundTransparency = 1;
		Border->BorderSize = 1;
		
		Border->BorderColor = Color(255,255,255);
		Border->BlurOffsets.x = 0.002f;
		Border->BlurOffsets.y = 0.002f;
		Border->ClipsDescendants = true;
		Border->AddChild(Body);
		Border->AddChild(Tab);
		//Border->Trapped = true;
		Wow->AddChild(Border);
		
		bool shouldDrag = false;
		Vector2 offset;
		std::function<void()> MouseDown = [Tab, &shouldDrag, &offset]() mutable
		{
			auto sound = (SoundHandler*) Tab->FindFirstChild("SoundEffect");
			sound->Play();
			
			offset.x = Enum.Mouse.Position.x - Tab->_body.getPosition().x;
			offset.y = Enum.Mouse.Position.y - Tab->_body.getPosition().y;
			shouldDrag = true;
		};
		std::function<void()> MouseUp = [Tab, &shouldDrag, &offset]() mutable
		{
			shouldDrag = false;
		};
		std::function<void()> MouseMove = [Border, &shouldDrag, &offset]() mutable
		{
			if (shouldDrag == true)
			{
				float xOffset = Enum.Mouse.Position.x - Border->_body.getPosition().x;
				float yOffset = Enum.Mouse.Position.y - Border->_body.getPosition().y;
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
