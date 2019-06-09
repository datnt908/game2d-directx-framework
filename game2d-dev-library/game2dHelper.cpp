#include <algorithm>
#include <fstream>
#include "game2dHelper.h"
#include "collisionHelper.h"

bool checkAABB_Box(BNDBOX box1, BNDBOX box2)
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

void printBndBoxOutput(MovementBox bb)
{
	printOnOutput(L"BB.Position = (%4.3f, %4.3f) - ", bb.position.x, bb.position.y);
	printOnOutput(L"BB.Size = (%4.3f, %4.3f) - ", bb.size.x, bb.size.y);
	printOnOutput(L"BB.Displayment = (%4.3f, %4.3f) - ", bb.dtPosition.x, bb.dtPosition.y);
	printOnOutput(L"\n");
}

BoundaryBox::BoundaryBox()
{
	position = Vector2(0.f, 0.f);
	size = Vector2(0.f, 0.f);
}
