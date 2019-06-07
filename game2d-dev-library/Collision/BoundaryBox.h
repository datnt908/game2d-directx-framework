#pragma once
#include "game2dHelper.h"

class BoundaryBox
{
/// Attributes
public:
	Vector2 position;
	Vector2 size;
	Vector2 dtPosition; // Độ dịch chuyển ví trí của BoundaryBox

/// Methods
public:
	// Lấy ra box vùng ảnh hưởng của BoundaryBox
	BOX getBox(); 
};