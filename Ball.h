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
	ManualObject* getShape(ManualObject* obj);
	float getXVelocity();
	float getYVelocity();
	void update(SceneNode* node);
	void isColliding(bool b);
	bool getIsColliding();
	bool getLose();
	void setLose(bool b);
private:

	string ballShape;
	Vector3 position, scale;
	float XVelocity;
	float YVelocity;
	bool Collide,Lose;
	float height, width,maxSpeed;


};

