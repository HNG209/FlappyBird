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
	if (!this->pipes.empty()) {
		if (active_time <= 8.f) {
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
				if (gen_star && star == nullptr && !hidden) {
					gen_star = false;
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
	//this->gen_dt += dt;
	//if (gen_dt >= 1.f) gen_dt = 0.f;
}

bool Pipes::check_collisions(const sf::IntRect& other) {
	if (!hidden && tint >= 255) {
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
	}
	return false;
}

void Pipes::draw() {
	if (star != nullptr) {
		star->animate();
		star->draw();
	}
	if (!star_hit) {
		for (auto& i : pipes) {
			if (hidden) {
				if (tint < 60) {
					i.pipe.first.setColor(sf::Color(255, 255, 255, 60));
					i.pipe.second.setColor(sf::Color(255, 255, 255, 60));
				}
			}
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
	tint = 255;
	star_hit = false;
	gen_star = false;
	this->pipes.clear();
	this->animation.clear();
	this->last_score = 0;
	index = 0;
	j = 0;
}

void Pipes::animate(float dt) {//animate the pipes grown based on their position
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

void Pipes::hide(bool state)
{
	this->hidden = state;
}

void Pipes::set_star_gen()
{
	this->gen_star = true;
}

bool Pipes::check() {//score update
	if (index < pipes.size()) {
		if (pipes[index].pipe.first.getPosition().x < window->getSize().x / 2 - 106.f) {
			index++;
			return true;
		}
	}
	return false;
}

bool Pipes::is_star_hit() 
{
	return star_hit;
}

bool Pipes::check_star_gen()
{
	return gen_star;
}

bool Pipes::check_star_hit(const sf::IntRect& r) {//check collision with the star
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
	//update the star's postition and animate it if existed
	if(star != nullptr)
		star->update(dt);

	if (!pipes.empty()) {
		//if the last pipe goes out of the screen, delete it, update the index for the next pipe
		if (pipes.front().pipe.first.getPosition().x < -100.f) {
			pipes.pop_front();
			animation.pop_front();
			if (index > 0 && j > 0) {
				index -= 1;
				j -= 1;
			}
		}
	}
	//move the pipes to the left
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
	//animate the hidden pipes
	for (auto& i : pipes) {
		if (hidden) {
			if (tint >= 60) {
				i.pipe.first.setColor(sf::Color(255, 255, 255, tint -= 1));
				i.pipe.second.setColor(sf::Color(255, 255, 255, tint -= 1));
			}
		}
		else {
			if (tint < 255) {
				i.pipe.first.setColor(sf::Color(255, 255, 255, tint += 1));
				i.pipe.second.setColor(sf::Color(255, 255, 255, tint += 1));
			}
		}
	}
}