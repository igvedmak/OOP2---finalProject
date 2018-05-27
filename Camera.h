#pragma once
#include "Constants.h"
class Camera
{
public:
	Camera() {}
	void init(sf::Vector2f playerPos);
	void update(const float playerX, const float playerY);
	void draw(sf::RenderWindow &window);
	virtual ~Camera() {}

private:
	sf::View CameraPosition;
	float cameraX, cameraY;     // the camera c and y position
};

