#include "Star.h"

Star::Star(sf::RenderWindow* wnd) {
	this->window = wnd;
	if (!Star_texture.loadFromFile(path))
		throw std::runtime_error("cannot load Star texture!");
	Star_sprite.setTexture(Star_texture);
	Star_sprite.setScale(0.05f, 0.05f);
	hitbox.height = Star_sprite.getGlobalBounds().height;
	hitbox.width = Star_sprite.getGlobalBounds().width;
}

void Star::set_postition(const sf::Vector2f& pos) {
	Star_sprite.setPosition(pos);
}

void Star::draw() {
	window->draw(Star_sprite);
}

void Star::update(float dt) {
	Star_sprite.move(-dt * speed, 0.f);
	hitbox.left = Star_sprite.getPosition().x;
	hitbox.top = Star_sprite.getPosition().y;
}

void Star::set_speed(float s) {
	this->speed = s;
}

void Star::animate() {
	angle += 2;
	Star_sprite.move(0, sin(toRad(angle)));
	if (angle > 360.f) angle = 0.f;
}

#ifdef _DEBUG
void Star::log_position() {
	std::cout << Star_sprite.getPosition().x << " - " << Star_sprite.getPosition().y << std::endl;
}
#endif // _DEBUG
