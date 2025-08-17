#pragma once
#include<memory>
#include<vector>
#include"../../Object/Common/Transform.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Player/Process/PlayerInput.h"
//#include"../../Object/Common/Capsule.h"
class Player;
class PlayerManager
{
public:
	//**************************************
	//�萔
	//**************************************
	static constexpr int PLAYER_NUM_MAX = 4;

	//�v���C���[1�l
	static constexpr int PLAYER_SINGLE = 1;

	//�v���C���[�J���[
	static constexpr COLOR_F PLAYER_COLOR[PLAYER_NUM_MAX] =
	{		
		{0.6f,0.8f,1.0f,1.0f},
		{1.0f,0.6f,0.9f,1.0f},
		{0.7f,1.0f,0.8f,1.0f},
		{1.0f,1.0f,0.7f,1.0f},
	};

	
	enum class PLAYER
	{
		PLAYER_ONE,
		PLAYER_TWO,
		PLAYER_THREE,
		PLAYER_FOUR
	};


	//**************************************
	

	/// <summary>
	/// �ÓI�ɃC���X�^���X����
	/// </summary>
	/// <param name="_playerNum">�v���C���[�l��</param>
	static void CreateInstance(void);

	//���
	void Destroy(void);

	//�ÓI�ɃC���X�^���X���擾����
	static PlayerManager& GetInstance(void);
	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);

	//*****************************************
	//�Q�b�^
	//*****************************************
	//���f�����Q�b�^
	const Transform& GetPlayerTransform(const int _num) { return players_[_num]->GetTransform(); }

	//�v���C���[���
	std::vector<std::unique_ptr<Player>>&GetPlayers(void) { return players_; }


	//�S�[���^�C���̃Q�b�^
	const std::vector<float> GetGoalTime(void);

	//****************************************
	//�Z�b�^
	//****************************************
	//�������W�ɖ߂�
	void SetInitPos(VECTOR _worldPos);
private:
	//�v���C���[�̑傫��
	static constexpr VECTOR MODEL_SCL = { 1.0f,1.0f,1.0f };



	//�������W
	static constexpr float START_POS = 50.0f;

	//�ÓI�C���X�^���X
	static PlayerManager* instance_;

	//�n�܂��Ă���̑��^�C��
	//float time_;

	//�S�[������
	std::vector<float>goalTime_;

	//*****************************************
	//�����o�ϐ�
	//*****************************************
	//�v���C���[
	std::vector<std::unique_ptr<Player>> players_;

	//�v���C���[�l��
	int playerNum_;

	//*****************************************
	//�����o�֐�
	//*****************************************

	//�v���C���[�ԍ����ƂŃ��f���������肷��
	Transform FixTrans(int _playerNum);

	//�v���C���[�J���[��ݒ�
	void InitPlayerColor();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="playerNum">�f�[�^�o���N����l���������Ă���</param>
	PlayerManager(void);
	PlayerManager(const PlayerManager& instance_) = default;
	~PlayerManager(void);
	

};

