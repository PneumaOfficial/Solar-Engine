#include <iostream>
#include "Frame.hpp"
#include "DEFINTIONS.hpp"
namespace Solar {
	extern struct Enums Enum;
	Frame::Frame()
	{
		this->Type = "Frame";
		this->Size = Udim2(0.0f, 50.0f, 0.0f, 50.0f);
		std::function<void()> ScrollUpEvent = [this]() mutable
		{
			if (this->Hovered)
				this->FireEvent("ScrollUp");
		};
		std::function<void()> ScrollDownEvent = [this]() mutable
		{
			if (this->Hovered)
				this->FireEvent("ScrollDown");
		};
		Enum.Mouse.HookEvent("ScrollUp", ScrollUpEvent);
		Enum.Mouse.HookEvent("ScrollDown", ScrollDownEvent);

		//Draggable Property
		std::function<void()> MouseDown = [this]() mutable
		{
			if (!this->Draggable)
				return;
			this->offset.x = Enum.Mouse.Position.x - this->_body.getPosition().x;
			this->offset.y = Enum.Mouse.Position.y - this->_body.getPosition().y;
			shouldDrag = true;
		};
		std::function<void()> MouseUp = [this]() mutable
		{
			if (!this->Draggable)
				return;
			this->shouldDrag = false;
		};
		std::function<void()> MouseMove = [this]() mutable
		{
			if (!this->Draggable || this->shouldDrag != true)
				return;

			float xOffset = Enum.Mouse.Position.x;
			float yOffset = Enum.Mouse.Position.y;
			this->Position = Udim2(0, xOffset - this->offset.x, 0, yOffset - this->offset.y);
		};

		this->HookEvent("MouseButton1Down", MouseDown);
		Enum.Mouse.HookEvent("LeftUp", MouseUp);
		Enum.Mouse.HookEvent("MouseMoved", MouseMove);

	};
	void Frame::AddChild(Instance* child)
	{
		if (child->Type != "Frame")
		{
			child->_body.setSize(this->_body.getSize());
			child->_body.setPosition(this->_body.getPosition());
		}
		this->children.emplace(this->children.size() + 1, child);
		child->Parent = this;
	}

