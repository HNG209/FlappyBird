#include<iostream>
#include<math.h>
#include<vector>
#include<deque>
#include<random>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Audio.hpp>
#include<ctime>
#include"Bird.h"
#include"Background.h"
#include"Ground.h"
#include"Pipes.h"
#include"SFX.h"
#include"Text.h"
#include"Boss.h"
#define Rand(a, b) a + (rand() % b)

int main() {
	sf::RenderWindow window(sf::VideoMode(576, 1024), "Flappy Bird", sf::Style::Default);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	srand((unsigned)time(0));
	float dt = 0.f;
	sf::Clock clk;
	Bird player(&window);
	Background bg(&window);
	Ground gnd(&window);
	Pipes pipes(&window);
	Boss boss(&window);
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
	sfx.set_volume(10.f);
	sf::RectangleShape r;
	r.setFillColor(sf::Color::Blue);
	r.setSize(sf::Vector2f(50.f, 50.f));
	r.setOrigin(sf::Vector2f(25.f, 25.f));
	r.setPosition(sf::Vector2f(window.getSize().x / 2.f, 600.f));
	const float base_velocity = 400.f;
	const float base_G = -981.f;
	int jumping = false;
	int index = 0;
	bool lose = false;
	bool start = false;
	bool star_generated = false;
	float vel = base_velocity;
	float G = base_G;
	float delay{};
	float percent_dt{};
	float phase_cooldown{};
	int c = 0;
	//bool play_once = false;
	//bool sw = false;
	//float size{};
	Text t(&window);
	std::deque<sf::Sprite*> silhouette;
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
				if (ev.key.code == sf::Keyboard::Space && !lose) {//jumping
					jump = true;
					start = true;
					c++;
					sfx.play_flap_sound();
					jumping = false;
					vel = base_velocity;
				}
				if (ev.key.code == sf::Keyboard::R && !jumping) {
					c = 0;
					point = 0;
					G = base_G;
					lose = false;
					star_generated = false;
					boss.reset();
					boss.set_spawn(false);
					pipes.reset();
					silhouette.clear();
					pipes.hide(false);
					r.setPosition(sf::Vector2f(window.getSize().x / 2.f, 600));
				}
				if (ev.key.code == sf::Keyboard::E)
					pipes.hide(true);
				if (ev.key.code == sf::Keyboard::W)
					pipes.hide(false);
				break;
			}
		}
		//---------------------------------------------------------

		window.clear();
		if (phase_cooldown > 0.f) {
			phase_cooldown -= dt;
		}
		else phase_cooldown = 0.f;
		percent_dt += dt;
		float percent{};
		if (percent_dt > 3.f && !lose &&
			!pipes.check_star_gen() && 
			!pipes.is_star_hit() &&
			point != 0 && 
			!star_generated &&
			phase_cooldown <= 0.f) {
			percent_dt = 0.f;
			percent = Rand(0, 100);
		}
		// 95 > percent > 80 : star
		//percent > 95: boss
		if (percent > 40 && percent < 70) {
			star_generated = true;
			pipes.set_star_gen();
		}
		else if (percent > 70) {
			pipes.hide(true);
			boss.set_spawn(true);
		}
		
		if (boss.boss_end()) {
			pipes.hide(false);
		}
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
		if (silhouette.size() > 10) silhouette.pop_front();
		//---------------------------------------------------------
		player = r;
		//--------------Rendering objects to window----------------
		bg.draw();//Background
		pipes.animate(dt);
		pipes.draw();//pipe
		if (pipes.check_star_hit(player.hitbox) && !lose) {
			star_generated = false;
			silhouette.push_back(new sf::Sprite(player.get_sprite()));
			G = -2000.f;
			//t.print("TAP HARDER!", sf::Vector2f(576.f / 2.f, 300.f), 40, dt);
		}
		else {
			silhouette.clear();
			t.reset();
			G = base_G;
		}
		gnd.draw();//ground
		int tint = 100;
		if (!lose)
			for (const auto& i : silhouette) {
				silhouette.back()->setColor(sf::Color(255, 255, 255, tint -= 5));
				window.draw(*i);
				i->move(-dt * 200.f, 0.f);
			}
		boss.update(dt);
		boss.draw();
		player.draw();//bird
		player.update(dt);//update
		txt.setString(std::to_string(point));
		window.draw(txt);
		if (!lose && c > 0) {//if lose, stop generating and updating(freezed)
			pipes.generate(dt);//generate pipe
			pipes.update(dt);
		}
		//----------------------------------------------------------

		//---------------------logic resolve------------------------
		if (pipes.check() && !lose) {
			point++;
			sfx.play_point_sound();
		}

		if (((pipes.check_collisions(player.hitbox) ||
			player.check_collision(gnd.hitbox)) ||
			boss.check_collision(player.hitbox) ||
			r.getPosition().y < -50.f) && !lose) {
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