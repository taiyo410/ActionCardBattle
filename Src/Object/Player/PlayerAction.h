#pragma once
#include<DxLib.h>
#include<memory>
#include<functional>
#include<map>

class Player;
class PlayerInput;
class AnimationController;
class CardDeck;
class CardBase;
class PlayerAction
{
public:
	//�萔
	//****************************************
	//�p���`�L������
	static constexpr float PUNCH_TIME_MAX = 0.5f;
	//�J�[�h�ő喇��
	static constexpr int CARD_NUM_MAX = 20;
	//�i�[����J�[�h�̋���
	static constexpr int CARD_POWS[20] = { 0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9 };
	//static constexpr int CARD_POWS[20] = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9};
	//****************************************

	enum class ATK_ACT
	{
		NONE,	//�����Ȃ�
		INPUT,	//����
		MOVE,	//�ړ�
		DASHMOVE,//�_�b�V��
		PUNCH,	//�p���`
		KNOCKBACK,//�p���`���ꂽ���
		JUMP
	};

	enum class ACT_SE
	{
		DASH,	//�_�b�V��
		JUMP,	//�W�����v
		PUNCH,	//�p���`
		PUNCH_HIT,//�p���`�q�b�g
		SLIME,	//�X���C��
	};

	PlayerAction(Player& _player, SceneManager& _scnMng, AnimationController& _animationController);
	~PlayerAction(void);

	/// <summary>
	/// ������
	/// </summary>
	/// <param name=""></param>
	void Init(void);

	/// <summary>
	/// �ǂݍ���
	/// </summary>
	void Load(void);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name=""></param>
	void Update(void);


	void DrawDebug(void);



	//��ԑJ��
	void ChangeAction(ATK_ACT _act);



	//*****************************************
	//�Q�b�^
	//*****************************************
	//�ړ���
	const VECTOR GetMovePow(void) { return movePow_; }

	//�W�����v��
	const VECTOR GetJumpPow(void) { return jumpPow_; }

	//�v���C���[�̊p�xY
	const Quaternion GetPlayerRotY(void) { return playerRotY_; }


	//�W�����v��
	const bool GetIsJump(void) { return isJump_; }

	//���
	const ATK_ACT GetAct(void)const { return act_; }

	//*****************************************
	//�Z�b�^
	//*****************************************
	//�W�����v��
	void SetJumpPow(const VECTOR _jumpPow) { jumpPow_ = _jumpPow; };

	//�ړ���
	void SetMovePow(const VECTOR _movePow) { movePow_ = _movePow; }

	//�X�s�[�h
	void SetSpeed(const float _spd) { speed_ = _spd; }

	//�󒆂��ǂ���
	void SetIsJump(const bool _isJump) { isJump_ = _isJump; }

	//�W�����v����
	void SetJumpDecel(const float _decel) { jumpDeceralation_ = _decel; }

	//�W�����v����
	void SetStepJump(const float _step) { stepJump_ = _step; }

	//����
	void SetDir(const VECTOR _dir) { dir_ = _dir; }

	//�Đ����Ă��郊�\�[�X�����ׂĎ~�߂�
	void StopResource(void);

	//�f�o�b�O
	float GetJumpDecel(void) { return jumpDeceralation_; }
	float GetStepJump(void) { return stepJump_; }

private:
	//*******************************************
	//�萔
	//*******************************************
	//�d�͂̊���
	static constexpr float GRAVITY_PER = 20.0f;
	//�ړ�
	//----------------------------------
	//�ړ��X�s�[�h
	static constexpr float MOVE_SPEED = 6.0f;

	//�X���C������ł̈ړ����x(�ʏ�)
	static constexpr float SLIME_FLOOR_MOVE_SPD = 3.0f;

	//�_�b�V���X�s�[�h
	static constexpr float DASH_SPEED = 11.0f;
	//�Ԃ���ԃX�s�[�h
	static constexpr float FLY_AWAY_SPEED = 12.0f;
	//�����Ă���Ƃ��̏d�͐���(jumpPow�ɉ��Z���Ă���̂�jumpPow�ɓK�p)
	static constexpr float LIMIT_GRAVITY = -20.0f;

	//�_�b�V���A�j���[�V�����X�s�[�h
	static constexpr float DASH_ANIM_SPEED = 200.0f;

	//�_�b�V��SE�Ԋu
	static constexpr float DASH_SE_TIME = 0.2f;

	//----------------------------------
	//�W�����v
	//----------------------------------

