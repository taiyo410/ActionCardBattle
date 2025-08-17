#pragma once
#include <DxLib.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "../Common/Vector2.h"

class UtilityCommon
{
public:

	// ���W�A��(rad)�E�x(deg)�ϊ��p
	static constexpr float RAD2DEG = (180.0f / DX_PI_F);
	static constexpr float DEG2RAD = (DX_PI_F / 180.0f);

	//�J���[�R�[�h
	static constexpr int BLACK = 0x000000;	//��
	static constexpr int RED = 0xFF0000;	//��
	static constexpr int BLUE = 0x0000FF;	//��
	static constexpr int YELLOW = 0xFFFF00;	//���F
	static constexpr int GREEN = 0x008000;	//��
	static constexpr int CYAN = 0x00FFFF;	//���F
	static constexpr int PINK = 0xFFC0CB;	//���F
	static constexpr int ORANGE = 0xFFA500;	//�I�����W
	static constexpr int LIME = 0xADFF2F;	//����
	static constexpr int PURPLE = 0x800080;	//��
	static constexpr int WHITE = 0xFFFFFF;	//��
	static constexpr int GRAY = 0xBBBBBB;	//�D�F
	static constexpr int BROWN = 0x8B4513;	//���F

	// �l�̌ܓ�
	static int Round(float v);

	// ������̕���
	static std::vector <std::string> Split(std::string& line, char delimiter);

	// ���W�A��(rad)����x(deg)
	static double Rad2DegD(double rad);
	static float Rad2DegF(float rad);
	static int Rad2DegI(int rad);

	// �x(deg)���烉�W�A��(rad)
	static double Deg2RadD(double deg);
	static float Deg2RadF(float deg);
	static int Deg2RadI(int deg);

	// 0�`360�x�͈̔͂Ɏ��߂�
	static double DegIn360(double deg);

	// 0(0)�`2��(360�x)�͈̔͂Ɏ��߂�
	static double RadIn2PI(double rad);

	// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
	static int DirNearAroundRad(float from, float to);

	// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
	static int DirNearAroundDeg(float from, float to);

	// ���`���
	static int Lerp(int start, int end, float t);
	static float Lerp(float start, float end, float t);
	static double Lerp(double start, double end, double t);
	static Vector2 Lerp(const Vector2& start, const Vector2& end, float t);
	static VECTOR Lerp(const VECTOR& start, const VECTOR& end, float t);

	// �p�x�̐��`���
	static double LerpDeg(double start, double end, double t);

	// �F�̐��`���
	static COLOR_F Lerp(const COLOR_F& start, const COLOR_F& end, float t);

	// �x�W�F�Ȑ�
	static Vector2 Bezier(const Vector2& p1, const Vector2& p2, const Vector2& p3, float t);
	static VECTOR Bezier(const VECTOR& p1, const VECTOR& p2, const VECTOR& p3, float t);

	//�ҋ@����
	static bool IsTimeOver(float& totalTime, const float& waitTime);

	/// <summary>
	/// �͈͊O�̒l���w�肵���͈͂Ɏ��߂�
	/// </summary>
	/// <param name="index"></param>���߂����l
	/// <param name="max"></param>�͈͂̍ő�l
	/// <returns></returns>0����N-1�͈̔͂ɕ␳�����l
	static int WrapIndex(int index, int max);

	/// <summary>
	/// �C�[�Y�C��
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="start">�J�n�l</param>
	/// <param name="change">�ω���</param>
	/// /// <returns>�v�Z����</returns>
	static float EaseInQuad(const float time, const float start, const float change);

	/// <summary>
	/// �C�[�Y�A�E�g
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="start">�J�n�l</param>
	/// <param name="change">�ω���</param>
	/// <returns>�v�Z����</returns>
	static float EaseOutQuad(const float time, const float start, const float change);

	/// <summary>
	/// CSV�t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	/// <returns>�ǂݍ��񂾃f�[�^</returns>
	static std::vector<std::vector<int>> LoadCSVData(const std::wstring& filePath);
	
	/// <summary>
	/// string�I�u�W�F�N�g����(SJIS)����wstring�I�u�W�F�N�g�ɕϊ�
	/// </summary>
	/// <param name="str"></param>string�I�u�W�F�N�g
	/// <returns></returns>wstring�I�u�W�F�N�g
	static std::wstring GetWStringFromString(const std::string& str);

};