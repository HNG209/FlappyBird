#include "Pipes.h"

Pipes::Pipes(sf::RenderWindow* wnd) {
	srand((unsigned)time(0));
	window = wnd;
	if (!Pipe_texture.loadFromFile(path))
		throw std::runtime_error("cannot load pipe!");
}

void Pipes::scale(float factor) {
	for (auto& i : pipes) {
		i.pipe.first.setScale(factor, factor);
		i.pipe.second.setScale(factor, factor);
	}
}

void Pipes::generate(float dt) {
	_Pipe last_pipe;
	last_pipe.pipe.first.setPosition(500.f, 0.f);
	last_pipe.hitbox.first.left = 500.f;
	last_pipe.pipe.second.setPosition(500.f, 0.f);
	last_pipe.hitbox.second.left = 500.f;
	if (!pipes.empty())
		last_pipe = pipes.back();
	//if (gen_dt == 0.f) {
	if (!this->pipes.empty()) {
		if (active_time <= 5.f) {
			if (this->pipes.back().pipe.first.getPosition().x < 540.f) {
				this->pipes.push_back({});
				//calibrate if needed
				int h = Rand(100, 400);
				scale(4.f);
				pipes.back().pipe.first.setTexture(Pipe_texture);
				pipes.back().pipe.first.setPosition(last_pipe.pipe.first.getPosition().x + pipes_spacing, h);
				pipes.back().pipe.first.move(0, pipes_spacing_width);
				pipes.back().pipe.first.setTextureRect(sf::IntRect(
					84.5f,//left
					0.f,//top
					26.5,//width
					160.f//heigth
				));
				//pipes.back().hitbox.first.left = pipes.back().pipe.first.getPosition().x;
				pipes.back().hitbox.first.left = last_pipe.hitbox.first.left + pipes_spacing;
				pipes.back().hitbox.first.top = pipes.back().pipe.first.getPosition().y;
				pipes.back().hitbox.first.height = pipes.back().pipe.first.getGlobalBounds().height;
				pipes.back().hitbox.first.width = pipes.back().pipe.first.getGlobalBounds().width;
				//pipes.back().pipe.first.setOrigin(0, 160.f);
				pipes.back().pipe.second.setTexture(Pipe_texture);
				pipes.back().pipe.second.setPosition(last_pipe.pipe.second.getPosition().x + pipes_spacing, h - 1024.f + 500.f);
				pipes.back().pipe.second.setTextureRect(sf::IntRect(
					56.f,
					0.f,
					26.5,
					160.f
				));
				//pipes.back().hitbox.second.left = pipes.back().pipe.second.getPosition().x;
				pipes.back().hitbox.second.left = last_pipe.hitbox.second.left + pipes_spacing;
				pipes.back().hitbox.second.top = pipes.back().pipe.second.getPosition().y;
				pipes.back().hitbox.second.height = pipes.back().pipe.second.getGlobalBounds().height;
				pipes.back().hitbox.second.width = pipes.back().pipe.second.getGlobalBounds().width;
				this->animation.push_back(pipes.back());
				float k = pipes.back().pipe.first.getGlobalBounds().height;
				this->animation.back().pipe.first.move(0.f, k);
				this->animation.back().pipe.second.move(0.f, -k);
				this->animation.back().hitbox.first.top += k;
				this->animation.back().hitbox.second.top -= k;
				if (Rand(0, 100) > 50 && star == nullptr) {
					star = new Star(this->window);
					star->set_speed(speed);
					star->set_postition(sf::Vector2f(pipes.back().pipe.first.getPosition().x + 10, pipes.back().pipe.first.getPosition().y - 200.f));
				}
			}
		}
	}
	else {
		delete star;
		star = nullptr;
		pipes_spacing = 300.f;
		speed = 150.f;
		pipes_spacing_width = 400.f;
		active_time = 0.f;
		star_hit = false;
		this->pipes.push_back({});
		//calibrate if needed
		int h = Rand(100, 400);
		scale(4.f);
		pipes.back().pipe.first.setTexture(Pipe_texture);
		pipes.back().pipe.first.setPosition(last_pipe.pipe.first.getPosition().x + pipes_spacing, h);
		pipes.back().pipe.first.move(0, pipes_spacing_width);
		pipes.back().pipe.first.setTextureRect(sf::IntRect(
			84.5f,//left
			0.f,//top
			26.5,//width
			160.f//heigth
		));
		pipes.back().hitbox.first.left = last_pipe.hitbox.first.left + pipes_spacing;
		pipes.back().hitbox.first.top = pipes.back().pipe.first.getPosition().y;
		pipes.back().hitbox.first.height = pipes.back().pipe.first.getGlobalBounds().height;
		pipes.back().hitbox.first.width = pipes.back().pipe.first.getGlobalBounds().width;
		pipes.back().pipe.second.setTexture(Pipe_texture);
		pipes.back().pipe.second.setPosition(last_pipe.pipe.second.getPosition().x + pipes_spacing, h - 1024.f + 500.f);
		pipes.back().pipe.second.setTextureRect(sf::IntRect(
			56.f,
			0.f,
			26.5,
			160.f
		));
		pipes.back().hitbox.second.left = last_pipe.hitbox.second.left + pipes_spacing;
		pipes.back().hitbox.second.top = pipes.back().pipe.second.getPosition().y;
		pipes.back().hitbox.second.height = pipes.back().pipe.second.getGlobalBounds().height;
		pipes.back().hitbox.second.width = pipes.back().pipe.second.getGlobalBounds().width;
		this->animation.push_back(pipes.back());
		float k = pipes.back().pipe.first.getGlobalBounds().height;
		this->animation.back().pipe.first.move(0.f, k);
		this->animation.back().pipe.second.move(0.f, -k);
		this->animation.back().hitbox.first.top += k;
		this->animation.back().hitbox.second.top -= k;
	}
	this->gen_dt += dt;
	if (gen_dt >= 1.f) gen_dt = 0.f;
}

