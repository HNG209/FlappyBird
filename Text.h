#pragma once
#include<SFML/Graphics.hpp>

class Text
{
private:
	sf::RenderWindow* window;
	const std::string font_path = "Assets\\FONT\\Retro_Gaming.ttf";
	sf::Font fnt;
	sf::Text txt;
	const float default_character_size = 50.f;
	float dt;
	float delay_time = 3.f;//3s
public:
	Text(sf::RenderWindow*);
	void set_delay_time(float);
	void centered();
	void reset();
	void print(const std::string&, sf::Vector2f);
	void print(const std::string&, sf::Vector2f, float);
	void print(const std::string&, sf::Vector2f, float, float);
};

