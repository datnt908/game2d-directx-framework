#pragma once
#include <vector>
#include <unordered_map>
#include "DxHelper.h"

using namespace std;

/// Collision

/// Graphic

/// Object
class GameObject;

/// Space

/// Common
class BaseGameWorld;

/// typedef
typedef class GameObject* LPGAMEOBJ;
// Con trỏ Base Class phân hoạch không gian
typedef class BasePartitioning* LPSPACE;
// GameObjects dưới dạng mảng thứ tự
typedef vector<LPGAMEOBJ> GAMEOBJS_V;
// GameObjects dưới dạng mảng không thứ tự
typedef unordered_map<int, LPGAMEOBJ> GAMEOBJS_U;
// GameObjects dưới dạng ma trận, để phân loại GameObject
typedef unordered_map<int, GAMEOBJS_V> GAMEOBJS_M; 
