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

	//Update Values
	void Frame::Tick(float dt)
	{
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
			/*for (auto& x : this->children) {
				x.second->Tick(dt);
			}*/
			for (int i = 0; i != this->children.size(); i++ ) {
				this->children[i]->Tick(dt);
			}
		}
	}
	void Frame::Render(float dt, sf::RenderTexture* target)
	{
		if (this->Enabled) {
			if (this->ClipsDescendants)
			{
				sf::View region = target->getView();
				
				sf::Vector2f Siz = sf::Vector2f(
					this->_body.getGlobalBounds().width / Enum.Window.SCREEN_WIDTH,
					this->_body.getGlobalBounds().height / Enum.Window.SCREEN_HEIGHT
				);

				sf::Vector2f Pos = sf::Vector2f(
					this->_body.getPosition().x / Enum.Window.SCREEN_WIDTH,
					this->_body.getPosition().y / Enum.Window.SCREEN_HEIGHT
				);

				if (region.getViewport().top > Pos.y)
				{
					float max = (region.getViewport().top) - (Pos.y);//+ region.getViewport().height);
					float tempHeight = Siz.y - max;
					if (tempHeight < 0)
						tempHeight = 0.f;
					Siz.y = tempHeight;
					Pos.y = Pos.y + max;
				}

				if (region.getViewport().left > Pos.x)
				{
					float max = (region.getViewport().left) - (Pos.x);//+ region.getViewport().height);
					float tempHeight = Siz.x - max;
					if (tempHeight < 0)
						tempHeight = 0.f;
					Siz.x = tempHeight;
					Pos.x = Pos.x + max;
				}

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
				target->setView(region);
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

			for (int i = 0; i != this->children.size(); i++) {
				auto& Selected = this->children[i];
				if (Selected->Type == "Folder")
				{
					Selected->_body.setPosition(this->_body.getPosition());
					Selected->_body.setSize(this->_body.getSize());
				}
				Selected->Render(dt, target);
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


		for (int i = 0; i != this->children.size(); i++) {
			this->children[i]->HandleEvents();
		}
	}
}