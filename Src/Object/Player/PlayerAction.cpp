#include"../Utility/Utility3D.h"
#include"../Utility/UtilityCommon.h"
#include"Player.h"
#include"Process/PlayerInput.h"
//#include "../../Manager/Game/GravityManager.h"
#include "../../Manager/Generic/Camera.h"
#include "../../Manager/Generic/SceneManager.h"
#include "../../Manager/Resource/ResourceManager.h"
//#include "../../Object/Common/EffectController.h"
#include "../../Object/Common/AnimationController.h"

#include"../Card/CardDeck.h"
#include"../Card/CardBase.h"

#include "PlayerAction.h"

PlayerAction::PlayerAction(Player& _player, SceneManager& _scnMng, AnimationController& _animationController):
	player_(_player)
	,scnMng_(_scnMng)
	,animationController_(_animationController)
{
	//����֘A
	//----------------------------------------------------
	changeAction_.emplace(ATK_ACT::NONE, [this]() {ChangeNone(); });
	changeAction_.emplace(ATK_ACT::MOVE, [this]() {ChangeMove(); });
	changeAction_.emplace(ATK_ACT::INPUT, [this]() {ChangeInput(); });
 	changeAction_.emplace(ATK_ACT::JUMP, [this]() {ChangeJump(); });

	//�G�t�F�N�g
	//effect_ = std::make_unique<EffectController>();
	
	//�W�����v�֌W
	isJump_ = false;
	stepJump_ = 0.0f;
	jumpPow_ = Utility3D::VECTOR_ZERO;
	jumpDeceralation_ = POW_JUMP;
	stepRotTime_ = 0.0f;
	speed_ = 0.0f;
	punchPos_ = {};
	punchedCnt_ = 0.0f;
	punchCoolCnt_ = 0.0f;

	isPunchHitTime_ = false;
	input_ = nullptr;
}

PlayerAction::~PlayerAction(void)
{
	StopResource();
}

void PlayerAction::Init(void)
{
	auto num = player_.GetPadNum();
	//auto cntl = player_.GetCntl();
	auto cntl = InputManager::CONTROLL_TYPE::ALL;
	//����
	input_ = std::make_unique<PlayerInput>(num, cntl);
	input_->Init();

	//�J�[�h�f�b�L
	cardCenterPos_ = { 140,140 };//�J�[�h�̒��S�ʒu
	deck_ = std::make_shared<CardDeck>(cardCenterPos_);
	//�f�b�L�ɎR�D�ǉ�
	for (int i = 0; i < CARD_NUM_MAX; i++)
	{
		deck_->AddDrawPile(CARD_POWS[i]);
	}
	deck_->Init();

	//�W�����v�֌W
	isJump_ = false;
	stepJump_ = 0.0f;
	jumpPow_ = Utility3D::VECTOR_ZERO;
	jumpDeceralation_ = POW_JUMP;
  	movePow_ = Utility3D::VECTOR_ZERO;

	//�X�s�[�h
	speed_ = 0.0f;

	isPunchHitTime_ = false;

	//if (scnMng_.GetInstance().GetSceneID() == SceneManager::SCENE_ID::TITLE)
	//{
	//	cameraNo_ = 0;
	//}
	//else
	//{
	//	cameraNo_ = player_.GetPlayerNum();
	//}
	act_ = ATK_ACT::NONE;
	ChangeAction(ATK_ACT::INPUT);
}

void PlayerAction::Load(void)
{
	//auto& res = ResourceManager::GetInstance();
	//actSE_.emplace(ACT_SE::DASH,SoundManager::SRC::PLAYER_DASH_START);
	//actSE_.emplace(ACT_SE::JUMP,SoundManager::SRC::PLAYER_JUMP);
	//actSE_.emplace(ACT_SE::PUNCH, SoundManager::SRC::PLAYER_PUNCH_MOTION);
	//actSE_.emplace(ACT_SE::SLIME, SoundManager::SRC::SLIME_SE);
	//actSE_.emplace(ACT_SE::PUNCH_HIT, SoundManager::SRC::PLAYER_PUNCH_HIT);
}

void PlayerAction::Update(void)
{
	//���͍X�V
	input_->Update();

	////�G�t�F�N�g�X�V
	//effect_->Update();

	//�v���C���[�̉���ݒ�
	static VECTOR dirDown = player_.GetTransform().GetDown();

	////�d��(�e�A�N�V�����ɏd�͂𔽉f���������̂Ő�ɏd�͂��ɏ���)
	//GravityManager::GetInstance().CalcGravity(dirDown,jumpPow_, GRAVITY_PER);

	//�e�A�N�V�����̍X�V
	actionUpdate_();

	//�v���C���[�̉�]
	Rotate();

	//�v���C���[�̕����ƃX�s�[�h�̍X�V
	UpdateMoveDirAndPow();

	//�J�[�h�֘A
	CardUseUpdate();
	CardChargeUpdate();
	CardMove();
}

