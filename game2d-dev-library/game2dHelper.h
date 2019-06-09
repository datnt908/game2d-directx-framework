#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "DxHelper.h"

using namespace std;

#define OBJ_KIND_WEIGHT 100

struct BoundaryBox {
	Vector2 position;
	Vector2 size;
	BoundaryBox();
};
typedef struct BoundaryBox BNDBOX;

/// Object
class GameObject;
class InteractiveObj;
typedef class GameObject* LPGAMEOBJ;

/// Graphic
class TextureCollection;
class Sprite;
class Animation;
class AnimationCollection;



/// Space
class SpacePartitioning;
class Node;

/// Common
class BaseGameWorld;
class BaseTileMap;

/// typedef
typedef vector<int> INTS;
typedef vector<string> STRINGS;
typedef class SpacePartitioning SPACE;
typedef class TextureCollection TEXTURES;
typedef vector<Sprite*> SPRITES;
typedef class Animation* LPANI;
typedef class AnimationCollection* LPANIS;
// Con trỏ hàm cho event kết thúc 1 animation
typedef void(*EndAnimationEvent)();
// Con trỏ Base Class phân hoạch không gian
typedef class BasePartitioning* LPSPACE;
// GameObjects dưới dạng mảng thứ tự
typedef vector<LPGAMEOBJ> GAMEOBJS_V;
// GameObjects dưới dạng mảng không thứ tự
typedef unordered_map<int, LPGAMEOBJ> GAMEOBJS_U;
// GameObjects dưới dạng ma trận, để phân loại GameObject
typedef unordered_map<int, GAMEOBJS_V> GAMEOBJS_M; 

/// Functions
// Kiểm tra overlap của 2 Box
bool checkAABB_Box(BNDBOX box1, BNDBOX box2);
// Biến đổi WorldPos sang ViewPos với gốc tọa độ(OriginPos) của ViewPort
Vector2 transformWorldToView(Vector2 worldPos, Vector2 originPos);
// Biến đổi ViewPos sang WorldPos với gốc tọa độ(OriginPos) của ViewPort
Vector2 transformViewToWorld(Vector2 viewPos, Vector2 originPos);
// Lấy phép hội 2 tập hợp số nguyên
INTS getUnionInt(INTS v1, INTS v2);
STRINGS readFileText(string filepath);
Vector2 getTextureSize(Texture texture);
// In ra màn hình Output
void printOnOutput(LPCWSTR format, ...);
