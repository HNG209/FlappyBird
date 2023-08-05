#include "Boss.h"


Boss::Boss(sf::RenderWindow* wnd) {
	srand((unsigned)time(0));
	window = wnd;
	if (!boss_texture.loadFromFile(boss_sprite_path))
		throw std::runtime_error("cannot load texture!");
	boss.setTexture(boss_texture);
	boss.setOrigin(sf::Vector2f(12.5f, 14.f));
	boss.setScale(-9.f, 9.f);
	boss.setPosition(base_pos);
}

bool Boss::boss_end() const
{
	return end;
}

void Boss::draw() {
	if(spawn || boss.getPosition().x < 650.f)
		window->draw(boss);
}

void Boss::reset()
{
	timer = 0.f;
	boss.setPosition(base_pos);
	hitbox.height = 12.5f * boss.getScale().x;
	hitbox.width = 14.f * boss.getScale().y;
	hitbox.left = boss.getPosition().x - hitbox.width / 2;
	hitbox.top = boss.getPosition().y - hitbox.height / 2;
}

void Boss::jump() {
	jmp = true;
	vel = base_vel;
	random_h = Rand(100, 650);
}

void Boss::attack(float dt, bool state)
{
	if (boss.getPosition().x < -200.f)
		dir = true;
	else if (boss.getPosition().x > (state == true ? 700.f : base_pos.x - 10.f))
		dir = false;
	if (dir) {
		boss.setScale(9.f, 9.f);
		boss.move(movement_speed * dt, 0.f);
	}
	else {
		boss.setScale(-9.f, 9.f);
		boss.move(-movement_speed * dt, 0.f);
	}
}

void Boss::appear(float dt)
{
	if(boss.getPosition().x >= 510.f)
		boss.move(-dt * 100.f, 0);
}

void Boss::disappear(float dt)
{
	if (boss.getPosition().x < -200.f)
		dir = true;
	else if (boss.getPosition().x > base_pos.x - 10.f)
		dir = false;
	if (dir) {
		boss.setScale(9.f, 9.f);
		boss.move(movement_speed * dt, 0.f);
	}
	else {
		boss.setScale(-9.f, 9.f);
		boss.move(-movement_speed * dt, 0.f);
	}
}

void Boss::update(float dt) {
	if (spawn) {
		timer += dt;
		end = false;
	}

	if (timer >= 10.f) {
		timer = 0.f;
		spawn = false;//return to based position
	}

	//if (!spawn && !end) {
	//	if (boss.getPosition().x < base_pos.x) {
	//		this->dt += dt;
	//		if (this->dt >= 0.2f) {
	//			this->dt = 0.f;
	//			index++;
	//			if (index > 2) index = 0;
	//		}

	//		boss.setTextureRect(sf::IntRect(25 * index, 0, 25, 28));

	//		if (jmp) {
	//			float offset = -dt * vel * 2;//future prediction
	//			if (boss.getPosition().y + offset > window->getSize().y - 25.f)
	//				boss.move(0, window->getSize().y - 25.f - boss.getPosition().y);
	//			else boss.move(0, -dt * vel * 2);//main part of jumping
	//			vel += dt * G;//here too
	//		}

	//		hitbox.height = 12.5f * boss.getScale().x;
	//		hitbox.width = 14.f * boss.getScale().y;
	//		hitbox.left = boss.getPosition().x - hitbox.width / 2;
	//		hitbox.top = boss.getPosition().y - hitbox.height / 2;
	//		float angle = _map(boss.getPosition().y, 0, 1024, -120, 80);//heading angle
	//		if (angle < -25) angle = -25;
	//		if (dir)
	//			boss.setRotation(angle);
	//		else
	//			boss.setRotation(360 - angle);

	//		if (boss.getPosition().y >= random_h) {
	//			if (boss.getPosition().y > 0.f) {
	//				jump();
	//			}
	//		}
	//		disappear(dt);
	//		if (boss.getPosition().x > base_pos.x - 10.f)
	//			end = true;
	//	}
	//}

	if (spawn || !end) {
		this->dt += dt;
		if (this->dt >= 0.2f) {
			this->dt = 0.f;
			index++;
			if (index > 2) index = 0;
		}

		boss.setTextureRect(sf::IntRect(25 * index, 0, 25, 28));

		if (jmp) {
			float offset = -dt * vel * 2;//future prediction
			if (boss.getPosition().y + offset > window->getSize().y - 25.f)
				boss.move(0, window->getSize().y - 25.f - boss.getPosition().y);
			else boss.move(0, -dt * vel * 2);//main part of jumping
			vel += dt * G;//here too
		}

		hitbox.height = 12.5f * boss.getScale().x;
		hitbox.width = 14.f * boss.getScale().y;
		hitbox.left = boss.getPosition().x - hitbox.width / 2;
		hitbox.top = boss.getPosition().y - hitbox.height / 2;
		float angle = _map(boss.getPosition().y, 0, 1024, -120, 80);//heading angle
		if (angle < -25) angle = -25;
		if(dir)
			boss.setRotation(angle);
		else
			boss.setRotation(360 - angle);

		if (boss.getPosition().y >= random_h) {
			if (boss.getPosition().y > 0.f) {
				jump();
			}
		}
		
		if (spawn)
			attack(dt, true);
		else
			attack(dt, false);
		if (boss.getPosition().x > base_pos.x - 10.f && !spawn) end = true;
	}
}

void Boss::set_spawn(bool s)
{
	end = false;
	spawn = s;
}
