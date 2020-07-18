#include "TextLabel.hpp"
#include "DEFINTIONS.hpp"
namespace Solar
{
	extern struct Enums Enum;

	void TextLabel::Tick(float dt)
	{
		//TODO: Parents
		sf::Vector2f ParentSize = this->Parent->_body.getSize();
		sf::Vector2f ParentPosition = this->Parent->_body.getPosition();
		if (this->Text != this->Properties.Text)
		{
			this->_text.setString(this->Text);
			this->Properties.Text = this->Text;
		}

		if (this->Font != this->Properties.Font)
		{
			std::string dir = "Resources/fonts/" + this->Font + ".ttf";
			if (Enum.data.assets.LoadFont(this->Properties.Font, dir))
			{
				this->_text.setFont(Enum.data.assets.GetFont(this->Properties.Font));
				this->_ValidFont = true;
			}
			else
			{
				//TODO: ERROR LOGGING
				this->_ValidFont = false;
				std::cout << "ERROR: Cannot load font" << std::endl;
			}
			this->Properties.Font = this->Font;
		}

		if (this->TextSize != this->Properties.TextSize)
		{
			this->_text.setCharacterSize(this->TextSize);
			this->Properties.TextSize = this->TextSize;
		}

		if (this->Position != this->Properties.Position || ParentPosition != this->Properties.previousParentPosition)
		{
			this->_body.setPosition(ParentPosition.x + (ParentSize.x * this->Position.x.scale) + this->Position.x.offset, ParentPosition.y + (ParentSize.y * this->Position.y.scale) + this->Position.y.offset);
			this->Properties.Position = this->Position;
			this->Properties.previousParentPosition = ParentPosition;

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
			this->_text.setPosition(this->_body.getPosition());

		}

		if (this->Size != this->Properties.Size || ParentSize != this->Properties.previousParentBounds)
		{
			this->_body.setSize(sf::Vector2f((ParentSize.x * this->Size.x.scale) + this->Size.x.offset, (ParentSize.y * this->Size.y.scale) + this->Size.y.offset));
			this->Properties.Size = this->Size;
			this->Properties.previousParentBounds = ParentSize;
		}

		if (!(this->TextColor == this->Properties.TextColor) || this->TextTransparency != this->Properties.TextTransparency)
		{
			this->_text.setFillColor(sf::Color(this->TextColor.getRed(), this->TextColor.getGreen(), this->TextColor.getBlue(), (1 - this->TextTransparency) * 255));
			this->Properties.TextTransparency = this->TextTransparency;
			this->Properties.TextColor = this->TextColor;
		}
		
		for (std::size_t i = 0; i < this->children.size(); ++i) {
			this->children[i]->Tick(dt);
		}
	}
	void TextLabel::Render(float dt, sf::RenderTexture* target)
	{	
		if(this->_ValidFont)
			target->draw(this->_text);
		for (std::size_t i = 0; i < this->children.size(); ++i) {
			this->children[i]->Render(dt, target);
		}
	}
	void TextLabel::HandleEvents()
	{

		for (std::size_t i = 0; i < this->children.size(); ++i) {
			this->children[i]->HandleEvents();
		}
	}
}