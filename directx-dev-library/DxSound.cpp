#include "DxSound.h"
#include "DxGraphic.h"

DxSound* DxSound::instance = NULL;

DxSound * DxSound::getInstance()
{
	if (instance == NULL)
		instance = new DxSound();
	return instance;
}

bool DxSound::initialize()
{
	soundManager = new CSoundManager();
	HRESULT result;
	result = soundManager->Initialize(DxGraphic::getInstance()->window, DSSCL_PRIORITY);
	if (result != DS_OK)
		return false;
	result = soundManager->SetPrimaryBufferFormat(2, 22050, 16);
	if (result != DS_OK)
		return false;
	return true;
}

bool DxSound::addSound(int id, LPCWSTR filepath)
{
	if (soundManager == NULL)
		return false;
	CSound *wave;
	HRESULT result = soundManager->Create(&wave, const_cast<LPTSTR>(filepath));
	if (result != DS_OK)
		return false;
	soundStorage[id] = wave;
	return true;
}

void DxSound::playSound(int id, bool isLoop, LONG volume)
{
	if (soundStorage[id] != NULL)
		soundStorage[id]->Play(0, isLoop, volume);
}

void DxSound::stopSound(int id)
{
	if (soundStorage[id] != NULL)
		soundStorage[id]->Stop();
}
