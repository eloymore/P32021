#include <OgreRoot.h>
#include "Entity.h"
#include "Transform.h"
#include "ComponentFactoryRegistration.h"
#include <btBulletDynamicsCommon.h>
#include "MotorLoop.h"

#if (defined _DEBUG) || !(defined _WIN32) //<-- Ya no lo tenemos en teor�a
int main() {
#else
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
    Ogre::Root* root;
    root = new Ogre::Root();
    //TODO: carne de canon de macro
    /*ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
    Entity* ent = new Entity();*/
    return 0;
}
