#pragma once
#include <map>
#include <functional>
#include"./Process/PlayerInput.h"
#include"./PlayerAction.h"
#include "../ObjectBase.h"

#define DEBUG_ON
class AnimationController;
class Camera;
class PlayerAction;
class PlayerOnHit;
class DateBank;
class Shadow;
class Camera;
class ModelMaterial;
class ModelRenderer;

class EffectController;

class Player :public ObjectBase
{
public:
	//******************************************
	//�萔
	//******************************************
	//���a
	static constexpr float RADIUS = 25.0f;
	//�f�t�H���g�̃A�j���[�V�����X�s�[�h
	static constexpr float DEFAULT_ANIM_SPD = 60.0f;

	//�i�[����J�[�h�̋���
	static constexpr int CARD_POWS[20] = { 0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9 };
	//******************************************


	enum class FLOOR_COL
	{
		NONE
		,SIDE
		,TOP
	};

	enum class ATK_ACT
	{
		NONE,	//�����Ȃ�
		INPUT,	//����
		MOVE,	//�ړ�
		PUNCH,	//�p���`
		KNOCKBACK,//�p���`���ꂽ���
		JUMP
	};

	enum class PLAYER_STATE
	{
		ALIVE
		,DEATH
		,GOAL
	};

	// �A�j���[�V�������
	enum class ANIM_TYPE
	{
		NONE = 0,
		IDLE = 1,
		WALK = 2,
		FALL = 4,
		HAND_UP = 5,
		HAND_WAVE = 6,
		DAMAGE = 9,
		PUNCH = 12,
		JUMP = 13,
		LAND=14,
		GOAL=6,
	};

	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_playerNum">�v���C���[�ԍ�</param>
	/// <param name="_cntl">�R���g���[���[���ʔԍ�</param>
	/// <param name="_tag">�v���C���[���Ƃ̃^�O</param>
	Player(int _playerNum,InputManager::CONTROLL_TYPE _cntl);

	// �f�X�g���N�^
	~Player(void);

	/// <summary>
	/// �ǂݍ���
	/// </summary>
	/// <param name=""></param>
	void Load(void)override;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name=""></param>
	void Init(void)override;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name=""></param>
	void Update(void)override;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name=""></param>
	void Draw(void)override;

	///// <summary>
	///// �����蔻���̏���
	///// </summary>
	///// <param name="_hitColTag">���葤�̓����蔻��</param>
	//void OnHit(const std::weak_ptr<Collider> _hitCol)override;

	//�Q�b�^
	//******************************************
	//�v���C���[�ԍ�
	inline const int GetPlayerNum(void)const { return playerNum_; }

	//�g�p����R���g���[���[
	inline const InputManager::CONTROLL_TYPE GetCntl(void)const { return cntl_; }

	//�R���g���[���[�ԍ�
	inline const InputManager::JOYPAD_NO GetPadNum(void)const { return padNum_; }

	//******************************************
	//�Z�b�^
	//******************************************
	/// <summary>
	/// ���W
	/// </summary>
	/// <param name="_worldPos">���[���h���W</param>
	//void SetPos(const VECTOR _worldPos);


	//*****************************************




private:
	//***********************************************
	//�萔
	//***********************************************
	//�d�͂̊���
	static constexpr float GRAVITY_PER = 20.0f;

	//�v���C���[�P��X���W
	static constexpr float PLAYER_ONE_POS_X = -20.0f;

	//���W�̊Ԋu
	static constexpr float DISTANCE_POS = 50.0f;

	//�v���C���[�̃��[�J���p�x
	static constexpr float MODEL_LOCAL_DEG = 180.0f;

	//������A�j���[�V�����̃X�^�[�g
	static constexpr float FALL_ANIM_START = 32.0f;
	//������A�j���[�V�����̏I���
	static constexpr float FALL_ANIM_END = 59.0f;

	//���ʔ���̍��W�̊
	static constexpr float DEATH_POS_Y = -600.0f;

	//���񂾂Ƃ��̃p�b�h�U������
	static constexpr int DEATH_PAD_VIBRATION_TIME = 300;

	//���񂾂Ƃ��̃p�b�h�U���̋���
	static constexpr int DEATH_PAD_VIBRATION_POW = 300;

	//�v���C���[�̑傫��
	static constexpr VECTOR MODEL_SCL = { 1.0f,1.0f,1.0f };
	//�p���`�͈̔�
	static constexpr float PUNCH_RADIUS = 50.0f;

	//--------------------------------------------------
	//�����蔻��
	//--------------------------------------------------
	//���C���̒���
	static constexpr float LINE_RANGE = 10.0f;
	//�v���C���[�̏�̍��W
	static constexpr VECTOR LOCAL_UP_POS = { 0.0f,RADIUS+ LINE_RANGE,0.0f };
	//�v���C���[�̉�
	static constexpr VECTOR LOCAL_DOWN_POS = { 0.0f,-RADIUS- LINE_RANGE,0.0f };
	//--------------------------------------------------
	//�Q�[���I�[�o�[�̑ҋ@����
	static constexpr float DEATH_DELAY = 2.0f;

	//�S�[�����̑ҋ@����
	static constexpr float GOAL_DELAY = 1.0f;

	//***********************************
	//�A�j���[�V�����֘A
	//***********************************

	//�����蔻����s���͈�
	static constexpr int COL_RANGE = 1;
	//******************************************
	//�����o�ϐ�
	//******************************************
	//���̓f�o�C�X
	InputManager::CONTROLL_TYPE cntl_;

	//�Q�[���p�b�h�ԍ�
	InputManager::JOYPAD_NO padNum_;

	//�I�u�W�F�N�g�֘A
	//--------------------------------------------
		//�s���n
	std::unique_ptr<PlayerAction>action_;

	// �A�j���[�V����
	std::unique_ptr<AnimationController> animationController_;

	//�J����
	std::weak_ptr<Camera>camera_;

	//�����o�ϐ�
	//--------------------------------------------
	//�v���C���[�P�̂������Ă������
	int playerNum_;			//�v���C���[�ԍ�

	//�v���p
	float time_;

	//�S�[�����Ԋi�[
	float goalTime_;

	//�v���C���[���
	PLAYER_STATE state_;	//�v���C���[�̏��(�������)

	//�v���C���[�̏�ԑJ��
	std::map<PLAYER_STATE, std::function<void(void)>>changeStates_;

	//��ԍX�V
	std::function<void(void)>stateUpdate_;

	float finishDelay_;	//�Q�[���I�����̑ҋ@����
				

	//--------------------------------------------
	//******************************************
	//�����o�֐�
	//******************************************
#ifdef DEBUG_ON
	void DrawDebug(void);
#endif // DEBUG_ON
	//�v���C���[���
	//**************************************************
	//��ԑJ��
	void ChangeState(PLAYER_STATE _state);
	//�������Ă���Ƃ�
	//------------------------------
	//��ԑJ��
	void ChangeAlive(void);
	//�����X�V
	void AliveUpdate(void);
	//------------------------------
	//���S���Ă���Ƃ�
	//------------------------------
	void ChangeDeath(void);
	void DeathUpdate(void);
	//------------------------------
	//�S�[��������
	void ChangeGoal(void);
	void GoalUpdate(void);
	
	//�A�N�V�����֌W
	void Action(void);


};

