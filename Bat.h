#pragma once
#include "Ogre.h"
using namespace Ogre;
using namespace std;
class Bat
{

public:
	Bat();
	~Bat();
	Vector3 getPosition();

	ManualObject* getShape(ManualObject* obj);
	void moveLeft(SceneNode* node);
	void moveRight(SceneNode* node);
	

private:
	string batShape;
	float batSpeed;
	Vector3 position;
	

};

