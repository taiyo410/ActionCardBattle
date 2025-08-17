#pragma once
#include <DxLib.h>
#include "../Common/Quaternion.h"

class UtilityDraw
{
public:

	// �`��n
	static void DrawLineDir(const VECTOR& pos, const VECTOR& dir, int color, float len = 50.0f);
	static void DrawLineXYZ(const VECTOR& pos, const MATRIX& rot, float len = 50.0f);
	static void DrawLineXYZ(const VECTOR& pos, const Quaternion& rot, float len = 50.0f);

	/// <summary>
	/// �_����`�悷��
	/// </summary>
	/// <param name="sPos">�n�_</param>
	/// <param name="ePos">�I�_</param>
	/// <param name="color">�F</param>
	/// <param name="len">�Ԋu</param>
	static void DrawPointLine3D(const VECTOR sPos, const VECTOR ePos, int color, float len = 50.0f);
};

