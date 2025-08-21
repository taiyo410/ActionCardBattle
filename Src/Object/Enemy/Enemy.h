#pragma once
#include "../ObjectBase.h"
#include"../../Common/Vector2.h"
#include<memory>
class CardDeck;
class EnemyInput;
class Enemy :public ObjectBase
{
public:
	//�萔
	static constexpr int RADIUS = 25; //�G�̃T�C�Y

	//�v���C���[�̃��[�J���p�x
	static constexpr float MODEL_LOCAL_DEG = 180.0f;

	//�v���C���[�̑傫��
	static constexpr VECTOR MODEL_SCL = { 1.0f,1.0f,1.0f };

	//�J�[�h�ő喇��
	static constexpr int CARD_NUM_MAX = 20;

	//�i�[����J�[�h�̋���
	static constexpr int CARD_POWS[20] = { 0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9 };

	Enemy(void);
	~Enemy(void)override;
	void Load(void) override;
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	Vector2 cardCenterPos_; //�J�[�h�̒��S���W
	//�����o�֐�
	void DrawDebug(void);

	//�G�̍s��
	std::unique_ptr<EnemyInput>input_; //�G�̓��̓N���X

	//�����o�ϐ�
	std::shared_ptr<CardDeck>deck_;
};

