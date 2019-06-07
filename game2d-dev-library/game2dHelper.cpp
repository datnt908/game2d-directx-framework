#include <algorithm>
#include <fstream>
#include "game2dHelper.h"
#include "BoundaryBox.h"

bool checkAABB_Box(BOX box1, BOX box2)
{
	if (box1.position.x + box1.size.x <= box2.position.x)
		return false;
	if (box1.position.x >= box2.position.x + box2.size.x)
		return false;
	if (box1.position.y + box1.size.y <= box2.position.y)
		return false;
	if (box1.position.y >= box2.position.y + box2.size.y)
		return false;
	return true;
}

// Tính toán va chạm có vận tốc
// Mô tả kết quả trả về:
// normal == (0,0) và return == 1.f thì không có va chạm
// normal == (0,0) và return == 0.f thì overlap từ đầu
// normal != (0,0) thì có va chạm trong khoản thời gian return
float sweptAABB(BndBox mObj, BndBox sObj, Vector2 & normal)
{
	normal = Vector2(0, 0);
	BOX bpb_mO = mObj.getBox();
	BOX bpb_sO = sObj.getBox();

	/// 2 vùng ảnh hưởng không overlap thì không có va chạm
	if (!checkAABB_Box(bpb_mO, bpb_sO))
		return 1.0f;

	/// Không di chuyển xem như không va chạm
	if (mObj.dtPosition == Vector2(0, 0) && sObj.dtPosition == Vector2(0, 0))
		return 1.0f;

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
		if (ExitT.x < abs(EntryT.x) && ExitT.y < abs(EntryT.y))
			return 1.f;
		else
			return 0.f;
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

Vector2 transformWorldToView(Vector2 worldPos, Vector2 originPos)
{
	D3DXVECTOR4 result;
	D3DXMATRIX matrixTransform;
	D3DXVECTOR3 worldPos_3D(worldPos.x, worldPos.y, 0);
	
	D3DXMatrixIdentity(&matrixTransform);
	matrixTransform._22 = -1.f;
	matrixTransform._41 = -originPos.x;
	matrixTransform._42 = originPos.y;
	D3DXVec3Transform(&result, &worldPos_3D, &matrixTransform);

	return Vector2(result.x, result.y);
}

Vector2 transformViewToWorld(Vector2 viewPos, Vector2 originPos)
{
	D3DXVECTOR4 result;
	D3DXMATRIX matrixTransform;
	D3DXVECTOR3 viewPos_3D(viewPos.x, viewPos.y, 0);
	
	D3DXMatrixIdentity(&matrixTransform);
	matrixTransform._22 = -1.f;
	matrixTransform._41 = originPos.x;
	matrixTransform._42 = originPos.y;
	D3DXVec3Transform(&result, &viewPos_3D, &matrixTransform);

	return Vector2(result.x, result.y);
}

INTS getUnionInt(INTS v1, INTS v2)
{
	INTS dest1;

	std::set_union(v1.begin(), v1.end(),
		v2.begin(), v2.end(),
		std::back_inserter(dest1));

	return dest1;
}

STRINGS readFileText(string filepath)
{
	STRINGS lines;
	string line;
	ifstream myTextFile(filepath);
	if (myTextFile.is_open())
	{
		while (getline(myTextFile, line))
			lines.push_back(line);
		myTextFile.close();
	}

	return lines;
}

Vector2 getTextureSize(Texture texture)
{
	D3DSURFACE_DESC surfaceDesc;
	texture->GetLevelDesc(0, &surfaceDesc);
	return Vector2((float)surfaceDesc.Width, (float)surfaceDesc.Height);
}

void printOnOutput(LPCWSTR format, ...)
{
	va_list argp;
	va_start(argp, format);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, format, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
}

void printBndBoxOutput(BoundaryBox bb)
{
	printOnOutput(L"BB.Position = (%4.3f, %4.3f) - ", bb.position.x, bb.position.y);
	printOnOutput(L"BB.Size = (%4.3f, %4.3f) - ", bb.size.x, bb.size.y);
	printOnOutput(L"BB.Displayment = (%4.3f, %4.3f) - ", bb.dtPosition.x, bb.dtPosition.y);
	printOnOutput(L"\n");
}
