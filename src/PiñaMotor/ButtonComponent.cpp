#include "ButtonComponent.h"
#include "Entity.h"
#include "Gui.h"
#include "MotorLoop.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>

bool ButtonComponent::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("text") == mapa.end() || mapa.find("position") == mapa.end() || mapa.find("size") == mapa.end() ||
		mapa.find("name") == mapa.end() || mapa.find("type") == mapa.end() || mapa.find("showCursor") == mapa.end() ||
		mapa.find("normal") == mapa.end() || mapa.find("normalImage") == mapa.end() ||
		mapa.find("continueBullet") == mapa.end() || mapa.find("nextScene") == mapa.end()) return false;
	
	std::string t = mapa.at("text");
	
	std::string p = mapa.at("position");
	std::string::size_type pa = 0, pb = 0;
	float a = std::stof(p, &pa);
	float b = std::stof(p.substr(pa + 1), &pb);
	
	std::string s = mapa.at("size");
	std::string::size_type sa = 0, sb = 0;
	float x = std::stof(s, &sa);
	float y = std::stof(s.substr(sa + 1), &sb);
	
	std::string n = mapa.at("name");
	
	_button = Gui::GetInstance()->createButton(t, glm::vec2(a, b), glm::vec2(x, y), n);
	_button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonComponent::onClick, this));
	
	std::string ty = mapa.at("type");
	if (ty == "EXIT")
		_buttonType = ButtonType::EXIT;
	else if (ty == "RESUME")
		_buttonType = ButtonType::RESUME;
	else {
		_buttonType = ButtonType::CHANGE_SCENE;
		std::string nS = mapa.at("nextScene");
		_nextScene = nS;
	}
	if (mapa.at("showCursor") == "true")
		Gui::GetInstance()->setMouseVisibility(true);

	// Propiedades
	std::string pN = mapa.at("normal");
	std::string pNI = mapa.at("normalImage");
	_button->setProperty(pN, pNI);
	
	//para despausar el mundo de bulet
	if (mapa.at("continueBullet") == "true")
		_continueBullet = true;
	
	return true;
}

void ButtonComponent::onClick() {
	switch (_buttonType) {
	case ButtonType::CHANGE_SCENE:
		SceneManager::GetInstance()->newScene(_nextScene, _continueBullet);
		break;
	case ButtonType::RESUME:
		SceneManager::GetInstance()->continueScene();
		Gui::GetInstance()->setMouseVisibility(false);
		break;
	case ButtonType::EXIT:
		MotorLoop::GetInstance()->stopLoop();
		break;
	}
}
ButtonComponent::~ButtonComponent() {
	CEGUI::WindowManager::getSingleton().destroyWindow(_button);
}