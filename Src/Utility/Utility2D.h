#pragma once
#include "../Common/Vector2.h"

class Utility2D
{
public:

	//�x�N�g���̒���
	static double Magnitude(const Vector2& v);
	static int SqrMagnitude(const Vector2& v);
	static double Distance(const Vector2& v1, const Vector2& v2);

	/// <summary>
	/// ���[���h���W���}�b�v���W��
	/// </summary>
	/// <param name="worldPos">���[���h���W</param>
	/// <param name="mapSize">�}�b�v�`�b�v���̃T�C�Y</param>
	/// <returns>�}�b�v���W</returns>
	static Vector2 WorldToMapPos(const Vector2& worldPos, const Vector2& mapSize);

	/// <summary>
	/// �}�b�v���W�����[���h���W��
	/// </summary>
	/// <param name="mapPos">�}�b�v���W</param>
	/// <param name="mapSize">�}�b�v�`�b�v���̃T�C�Y</param>
	/// <returns>���[���h���W</returns>
	static Vector2 MapToWorldPos(const Vector2& mapPos, const Vector2& mapSize);

	/// <summary>
	/// �~���m�̏Փ˔���
	/// </summary>
	/// <param name="circlePos1">�~���W1</param>
	/// <param name="radius1">�~���a1</param>
	/// <param name="circlePos2">�~���W2</param>
	/// <param name="radius2">�~���a2</param>
	/// <returns>�Փ˂��Ă���true, ��������Ȃ��ꍇfalse</returns>
	static bool IsHitCircles(const Vector2& circlePos1, const float radius1, const Vector2& circlePos2, const float radius2);

};