	//Update Values
	void Frame::Tick(float dt)
	{
		//TODO: Parents
		/*if (this->Parent != this->PreviousParent)
		{
			std::cout << "PARENT CHANGE!" << std::endl;
			this->Parent->AddChild(this);
			this->PreviousParent = this->Parent;
		}*/
		if (this->Enabled) 
		{
			if (this->Parent != nil)
			{

				sf::Vector2f ParentSize = this->Parent->_body.getSize();
				sf::Vector2f ParentPosition = this->Parent->_body.getPosition();

				if (!(this->BackgroundColor == this->PropertyChecks.BackgroundColor) || this->BackgroundTransparency != this->PropertyChecks.BackgroundTransparency)
				{
					this->_body.setFillColor(sf::Color(this->BackgroundColor.getRed(), this->BackgroundColor.getGreen(), this->BackgroundColor.getBlue(), (1 - this->BackgroundTransparency) * 255));
					this->PropertyChecks.BackgroundTransparency = this->BackgroundTransparency;
					this->PropertyChecks.BackgroundColor = this->BackgroundColor;
				}

				if (!(this->BorderColor == this->PropertyChecks.BorderColor) || this->BorderTransparency != this->PropertyChecks.BorderTransparency || this->BorderSize != this->PropertyChecks.BorderSize)
				{
					this->_body.setOutlineColor(sf::Color(this->BorderColor.getRed(), this->BorderColor.getGreen(), this->BorderColor.getBlue(), (1 - this->BorderTransparency) * 255));
					this->_body.setOutlineThickness(this->BorderSize);
					this->PropertyChecks.BorderTransparency = this->BorderTransparency;
					this->PropertyChecks.BorderColor = this->BorderColor;
					this->PropertyChecks.BorderSize = this->BorderSize;
				}


				if (this->Position != this->PropertyChecks.Position || ParentPosition != this->PropertyChecks.previousParentPosition)
				{
					this->_body.setPosition(ParentPosition.x + (ParentSize.x * this->Position.x.scale) + this->Position.x.offset, ParentPosition.y + (ParentSize.y * this->Position.y.scale) + this->Position.y.offset);
					this->PropertyChecks.Position = this->Position;
					this->PropertyChecks.previousParentPosition = ParentPosition;

					if (this->Trapped)
					{
						//Top Left
						if (this->_body.getPosition().x < this->Parent->_body.getPosition().x)
							this->_body.setPosition(sf::Vector2f(this->Parent->_body.getPosition().x, this->_body.getPosition().y));
						
						if (this->_body.getPosition().y < this->Parent->_body.getPosition().y)
							this->_body.setPosition(sf::Vector2f(this->_body.getPosition().x, this->Parent->_body.getPosition().y));

						//Bottom Right
						if (this->_body.getPosition().x + this->_body.getSize().x > this->Parent->_body.getPosition().x + this->Parent->_body.getSize().x)
							this->_body.setPosition(sf::Vector2f(this->Parent->_body.getPosition().x + this->Parent->_body.getSize().x - this->_body.getSize().x, this->_body.getPosition().y));
						
						if (this->_body.getPosition().y + this->_body.getSize().y > this->Parent->_body.getPosition().y + this->Parent->_body.getSize().y)
							this->_body.setPosition(sf::Vector2f(this->_body.getPosition().x, this->Parent->_body.getPosition().y + this->Parent->_body.getSize().y - this->_body.getSize().y));
					}
				}
				if (this->Size != this->PropertyChecks.Size || ParentSize != this->PropertyChecks.previousParentBounds)
				{
					this->_body.setSize(sf::Vector2f((ParentSize.x * this->Size.x.scale) + this->Size.x.offset, (ParentSize.y * this->Size.y.scale) + this->Size.y.offset));
					this->PropertyChecks.Size = this->Size;
					this->PropertyChecks.previousParentBounds = ParentSize;
				}
			} 
			for (auto& x : this->children) {
				x.second->Tick(dt);
			}
		}
	}
	void Frame::Render(float dt, sf::RenderTexture* target)
	{
		if (this->Enabled) {
			if (this->ClipsDescendants)
			{
				sf::View region = Enum.data.window.getView();
				
				sf::Vector2f Siz = sf::Vector2f(
					this->_body.getGlobalBounds().width / Enum.Window.SCREEN_WIDTH,
					this->_body.getGlobalBounds().height / Enum.Window.SCREEN_HEIGHT
				);

				sf::Vector2f Pos = sf::Vector2f(
					this->_body.getPosition().x / Enum.Window.SCREEN_WIDTH,
					this->_body.getPosition().y / Enum.Window.SCREEN_HEIGHT
				);
				/*if (region.getViewport().top < Pos.y)
				{
					float max = (region.getViewport().top + region.getViewport().height) - (Siz.y);
					float tempHeight = max - Siz.y;
					std::cout << "New Pos: " << max << std::endl;
					std::cout << "New Size: " << tempHeight << std::endl;
					if (tempHeight < 0)
						tempHeight = 0.f;
					Pos.y = Pos.y + (Siz.y - tempHeight);
					Siz.y = tempHeight;
				}*/
				if (region.getViewport().left + region.getViewport().width < Siz.x + Pos.x)
				{
					float max = (Siz.x + Pos.x) - (region.getViewport().left + region.getViewport().width);
					float tempHeight = Siz.x - max;
					if (tempHeight < 0)
						tempHeight = 0.f;
					Siz.x = tempHeight;
				}
				if (region.getViewport().top + region.getViewport().height < Siz.y + Pos.y)
				{
					float max = (Siz.y + Pos.y) - (region.getViewport().top + region.getViewport().height);
					float tempHeight = Siz.y - max;
					if (tempHeight < 0)
						tempHeight = 0.f;
					Siz.y = tempHeight;
				}
				region.setViewport(sf::FloatRect(Pos.x, Pos.y, Siz.x, Siz.y));
				region.setSize(sf::Vector2f(
					Siz.x * Enum.Window.SCREEN_WIDTH, 
					Siz.y * Enum.Window.SCREEN_HEIGHT
				));
				region.setCenter(sf::Vector2f(
					(Pos.x * Enum.Window.SCREEN_WIDTH) + ((Siz.x * Enum.Window.SCREEN_WIDTH) / 2),
					(Pos.y * Enum.Window.SCREEN_HEIGHT) + ((Siz.y * Enum.Window.SCREEN_HEIGHT) / 2)));
				Enum.data.window.setView(region);
			}
			this->CurrentView = Enum.data.window.getView();
			if (this->Visible) {
				if (this->BlurBackground)
				{
					sf::Shader shader;
					shader.loadFromFile("Resources/shaders/Blur/Blur.frag", sf::Shader::Fragment);
					sf::Sprite sprite(target->getTexture(), sf::IntRect(this->_body.getPosition().x, this->_body.getPosition().y, this->_body.getSize().x, this->_body.getSize().y));
					sprite.setPosition(this->_body.getPosition());
					shader.setUniform("source", sf::Shader::CurrentTexture);
					shader.setUniform("xOffset", this->BlurOffsets.x);
					shader.setUniform("yOffset", this->BlurOffsets.y);
					target->draw(sprite, &shader);
				}
				target->draw(this->_body);
			}
			for (auto& x : this->children) {
				if (x.second->Type == "Folder")
				{
					x.second->_body.setPosition(this->_body.getPosition());
					x.second->_body.setSize(this->_body.getSize());
				}
				x.second->Render(dt, target);
			}
		}
	}

	//Event Variables
	void Frame::HandleEvents()
	{
		if (/*Enum.data.input.Contains(this->CurrentView, sf::Mouse::getPosition()) &&*/ Enum.data.input.IsRectHovered(this->_body) != this->EventChecks.Hovered)
		{
			this->EventChecks.Hovered = Enum.data.input.IsRectHovered(this->_body);
			if (this->EventChecks.Hovered)
			{
				this->FireEvent("MouseEnter");
			}
			else
			{
				this->FireEvent("MouseLeave");
			}
		}

		if (this->EventChecks.Hovered && this->EventChecks.Pressed != Enum.Mouse.Buttons.Left)
		{
			this->EventChecks.Pressed = Enum.Mouse.Buttons.Left;
			if (this->EventChecks.Pressed)
			{
				FireEvent("MouseButton1Down");
			} 
			else
			{
				FireEvent("MouseButton1Up");
			}
		}


		for (auto& x : this->children) {
			x.second->HandleEvents();
		}
	}

	void Frame::HookEvent(std::string Event, std::function<void()> function)
	{
		EventStruct fun;
		fun.StoredFunction = function;
		fun.EventName = Event;
		this->EventQueue.emplace(this->EventQueue.size() + 1, fun);
	}
	void Frame::FireEvent(std::string Event)
	{
		for (auto& x : this->EventQueue)
			if (x.second.EventName == Event)
				x.second.StoredFunction();
	}
}