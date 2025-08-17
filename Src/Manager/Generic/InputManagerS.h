#pragma once
#include <DxLib.h>
#include <map>				//�Ή��\�̂���
#include <unordered_map>	//�Ή��\�̂���
#include <string>			//�Ή��L�[�̂���
#include <vector>			//�f�o�C�X��ǉ����邽��
#include <functional>
#include"InputManager.h"
#include "../../Template/Singleton.h"

/// <summary>
/// ���̓C�x���g
/// </summary>
enum class INPUT_EVENT
{
	OK,		//����
	CANCEL,	//�L�����Z��
	PAUSE,	//�|�[�Y
	RIGHT,	//�E��
	LEFT,	//����
	UP,		//���
	DOWN,	//����
	MAX
};
//���̓C�x���g�̍ő吔
static constexpr int INPUT_EVENT_MAX = static_cast<int>(INPUT_EVENT::MAX); 


/// <summary>
/// ��ϋ@����
/// </summary>
enum class PEIPHERAL_TYPE
{
	KEYBOARD,	//�L�[�{�[�h
	GAMEPAD,	//�Q�[���p�b�h
	//MOUSE,		//�}�E�X
	X_ANALOG,	//XBOX�A�i���O�X�e�B�b�N
	MAX
};

/// <summary>
/// �A�i���O���͎��
/// </summary>
enum class ANALOG_INPUT_TYPE
{
	NONE,
	L_UP,		//���X�e�B�b�N�̏㉺
	L_DOWN,		//���X�e�B�b�N�̏㉺
	L_RIGHT,	//���X�e�B�b�N�̍��E
	L_LEFT,		//���X�e�B�b�N�̍��E
	R_UP,		//�E�X�e�B�b�N�̏㉺
	R_DOWN,		//�E�X�e�B�b�N�̏㉺
	R_RIGHT,	//�E�X�e�B�b�N�̍��E
	R_LEFT,		//�E�X�e�B�b�N�̍��E
	L_TRIGGER,		//���g���K�[
	R_TRIGGER,		//�E�g���K�[
};

class InputManagerS : public Singleton<InputManagerS>
{
	friend class Singleton<InputManagerS>;

public:	
	
	/// <summary>
	/// ����������
	/// </summary>
	void Init();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �������
	/// </summary>
	void Release();

	/// <summary>
	/// �w�肳�ꂽ�R�[�h�������ꂽ�u�Ԃ�
	/// </summary>
	/// <param name="inputEvent">���̓C�x���g</param>
	/// <returns>�����ꂽ�u�Ԃ�true,�����łȂ��ꍇfalse</returns>
	bool IsTrgDown(INPUT_EVENT inputEvent) const;

	/// <summary>
	/// �w�肳�ꂽ�R�[�h��������Ă��邩
	/// </summary>
	/// <param name="inputEvent">���̓C�x���g</param>
	/// <returns>������Ă�ꍇtrue, �����łȂ��ꍇfalse</returns>
	bool IsPressed(INPUT_EVENT inputEvent) const;

	/// <summary>
	/// �Ή��\�̃��Z�b�g
	/// </summary>
	void ResetTable();

	//L�X�e�B�b�N�̊p�x���擾
	float GetLStickDeg(InputManager::JOYPAD_NO no) const;

	//R�X�e�B�b�N�̊p�x���擾
	float GetRStickDeg(InputManager::JOYPAD_NO no) const;

private:
	//���0.0�x�Ƃ��Ċp�x��n��
	Vector2 GetKnockLStickSize(InputManager::JOYPAD_NO no) const;
	Vector2 GetKnockRStickSize(InputManager::JOYPAD_NO no) const;

	//���̓C�x���g�̑Ή��\
	struct InputState
	{
		PEIPHERAL_TYPE type;	//�f�o�C�X�̎��
		uint32_t code;			//���̓R�[�h
	};

	//���̓C�x���g�Ǝ��ۂ̓��͂̑Ή��\
	using InputTable_t = std::unordered_map<INPUT_EVENT, std::vector<InputState>>;
	InputTable_t inputTable_;		//�C�x���g�Ǝ��ۂ̓��͂̑Ή��\	
	InputTable_t tmpInputTable_;	//�ꎞ�I�ȓ��̓e�[�u��

	//���݂̏�ԂƑO�̏�Ԃ��r���邽�߂̕ϐ�
	InputState currentState_;		//���݂̏��
	InputState lastState_;			//�O�̏��

	//���݂̓��͏�ԂƑO�̓��͏�Ԃ�ێ����邽�߂̕ϐ�
	using InputData_t = std::unordered_map<INPUT_EVENT, bool>;
	InputData_t currentInput_;		//���̃C�x���g�ɑΉ�����{�^����������Ă��Ԃ�
	InputData_t lastInput_;			//���̃C�x���g�ɑΉ�����{�^����������Ă���Ԃ�(���O)

	//���̓f�o�C�X�̃��X�g
	std::string inputListForDisplay_[INPUT_EVENT_MAX] = 
	{
		"OK",
		"Cancel",
		"Pause",
		"Right",
		"Left",
		"Up",
		"Down",
	};

	//�A�i���O���͂̑Ή��\
	using AnalogInputTable_t = std::unordered_map<ANALOG_INPUT_TYPE, std::function<bool(XINPUT_STATE&)>>;
	AnalogInputTable_t analogInputTable_;

	//�R���X�g���N�^
	InputManagerS(); 

	//�f�X�g���N�^
	~InputManagerS() = default;

};

