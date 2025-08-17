#pragma once
#include <map>
#include <Dxlib.h>
#include "../../Template/Singleton.h"
#include "../../Common/Vector2.h"

class InputManager : public Singleton<InputManager>
{
	// �V���O���g���ɂ������L����
	friend class Singleton<InputManager>;

public:

	// �Q�[���R���g���[���[�̔F���ԍ�
	// DxLib�萔�ADX_INPUT_PAD1���ɑΉ�
	enum class JOYPAD_NO
	{
		KEY_PAD1,			// �L�[���͂ƃp�b�h�P����
		PAD1,				// �p�b�h�P����
		PAD2,				// �p�b�h�Q����
		PAD3,				// �p�b�h�R����
		PAD4,				// �p�b�h�S����
		INPUT_KEY = 4096	// �L�[����
	};

	// �Q�[���R���g���[���[�^�C�v
	// DxLib�萔�ADX_OTHER���ɑΉ�
	enum class JOYPAD_TYPE
	{
		OTHER = 0,
		XBOX_360,
		XBOX_ONE,
		DUAL_SHOCK_4,
		DUAL_SENSE,
		SWITCH_JOY_CON_L,
		SWITCH_JOY_CON_R,
		SWITCH_PRO_CTRL,
		MAX
	};

	// �Q�[���R���g���[���[�{�^��
	enum class JOYPAD_BTN
	{
		RIGHTBUTTON_LEFT = 0,	// X
		RIGHTBUTTON_RIGHT,		// B
		RIGHTBUTTON_TOP,		// Y
		RIGHTBUTTON_DOWN,		// A
		R_TRIGGER,				// R_TRIGGER
		L_TRIGGER,				// L_TRIGGER
		R_BUTTON,				// R_BUTTON
		L_BUTTON,				// L_BUTTON
		START_BUTTON,			// START_BUTTON
		SELECT_BUTTON,			// SELECT_BUTTON
		LEFTBUTTON_TOP,			// ��
		LEFTBUTTON_DOWN,		// ��
		LEFTBUTTON_LEFT,		// ��
		LEFTBUTTON_RIGHT,		// �E
		LEFT_STICK,				// ���X�e�B�b�N��������
		RIGHT_STICK,			// �E�X�e�B�b�N��������
		MAX
	};

	// �Q�[���R���g���[���[�̓��͏��
	struct JOYPAD_IN_STATE
	{
		unsigned char ButtonsOld[static_cast<int>(JOYPAD_BTN::MAX)];
		unsigned char ButtonsNew[static_cast<int>(JOYPAD_BTN::MAX)];
		bool IsOld[static_cast<int>(JOYPAD_BTN::MAX)];
		bool IsNew[static_cast<int>(JOYPAD_BTN::MAX)];
		bool IsTrgDown[static_cast<int>(JOYPAD_BTN::MAX)];
		bool IsTrgUp[static_cast<int>(JOYPAD_BTN::MAX)];
		int AKeyLX;
		int AKeyLY;
		int AKeyRX;
		int AKeyRY;
	};

	//�R���g���[���[�f�o�C�X
	enum class CONTROLL_TYPE
	{
		KEY_BOARD		//�L�[�{�[�h
		,CONTROLLER		//�R���g���[���[
		,ALL			//���ׂĂ̓��͂��󂯕t����
	};

	void Init(void);
	void Update(void);

	// ���\�[�X�̔j��
	void Release(void);

	// ������s���L�[��ǉ�
	void Add(int key);

	// ������s���L�[���N���A
	void Clear(void);

	// �L�[�̉�������
	bool IsNew(int key) const;

	// �L�[�̉�������(�������ςȂ���NG)
	bool IsTrgDown(int key) const;

	// �L�[�𗣂������̔���
	bool IsTrgUp(int key) const;

	// �}�E�X���W�̎擾
	Vector2 GetMousePos(void) const;

	// �}�E�X�̃N���b�N��Ԃ��擾(MOUSE_INPUT_LEFT�ARIGHT)
	int GetMouse(void) const;

	// �}�E�X�����N���b�N���ꂽ��
	bool IsClickMouseLeft(void) const;

	// �}�E�X���E�N���b�N���ꂽ��
	bool IsClickMouseRight(void) const;

	// �}�E�X�����N���b�N���ꂽ��(�������ςȂ���NG)
	bool IsTrgMouseLeft(void) const;

	// �}�E�X���E�N���b�N���ꂽ��(�������ςȂ���NG)
	bool IsTrgMouseRight(void) const;

	// �R���g���[���̓��͏����擾����
	JOYPAD_IN_STATE GetJPadInputState(JOYPAD_NO no);

	// �{�^���������ꂽ
	bool IsPadBtnNew(JOYPAD_NO no, JOYPAD_BTN btn) const;
	bool IsPadBtnTrgDown(JOYPAD_NO no, JOYPAD_BTN btn) const;
	bool IsPadBtnTrgUp(JOYPAD_NO no, JOYPAD_BTN btn) const;

	// �R���g���[���̓��͏����擾����
	DINPUT_JOYSTATE GetJPadDInputState(JOYPAD_NO no);

	// �R���g���[��(XBOX)�̓��͏����擾����
	XINPUT_STATE GetJPadXInputState(JOYPAD_NO no);

private:

	// �L�[���
	struct Info
	{
		int key;			// �L�[ID
		bool keyOld;		// 1�t���[���O�̉������
		bool keyNew;		// ���t���[���̉������
		bool keyTrgDown;	// ���t���[���Ń{�^���������ꂽ��
		bool keyTrgUp;		// ���t���[���Ń{�^���������ꂽ��
	};

	// �}�E�X
	struct MouseInfo
	{
		int key;			// �L�[ID
		bool keyOld;		// 1�t���[���O�̉������
		bool keyNew;		// ���t���[���̉������
		bool keyTrgDown;	// ���t���[���Ń{�^���������ꂽ��
		bool keyTrgUp;		// ���t���[���Ń{�^���������ꂽ��
	};

	// �R���g���[�����
	DINPUT_JOYSTATE joyDInState_;

	// �R���g���[�����(XBOX)
	XINPUT_STATE joyXInState_;

	// �L�[���
	std::map<int, InputManager::Info> keyInfos_;
	InputManager::Info infoEmpty_;

	// �}�E�X���
	std::map<int, InputManager::MouseInfo> mouseInfos_;
	InputManager::MouseInfo mouseInfoEmpty_;

	// �}�E�X�J�[�\���̈ʒu
	Vector2 mousePos_;
	
	// �}�E�X�{�^���̓��͏��
	int mouseInput_;

	// �p�b�h���
	JOYPAD_IN_STATE padInfos_[5];

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	InputManager(void);
	~InputManager(void) = default;

	// �z��̒�����L�[�����擾����
	const InputManager::Info& Find(int key) const;

	// �z��̒�����}�E�X�����擾����
	const InputManager::MouseInfo& FindMouse(int key) const;

	// �ڑ����ꂽ�R���g���[���̎�ʂ��擾����
	JOYPAD_TYPE GetJPadType(JOYPAD_NO no);

	// �R���g���[���̓��͏����X�V����
	void SetJPadInState(JOYPAD_NO jpNo);

};