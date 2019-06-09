#include "collisionHelper.h"

MovementBox::MovementBox()
{
	dtPosition = Vector2(0.f, 0.f);
	position = Vector2(0.f, 0.f);
	size = Vector2(0.f, 0.f);
}

BNDBOX MovementBox::getBndBox()
{
	BNDBOX result;

	if (dtPosition.x >= 0)
	{
		result.position.x = position.x;
		result.size.x = dtPosition.x + size.x;
	}
	else
	{
		result.position.x = position.x + dtPosition.x;
		result.size.x = size.x - dtPosition.x;
	}

	if (dtPosition.y >= 0)
	{
		result.position.y = position.y;
		result.size.y = dtPosition.y + size.y;
	}
	else
	{
		result.position.y = position.y + dtPosition.y;
		result.size.y = size.y - dtPosition.y;
	}

	return result;
}

CollisionEvent::CollisionEvent()
{
	colliTime = 0.f;
	gameObj = NULL;
	normal = Vector2(0, 0);
}

// Tính toán va chạm có vận tốc
// Mô tả kết quả trả về:
// normal == (0,0) và return == 1.f thì không có va chạm
// normal == (0,0) và return == 0.f thì overlap từ đầu
// normal != (0,0) thì có va chạm trong khoản thời gian return
float sweptAABB(MOVEBOX mObj, MOVEBOX sObj, Vector2 & normal)
{
	normal = Vector2(0, 0);
	BNDBOX bpb_mO = mObj.getBndBox();
	BNDBOX bpb_sO = sObj.getBndBox();

	/// 2 vùng ảnh hưởng không overlap thì không có va chạm
	if (!checkAABB_Box(bpb_mO, bpb_sO))
		return 1.0f;

	/// Nếu cả 2 k chuyển động tức vùng ảnh hưởng là vùng vật => overlap
	if (mObj.dtPosition == Vector2(0, 0) && sObj.dtPosition == Vector2(0, 0))
		return 0.f;

	/// Chuyển vận tốc về cho 1 đối tượng - tính tương đối vận tốc
	mObj.dtPosition -= sObj.dtPosition;
	sObj.dtPosition = Vector2(0, 0);

	/// Tính toán khoảng cách 2 mặt xa và 2 mặt gân theo từng chiều x, y
	Vector2 InvEntry(0, 0);
	Vector2 InvExit(0, 0);

	if (mObj.dtPosition.x > 0)
	{
		InvEntry.x = sObj.position.x - (mObj.position.x + mObj.size.x);
		InvExit.x = (sObj.position.x + sObj.size.x) - mObj.position.x;
	}
	else if (mObj.dtPosition.x < 0)
	{
		InvEntry.x = (sObj.position.x + sObj.size.x) - mObj.position.x;
		InvExit.x = sObj.position.x - (mObj.position.x + mObj.size.x);
	}

	if (mObj.dtPosition.y > 0)
	{
		InvEntry.y = sObj.position.y - (mObj.position.y + mObj.size.y);
		InvExit.y = (sObj.position.y + sObj.size.y) - mObj.position.y;
	}
	else if (mObj.dtPosition.y < 0)
	{
		InvEntry.y = (sObj.position.y + sObj.size.y) - mObj.position.y;
		InvExit.y = sObj.position.y - (mObj.position.y + mObj.size.y);
	}

	/// Tính toán thời gian bắt đầu(Entry) và kết thúc(Exit) va chạm theo từng chiều x, y
	Vector2 EntryT(0, 0);
	Vector2 ExitT(0, 0);

	if (mObj.dtPosition.x == 0)
	{
		EntryT.x = -std::numeric_limits<float>::infinity();
		ExitT.x = std::numeric_limits<float>::infinity();
	}
	else
	{
		EntryT.x = InvEntry.x / mObj.dtPosition.x;
		ExitT.x = InvExit.x / mObj.dtPosition.x;
	}

	if (mObj.dtPosition.y == 0)
	{
		EntryT.y = -std::numeric_limits<float>::infinity();
		ExitT.y = std::numeric_limits<float>::infinity();
	}
	else
	{
		EntryT.y = InvEntry.y / mObj.dtPosition.y;
		ExitT.y = InvExit.y / mObj.dtPosition.y;
	}

	float entryTime = max(EntryT.x, EntryT.y);
	float exitTime = min(ExitT.x, ExitT.y);

	if (entryTime > exitTime || EntryT.x > 1.0f || EntryT.y > 1.0f)
		return 1.0f;

	/// Trường hợp overlap ngay từ đầu
	if (entryTime < 0.0f)
	{
		/// Nếu chuyển động ra xa nhau thì xem như không overlap
		if (ExitT.x > abs(EntryT.x) || ExitT.y > abs(EntryT.y))
			return 0.f;
		else
			return 1.f;
	}

	/// Tính toán vector phản hồi va chạm
	if (EntryT.x > EntryT.y)
		normal.x = mObj.dtPosition.x < 0.0f ? 1.0f : -1.0f;
	else if (EntryT.x == EntryT.y)
	{
		normal.x = mObj.dtPosition.x < 0.0f ? 1.0f : -1.0f;
		normal.y = mObj.dtPosition.y < 0.0f ? 1.0f : -1.0f;
	}
	else
		normal.y = mObj.dtPosition.y < 0.0f ? 1.0f : -1.0f;

	return entryTime;
}