#include "GameObject.h"

GameObject::GameObject() {

}

void GameObject::update() {
	move(velocity);
}