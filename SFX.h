#pragma once
#include<SFML/Audio.hpp>
#include<stdio.h>

class SFX
{
private:
	const std::string jump_path = "Assets\\SFX\\flap.wav";
	const std::string hit_path = "Assets\\SFX\\hit.wav";
	const std::string point_path = "Assets\\SFX\\point.wav";
	const std::string die_path = "Assets\\SFX\\die.wav";
	const std::string powerup_path = "Assets\\SFX\\smb_powerup.wav";
	const std::string EQ_path = "Assets\\SFX\\EQ.wav";
	sf::SoundBuffer jump_buffer;
	sf::SoundBuffer hit_buffer;
	sf::SoundBuffer point_buffer;
	sf::SoundBuffer die_buffer;
	sf::SoundBuffer powerup_buffer;
	sf::SoundBuffer EQ_buffer;
	sf::Sound jump_sound;
	sf::Sound hit_sound;
	sf::Sound point_sound;
	sf::Sound die_sound;
	sf::Sound powerup_sound;
	sf::Sound EQ_sound;
public:
	SFX();
	void set_volume(float);
	void play_flap_sound();
	void play_hit_sound();
	void play_point_sound();
	void play_die_sound();
	void play_powerup_sound();
	//void play_EQ_sound();
};

