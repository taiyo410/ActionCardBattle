#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "Manager/Generic/SceneManager.h"
#include "Manager/Generic/InputManager.h"
#include "Manager/Generic/InputManagerS.h"
#include "Manager/Resource/ResourceManager.h"
#include "Manager/Resource/FontManager.h"
#include "FpsControl/FpsControl.h"
#include "Application.h"

const std::wstring Application::PATH_IMAGE = L"Data/Image/";
const std::wstring Application::PATH_MODEL = L"Data/Model/";
const std::wstring Application::PATH_EFFECT = L"Data/Effect/";
const std::wstring Application::PATH_SOUND = L"Data/Sound/";
const std::wstring Application::PATH_FONT = L"Data/Font/";
const std::wstring Application::PATH_TEXT = L"Data/Text/";
const std::wstring Application::PATH_JSON = L"Data/JSON/";
const std::wstring Application::PATH_CSV = L"Data/CSV/";
const std::wstring Application::PATH_SHADER = L"Data/Shader/";

bool Application::Init()
{

	// �A�v���P�[�V�����̏����ݒ�
	SetWindowText(L"BaseProject.ver1.2");

	// �E�B���h�E�T�C�Y
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	// DxLib�̏�����
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	if (DxLib_Init() == -1)
	{
		return false;
	}

	// Effekseer�̏�����
	InitEffekseer();

	// �L�[���䏉����
	SetUseDirectInputFlag(true);
	InputManager::CreateInstance();			//����
	InputManagerS::CreateInstance();			//����
	InputManager::GetInstance().Init();		//������
	InputManagerS::GetInstance().Init();		//������

	// ���\�[�X�Ǘ�������
	ResourceManager::CreateInstance();
	ResourceManager::GetInstance().Init();

	// �V�[���Ǘ�������
	SceneManager::CreateInstance();		
	SceneManager::GetInstance().Init();	

	// FPS������
	fps_ = std::make_unique<FpsControl>();
	fps_->Init();

	// �t�H���g�Ǘ�������
	fontMng_ = std::make_unique<FontManager>();
	fontMng_->Init();

	return true;
}

void Application::Run()
{
	LONGLONG time = GetNowHiPerformanceCount();

	auto& inputManager = InputManager::GetInstance();
	auto& inputManagerS = InputManagerS::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�t���[�����[�g���X�V
		if (!fps_->UpdateFrameRate()) continue;

		//�X�V����
		inputManager.Update();
		inputManagerS.Update();
		sceneManager.Update();

		//�`�揈��
		sceneManager.Draw();

		//�t���[�����[�g�v�Z
		fps_->CalcFrameRate();

		ScreenFlip();
	}

}

bool Application::Release()
{
	//�e�N���X�̃��\�[�X�̔j��
	InputManager::GetInstance().Release();
	InputManagerS::GetInstance().Release();
	ResourceManager::GetInstance().Release();
	SceneManager::GetInstance().Release();

	//�C���X�^���X�̔j��
	fontMng_->Destroy();
	InputManager::GetInstance().Destroy();
	InputManagerS::GetInstance().Destroy();
	ResourceManager::GetInstance().Destroy();
	SceneManager::GetInstance().Destroy();

	// Effekseer���I������B
	Effkseer_End();

	// DxLib�I��
	if (DxLib_End() == -1)
	{
		return false;
	}

	return true;
}

Application::Application()
{
	fps_ = nullptr;
	fontMng_ = nullptr;
}

void Application::InitEffekseer()
{
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
}
