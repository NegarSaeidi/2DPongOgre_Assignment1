#pragma once

#include "Ogre.h"

using namespace Ogre;
using namespace std;
class Ball
{
public:

	Ball();
	~Ball();
	Ball* getBall();
	Vector3 getPosition();
	Vector3 getScale();
	void checkCollision(SceneNode* bat, SceneNode* ball);
	void move(SceneNode* ball, Ogre::Real time);
	void checkBound(SceneNode* ball);
	ManualObject* getShape(ManualObject* obj);
	float getXVelocity();
	float getYVelocity();
	void update(SceneNode* node, SceneNode* bat, Ogre::Real time);

	bool getIsColliding();
	bool getLose();
	void setLose(bool b);
private:

	string ballShape;
	Vector3 position, scale;
	float XVelocity;
	float YVelocity;
	float radius,batWidth,batHeight;
	bool Collide, Lose;
	float ScreenHeight, ScreenWidth, maxSpeed;


};