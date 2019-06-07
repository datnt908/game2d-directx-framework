#pragma once
#include <vector>
#include <unordered_map>
#include "DxHelper.h"

using namespace std;


#define OBJ_KIND_WEIGHT 100


/// Collision
// class BoundaryBox cho xét va chạm chó chuyển động
class BoundaryBox;
class CollisionEvent;
// struct BroadphaseBox cho xét 2 rect overlap 
struct BroadphaseBox {
	Vector2 position;
	Vector2 size;
};

/// Graphic

/// Object
class GameObject;

/// Space

/// Common
class BaseGameWorld;

/// typedef
typedef class GameObject* LPGAMEOBJ;
typedef struct BroadphaseBox BOX;
typedef class BoundaryBox BndBox;
typedef class CollisionEvent COLLIEVENT;
// Con trỏ Base Class phân hoạch không gian
typedef class BasePartitioning* LPSPACE;
// GameObjects dưới dạng mảng thứ tự
typedef vector<LPGAMEOBJ> GAMEOBJS_V;
// GameObjects dưới dạng mảng không thứ tự
typedef unordered_map<int, LPGAMEOBJ> GAMEOBJS_U;
// GameObjects dưới dạng ma trận, để phân loại GameObject
typedef unordered_map<int, GAMEOBJS_V> GAMEOBJS_M; 

