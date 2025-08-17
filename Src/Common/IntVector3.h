#pragma once

struct IntVector3
{
public:

	int x;
	int y;
	int z;

	// �R���X�g���N�^
	IntVector3(void);
	// �R���X�g���N�^
	IntVector3(int vX, int vY, int vZ);
	// �f�X�g���N�^
	~IntVector3(void);

	//���Z
	const IntVector3 operator+(const IntVector3 _value)const;
	void operator+=(const IntVector3 _value);
	const IntVector3 operator-(const IntVector3 _value)const;
	void operator-=(const IntVector3 _value);
	const IntVector3 operator*(const int _value)const;
	void operator*=(const int _value);
	const IntVector3 operator/(const int _value)const;
	void operator/=(const int _value);

private:
};

