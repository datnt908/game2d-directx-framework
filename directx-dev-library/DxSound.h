#pragma once

#include "DSutil.h"
#include <unordered_map>

using namespace std;

class DxSound
{
// Attributes
private:
	static DxSound* instance;
	CSoundManager* soundManager;
	unordered_map<int, CSound*> soundStorage;

// Methods
public:
	static DxSound* getInstance();
	bool initialize();
	bool addSound(int id, LPCWSTR filepath);
	void playSound(int id, bool isLoop = false, LONG volume = 1L);
	void stopSound(int id);
};