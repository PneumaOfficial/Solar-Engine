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
		if (Enum.data.input.IsRectHovered(this->_body) != this->EventChecks.Hovered)
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
		if (this->EventChecks.Hovered && this->EventChecks.Pressed != Enum.Mouse.isButtonPressed(sf::Mouse::Button::Left))
		{
			this->EventChecks.Pressed = Enum.Mouse.isButtonPressed(sf::Mouse::Button::Left);
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