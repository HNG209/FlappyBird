#include "Collider.h"

bool Collider::check_collision(const sf::IntRect& other) {
	return hitbox.intersects(other);
}