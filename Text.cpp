#include "Text.h"

Text::Text(sf::RenderWindow* wnd) {
	this->window = wnd;
	if (!fnt.loadFromFile("Assets\\FONT\\Retro_Gaming.ttf"))
		throw std::runtime_error("cannot load font!");
	txt.setFont(fnt);
	txt.setCharacterSize(default_character_size);
}

void Text::set_delay_time(float dl)
{
	this->delay_time = dl;
}

void Text::centered()
{
	sf::FloatRect textRect = txt.getLocalBounds();
	txt.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

void Text::reset()
{
	this->dt = 0.f;
}

void Text::print(const std::string& text, sf::Vector2f pos)
{
	txt.setString(text);
	txt.setPosition(pos);
	window->draw(txt);
}

void Text::print(const std::string& text, sf::Vector2f pos, float size)
{
	txt.setCharacterSize(size);
	txt.setString(text);
	txt.setPosition(pos);
	window->draw(txt);
}

void Text::print(const std::string& text, sf::Vector2f pos, float size, float dt)
{
	this->dt += dt;
	txt.setCharacterSize(size);
	txt.setString(text);
	txt.setPosition(pos);
	this->centered();
	if(this->dt < delay_time)
		window->draw(txt);
}
