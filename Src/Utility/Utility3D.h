#pragma once
#include <DxLib.h>
#include "../Common/Vector2.h"
#include "../Common/Quaternion.h"

class Utility3D
{
public:

	//VECTOR�̏�����
	static constexpr VECTOR VECTOR_ZERO = { 0.0f, 0.0f, 0.0f };
	static constexpr VECTOR VECTOR_ONE = { 1.0f, 1.0f, 1.0f };

	// ��]��
	static constexpr VECTOR AXIS_X = { 1.0f, 0.0f, 0.0f };
	static constexpr VECTOR AXIS_Y = { 0.0f, 1.0f, 0.0f };
	static constexpr VECTOR AXIS_Z = { 0.0f, 0.0f, 1.0f };
	static constexpr VECTOR AXIS_XZ = { 1.0f, 0.0f, 1.0f };
	static constexpr VECTOR AXIS_XYZ = { 1.0f, 1.0f, 1.0f };

	// ����
	static constexpr VECTOR DIR_F = { 0.0f, 0.0f, 1.0f };
	static constexpr VECTOR DIR_B = { 0.0f, 0.0f, -1.0f };
	static constexpr VECTOR DIR_R = { 1.0f, 0.0f, 0.0f };
	static constexpr VECTOR DIR_L = { -1.0f, 0.0f, 0.0f };
	static constexpr VECTOR DIR_U = { 0.0f, 1.0f, 0.0f };
	static constexpr VECTOR DIR_D = { 0.0f, -1.0f, 0.0f };

	static constexpr float kEpsilonNormalSqrt = 1e-15F;

	// Y����]
	static VECTOR RotXZPos(const VECTOR& centerPos, const VECTOR& radiusPos, float rad);

	// �x�N�g���̒���
	static double Magnitude(const VECTOR& v);
	static float MagnitudeF(const VECTOR& v);
	static float SqrMagnitudeF(const VECTOR& v);
	static double SqrMagnitude(const VECTOR& v);
	static double SqrMagnitude(const VECTOR& v1, const VECTOR& v2);
	static double Distance(const VECTOR& v1, const VECTOR& v2);

	// ���̓��m�̏Փ˔���
	static bool IsHitSpheres(
		const VECTOR& pos1, float radius1, const VECTOR& pos2, float radius2);

	// ���̂ƃJ�v�Z���̏Փ˔���
	static bool IsHitSphereCapsule(
		const VECTOR& sphPos, float sphRadius,
		const VECTOR& capPos1, const VECTOR& capPos2, float capRadius);

	// ��r
	static bool Equals(const VECTOR& v1, const VECTOR& v2);
	static bool EqualsVZero(const VECTOR& v1);

	// ���K��
	static VECTOR Normalize(const Vector2& v);
	static VECTOR VNormalize(const VECTOR& v);

	// 2�̃x�N�g���̊Ԃ̊p�x
	static double AngleDeg(const VECTOR& from, const VECTOR& to);

	/// <summary>
	/// �Ƃ���_����Ƃ���_�܂ł̈ړ��x�N�g����Ԃ�
	/// </summary>
	/// <param name="_start">�_����</param>
	/// <param name="_goal">��������</param>
	/// <param name="_speed">�ݒ葬�x(���ݒ肾�ƁA�����x�N�g���݂̂�Ԃ�)</param>
	/// <returns>��������܂ł̈ړ��x�N�g��</returns>
	static const VECTOR GetMoveVec(const VECTOR _start, const VECTOR _goal, const float _speed = 1.0f);

	/// <summary>
	/// �ΏۂɌ�������]��
	/// </summary>
	/// <param name="_pos">���g�̍��W</param>
	/// <param name="_targetPos">�Ώۂ̍��W</param>
	/// <param name="_needAxis">�K�v�ȉ�]��</param>
	/// <returns>��]��</returns>
	static const VECTOR GetRotAxisToTarget(const VECTOR _pos, const VECTOR _targetPos, const VECTOR _needAxis = AXIS_XYZ);

	/// <summary>
/// ���W�𑫂��ĉ�]
/// </summary>
/// <param name="_followPos">�Ǐ]�Ώۂ̍��W</param>
/// <param name="_followRot">�Ǐ]�Ώۂ̊p�x</param>
/// <param name="_localPos">���΍��W</param>
	VECTOR AddPosRotate(VECTOR _followPos, Quaternion _followRot, VECTOR _localPos);

};

