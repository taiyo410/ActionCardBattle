#include "GameScene.h"
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Manager/Resource/ResourceManager.h"
#include "../Manager/Resource/FontManager.h"
#include "PauseScene.h"

GameScene::GameScene(void)
{
	//�X�V�֐��̃Z�b�g
	updataFunc_ = std::bind(&GameScene::LoadingUpdate, this);
	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&GameScene::LoadingDraw, this);

	
}

GameScene::~GameScene(void)
{
	//�C���X�^���X�̍폜
}

void GameScene::Load(void)
{
	//�t�H���g�̓o�^
	buttnFontHandle_ = CreateFontToHandle(FontManager::FONT_DOT.c_str(), FONT_SIZE, 0);

	//�|�[�Y��ʂ̃��\�[�X
	pauseScene_ = std::make_shared<PauseScene>();
	pauseScene_->Load();

	PlayerManager::CreateInstance();
	PlayerManager::GetInstance().Load();
}

void GameScene::Init(void)
{
	PlayerManager::GetInstance().Init();
}

void GameScene::NormalUpdate(void)
{
	//�|�[�Y��ʂ֑J��
	if (inputMng_.IsTrgDown(KEY_INPUT_P))
	{
		scnMng_.PushScene(pauseScene_);
		return;
	}
	
	//�v���C���[�̍X�V
	PlayerManager::GetInstance().Update();

	//�f�o�b�O����
	DebagUpdate();
}

void GameScene::NormalDraw(void)
{
	//�f�o�b�O����
	DebagDraw();

	//�v���C���[�̕`��
	PlayerManager::GetInstance().Draw();
}

void GameScene::ChangeNormal(void)
{
	//�����ύX
	updataFunc_ = std::bind(&GameScene::NormalUpdate, this);
	drawFunc_ = std::bind(&GameScene::NormalDraw, this);
}

void GameScene::DebagUpdate(void)
{
	// �V�[���J��
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
	frame_++;
}

void GameScene::DebagDraw(void)
{
	DrawBox(
		0,
		0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0x00ff00,
		true
	);

	DrawFormatString(
		0, 0,
		0x000000,
		L"GameScene"
	);

	constexpr float r = 40.0f;
	float angle = DX_PI_F * 2.0f * static_cast<float>(frame_ % 360) / 60.0f;

	//�~�^����`��
	DrawCircleAA(
		320+cos(angle) * r, 
		240+sin(angle) * r,
		r, 
		32, 
		0xff8888, 
		true);
}
