  /*
* Ball class
* Circle shape
* 
*/
#include "Ball.h"

Ball::Ball() :ballShape("circle"), position(20, 100, 0), scale(0.2f, 0.05f, 1.0f), XVelocity(35.0f), YVelocity(35.0f), Collide(false), Lose(false)
{
    width = 120.0f;
    height = 138.0f;
    maxSpeed = 50.0f;
}
Ball::~Ball()
{
}

Ball* Ball::getBall()
{
    return this;
}


//returns ball's position
Vector3 Ball::getPosition()
{
    return position;
}

Vector3 Ball::getScale()
{
    return scale;
}

//Creates the shape of the ball
ManualObject* Ball::getShape(ManualObject* obj)
{
    float const radius = 4;
    float const accuracy = 50;
    unsigned index = 0;
    obj->begin("FlatVertexColour", RenderOperation::OT_TRIANGLE_FAN);
    for (float theta = 0; theta <= 2 * Math::PI; theta += Math::PI / accuracy)
    {
        obj->colour(ColourValue(0.0f, 0.0f, 1.0f, 1.0f));
        obj->position(radius * Math::Cos(theta), radius * Math::Sin(theta), 0);
        index++;


    }
    obj->end();
    return obj;
}
//returns ball's velocity in X direction
float Ball::getXVelocity()
{
    return XVelocity;
}
//returns ball's velocity in Y direction
float Ball::getYVelocity()
{
    return YVelocity;
}
//Updates ball's velocity
//Checks for boundries collision
void Ball::update(SceneNode* node)
{
  
    XVelocity -= 0.1;
    if (Math::Abs(YVelocity) < 1)
        YVelocity = -20;
    else
    YVelocity -= 1;
   
    if (node->getPosition().x < -width  || node->getPosition().x > width)
    {
        XVelocity = -XVelocity;
      
    }
    if  ( Math::Abs(node->getPosition().y+8-height)<1 )
    {
        YVelocity = -YVelocity;
      
      
    }
     if (Collide)
    {
        if(YVelocity<0  && Math::Abs(YVelocity<60))
        YVelocity = (-1*YVelocity)+5;
        else if (YVelocity > 0 && Math::Abs(YVelocity < 60))
                YVelocity = -(YVelocity + 5);
 
       // Collide = false;
        
    }
   if (node->getPosition().y < -48)
    {
        Lose = true;
        XVelocity = 55.0;
        YVelocity = -20;
    }
  
  

        
}

void Ball::isColliding(bool b)
{
    Collide = b;
}

bool Ball::getIsColliding()
{
    return Collide;
}

bool Ball::getLose()
{
    return Lose;
}

void Ball::setLose(bool b)
{
    Lose = b;
}
