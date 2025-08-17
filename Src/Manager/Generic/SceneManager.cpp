#include <chrono>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../../Scene/TitleScene.h"
#include "../../Scene/GameScene.h"
#include "../Resource/ResourceManager.h"
#include "SceneManager.h"
#include "Camera.h"

void SceneManager::Init(void)
{

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	fader_ = std::make_unique<Fader>();
	fader_->Init();

	// �J����
	camera_ = std::make_shared<Camera>();
	camera_->Init();

	isSceneChanging_ = true;

	// �f���^�^�C��
	preTime_ = std::chrono::system_clock::now();

	//�E�B���h�E���A�N�e�B�u��ԂłȂ��Ƃ��������s��
	SetAlwaysRunFlag(true);

	// 3D�p�̐ݒ�
	Init3D();

	// �����V�[���̐ݒ�
	DoChangeScene(SCENE_ID::TITLE);
}

void SceneManager::Init3D(void)
{
	// �w�i�F�ݒ�
	SetBackgroundColor(0, 0, 0);

	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(true);

	// �o�b�N�J�����O��L���ɂ���
	SetUseBackCulling(true);

	// ���C�g�̐ݒ�
	SetUseLighting(true);
	
	// ���C�g�̐ݒ�
	ChangeLightTypeDir({ 0.3f, -0.7f, 0.8f });

	// �t�H�O�ݒ�
	SetFogEnable(true);
	SetFogColor(5, 5, 5);
	SetFogStartEnd(10000.0f, 20000.0f);

}

void SceneManager::Update(void)
{
	//if (scene_ == nullptr) { return; }

	// �f���^�^�C��
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;
	totalTime_ += deltaTime_;

	fader_->Update();
	if (isSceneChanging_)
	{
		Fade();
	}
	
	//�V�[�����Ƃ̍X�V
	scenes_.back()->Update();

	// �J�����X�V
	camera_->Update();

}

void SceneManager::Draw(void)
{
	
	// �`���O���t�B�b�N�̈�̎w��
	// (�R�c�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ�������
	ClearDrawScreen();

	// �J�����ݒ�
	camera_->SetBeforeDraw();

	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();

	// �`��
	for (auto& scene : scenes_)
	{
		scene->Draw();
	}

	// ��Ƀ|�X�g�G�t�F�N�g�p
	camera_->Draw();

	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
	
	// �Ó]�E���]
	fader_->Draw();

}

void SceneManager::CreateScene(std::shared_ptr<SceneBase> scene)
{
	if (scenes_.empty())
	{
		scenes_.push_back(scene);
	}
	else
	{
		scenes_.front() = scene;
	}

	//�f�[�^�̃��[�h
	scenes_.front()->Load();
}

void SceneManager::ChangeAllScene(std::shared_ptr<SceneBase> scene)
{
	////�t�F�[�h�J�n
	//StartFadeIn();

	//scenes_.clear();
	//scenes_.push_back(scene);
	////�f�[�^�̃��[�h
	//scenes_.front()->LoadData();
}

void SceneManager::PushScene(std::shared_ptr<SceneBase> scene)
{
	scene->Init();
	scenes_.push_back(scene);
}

void SceneManager::PopScene()
{
	if (scenes_.size() >= 1)
	{
		scenes_.pop_back();
	}
}

void SceneManager::Release(void)
{
	//�S�ẴV�[���Ŏg���V���O���g���N���X�⃊�\�[�X�͂����ŉ������
}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	// �t�F�[�h�������I����Ă���V�[����ς���ꍇ�����邽�߁A
	// �J�ڐ�V�[���������o�ϐ��ɕێ�
	waitSceneId_ = nextId;

	// �t�F�[�h�A�E�g(�Ó])���J�n����
	fader_->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;

}

void SceneManager::StartFadeIn(void)
{
	//�t�F�[�h�𖾂���
	fader_->SetFade(Fader::STATE::FADE_IN);

	//�V�[���`�F���W
	isSceneChanging_ = false;
}

SceneManager::SceneManager(void)
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	scenes_.clear();
	fader_ = nullptr;

	isSceneChanging_ = false;

	// �f���^�^�C��
	deltaTime_ = 1.0f / 60.0f;

	camera_ = nullptr;

	totalTime_ = -1.0f;

}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{
	// ���\�[�X�̉��
	ResourceManager::GetInstance().SceneChangeRelease();

	// �V�[����ύX����
	sceneId_ = sceneId;

	// ���݂̃V�[��������i��`�F�b�N����j
	if (!scenes_.empty() && scenes_.back() != nullptr)
	{
		scenes_.back().reset();
		scenes_.pop_back(); // �V�[�����g���I������̂Ń��X�g������폜
	}

	//�V�[������
	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		CreateScene(std::make_unique<TitleScene>());
		break;
	case SCENE_ID::GAME:
		CreateScene(std::make_unique<GameScene>());
		break;
	}

	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;

}

void SceneManager::Fade(void)
{

	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		// ���]��
		if (fader_->IsEnd())
		{
			// ���]���I��������A�t�F�[�h�����I��
			fader_->SetFade(Fader::STATE::NONE);
			//isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		// �Ó]��
		if (fader_->IsEnd())
		{
			// ���S�ɈÓ]���Ă���V�[���J��
			DoChangeScene(waitSceneId_);
			// �Ó]���疾�]��
			//fader_->SetFade(Fader::STATE::FADE_IN);
			fader_->SetFade(Fader::STATE::NONE);
		}
		break;
	}
}