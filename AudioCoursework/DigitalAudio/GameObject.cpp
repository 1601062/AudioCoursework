#include "GameObject.h"

GameObject::GameObject() {

}

void GameObject::update() {
	move(velocity);
	HandleRotation();
}

void GameObject::HandleRotation()
{
	if (velocity.x < 0) {
		if (velocity.y < 0) {
			setRotation(315.0f);
		}
		else if (velocity.y > 0) {
			setRotation(225.0f);
		}
		else if (velocity.y == 0) {
			setRotation(270.0f);
		}
	}
	else if (velocity.x > 0) {
		if (velocity.y < 0) {
			setRotation(45.0f);
		}
		else if (velocity.y > 0) {
			setRotation(135.0f);
		}
		else if (velocity.y == 0) {
			setRotation(90.0f);
		}
	}
	else {
		if (velocity.y < 0) {
			setRotation(0.0f);
		}
		else if (velocity.y > 0) {
			setRotation(180.0f);
		}
		else if (velocity.y == 0) {
			setRotation(getRotation());
		}
	}
}
