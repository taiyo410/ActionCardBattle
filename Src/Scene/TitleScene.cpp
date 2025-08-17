#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Manager/Generic/InputManagerS.h"
#include "../Manager/Resource/ResourceManager.h"
#include "../Manager/Resource/FontManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
	//�X�V�֐��̃Z�b�g
	updataFunc_ = std::bind(&TitleScene::LoadingUpdate, this);
	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&TitleScene::LoadingDraw, this);
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Load(void)
{
	//�t�H���g�̓o�^
	buttnFontHandle_ = CreateFontToHandle(FontManager::FONT_DOT.c_str(), FONT_SIZE, 0);
}

void TitleScene::Init(void)
{
}

void TitleScene::NormalUpdate(void)
{	
	// �V�[���J��
	InputManager& ins = InputManager::GetInstance();
	InputManagerS& insS = InputManagerS::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
	else if (insS.IsTrgDown(INPUT_EVENT::OK))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}

void TitleScene::NormalDraw(void)
{
	DrawBox(
		0,
		0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0x0000ff,
		true
	);

	DrawFormatString(
		0, 0,
		0x000000,
		L"TitleScene"
	);
}

void TitleScene::ChangeNormal(void)
{
	//�����ύX
	updataFunc_ = std::bind(&TitleScene::NormalUpdate, this);
	drawFunc_ = std::bind(&TitleScene::NormalDraw, this);
}

