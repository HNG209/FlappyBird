#include "SFX.h"

SFX::SFX() {
	if (!jump_buffer.loadFromFile(jump_path))
		throw std::runtime_error("cannot load sound effect!");
	jump_sound.setBuffer(jump_buffer);
	if (!hit_buffer.loadFromFile(hit_path))
		throw std::runtime_error("cannot load sound effect!");
	hit_sound.setBuffer(hit_buffer);
	if (!point_buffer.loadFromFile(point_path))
		throw std::runtime_error("cannot load sound effect!");
	point_sound.setBuffer(point_buffer);
	if (!die_buffer.loadFromFile(die_path))
		throw std::runtime_error("cannot load sound effect!");
	die_sound.setBuffer(die_buffer);
}

void SFX::set_volume(float v) {
	this->jump_sound.setVolume(v);
	this->hit_sound.setVolume(v);
	this->point_sound.setVolume(v);
}

void SFX::play_flap_sound() {
	this->jump_sound.play();
}

void SFX::play_hit_sound() {
	this->hit_sound.play();
}

void SFX::play_point_sound() {
	this->point_sound.play();
}
void SFX::play_die_sound() {
	this->die_sound.play();
}