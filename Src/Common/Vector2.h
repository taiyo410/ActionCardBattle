#pragma once

class Vector2F;

class Vector2
{
public:

	int x;
	int y;

	// �R���X�g���N�^
	Vector2(void);

	// �R���X�g���N�^
	Vector2(int vX, int vY);

	// �f�X�g���N�^
	~Vector2(void);

	//Vector2�֕ϊ�����֐�
	Vector2F ToVector2F(void);
	
	//���K������
	Vector2 Normalize(void) const;

	//���������߂�
	float Length(void) const;

	//Vector2���m�̔�r
	static bool IsVector2(const Vector2 value1, const Vector2 value2);

	//Vector2���m�̒l������������r
	static bool IsSameVector2(const Vector2 value1, const Vector2 value2);

	//Vector2���m�̑����Z
	static Vector2 AddVector2(const Vector2 value1, const Vector2 value2);

	//Vector2���m�̈����Z
	static Vector2 SubVector2(const Vector2 value1, const Vector2 value2);

	//Vector2���m�̊|���Z
	static Vector2 MultiVector2(const Vector2 value1, const Vector2 value2);

};

