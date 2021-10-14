/*
* Bat class
* Rectangular shape
*
*/
#include "Bat.h"

Bat::Bat():batShape("rectangle"), position(45,-35, 0),batSpeed(2.0f)
{
}

Bat::~Bat()
{
}

Vector3 Bat::getPosition()
{
	return position;
}

ManualObject* Bat::getShape(ManualObject* obj)
{
    obj->begin("FlatVertexColour",
        Ogre::RenderOperation::OT_TRIANGLE_LIST);
    obj->position(0, 0, 0);
    obj->colour(0.4, 0, 0);
    obj->position(40, 0, 0);
    obj->colour(0.4, 0, 0);
    obj->position(40, 10, 0);
    obj->colour(0.4, 0, 0);
    obj->triangle(0, 1, 2);

    obj->position(40, 10, 0);
    obj->colour(0.4, 0, 0);
    obj->position(0, 10, 0);
    obj->colour(0.4, 0, 0);
    obj->position(0, 0, 0);
    obj->colour(0.4, 0, 0);
    obj ->triangle(3, 4, 5);
    obj->end();
    return obj;
}

void Bat::moveLeft(SceneNode* node)
{
   
    
	node->translate(Vector3(-1,0,0) * batSpeed);
}

void Bat::moveRight(SceneNode* node)
{
    node->translate(Vector3(1, 0, 0) * batSpeed);
}
