#include "Camera.h"

// Function which initialiaze the location of the cmaera according to current wizard position
void Camera::init(sf::Vector2f playerPos){
	cameraX = playerPos.x;
	cameraY = playerPos.y;
}

// Function which update the camera position according to every move of the wizard
// call from board class
void Camera::update(const float playerX, const float playerY){
	// when the player will go in the center of the screen we will start to scroll
	cameraX = playerX - (float)(640 / 2);
	cameraY = playerY - (float)(504 / 2);

	// we check it in order to stay in ther range 
	if (cameraX < 0)
		cameraX = 0;
	else if (cameraX > 3500)
		cameraX = 3305;
	if (cameraY < 0)
		cameraY = 0;
	else if(cameraY > 360)
		cameraY = 277;
		
	CameraPosition.reset(sf::FloatRect(cameraX, cameraY, 640, 504));
	CameraPosition.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.9f));
}

// Function which draw the camera object by set the view of the window according
// to the current camera position we already calculate
void Camera::draw(sf::RenderWindow & window){
	window.setView(CameraPosition);
}
