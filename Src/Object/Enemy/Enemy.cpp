#include"../Utility/Utility3D.h"
#include"../Utility/UtilityCommon.h"
#include"../../Application.h"
#include"../Card/CardDeck.h"
#include"../Player/Process/EnemyInput.h"


#include "Enemy.h"

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}
void Enemy::Load(void)
{
}
	//Transform
void Enemy::Init(void)
{
	//�J�[�h�f�b�L
	cardCenterPos_ = { Application::SCREEN_SIZE_X-140,140 };//�J�[�h�̒��S�ʒu
	deck_ = std::make_shared<CardDeck>(cardCenterPos_);
	for (int i = 0; i < CARD_NUM_MAX; i++)
	{
		deck_->AddDrawPile(CARD_POWS[i]);
	}
	deck_->Init();
	input_ = std::make_unique<EnemyInput>();
	input_->Init();
	//Transform�̐ݒ�
	trans_.quaRot = Quaternion();
	trans_.scl = MODEL_SCL;
	trans_.quaRotLocal =
		Quaternion::Euler({ 0.0f, UtilityCommon::Deg2RadF(MODEL_LOCAL_DEG), 0.0f });

	trans_.pos = { 20.0f,0.0f,0.0f };
	trans_.localPos = { 0.0f,-RADIUS,0.0f };
}

void Enemy::Update(void)
{
	input_->Update();
	if (input_->CheckAct(EnemyInput::ACT_CNTL::CARD_MOVE_LEFT))
	{
		deck_->CardMoveLeft();
	}
	else if(input_->CheckAct(EnemyInput::ACT_CNTL::CARD_MOVE_RIGHT) )
	{
		deck_->CardMoveRight();
	}
	else if (input_->CheckAct(EnemyInput::ACT_CNTL::_CARD_USE))
	{
		deck_->CardUse();
	}
}

void Enemy::Draw(void)
{
	DrawSphere3D(trans_.pos, RADIUS, 4, 0xff0000, 0xff0000, true);
	deck_->Draw();
}
