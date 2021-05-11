#pragma once
//#include <CEGUI/CEGUI.h>
//#include <CEGUI/MouseCursor.h>
//#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <Ogre.h>
#include <iostream>

class Gui : public Ogre::FrameListener {
public:
	Gui();
	~Gui();

	static Gui* GetInstance();

	static bool Init();

private:
	static Gui* _guiInstance;

	Ogre::RenderWindow* _mWindow = nullptr;
	//CEGUI::OgreRenderer* _mRenderer = nullptr;
	Ogre::Root* _mRoot = nullptr;
	//CEGUI::GUIContext* _mContext = nullptr;

	//CEGUI::Window* _sheet = nullptr;
	//CEGUI::WindowManager* _mWindowManager = nullptr;
};