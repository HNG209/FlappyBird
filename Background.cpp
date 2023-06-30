#include "Background.h"

Background::Background(sf::RenderWindow* wnd) {
	this->window = wnd;
	if (!BG_texture.loadFromFile(BG_path))
		throw std::runtime_error("cannot load background!");
	BG.setTexture(BG_texture);
	BG.setScale(4.f, 4.f);
}

void Background::draw() {
	window->draw(BG);
}
