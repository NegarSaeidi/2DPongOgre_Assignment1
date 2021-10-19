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
/**
 * GameFrame Listener class, for listening to the events that occur each frame
 */
class GameFrameListener : public Ogre::FrameListener
{
private:
    Ogre::SceneNode* _BatNode;
    Ogre::SceneNode* _BallNode;
    Ball* _ballInstance;
    OgreBites::Label* _liveLabel;
    OgreBites::Label* _scLabel;
    OgreBites::Label* _timeLabel;
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
    
 /**
 * Used as the update function, calls the update function of the ball, check for the lose condition, update the huds
 * @param const Ogre::FrameEvent& evt
 * @return bool
 */
    bool frameStarted(const Ogre::FrameEvent& evt)
    {
       
        _timeLabel->setCaption(Ogre::StringConverter::toString(evt.timeSinceLastFrame*1000));
        if (!dead)
        {
            _ballInstance->update(_BallNode, _BatNode, evt.timeSinceLastFrame);
            if (_ballInstance->getLose())
            {
                _ballInstance->setLose(false);

                if (livesnumber > 1)
                {
                    livesnumber--;

                    _BallNode->setPosition(10, 100, 0);
                    _liveLabel->setCaption(Ogre::StringConverter::toString(livesnumber));
                }
                else
                {
                    dead = true;
                    _liveLabel->setCaption(Ogre::StringConverter::toString(0));

                }

            }

            if (_ballInstance->getIsColliding())
            {

                scoreNumber++;
                _scLabel->setCaption(Ogre::StringConverter::toString(scoreNumber));

            }







        }
        return true;
    }
};

/**
 * Constuctor, sets up a commmon context for application
 * @return no return
 */
Game::Game()
    : ApplicationContext("NegarSaeidi-101261396")
{
}


/**
 * In this function, scene elements get created, like lights , camera, trayManager, hud...
 * @param None
 * @return void
 */

void Game::setup()
{

    ApplicationContext::setup();
    getRenderWindow()->resize(1000, 500);
    addInputListener(this);
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);


    //Light
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    Light* light = scnMgr->createLight("MainLight");
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    lightNode->setPosition(20, 80, 50);

    //Create camera
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
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

    mTpuLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "Time/Update", "Time/Update(ms):", 150);
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
/**
 * This function creates a new game frame listener instance and adds it to the scene root.
 * @param None
 * @return void
 */
void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new GameFrameListener(batNode, BallNode, ball, mLives, mScore, mTpu);
    mRoot->addFrameListener(FrameListener);

}



/**
 * keyboard event handler, handling A and D keys
 * @param const KeyboardEvent& evt
 * @return bool
 */
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



/**
 * Startting point of the application, creates an instance of the game class, initializes it and starts rendering it
 * @param int argc, char** argv
 * @return int
 */
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