	//�W�����v�����̔{��
	static constexpr float TIME_JUMP_SCALE = 1.0f;
	//�X���C������ł̃W�����v��
	static constexpr float SLIME_FLOOR_JUMP_POW = 10.0f;

	//�W�����v�A�j���[�V�������[�v�J�n
	static constexpr float JUMP_ANIM_LOOP_START_FRAME = 23.0f;
	//�W�����v�A�j���[�V�������[�v����
	static constexpr float JUMP_ANIM_LOOP_END_FRAME = 25.0f;
	//�W�����v�A�j���[�V�������[�v���̃X�s�[�h
	static constexpr float JUMP_ANIM_ATTACK_BLEND_TIME = 5.0f;

	//�W�����v�J�n�A�j���X�e�b�v
	static constexpr float JUMP_ANIM_START_FRAME = 10.0f;
	static constexpr float JUMP_ANIM_END_FRAME = 60.0f;

	//�W�����v��
	static constexpr float POW_JUMP = 20.0f;

	// ��]�����܂ł̎���
	static constexpr float TIME_ROT = 0.1f;

	//-------------------------------------------------
	//�����o�ϐ�
	//-------------------------------------------------
	// �V�[���}�l�[�W���Q��
	SceneManager& scnMng_;

	//�v���C���[
	Player& player_;

	//�A�j���[�V�����R���g���[���[
	AnimationController& animationController_;

	//��ԑJ��
	std::map<ATK_ACT, std::function<void(void)>>changeAction_;

	//��ԍX�V
	std::function<void(void)>actionUpdate_;

	//�������
	std::unique_ptr<PlayerInput> input_;

	//���
	ATK_ACT act_;

	//�f�ފ֘A
	//------------------------


	//�ړ�
	//------------------------
	float speed_;			// �ړ��X�s�[�h
	VECTOR moveDir_;		// �ړ�����
	VECTOR movePow_;		// �ړ���
	VECTOR dir_;			//����

	//��]
	Quaternion playerRotY_;		//�v���C���[Y�p�x
	Quaternion goalQuaRot_;		//�ړI�̉�]
	float stepRotTime_;			//�⊮����



	//�W�����v
	//-----------------------
	bool isJump_;			// �W�����v����
	float stepJump_;		// �W�����v�̓��͎�t����
	VECTOR jumpPow_;		// �W�����v��
	float jumpDeceralation_;	//�W�����v������

	//�p���`
	//-----------------------
	bool isPunchHitTime_;		//�p���`�����蔻��̎��ԃt���O
	float punchCnt_;				//�p���`�J�E���g
	float punchCoolCnt_;			//�p���`�N�[���^�C��
	VECTOR punchPos_;			//�U�����W
	float punchedCnt_;			//�p���`���ʎ��ԃJ�E���g

	//�R�D(�f�b�L�N���X�Ɋi�[�p)
	std::vector<std::shared_ptr<CardBase>>drawPile_;
	Vector2 cardCenterPos_;	//�J�[�h�̈ʒu
	//-------------------------------------------------
	//�����o�֐�
	//-------------------------------------------------
	//�������Ȃ�
	void NoneUpdate(void);

	//����
	void ActionInputUpdate(void);
	void ChangeInput(void);

	//�����Ȃ�
	void ChangeNone(void);

	//�ړ���Ԃ̍X�V
	void MoveUpdate(void);
	//���͕����ɉ����ĕ��������߂�
	void MoveDirFronInput(void);
	//�ړ���ԕύX
	void ChangeMove(void);

	//�_�b�V��
	void ChangeDashMove(void);

	//���t���[���ړ������ƃX�s�[�h���X�V����
	void UpdateMoveDirAndPow(void);
	//�ړ����x
	void Speed(void);

	//�W�����v
	void JumpUpdate(void);
	void Jump(void);
	void ChangeJump(void);

	//�J�[�h�֘A
	//�J�[�h�g�p
	void CardUseUpdate(void);
	//�J�[�h�`���[�W
	void CardChargeUpdate(void);
	//�J�[�h�I��
	void CardMove(void);

	//�W�����v���ł������
	bool CheckJumpInput(void);

	//�J�[�h�f�b�L
	std::shared_ptr<CardDeck>deck_;

	/// <summary>
	/// �Đ���������SE�ȊO���ׂĎ~�߂�
	/// </summary>
	/// <param name="_se">���ݍĐ���������SE</param>
	//void StopSe(const ACT_SE _se);

	//��]
	void Rotate(void);
	//�ŏI�I�ɓ����������p�x�̐ݒ�
	void SetGoalRotate(double _deg);


};

