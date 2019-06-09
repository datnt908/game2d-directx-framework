#pragma once
#include <unordered_map>
#include "DSutil.h"

using namespace std;

class DxSound
{
/// Attributes
private:
	static DxSound* instance;
	CSoundManager* soundManager;
	unordered_map<int, CSound*> soundStorage;

/// Methods
private:
	DxSound();
public:
	static DxSound* getInstance();
	~DxSound();
	bool initialize();
	bool addSound(int id, LPCWSTR filepath);
	void playSound(int id, bool isLoop = false, LONG volume = 1L);
	void stopSound(int id);
};