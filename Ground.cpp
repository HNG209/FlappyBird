#include "Ground.h"

Ground::Ground(sf::RenderWindow* wnd) {
	this->window = wnd;
	if (!ground_texture.loadFromFile(path))
		throw std::runtime_error("cannot load ground!");
	ground.setTexture(ground_texture);
	ground.setScale(3.5f, 3.5f);
	ground.setPosition(0, window->getSize().y - 50);
	hitbox.height = ground.getGlobalBounds().height;
	hitbox.width = ground.getGlobalBounds().width;
	hitbox.left = ground.getPosition().x;
	hitbox.top = ground.getPosition().y;
}

void Ground::show_hitbox() {
	sf::RectangleShape r;
	r.setFillColor(sf::Color(0, 0, 255, 100));
	r.setSize(sf::Vector2f(hitbox.width, hitbox.height));
	r.setPosition(sf::Vector2f(hitbox.left, hitbox.top));
	window->draw(r);
}

void Ground::draw() {
	this->window->draw(ground);
}