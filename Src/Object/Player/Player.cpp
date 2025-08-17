#include "../../Utility/Utility3D.h"
#include "../../Utility/UtilityCommon.h"
#include "../Application.h"

//#include "../../Manager/Game/GravityManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Manager/Resource/ResourceManager.h"
//#include "../../Manager/System/SoundManager.h"
#include "../../Manager/Generic/SceneManager.h"
//#include"../../Manager/System/DateBank.h"

#include "../../Manager/Generic/Camera.h"

//#include "../../Renderer/ModelMaterial.h"
//#include "../../Renderer/ModelRenderer.h"

//#include "../../Object/Common/Geometry/Sphere.h"
//#include "../../Object/Common/Geometry/Line.h"
//#include"../../Object/Common/Geometry/Model.h"
//#include"../../Object/Common/EffectController.h"

#include "../../Object/Common/AnimationController.h"
#include"./PlayerAction.h"
//#include"./PlayerOnHit.h"
#include "./Process/PlayerInput.h"
#include<algorithm>


#include "Player.h"
Player::Player(int _playerNum, InputManager::CONTROLL_TYPE _cntl)
	:playerNum_(_playerNum)
	, cntl_(_cntl)
{
	trans_ = Transform();

	//���߂�JOYPAD��key_pad�Ȃ̂Ńp�b�h�̔ԍ��ɍ��킹��
	//�p�b�h�ԍ���ݒ�
	padNum_ = static_cast<InputManager::JOYPAD_NO>(playerNum_ + 1);

	//�v���C���[���
	changeStates_.emplace(PLAYER_STATE::ALIVE, [this]() {ChangeAlive();});
	changeStates_.emplace(PLAYER_STATE::DEATH, [this]() {ChangeDeath(); });
	changeStates_.emplace(PLAYER_STATE::GOAL, [this]() {ChangeGoal(); });

	ChangeState(PLAYER_STATE::ALIVE);
}

Player::~Player(void)
{
}

void Player::Load(void)
{
	////�A�j���[�V������modelId���g���̂Ő�Ƀ��f���Z�b�g����
	//trans_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::CHICKEN));

	////���\�[�X�̓ǂݍ��݂Ȃ�
	//animationController_ = std::make_unique<AnimationController>(trans_.modelId);
	//animationController_->Add(static_cast<int>(ANIM_TYPE::IDLE), DEFAULT_ANIM_SPD);
	//animationController_->Add(static_cast<int>(ANIM_TYPE::WALK), DEFAULT_ANIM_SPD);
	//animationController_->Add(static_cast<int>(ANIM_TYPE::FALL), DEFAULT_ANIM_SPD);
	//animationController_->Add(static_cast<int>(ANIM_TYPE::JUMP), DEFAULT_ANIM_SPD);
	//animationController_->Add(static_cast<int>(ANIM_TYPE::LAND), DEFAULT_ANIM_SPD);
	//animationController_->Add(static_cast<int>(ANIM_TYPE::GOAL), DEFAULT_ANIM_SPD);
	//animationController_->Add(static_cast<int>(ANIM_TYPE::PUNCH), DEFAULT_ANIM_SPD / PlayerAction::PUNCH_TIME_MAX);

	//�A�N�V����
	action_ = std::make_unique<PlayerAction>(*this, scnMng_, *animationController_);
	action_->Load();
}

void Player::Init(void)
{
	//Transform�̐ݒ�
	trans_.quaRot = Quaternion();
	trans_.scl = MODEL_SCL;
	trans_.quaRotLocal = 
		Quaternion::Euler({ 0.0f, UtilityCommon::Deg2RadF(MODEL_LOCAL_DEG), 0.0f });

	float posX = PLAYER_ONE_POS_X + DISTANCE_POS * playerNum_;
	trans_.pos={ posX,0.0f,0.0f };
	trans_.localPos = { 0.0f,-Player::RADIUS,0.0f };

	//�������
	ChangeState(PLAYER_STATE::ALIVE);

	action_->Init();

	//�X�V
	trans_.Update();
}

void Player::Update(void)
{
	//animationController_->Update();
#ifdef DEBUG_ON
	//CubeMove();
#endif // DEBUG_ON

	//�v���C���[��ԍX�V
	stateUpdate_();

	//��]�̓���
	trans_.quaRot = action_->GetPlayerRotY();
	
	trans_.pos = VAdd(trans_.pos, action_->GetMovePow());


	trans_.Update();
}

void Player::Draw(void)
{
	//if (IsDeath())return;
	//���f���`���ZBuffer�𖳌��ɂ���
	MV1SetWriteZBuffer(trans_.modelId, false);

	////�A�E�g���C���`��
	//renderer_->Draw();

	////���f���`���ZBuffer��߂�
	//MV1SetWriteZBuffer(trans_.modelId, true);

	//�ʏ�`��
	//MV1DrawModel(trans_.modelId);

	action_->DrawDebug();
	
	////�e�̕`��
	//shadow_->Draw();

#ifdef DEBUG_ON
	DrawDebug();
#endif // DEBUG_ON
}
#ifdef DEBUG_ON
void Player::DrawDebug(void)
{
	unsigned int color = 0xffffff;
	const int HIGH = 10;
	const int WIDTH = 200;
	DrawSphere3D(trans_.pos, RADIUS, 4, 0xff0000, 0xff0000, true);

}

#endif // DEBUG_ON

void Player::ChangeState(PLAYER_STATE _state)
{
	state_ = _state;
	changeStates_[state_]();
}
void Player::ChangeAlive(void)
{
	stateUpdate_ = std::bind(&Player::AliveUpdate, this);
}
void Player::AliveUpdate(void)
{
	//�A�N�V�����֌W�X�V
	Action();
}
void Player::ChangeDeath(void)
{
	stateUpdate_ = std::bind(&Player::DeathUpdate, this);
}
void Player::DeathUpdate(void)
{

}
void Player::ChangeGoal(void)
{

}
void Player::GoalUpdate(void)
{

}

void Player::Action(void)
{
	//�A�N�V�����֌W�̍X�V
	action_->Update();
	//
	////���񂾂牽�����Ȃ��悤�ɂ���
	//if (IsDeath())
	//{
	//	//�����ł��Ȃ��悤�ɂ���
	//	action_->ChangeAction(PlayerAction::ATK_ACT::NONE);
	//}
}