bool Pipes::check_collisions(const sf::IntRect& other) {
	if (!star_hit) {
		for (auto& i : pipes) {
			if (i.check_collision(other)) return true;
		}
	}
	else {
		for (auto& i : animation) {
			if (i.check_collision(other)) return true;
		}
	}
	return false;
}

void Pipes::draw() {
	if (star != nullptr) {
		star->animate();
		star->draw();
	}
	if (!star_hit) {
		for (const auto& i : pipes) {
			window->draw(i.pipe.first);//down
			window->draw(i.pipe.second);//up
		}
	}
	else {
		for (const auto& i : animation) {
			window->draw(i.pipe.first);//down
			window->draw(i.pipe.second);//up
		}
	}
}

void Pipes::reset() {
	delete star;
	star = nullptr;
	pipes_spacing = 300.f;
	speed = 150.f;
	pipes_spacing_width = 400.f;
	active_time = 0.f;
	star_hit = false;
	this->pipes.clear();
	this->animation.clear();
	this->last_score = 0;
	index = 0;
	j = 0;
}

void Pipes::animate(float dt) {
	//for (auto& i : animation) {
	//	if (i.pipe.first.getPosition().y > pipes[j].pipe.first.getPosition().y) {
	//		i.pipe.first.move(0.f, -dt * 250);
	//		i.hitbox.first.top = i.pipe.first.getPosition().y;
	//	}
	//	else {
	//		i.pipe.first.setPosition(pipes[j].pipe.first.getPosition());
	//		i.hitbox.first.top = i.pipe.first.getPosition().y;
	//	}

	//	if (i.pipe.second.getPosition().y < pipes[j].pipe.second.getPosition().y) {
	//		i.pipe.second.move(0.f, dt * 250);
	//		i.hitbox.second.top = i.pipe.second.getPosition().y;
	//	}
	//	else {
	//		i.pipe.second.setPosition(pipes[j].pipe.second.getPosition());
	//		i.hitbox.second.top = i.pipe.second.getPosition().y;
	//	}
	//	j++;
	//}
	if (!animation.empty()) {
		for (int k = 0; k <= j; k++) {
			if (animation[k].pipe.first.getPosition().y > pipes[k].pipe.first.getPosition().y) {
				animation[k].pipe.first.move(0.f, -dt * animation_speed);
				animation[k].hitbox.first.top = animation[k].pipe.first.getPosition().y;
			}
			else {
				animation[k].pipe.first.setPosition(pipes[k].pipe.first.getPosition());
				animation[k].hitbox.first.top = animation[k].pipe.first.getPosition().y;
			}
			 
			if (animation[k].pipe.second.getPosition().y < pipes[k].pipe.second.getPosition().y) {
				animation[k].pipe.second.move(0.f, dt * animation_speed);
				animation[k].hitbox.second.top = animation[k].pipe.second.getPosition().y;
			}
			else {
				animation[k].pipe.second.setPosition(pipes[k].pipe.second.getPosition());
				animation[k].hitbox.second.top = animation[k].pipe.second.getPosition().y;
			}
		}
	}
	if (j < animation.size()) {
		if (animation[j].pipe.second.getPosition().x < window->getSize().x - 200.f)
			j++;
	}
	if(star_hit)
		active_time += dt;
}

bool Pipes::check() {
	if (index < pipes.size()) {
		if (pipes[index].pipe.first.getPosition().x < window->getSize().x / 2 - 106.f) {
			index++;
			return true;
		}
	}
	return false;
}

bool Pipes::check_star_hit(const sf::IntRect& r) {
	if(star != nullptr)
		if (star->check_collision(r)) {
			star_hit = true;
		}
	if (star_hit) {
		delete star;
		star = nullptr;
		pipes_spacing = 200.f;
		speed = 200.f;
		pipes_spacing_width = 350.f;
	}
	return star_hit;
}

void Pipes::update(float dt) {
	if(star != nullptr)
		star->update(dt);
	if (!pipes.empty()) {
		if (pipes.front().pipe.first.getPosition().x < -100.f) {
			pipes.pop_front();
			animation.pop_front();
			if (index > 0 && j > 0) {
				index -= 1;
				j -= 1;
			}
		}
	}

	for (auto& i : pipes) {
		i.pipe.first.move(-dt * speed, 0.f);
		i.pipe.second.move(-dt * speed, 0.f);
		i.hitbox.first.left = i.pipe.first.getPosition().x;
		i.hitbox.second.left = i.pipe.second.getPosition().x;
	}

	for (auto& i : animation) {
		i.pipe.first.move(-dt * speed, 0.f);
		i.pipe.second.move(-dt * speed, 0.f);
		i.hitbox.first.left = i.pipe.first.getPosition().x;
		i.hitbox.second.left = i.pipe.second.getPosition().x;
	}
}