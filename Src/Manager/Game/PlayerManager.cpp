#include<cmath>
#include"../../Utility/Utility3D.h"
#include"../../Utility/UtilityCommon.h"
#include"../../Manager/Resource/ResourceManager.h"
#include"../../Manager/Generic/Camera.h"
//#include"../../Manager/System/SoundManager.h"
//#include"../System/DateBank.h"
#include "PlayerManager.h"
PlayerManager* PlayerManager::instance_ = nullptr;


PlayerManager::PlayerManager(void)
{
	playerNum_ = 1;
}

PlayerManager::~PlayerManager(void)
{
	instance_ = nullptr;

}

void PlayerManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new PlayerManager();
	}
	//instance_->Init();
}

void PlayerManager::Destroy(void)
{
	//delete���Ă���nullptr
	delete instance_;
	instance_ = nullptr;
}

PlayerManager& PlayerManager::GetInstance(void)
{
	return *instance_;
}

void PlayerManager::Load(void)
{
	////�f�[�^�o���N����l�����擾
	//playerNum_ = DateBank::GetInstance().GetPlayerNum();

	//for (int i = 0; i < playerNum_; i++)
	//{
	//	goalTime_.emplace_back(0.0f);
	//}

	for (int i = 0; i < playerNum_; i++)
	{
		//KeyConfig::TYPE cntlType;
  //		if (playerNum_==1)
		//{
		//	cntlType = KeyConfig::TYPE::ALL;
		//}
		//else
		//{
		//	cntlType = KeyConfig::TYPE::PAD;
		//}
		std::unique_ptr<Player> player = std::make_unique<Player>(i, InputManager::CONTROLL_TYPE::ALL);


		player->Load();
		players_.push_back(std::move(player));
	}
}

void PlayerManager::Init(void)
{
	for (auto& player : players_)
	{
		player->Init();
	}
}

void PlayerManager::Update(void)
{
	//time_ += SceneManager::GetInstance().GetDeltaTime();
	for (auto& p : players_)
	{
		p->Update();
	}
	if (SceneManager::GetInstance().GetSceneID() == SceneManager::SCENE_ID::TITLE)
	{
		return;
	}

	//PlayersCollision();

	
	//for (int i = 0; i < playerNum_; i++)
	//{
	//	if (goalTime_[i] >= 0.0f)
	//	{
	//		continue;
	//	}
	//}

}

void PlayerManager::Draw(void)
{
	for (auto& p : players_)
	{
		p->Draw();
	}
}




Transform PlayerManager::FixTrans(int _playerNum)
{
	Transform trans = Transform();
	//���f���ł�����ԍ����ƂŐݒ肷��
	ResourceManager& resIns = ResourceManager::GetInstance();
	//�ԍ��Ń��f����ς���(�\��)
	//trans.SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::CHICKEN));

	//trans�̏�����
	PLAYER num = static_cast<PLAYER>(_playerNum);
	
	trans.quaRot = Quaternion();
	trans.scl = MODEL_SCL;
	trans.quaRotLocal =
		Quaternion::Euler({ 0.0f, UtilityCommon::Deg2RadF(180.0f), 0.0f });

	trans.localPos = { 0.0f,-Player::RADIUS,0.0f };
	return trans;
}

//void PlayerManager::InitPlayerColor()
//{
//	//�}���` ���� �^�C�g���ȊO�͐ݒ���s��Ȃ�
//	if (SceneManager::GetInstance().GetSceneID() != SceneManager::SCENE_ID::MULTI
//		&& SceneManager::GetInstance().GetSceneID() != SceneManager::SCENE_ID::TITLE)
//	{
//		//�F�̓f�t�H���g�̔��ɂȂ�
//		return;
//	}
//
//	//�e�v���C���[���ƂɐF��ݒ�
//	for (int i = 0; i < players_.size(); i++)
//	{
//		players_[i]->ChangeModelColor(PLAYER_COLOR[i]);
//	}
//}

