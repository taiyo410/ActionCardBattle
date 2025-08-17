#pragma once
#include <string>
#include "Template/Singleton.h"

class FpsControl;
class FontManager;

class Application : public Singleton<Application>
{
	friend class Singleton<Application>; 

public:

	// �X�N���[���T�C�Y
	static constexpr int SCREEN_SIZE_X = 1024;
	static constexpr int SCREEN_SIZE_Y = 640;

	// �X�N���[���T�C�Y�n�[�t
	static constexpr int SCREEN_HALF_X = SCREEN_SIZE_X / 2;
	static constexpr int SCREEN_HALF_Y = SCREEN_SIZE_Y / 2;

	// �f�[�^�p�X�֘A
	//-------------------------------------------
	static const std::wstring PATH_IMAGE;
	static const std::wstring PATH_MODEL;
	static const std::wstring PATH_EFFECT;
	static const std::wstring PATH_SOUND;
	static const std::wstring PATH_FONT;
	static const std::wstring PATH_TEXT;
	static const std::wstring PATH_JSON;
	static const std::wstring PATH_CSV;
	static const std::wstring PATH_SHADER;
	//-------------------------------------------

	/// <summary>
	/// ������
	/// </summary>
	/// <param name=""></param>
	/// <returns>�����������̏ꍇtrue,��������Ȃ��ꍇfalse</returns>
	bool Init();

	/// <summary>
	/// �Q�[���̎��s���[�v
	/// </summary>
	/// <param name=""></param>
	void Run();

	/// <summary>
	/// ���\�[�X�̔j��
	/// </summary>
	/// <param name=""></param>
	/// <returns>��������̏ꍇtrue,��������Ȃ��ꍇfalse</returns>
	bool Release();

private:

	//FPS
	std::unique_ptr<FpsControl> fps_;

	//�t�H���g
	std::unique_ptr<FontManager> fontMng_;

	//�R���X�g���N�^
	Application();

	//�f�X�g���N�^
	~Application() = default;

	// Effekseer�̏�����
	void InitEffekseer();

};