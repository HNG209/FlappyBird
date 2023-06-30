#include<iostream>
#include<math.h>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Audio.hpp>
#include"Bird.h"
#include"Background.h"
#include"Ground.h"
#include"Pipes.h"
#include"SFX.h"


int main() {
	sf::RenderWindow window(sf::VideoMode(576, 1024), "Flappy Bird", sf::Style::Default);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	float dt = 0.f;
	sf::Clock clk;
	Bird player(&window);
	Background bg(&window);
	Ground gnd(&window);
	Pipes pipes(&window);
	SFX sfx;
	sf::Font fnt;
	sf::Text txt;
	int point{};
	if (!fnt.loadFromFile("Assets\\FONT\\Retro_Gaming.ttf"))
		throw std::runtime_error("cannot load font!");
	txt.setFont(fnt);
	txt.setCharacterSize(50);
	txt.setPosition(10.f, 0.f);
	txt.setOutlineThickness(1.f);
	txt.setOutlineColor(sf::Color::Black);
	sfx.set_volume(40.f);
	sf::RectangleShape r;
	r.setFillColor(sf::Color::Blue);
	r.setSize(sf::Vector2f(50.f, 50.f));
	r.setOrigin(sf::Vector2f(25.f, 25.f));
	r.setPosition(sf::Vector2f(window.getSize().x / 2.f, 600.f));
	int jumping = false;
	const float base_velocity = 400.f;
	const float base_G = -981.f;
	float vel = base_velocity;
	float G = base_G;
	//float jumpHeight = 100.f;
	int index = 0;
	bool lose = false;
	bool play_once = false;
	float delay{};
	while (window.isOpen()) {
		//-----------------------window events-----------------------
		sf::Event ev;
		bool jump = false;
		while (window.pollEvent(ev)) {
			if (ev.type == ev.Closed) window.close();
			switch (ev.type) {
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
					window.close();
				if (ev.key.code == sf::Keyboard::Space && !lose) {
					sfx.play_flap_sound();
					jump = true;
					jumping = false;
					vel = base_velocity;
				}
				if (ev.key.code == sf::Keyboard::R && !jumping) {
					point = 0;
					G = base_G;
					lose = false;
					pipes.reset();
					r.setPosition(sf::Vector2f(window.getSize().x / 2.f, 600));
				}
				break;
			}
		}
		//---------------------------------------------------------

		window.clear();

		//----------------------jumping----------------------------
		if (jump) jumping = true;

		if (jumping) {
			float offset = -dt * vel * 2;//future prediction
			if (r.getPosition().y + offset > window.getSize().y - 25.f)
				r.move(0, window.getSize().y - 25.f - r.getPosition().y);
			else r.move(0, -dt * vel * 2);//main part of jumping
			vel += dt * G;//here too
		}

		if (r.getPosition().y >= window.getSize().y - 25.f && jumping == true) {//touching the ground
			r.setPosition(r.getPosition().x, window.getSize().y - 25.f);
			jumping = false;
			vel = base_velocity;
		}

		//---------------------------------------------------------

		player = r;

		//--------------Rendering objects to window----------------
		bg.draw();//Background
		pipes.animate(dt);
		pipes.draw();//pipe
		gnd.draw();//ground
		player.draw();//bird
		player.update(dt);//update
		txt.setString(std::to_string(point));
		window.draw(txt);
		if (!lose) {//if lose, stop generating and updating(freezed)
			pipes.generate(dt);//generate pipe
			pipes.update(dt);
		}
		//----------------------------------------------------------

		//---------------------logic resolve------------------------
		if (pipes.check() && !lose) {
			point++;
			sfx.play_point_sound();
		}

		if ((pipes.check_collisions(player.hitbox) || player.check_collision(gnd.hitbox)) && !lose) {
			sfx.play_hit_sound();
			jump = false;
			jumping = true;
			vel = 600.f;
			G = -1200.f;
			delay = 0.f;
			lose = true;
		}
		if (lose && delay < 0.3f) {
			delay += dt;
			if (delay >= 0.3f) {
				sfx.play_die_sound();
			}
		}
		//---------------------------------------------------------
		// 
		//----------------------FPS counter------------------------
		dt = clk.restart().asSeconds();
		float FPS = 1 / dt;
		//---------------------------------------------------------
		//std::cout << FPS << std::endl;
		window.display();
	}
	return 0;
}