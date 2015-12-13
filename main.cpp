#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSprite.h"
#include "cBkGround.h"
#include "cFontMgr.h"
#include "cFileHandler.h"
#include "cButton.h"
#include "cSoundMgr.h"
#include "cSound.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
    const int windowWidth = 800;
	const int windowHeight = 600;
    const int windowBPP = 16;



    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
	
	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();


    //The example OpenGL code
    windowOGL theOGLWnd;
	
    //Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

	// Cube

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER | theInputMgr->MOUSE_BUFFER);

	// Load Fonts
	LPCSTR gameFonts[3] = { "Fonts/space font.ttf", "Fonts/game over font.ttf","Fonts/space font.ttf"};

	theFontMgr->addFont("Space", gameFonts[0], 100);
	theFontMgr->addFont("Gameover", gameFonts[1], 82);
	theFontMgr->addFont("Instructions", gameFonts[2], 24);

	//Load sounds
	LPCSTR gameSounds[4] = { "Audio/backgroundMusic.wav","Audio/buttonSound.wav","Audio/rockSound.wav","Audio/hitSound.wav" };

	theSoundMgr->add("music", gameSounds[0]);
	theSoundMgr->add("button", gameSounds[1]);
	theSoundMgr->add("rock", gameSounds[2]);
	theSoundMgr->add("hit", gameSounds[3]);

	cTexture ufoTxt;
	ufoTxt.createTexture("Images/Sprites/ufo.png");
	cSprite ufoSprite;
	ufoSprite.attachInputMgr(theInputMgr);
	ufoSprite.setSpritePos(glm::vec2(300.0f, 530.0f));
	ufoSprite.setSpriteTranslation(glm::vec2(11.0f, 0.0f));
	ufoSprite.setTexture(ufoTxt.getTexture());
	ufoSprite.setTextureDimensions(ufoTxt.getTWidth(), ufoTxt.getTHeight());
	
	//attach sound manager to ufo sprite
	ufoSprite.attachSoundMgr(theSoundMgr);

	cTexture rockTxt;
	rockTxt.createTexture("Images/Sprites/rock.png");
	
	cSprite rock1Sprite;
	rock1Sprite.setSpriteTranslation(glm::vec2(0.0f, 4.0f));
	rock1Sprite.setSpritePos(glm::vec2(20.0f, 0.0f));
	rock1Sprite.setTexture(rockTxt.getTexture());
	rock1Sprite.setTextureDimensions(rockTxt.getTWidth(), rockTxt.getTHeight());

	cSprite rock2Sprite;
	rock2Sprite.setSpriteTranslation(glm::vec2(0.0f, 4.0f));
	rock2Sprite.setSpritePos(glm::vec2(180.0f, 0.0f));
	rock2Sprite.setTexture(rockTxt.getTexture());
	rock2Sprite.setTextureDimensions(rockTxt.getTWidth(), rockTxt.getTHeight());

	cSprite rock3Sprite;
	rock3Sprite.setSpriteTranslation(glm::vec2(0.0f, 4.0f));
	rock3Sprite.setSpritePos(glm::vec2(240.0f, 0.0f));
	rock3Sprite.setTexture(rockTxt.getTexture());
	rock3Sprite.setTextureDimensions(rockTxt.getTWidth(), rockTxt.getTHeight());

	cSprite rock4Sprite;
	rock4Sprite.setSpriteTranslation(glm::vec2(0.0f, 4.0f));
	rock4Sprite.setSpritePos(glm::vec2(400.0f, 0.0f));
	rock4Sprite.setTexture(rockTxt.getTexture());
	rock4Sprite.setTextureDimensions(rockTxt.getTWidth(), rockTxt.getTHeight());

	cSprite rock5Sprite;
	rock5Sprite.setSpriteTranslation(glm::vec2(0.0f, 4.0f));
	rock5Sprite.setSpritePos(glm::vec2(560.0f, 0.0f));
	rock5Sprite.setTexture(rockTxt.getTexture());
	rock5Sprite.setTextureDimensions(rockTxt.getTWidth(), rockTxt.getTHeight());

	// Create vector array of textures
	vector<cTexture*> textureBkgList;
	LPCSTR bkgTexturesToUse[] = { "Images/main.png", "Images/game.png", "Images/gameover.png" };
	for (int tCount = 0; tCount < 3; tCount++)
	{
		textureBkgList.push_back(new cTexture());
		textureBkgList[tCount]->createTexture(bkgTexturesToUse[tCount]);
	}

	cTexture transSprite;
	transSprite.createTexture("Images/blank.png");

	cBkGround startBkgd;
	startBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	startBkgd.setTexture(textureBkgList[0]->getTexture());
	startBkgd.setTextureDimensions(textureBkgList[0]->getTWidth(), textureBkgList[0]->getTHeight());

	cBkGround mainBkgd;
	mainBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	mainBkgd.setTexture(textureBkgList[1]->getTexture());
	mainBkgd.setTextureDimensions(textureBkgList[1]->getTWidth(), textureBkgList[1]->getTHeight());

	cBkGround endBkgd;
	endBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	endBkgd.setTexture(textureBkgList[2]->getTexture());
	endBkgd.setTextureDimensions(textureBkgList[2]->getTWidth(), textureBkgList[2]->getTHeight());

	

	// Create vector array of button textures
	vector<cTexture*> btnTextureList;
	LPCSTR btnTexturesToUse[] = { "Images/Buttons/QUIT_BUTTON.png", "Images/Buttons/RE-PLAY_BUTTON.png", "Images/Buttons/PLAY_BUTTON.png"};
	for (int tCount = 0; tCount < 3; tCount++)
	{
		btnTextureList.push_back(new cTexture());
		btnTextureList[tCount]->createTexture(btnTexturesToUse[tCount]);
	}

	cButton replayButton;
	replayButton.attachInputMgr(theInputMgr);
	replayButton.setTexture(btnTextureList[1]->getTexture());
	replayButton.setTextureDimensions(btnTextureList[1]->getTWidth(), btnTextureList[1]->getTHeight());

	cButton exitButton;
	exitButton.attachInputMgr(theInputMgr);
	exitButton.setTexture(btnTextureList[0]->getTexture());
	exitButton.setTextureDimensions(btnTextureList[0]->getTWidth(), btnTextureList[0]->getTHeight());

	cButton playButton;
	playButton.attachInputMgr(theInputMgr);
	playButton.setTexture(btnTextureList[2]->getTexture());
	playButton.setTextureDimensions(btnTextureList[2]->getTWidth(), btnTextureList[2]->getTHeight());

	// include an exit button

	int sc = 0;
	string scoreMsg;
	string score[] = { "0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30" };
	

	string outputMsg;
	string strMsg[] = { "SPACE GAME!", "use Arrow Keys to move", "avoid the falling rocks","Score:","GAME OVER!","Your score is:" };


	gameState theGameState = MENU;
	btnTypes theBtnType = EXIT;

	float timePassed = 0.0f;
	float startTimePassed = 0.0f;
	startTimePassed = timeGetTime();
	
	float currentTime = 0.0f;
	float startTime = 0.0f;
	startTime = timeGetTime();
	

	ufoSprite.playMusic();

	//This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		timePassed = timeGetTime();

		if (timePassed - startTimePassed > 16800)
		{
			ufoSprite.playMusic();
			startTimePassed = timeGetTime();
		}

		float b = 0.0f;
		glm::vec2 t;

		switch (theGameState)
		{
		case MENU:
			startBkgd.render();

			playButton.setSpritePos(glm::vec2(200.0f, 350.0f));
			exitButton.setSpritePos(glm::vec2(500.0f, 350.0f));
			playButton.render();
			exitButton.render();

			theGameState = playButton.update(theGameState, PLAYING);
			exitButton.update();

			if (theGameState == PLAYING)
			{
				ufoSprite.playPress();
				startTime = timeGetTime();
			}


			outputMsg = strMsg[0];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(240, 100, 0.0f));
			outputMsg = strMsg[1];
			theFontMgr->getFont("Instructions")->printText(outputMsg.c_str(), FTPoint(330, 150, 0.0f));
			outputMsg = strMsg[2];
			theFontMgr->getFont("Instructions")->printText(outputMsg.c_str(), FTPoint(330, 200, 0.0f));
			if (exitButton.getClicked())
			{
				ufoSprite.playPress();
				SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
			}
			break;
		case PLAYING:
			
			t = ufoSprite.getSpritePos();
			b = t.x;

			if (b <= 0)
			{
				ufoSprite.updateLeft();
			}

			if (b > 0 && b < 700)
			{
				ufoSprite.update();
			}

			if (b >= 700)
			{
				ufoSprite.updateRight();
			}

			currentTime = timeGetTime();
			mainBkgd.render();

			outputMsg = strMsg[3];
			theFontMgr->getFont("Instructions")->printText(outputMsg.c_str(), FTPoint(20, 20, 0.0f));
			scoreMsg = score[sc];
			theFontMgr->getFont("Instructions")->printText(scoreMsg.c_str(), FTPoint(70, 20, 0.0f));

			
			ufoSprite.render();


			if (currentTime - startTime > 3000)
			{
				float x;
				x = rand() % 160;
				rock1Sprite.setSpritePos(glm::vec2(x, 0.0f));
			}

			if (currentTime - startTime > 3000)
			{
				float x;
				x = rand() % 160 + 160;
				rock2Sprite.setSpritePos(glm::vec2(x, 0.0f));
			}

			if (currentTime - startTime > 3000)
			{
				float x;
				x = rand() % 160 + 320;
				rock3Sprite.setSpritePos(glm::vec2(x, 0.0f));
			}

			if (currentTime - startTime > 3000)
			{
				float x;
				x = rand() % 160 + 480;
				rock4Sprite.setSpritePos(glm::vec2(x, 0.0f));
			}

			if (currentTime - startTime > 3000)
			{
				float x;
				x = rand() % 160 + 540;
				rock5Sprite.setSpritePos(glm::vec2(x, 0.0f));

				startTime = currentTime;
				sc++;
				ufoSprite.playRock();
			}

			if (ufoSprite.collidedWith(ufoSprite.getBoundingRect(), rock1Sprite.getBoundingRect())
				|| ufoSprite.collidedWith(ufoSprite.getBoundingRect(), rock2Sprite.getBoundingRect())
				|| ufoSprite.collidedWith(ufoSprite.getBoundingRect(), rock3Sprite.getBoundingRect())
				|| ufoSprite.collidedWith(ufoSprite.getBoundingRect(), rock4Sprite.getBoundingRect())
				|| ufoSprite.collidedWith(ufoSprite.getBoundingRect(), rock5Sprite.getBoundingRect()))
			{
				rock1Sprite.setSpritePos(glm::vec2(-100.0f, 0.0f));
				rock2Sprite.setSpritePos(glm::vec2(-100.0f, 0.0f));
				rock3Sprite.setSpritePos(glm::vec2(-100.0f, 0.0f));
				rock4Sprite.setSpritePos(glm::vec2(-100.0f, 0.0f));
				rock5Sprite.setSpritePos(glm::vec2(-100.0f, 0.0f));
				theGameState = END;
				ufoSprite.playHit();
				
			}
			

			rock1Sprite.updateRock();
			rock1Sprite.render();
			rock2Sprite.updateRock();
			rock2Sprite.render();
			rock3Sprite.updateRock();
			rock3Sprite.render();
			rock4Sprite.updateRock();
			rock4Sprite.render();
			rock5Sprite.updateRock();
			rock5Sprite.render();
			

			break;
		case END:
			endBkgd.render();

			replayButton.setClicked(false);
			exitButton.setClicked(false);

			replayButton.setSpritePos(glm::vec2(200.0f, 400.0f));
			exitButton.setSpritePos(glm::vec2(400.0f, 400.0f));
			replayButton.render();
			exitButton.render();

			theGameState = replayButton.update(theGameState, PLAYING);
			exitButton.update();

			if (theGameState == PLAYING)
			{
				ufoSprite.playPress();
				sc = 0;
			}

			outputMsg = strMsg[4];
			theFontMgr->getFont("Gameover")->printText(outputMsg.c_str(), FTPoint(200, 120, 0.0f));
			outputMsg = strMsg[5];
			theFontMgr->getFont("Instructions")->printText(outputMsg.c_str(), FTPoint(20, 20, 0.0f));
			scoreMsg = score[sc];
			theFontMgr->getFont("Instructions")->printText(scoreMsg.c_str(), FTPoint(130, 20, 0.0f));
			
			if (exitButton.getClicked())
			{
				ufoSprite.playPress();
				SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
			}

			break;
		}

		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER | theInputMgr->MOUSE_BUFFER);
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
