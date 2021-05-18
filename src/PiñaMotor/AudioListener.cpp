#include "AudioListener.h"
#include"fmod_errors.h"
#include "Entity.h"

AudioListener::AudioListener() { }

bool AudioListener::init(const std::map<std::string, std::string>& mapa) {
    _system = Audio::GetInstance()->getSystemFMOD();
    _result = Audio::GetInstance()->getResult();
    _trans = _myEntity->getComponent<Transform>();

    _p = _trans->position();
    _v = { 0,0,0 };
    _f = { 0,0,1 };
    _u = { 0,1,0 };
    _initialized = true;

    return true;
}

void AudioListener::set3DAtributes(Vector3<float> position, Vector3<float> velocity) {
    _p.x = position.x;
    _p.y = position.y;
    _p.z = position.z;

     if (_system != nullptr) {
         _result = _system->set3DListenerAttributes(0, &_p, &_v, &_f, &_u);
         errorCheck(_result);
     }
}

void AudioListener::update() {
 
    _p= _trans->position();

    if (_system != nullptr) {
        _result = _system->set3DListenerAttributes(0, &_p, &_v, &_f, &_u);
        errorCheck(_result);
    }
    _result = _system->update();
    errorCheck(_result);
  
}

void AudioListener::errorCheck(FMOD_RESULT result) {
    if (result != FMOD_RESULT::FMOD_OK)
        throw std::exception(FMOD_ErrorString(result));
}
