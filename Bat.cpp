/*
* Bat class
* Rectangular shape
*
*/
#include "Bat.h"

/**
 * Constructor
 * Initializes the class variables
* @return no return
 */
Bat::Bat() :batShape("rectangle"), position(0, -35, 0), batSpeed(2.0f)
{
}

Bat::~Bat()
{
}
/**
 * returns the position of this instance
 * @param None.
 * @return Vector3
 */


Vector3 Bat::getPosition()
{
    return position;
}


/**
 * Creates the rectangular shape of the object
 * @param ManualObject* obj
 * @return ManualObject*
 */


ManualObject* Bat::getShape(ManualObject* obj)
{
    obj->begin("FlatVertexColour",
        Ogre::RenderOperation::OT_TRIANGLE_LIST);
    obj->position(0, 0, 0);
    obj->colour(1, 0, 0);
    obj->position(40, 0, 0);
    obj->colour(1, 0, 0);
    obj->position(40, 10, 0);
    obj->colour(1, 0, 0);
    obj->triangle(0, 1, 2);

    obj->position(40, 10, 0);
    obj->colour(1, 0, 0);
    obj->position(0, 10, 0);
    obj->colour(1, 0, 0);
    obj->position(0, 0, 0);
    obj->colour(1, 0, 0);
    obj->triangle(3, 4, 5);
    obj->end();
    return obj;
}

/**
 * Moves the object to the left
 * @param SceneNode* node
 * @return void
 */


void Bat::moveLeft(SceneNode* node)
{


    node->translate(Vector3(-1, 0, 0) * batSpeed);
}
/**
 * Moves the object to the right
 * @param SceneNode* node
 * @return void
 */

void Bat::moveRight(SceneNode* node)
{
    node->translate(Vector3(1, 0, 0) * batSpeed);
}