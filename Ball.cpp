
/**
* <summary>
* Ball class - have checkCollision, checkBounds, move functions
* Creates the shape of the ball
*</summary>
*/
#include "Ball.h"
#include <iostream>

/**
 * Constructor
 * Initializes the class variables
 * @return no return
 */

Ball::Ball() :ballShape("circle"), position(100, 100, 0), scale(0.2f, 0.05f, 1.0f), XVelocity(50.0f), YVelocity(50.0f), Collide(false), Lose(false)
{
    ScreenWidth = 120.0f;
    ScreenHeight = 133.0f;
    radius = 8;
    batWidth = 40;
    batHeight = 12;
    maxSpeed = 50.0f;
}
Ball::~Ball()
{
}
/**
 *Returns the current instance of this class
 * @param None
 * @return Ball*
 */
Ball* Ball::getBall()
{
    return this;
}

/**
 * returns the position of this instance
 * @param None.
 * @return Vector3
 */


Vector3 Ball::getPosition()
{
    return position;
}

/**
 *If the object is colliding with the bat this function sets the Collide variable to true
 * @param None
 * @return bool
 */
bool Ball::getIsColliding()
{
    return Collide;
}

Vector3 Ball::getScale()
{
    return scale;
}

/**
 * Checks to see if the ball is colliding with the bat.
 * @param SceneNode* bat.
 * @param SceneNode* ball
 * @return void
 */

void Ball::checkCollision(SceneNode* bat, SceneNode* ball)
{
  
    if (((ball->getPosition().x >= bat->getPosition().x) &&
        (ball->getPosition().x + radius <= bat->getPosition().x + batWidth) &&
        (ball->getPosition().y <= bat->getPosition().y + batHeight) &&
        (ball->getPosition().y + radius >= bat->getPosition().y + batHeight)) ||

        ((ball->getPosition().x + radius >= bat->getPosition().x) &&
            (ball->getPosition().x <= bat->getPosition().x) &&
            (ball->getPosition().y <= bat->getPosition().y + batHeight) &&
            (ball->getPosition().y + radius >= bat->getPosition().y + batHeight)) ||

        ((ball->getPosition().x <= bat->getPosition().x + batWidth) &&
            (ball->getPosition().x + radius >= bat->getPosition().x + batWidth) &&
            (ball->getPosition().y <= bat->getPosition().y + batHeight) &&
            (ball->getPosition().y + radius >= bat->getPosition().y + batHeight)))
    {

        YVelocity = (-1 * YVelocity) + maxSpeed;
        Collide = true;


    }
    else
        Collide = false;
}

/**
 * moves the ball based on time
 * @param SceneNode* ball
 * @param Ogre::Real time
 * @return void
 */


void Ball::move(SceneNode* ball, Ogre::Real time)
{
    Vector3 tempVel;
    tempVel.x = XVelocity;
    tempVel.y = YVelocity;
    tempVel.z = 0;
    ball->translate(tempVel * time);
}

/**
 * Checks to see if the ball is colliding with edges.
 * @param SceneNode* ball.
 * @return void
 */


void Ball::checkBound(SceneNode* ball)
{
    if (ball->getPosition().y + radius >= ScreenHeight)
    {

        YVelocity = -1 * (YVelocity + 10);

    }
    else if (ball->getPosition().x < -ScreenWidth || ball->getPosition().x+radius > ScreenWidth)
    {

        if (XVelocity > 0)
            XVelocity = -1 * (XVelocity + 10);
        else
            XVelocity = (-1 * XVelocity) + 10;

    }


    if (ball->getPosition().y < -48)
    {
        Lose = true;
        XVelocity = 35.0;
        YVelocity = 35.0;
    }



}

/**
 * Creates the circular shape of the object
 * @param ManualObject* obj
 * @return ManualObject*
 */


ManualObject* Ball::getShape(ManualObject* obj)
{
    float const radius = 4;
    float const accuracy = 50;
    unsigned index = 0;
    obj->begin("FlatVertexColour", RenderOperation::OT_TRIANGLE_FAN);
    for (float theta = 0; theta <= 2 * Math::PI; theta += Math::PI / accuracy)
    {
        obj->colour(ColourValue(0.0f, 0.0f, 0.2f, 1.0f));
        obj->position(radius * Math::Cos(theta), radius * Math::Sin(theta), 0);
        index++;


    }
    obj->end();
    return obj;
}

/**
 * Returns the velocity of the object in X axis
 * @param None
 * @return float
 */


float Ball::getXVelocity()
{
    return XVelocity;
}

/**
 * Returns the velocity of the object in Y axis
 * @param None
 * @return float
 */

float Ball::getYVelocity()
{
    return YVelocity;
}

/**
 * updates the velocity of object per frame, calls the checkCollision, checkBound and move functions
 * @param SceneNode* ball
  * @param SceneNode* bat
  * @param Ogre::Real time
 * @return void
 */

void Ball::update(SceneNode* ball, SceneNode* bat, Ogre::Real time)
{


    if (Math::Abs(YVelocity) >= maxSpeed)
    {
        if (YVelocity > 0)
            YVelocity -= 0.5;
        else
            YVelocity += 0.5;
    }
    if (Math::Abs(XVelocity) >= maxSpeed)
    {
        if (XVelocity > 0)
            XVelocity -= 0.5;
        else
            XVelocity += 0.5;
    }
    if (Math::Abs(YVelocity) < 1.5)
        YVelocity = -35;
    checkCollision(bat, ball);
    checkBound(ball);
    move(ball, time);




}



bool Ball::getLose()
{
    return Lose;
}

void Ball::setLose(bool b)
{
    Lose = b;
}