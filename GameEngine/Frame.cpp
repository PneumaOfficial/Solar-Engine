#include <iostream>
#include "Frame.hpp"
#include "DEFINTIONS.hpp"
namespace Solar {
	extern struct Enums Enum;
	void Frame::AddChild(Instance* child)
	{
		if (child->Type == "Folder")
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
		if (this->Enabled) 
		{
			if (this->Parent != nil)
			{
				sf::Vector2f ParentSize = this->Parent->_body.getSize();
				sf::Vector2f ParentPosition = this->Parent->_body.getPosition();

				if (!(this->BackgroundColor == this->PropertyChecks.BackgroundColor) || this->Transparency != this->PropertyChecks.BackgroundTransparency)
				{
					this->_body.setFillColor(sf::Color(this->BackgroundColor.getRed(), this->BackgroundColor.getGreen(), this->BackgroundColor.getBlue(), (1 - this->Transparency) * 255));
					this->PropertyChecks.BackgroundTransparency = this->Transparency;
					this->PropertyChecks.BackgroundColor = this->BackgroundColor;
				}


				if (this->Position != this->PropertyChecks.Position || ParentPosition != this->PropertyChecks.previousParentPosition)
				{
					this->_body.setPosition(ParentPosition.x + (ParentSize.x * this->Position.x.scale) + this->Position.x.offset, ParentPosition.y + (ParentSize.y * this->Position.y.scale) + this->Position.y.offset);
					this->Position = this->Position;
					this->PropertyChecks.previousParentPosition = ParentPosition;
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
	void Frame::Render(float dt)
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
				
				if (region.getViewport().left + region.getViewport().width < Siz.x + Pos.x)
				{
					float max = (Siz.x + Pos.x) - (region.getViewport().left + region.getViewport().width);
					float tempHeight = Siz.x - max;
					Siz.x = tempHeight;
				}
				if (region.getViewport().top + region.getViewport().height < Siz.y + Pos.y)
				{
					float max = (Siz.y + Pos.y) - (region.getViewport().top + region.getViewport().height);
					float tempHeight = Siz.y - max;
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
				Enum.data.window.draw(this->_body);
			}
			for (auto& x : this->children) {
				x.second->Render(dt);
			}
		}
	}

	//Event Variables
	void Frame::HandleEvents()
	{
		sf::View view = this->CurrentView;
		sf::FloatRect port = view.getViewport();

		if (Enum.data.input.Contains(port, sf::Mouse::getPosition()) != this->EventChecks.Hovered)
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