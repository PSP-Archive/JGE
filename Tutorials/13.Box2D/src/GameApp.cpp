//-------------------------------------------------------------------------------------
//
// JGE++ is a hardware accelerated 2D game SDK for PSP/Windows.
//
// Licensed under the BSD license, see LICENSE in JGE root for details.
// 
// Copyright (c) 2007 James Hui (a.k.a. Dr.Watson) <jhkhui@gmail.com>
// 
//-------------------------------------------------------------------------------------

#include <stdio.h>

#include <JGE.h>
#include <JRenderer.h>
#include <JLBFont.h>
#include <JTypes.h>

#include "FlyingBox.h"
#include "FrictionTest.h"

#include "GameApp.h"



//-------------------------------------------------------------------------------------
// Constructor. Variables can be initialized here.
//
//-------------------------------------------------------------------------------------
GameApp::GameApp()
{
	mBox2D = NULL;
}


//-------------------------------------------------------------------------------------
// Destructor.
//
//-------------------------------------------------------------------------------------
GameApp::~GameApp()
{
	
}


//-------------------------------------------------------------------------------------
// This is the init callback function. You should load and create your in-game 
// resources here.
// 
//-------------------------------------------------------------------------------------
void GameApp::Create()
{
	mCurr = 0;

	Reset();

}


void GameApp::Reset()
{

	SAFE_DELETE(mBox2D);

	switch (mCurr)
	{
	case 0:
		mBox2D = new FlyingBox();
		break;
	case 1:
		mBox2D = new FrictionTest();
		break;
	}
	
	mBox2D->Create();
}


//-------------------------------------------------------------------------------------
// This is the clean up callback function. You should delete all your in-game 
// resources, for example texture and quads, here.
// 
//-------------------------------------------------------------------------------------
void GameApp::Destroy()
{
	SAFE_DELETE(mBox2D);

}


//-------------------------------------------------------------------------------------
// This is the update callback function and is called at each update frame
// before rendering. You should update the game logic here.
//
//-------------------------------------------------------------------------------------
void GameApp::Update()
{

	JGE* engine = JGE::GetInstance();

	// do a screen shot when the TRIANGLE button is pressed
	if (engine->GetButtonClick(PSP_CTRL_TRIANGLE))		
	{
		char s[80];

		// save screen shot to root of Memory Stick 
		sprintf(s, "ms0:/screenshot.png");				
		JRenderer::GetInstance()->ScreenShot(s);
	}

	// exit when the CROSS button is pressed
	if (engine->GetButtonClick(PSP_CTRL_CROSS))	
	{
		engine->End();
		return;
	}

	if (engine->GetButtonClick(PSP_CTRL_CIRCLE))	
	{
		Reset();
		return;
	}

	if (engine->GetButtonClick(PSP_CTRL_RIGHT))
	{

		mCurr++;
		if (mCurr >= DEMO_COUNT)
			mCurr = 0;
		Reset();
		return;
	}

	if (engine->GetButtonClick(PSP_CTRL_LEFT))
	{

		mCurr--;
		if (mCurr < 0)
			mCurr = DEMO_COUNT-1;
		Reset();
		return;
	}

	float dt = engine->GetDelta();		// Get time elapsed since last update.

	//
	// Your updating code here...
	//

	if (mBox2D)
		mBox2D->Update(dt);
	
	

}


//-------------------------------------------------------------------------------------
// All rendering operations should be done in Render() only.
// 
//-------------------------------------------------------------------------------------
void GameApp::Render()
{

	// get JRenderer instance
	JRenderer* renderer = JRenderer::GetInstance();		

	// clear screen to black
	renderer->ClearScreen(ARGB(255,128,128,128));

	//
	// Your rendering code here...
	//

	if (mBox2D)	
		mBox2D->Render();
	

}


//-------------------------------------------------------------------------------------
// This function is called when the system wants to pause the game. You can set a flag
// here to stop the update loop and audio playback.
//
//-------------------------------------------------------------------------------------
void GameApp::Pause()
{
	
}


//-------------------------------------------------------------------------------------
// This function is called when the game returns from the pause state.
//
//-------------------------------------------------------------------------------------
void GameApp::Resume()
{
	
}
