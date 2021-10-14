/**-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// Main class containing the main function
//
//
-------------------------------------------------------------------------*/

//! [fullsource]
#include "Ball.h"  
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreMaterial.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include "Ball.h"
#include "Game.h"
#include "Bat.h"
#include <iostream>

using namespace std;
using namespace Ogre;
using namespace OgreBites;

Ogre::Vector3 translate(0, 0, 0);
int scoreNumber = 0;
int livesnumber = 3;
//GameFrameListener class

class GameFrameListener : public Ogre::FrameListener
{
private:
    Ogre::SceneNode* _BatNode;
    Ogre::SceneNode* _BallNode;
    Ball* _ballInstance;
    OgreBites::Label* _liveLabel;
    OgreBites::Label* _scLabel;
    OgreBites::Label* _timeLabel;
    OgreBites::Label* _deadLabel;
    bool dead = false;

public:

    GameFrameListener(Ogre::SceneNode* batNode, Ogre::SceneNode* ballNode, Ball* tempBall, OgreBites::Label* Live, OgreBites::Label* sc, OgreBites::Label* time)
    {
        _BatNode = batNode;
        _BallNode = ballNode;
        _ballInstance = tempBall;
        _liveLabel = Live;
        _scLabel = sc;
        _timeLabel = time;
        

    }
    //Used as the update function
    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        const auto batCollider = _BatNode->_getWorldAABB();
        const auto ballCollider = _BallNode->_getWorldAABB();

        _timeLabel->setCaption(Ogre::StringConverter::toString(evt.timeSinceLastFrame));
        if (!dead)
        {
            _ballInstance->update(_BallNode);
            if (_ballInstance->getLose())
            {
                _ballInstance->setLose(false);

                if (livesnumber > 1)
                {
                    livesnumber--;

                    _BallNode->setPosition(10, 115, 0);
                    _liveLabel->setCaption(Ogre::StringConverter::toString(livesnumber));
                }
                else
                {
                    dead = true;
                    _liveLabel->setCaption(Ogre::StringConverter::toString(0));
                   // _deadLabel->show();
                }

            }
       
         
            if(!_ballInstance->getIsColliding())
           if((_BallNode->getPosition().x<= batCollider.getMaximum().x)&&
               (_BallNode->getPosition().x >= batCollider.getMinimum().x) &&
               (_BallNode->getPosition().y <= batCollider.getMaximum().y) &&
               (_BallNode->getPosition().y >= batCollider.getMinimum().y))
               
            {
                _ballInstance->isColliding(true);
               
                scoreNumber++;
                _scLabel->setCaption(Ogre::StringConverter::toString(scoreNumber));

            }
            translate.x = _ballInstance->getXVelocity();

            translate.y = _ballInstance->getYVelocity();
          


          
            _BallNode->translate(translate * evt.timeSinceLastFrame);

        }
        return true;
    }
};


Game::Game()
    : ApplicationContext("NegarSaeidi-101261396")
{
}




void Game::setup()
{
    
    ApplicationContext::setup();
    getRenderWindow()->resize(1000,500 );
    addInputListener(this);

   
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();

   
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);



    
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    

   
    Light* light = scnMgr->createLight("MainLight");
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
  

  
    lightNode->setPosition(20, 80, 50);
   
   
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

   //Create camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); 
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 140);

   
    getRenderWindow()->addViewport(cam);
   
    getRenderWindow()->getViewport(0)->setBackgroundColour(ColourValue(0.8f, 0.8f, 0.0f, 1.0f));
    windowHeight = getRenderWindow()->getHeight();
    windowWidth = getRenderWindow()->getWidth();
    
   
    camNode->setPosition(0, 47, 222);
  

    OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("HUD", getRenderWindow());

   
    scnMgr->addRenderQueueListener(mOverlaySystem);
   
  

    //TrayManager
    addInputListener(mTrayMgr);
    mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
    mTrayMgr->toggleAdvancedFrameStats();
 
   



    // HUD
   
  

   
    mTpuLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "Time/Update", "Time/Update:", 150);
    mTpu = mTrayMgr->createLabel(TL_TOPRIGHT, "tpu", "0", 150);

    mScoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Score", "Score:", 150);
    mScore = mTrayMgr->createLabel(TL_TOPLEFT, "score", "0", 150);

    mLivesLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Lives", "Lives:", 150);
    mLives = mTrayMgr->createLabel(TL_TOPLEFT, "lives", "3", 150);


    //Ball
    ball = new Ball();
    ManualObject* circle = scnMgr->createManualObject("Ball");
    circle->setDynamic(true);
    ball->getShape(circle);
    BallNode = scnMgr->getRootSceneNode()->createChildSceneNode("BallNode");
    BallNode->setPosition(ball->getPosition());
    BallNode->attachObject(circle);

    //Bat
    bat = new Bat();
    ManualObject* rectangle = scnMgr->createManualObject("Bat");
    rectangle->setDynamic(true);
    bat->getShape(rectangle);
    batNode = scnMgr->getRootSceneNode()->createChildSceneNode("BatNode");
    batNode->setPosition(bat->getPosition());
    batNode->attachObject(rectangle);



    scnMgr->showBoundingBoxes(true);
    createFrameListener();

}
void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new GameFrameListener(batNode, BallNode, ball, mLives, mScore,mTpu);
    mRoot->addFrameListener(FrameListener);

}


//Input 
//handling A and D keys pressed
bool Game::keyPressed(const KeyboardEvent& evt)
{
   
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;

    case 'a':
        if (batNode->getPosition().x > -122)
            bat->moveLeft(batNode);
        break;
    case 'd':
        if (batNode->getPosition().x + 40 < 122)
            bat->moveRight(batNode);
        break;


    default:
        break;
    }

    return true;
}



//Start point
int main(int argc, char** argv)
{
    try
    {
        Game app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

//! [fullsource]


