#pragma once

class Vector2;

class Vector2F
{
public:

	//�f�t�H���g�R���X�g���N�^
	Vector2F(void);

	//�R���X�g���N�^
	Vector2F(float ix, float iy);

	//�f�X�g���N�^
	~Vector2F(void);

	//Vector2�֕ϊ�����֐�
	Vector2 ToVector2(void);

	//�x�N�g���������
	Vector2F CreateVectorLine(Vector2 value1, Vector2 value2);

	//Vector2F���m�̔�r
	static bool IsVector2F(const Vector2F value1, const Vector2F value2);

	//Vector2F���m�̒l����������r
	static bool IsSameVector2F(const Vector2F value1, const Vector2F value2);

	//Vector2F���m�̉��Z
	static Vector2F AddVector2F(Vector2F value1, Vector2F value2);

	//Vector2F���m�̌��Z
	static Vector2F SubVector2F(Vector2F value1, Vector2F value2);

	//Vector2F���m�̏�Z
	static Vector2F MulVector2F(Vector2F value1, Vector2F value2);

	//Vector2F���m�̏��Z
	static Vector2F DivVector2F(Vector2F value1, Vector2F value2);

	float x;
	float y;

private:
};