void PlayerAction::DrawDebug(void)
{
	//int dashSeCnt = effect_->GetPlayNum(EffectController::EFF_TYPE::DASH);
	//DrawFormatString(0, 300, 0x000000, "act(%d)\ndashSESize(%d)", (int)input_->GetAct(), dashSeCnt);
	deck_->Draw();
	
}

void PlayerAction::NoneUpdate(void)
{
	//�������Ȃ�
}

void PlayerAction::ChangeNone(void)
{
	actionUpdate_ = [this]() {NoneUpdate(); };
}

void PlayerAction::ActionInputUpdate(void)
{
	//���͂ɉ����ăA�N�V������ς���
	using ACT_CNTL = PlayerInput::ACT_CNTL;
	if (input_->CheckAct(ACT_CNTL::MOVE))
	{
		ChangeAction(ATK_ACT::MOVE);
		return;
	}
}

void PlayerAction::ChangeAction(ATK_ACT _act)
{
	if (act_ == _act)return;
	act_ = _act;
	changeAction_[act_]();
 }

void PlayerAction::ChangeInput(void)
{
	actionUpdate_ = std::bind(&PlayerAction::ActionInputUpdate, this);
}



void PlayerAction::MoveUpdate(void)
{
	Speed();
	//�ړ����ɓ��͂����������̏�ԑJ��
	if (CheckJumpInput())
	{
		ChangeAction(ATK_ACT::JUMP);
		return;
	}
	if (input_->CheckAct(PlayerInput::ACT_CNTL::MOVE))
	{
		ChangeAction(ATK_ACT::MOVE);
	}
	if (input_->CheckAct(PlayerInput::ACT_CNTL::DASHMOVE))
	{
		ChangeAction(ATK_ACT::DASHMOVE);
	}
	else if (input_->CheckAct(PlayerInput::ACT_CNTL::PUNCH))
	{
		speed_ = 0.0f;
		ChangeAction(ATK_ACT::PUNCH);
		return;
	}
	else if (!input_->CheckAct(PlayerInput::ACT_CNTL::MOVE)
		&&!input_->CheckAct(PlayerInput::ACT_CNTL::DASHMOVE))
	{
		speed_ = 0.0f;
		ChangeAction(ATK_ACT::INPUT);
		return;
	}

	float animationSpeed = Player::DEFAULT_ANIM_SPD * (speed_ / MOVE_SPEED)*3.0f;

	//���͕����̈ړ�
	MoveDirFronInput();
}

void PlayerAction::MoveDirFronInput(void)
{
	//�ړ��ʂ�0�Ƀ��Z�b�g
	movePow_ = Utility3D::VECTOR_ZERO;

	//�v���C���[���̓N���X����p�x���擾
	VECTOR getDir = input_->GetDir();
	float deg = input_->GetMoveDeg();

	//�J�����̊p�x�Ǔ��͊p�x�Ńv���C���[�̕�����ς���
	Quaternion cameraRot = scnMng_.GetCamera().lock()->GetQuaRotOutX();
	dir_ = cameraRot.PosAxis(getDir);
	dir_ = VNorm(dir_);

	if (!Utility3D::EqualsVZero(dir_))
	{
		//�⊮�p�x�̐ݒ�(���͊p�x�܂ŕ����]������)
		SetGoalRotate(deg);
	}
}

void PlayerAction::ChangeMove(void)
{
	speed_ = MOVE_SPEED;
	//animationController_.Play(static_cast<int>(Player::ANIM_TYPE::WALK));
	actionUpdate_ = std::bind(&PlayerAction::MoveUpdate, this);
}

void PlayerAction::ChangeDashMove(void)
{
	speed_ = DASH_SPEED;
	//animationController_.Play(static_cast<int>(Player::ANIM_TYPE::WALK));

	auto& trans = player_.GetTransform();
	const float SCL = 10.0f;
	//effect_->Play(EffectController::EFF_TYPE::DASH, trans.pos, trans.quaRot, { SCL,SCL,SCL }, false, 1.0f);
	actionUpdate_ = [this]() {MoveUpdate(); };
}



void PlayerAction::UpdateMoveDirAndPow(void)
{
	//�����̍X�V
	moveDir_ = dir_;
	//�ړ��ʂ̍X�V
	movePow_ = VScale(moveDir_, speed_);
	
}

void PlayerAction::Speed(void)
{
	if (input_->CheckAct(PlayerInput::ACT_CNTL::MOVE))
	{
		speed_ = MOVE_SPEED;
	}
	else if (input_->CheckAct(PlayerInput::ACT_CNTL::DASHMOVE))
	{
		speed_ = DASH_SPEED;
	}
	else
	{
		speed_ = 0.0f;
	}
}

void PlayerAction::JumpUpdate(void)
{
	//�ړ����͂���������X�s�[�h�Z�b�g
	Speed();
	//�W�����v����
	Jump();
}

