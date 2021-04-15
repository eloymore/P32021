#pragma once
#include "OgreSceneManager.h"
#include "OgreRoot.h"

class OgreInstance {
public:
	/// <summary>
	/// Devuelve una instancia de la clase. La crea si no existe.
	/// </summary>
	static OgreInstance* getInstance();

	/// <summary>
	/// devuelve un puntero de mSM que es el sceneManager
	/// </summary>
	Ogre::SceneManager* getmSM() {
		return _mSM;
	}

	/// <summary>
	/// Crea un sceneManager si no existe uno
	/// </summary>
	Ogre::SceneManager* createmSM(Ogre::Root* mRoot) {
		if(_mSM==nullptr)
			_mSM = mRoot->createSceneManager();
	}

protected:
	static OgreInstance* _singleton;
	Ogre::SceneManager* _mSM = nullptr;
};