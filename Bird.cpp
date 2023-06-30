#include "Bird.h"
Bird::Bird(sf::RenderWindow* wnd) {
	this->dt = 0.f;
	this->window = wnd;
	if (!bird_texture.loadFromFile(texture_path))
		throw std::runtime_error("cannot load bird texture!");
	bird.setTexture(bird_texture);
	bird.setOrigin(sf::Vector2f(12.5f, 14.f));
	bird.setScale(sf::Vector2f(5.f, 5.f));
}

void Bird::set_position(const sf::Vector2f& pos) {
	this->bird.setPosition(pos);
}

void Bird::operator=(const sf::RectangleShape& hitbox) {
	this->bird.setPosition(hitbox.getPosition());
}

void Bird::draw() {
	window->draw(bird);
}

void Bird::show_hitbox() {
	sf::RectangleShape r;
	r.setFillColor(sf::Color(0, 0, 255, 100));
	r.setSize(sf::Vector2f(hitbox.width, hitbox.height));
	r.setPosition(sf::Vector2f(hitbox.left, hitbox.top));
	window->draw(r);
}


void Bird::update(float dt) {
	this->dt += dt;
	hitbox.height = 12.5f * bird.getScale().x;
	hitbox.width = 14.f * bird.getScale().y;
	hitbox.left = bird.getPosition().x - hitbox.width / 2;
	hitbox.top = bird.getPosition().y - hitbox.height / 2;
	bird.setTextureRect(sf::IntRect(25 * i, 0, 25, 28));
	float angle = _map(bird.getPosition().y, 0, 1024, -120, 80);//heading angle
	if (angle < -25) angle = -25;
	bird.setRotation(angle);
	if (this->dt >= refresh_time) {
		this->dt = 0.f;
		i++;
		if (i > 2) i = 0;
	}
}