void PlayerAction::Jump(void)
{
	//�X�e�b�v�W�����v����ɃW�����v�����ʂ����߂�
	float deltaTime = SceneManager::GetInstance().GetDeltaTime();
	stepJump_ += deltaTime;

	////�󒆃A�j���[�V�����X�e�b�v�̃��[�v�ݒ�
	//animationController_.SetEndLoop(JUMP_ANIM_LOOP_START_FRAME
	//	, JUMP_ANIM_LOOP_END_FRAME, JUMP_ANIM_ATTACK_BLEND_TIME);

	//�W�����v�����ړ��ł���悤�ɂ���
	MoveDirFronInput();

	//�W�����v�J�E���g��0�ȏ�Ȃ�
	if (stepJump_ > 0.0f)
	{
		stepJump_ += deltaTime;
		//�v���C���[���������Ă�����
		if (jumpDeceralation_ < 0.0f)
		{
			//animationController_.Play(static_cast<int>(Player::ANIM_TYPE::LAND));
		}
		//�����ʂ̌v�Z
		float deceralation = stepJump_ * TIME_JUMP_SCALE;
		jumpDeceralation_ -= deceralation;

		//�W�����v�ʂɊ|����
		jumpPow_ = VScale(player_.GetTransform().GetUp(), jumpDeceralation_);
	}

	//�n�ʂɒ�������W�����v�֌W�̕ϐ����Z�b�g
	if (!isJump_)
	{
		jumpDeceralation_ = POW_JUMP;
		jumpPow_ = Utility3D::VECTOR_ZERO;
		stepJump_ = 0.0f;

		//���n�G�t�F�N�g
		Transform trans = player_.GetTransform();
		const float EFF_SCL = 30.0f;

		//�����Ă����ꍇ�̈ړ��ʃ��Z�b�g
		speed_ = 0.0f;
		ChangeAction(ATK_ACT::INPUT);
		return;
	}
}

void PlayerAction::ChangeJump(void)
{
	//�W�����v�֌W
  	isJump_ = true;
	stepJump_ = 0.0f;

	//�v���C���[�̏��
	Transform trans = player_.GetTransform();
	//�G�t�F�N�g�̃X�P�[��
	const VECTOR EFF_SCL = { 10.0f,10.0f,10.0f };

	//��ԑJ��
	actionUpdate_ = [this]() {JumpUpdate(); };
}

void PlayerAction::CardUseUpdate(void)
{
	if (input_->CheckAct(PlayerInput::ACT_CNTL::_CARD_USE))
	{
		deck_->CardUse();
	}
	
}

void PlayerAction::CardChargeUpdate(void)
{
	if (input_->CheckAct(PlayerInput::ACT_CNTL::CARD_CHARGE))
	{
		deck_->CardCharge();
	}
	
}

void PlayerAction::CardMove(void)
{
	if (input_->CheckAct(PlayerInput::ACT_CNTL::CARD_MOVE_LEFT))
	{
		deck_->CardMoveLeft();
	}
	else if (input_->CheckAct(PlayerInput::ACT_CNTL::CARD_MOVE_RIGHT))
	{
		deck_->CardMoveRight();
	}
}

bool PlayerAction::CheckJumpInput(void)
{
	return input_->CheckAct(PlayerInput::ACT_CNTL::JUMP);
}

void PlayerAction::Rotate(void)
{
	stepRotTime_ -= SceneManager::GetInstance().GetDeltaTime();
	// ��]�̋��ʕ��
	playerRotY_ = Quaternion::Slerp(
		playerRotY_, goalQuaRot_, (TIME_ROT - stepRotTime_) / TIME_ROT);
}

void PlayerAction::SetGoalRotate(double _deg)
{
	//�J�����̊p�x���擾
	VECTOR cameraRot = scnMng_.GetCamera().lock()->GetAngles();
	Quaternion axis = Quaternion::AngleAxis(
		(double)cameraRot.y + UtilityCommon::Deg2RadD(_deg), Utility3D::AXIS_Y);


	 //���ݐݒ肳��Ă����]�Ƃ̊p�x�������
	double angleDiff = Quaternion::Angle(axis, goalQuaRot_);

	constexpr double ANGLE_THRESHOLD = 0.1;
	// �������l
	if (angleDiff > ANGLE_THRESHOLD)
	{
		stepRotTime_ = TIME_ROT;
	}
	goalQuaRot_ = axis;
}

void PlayerAction::StopResource(void)
{
	//SE�̒�~
	//SoundManager::GetInstance().Stop(actSE_[ACT_SE::DASH]);
	//SoundManager::GetInstance().Stop(actSE_[ACT_SE::JUMP]);
	//SoundManager::GetInstance().Stop(actSE_[ACT_SE::PUNCH]);
	//SoundManager::GetInstance().Stop(actSE_[ACT_SE::SLIME]);
	//SoundManager::GetInstance().Stop(actSE_[ACT_SE::PUNCH_HIT]);
	//�G�t�F�N�g�̒�~
	//effect_->StopAll();
}
