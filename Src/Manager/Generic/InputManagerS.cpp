#include "InputManagerS.h"

void InputManagerS::Init()
{
	//���̓C�x���g�̏�����
	ResetTable();

	//�A�i���O���͂̑Ή��\��������
	analogInputTable_[ANALOG_INPUT_TYPE::L_UP] = [](const XINPUT_STATE& state) 
		{
		return state.ThumbLY > 10000;
		};
	analogInputTable_[ANALOG_INPUT_TYPE::L_DOWN] = [](const XINPUT_STATE& state) 
		{
		return state.ThumbLY < -10000;
		};
	analogInputTable_[ANALOG_INPUT_TYPE::L_RIGHT] = [](const XINPUT_STATE& state)
		{
		return state.ThumbLX > 10000;
		};
	analogInputTable_[ANALOG_INPUT_TYPE::L_LEFT] = [](const XINPUT_STATE& state)
		{
		return state.ThumbLX < -10000;
		};
	analogInputTable_[ANALOG_INPUT_TYPE::R_UP] = [](const XINPUT_STATE& state)
		{
		return state.ThumbRY > 10000;
		};
	analogInputTable_[ANALOG_INPUT_TYPE::R_DOWN] = [](const XINPUT_STATE& state) 
		{
		return state.ThumbRY < -10000;
		};
	analogInputTable_[ANALOG_INPUT_TYPE::R_RIGHT] = [](const XINPUT_STATE& state)
		{
		return state.ThumbRX > 10000;
		};
	analogInputTable_[ANALOG_INPUT_TYPE::R_LEFT] = [](const XINPUT_STATE& state) 
		{
		return state.ThumbRX < -10000;
		};
	analogInputTable_[ANALOG_INPUT_TYPE::L_TRIGGER] = [](const XINPUT_STATE& state) 
		{
		return state.LeftTrigger > 10000;
		};
	analogInputTable_[ANALOG_INPUT_TYPE::R_TRIGGER] = [](const XINPUT_STATE& state) 
		{
		return state.RightTrigger > 10000;
		};

	for (const auto& keyValue : inputTable_)
	{
		currentInput_[keyValue.first] = false;
	}
	lastInput_ = currentInput_;
}

void InputManagerS::Update()
{
	//�������������ĂȂ����L�^����
	lastInput_ = currentInput_;	//�O�̃v�b�V�������L�^����

	//�L�[�{�[�h���
	char keyState[256] = {};
	GetHitKeyStateAll(keyState);

	//�p�b�h���
	int padState = GetJoypadInputState(DX_INPUT_PAD1);

	//�}�E�X���
	int mouseState = GetMouseInput();

	//�A�i���O���͏��
	XINPUT_STATE xinputState = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &xinputState);

	//�e�[�u���̍s����
	for (const auto& keyValue : inputTable_)
	{
		//����̃L�[�̓��͏����擾
		for (auto input : keyValue.second)
		{
			bool pressed = false;	//�����ĂȂ���Ԃŏ�����
			if (input.type == PEIPHERAL_TYPE::KEYBOARD)
			{
				pressed = keyState[input.code];
			}
			else if (input.type == PEIPHERAL_TYPE::GAMEPAD)
			{
				pressed = padState & input.code;
			}
			else if (input.type == PEIPHERAL_TYPE::X_ANALOG)
			{
				auto analogType = static_cast<ANALOG_INPUT_TYPE>(input.code);
				if (analogInputTable_.contains(analogType))
				{
					pressed = analogInputTable_.at(analogType)(xinputState);
				}
			}
			currentInput_[keyValue.first] = pressed;
			if (pressed)
			{
				break;
			}
		}
	}
}

void InputManagerS::Release()
{
}

bool InputManagerS::IsTrgDown(INPUT_EVENT inputEvent) const
{
	if (!currentInput_.contains(inputEvent))
	{
		return false;
	}
	return currentInput_.at(inputEvent) && !lastInput_.at(inputEvent);
}

bool InputManagerS::IsPressed(INPUT_EVENT inputEvent) const
{
	return currentInput_.at(inputEvent);
}

void InputManagerS::ResetTable()
{
	inputTable_ = 
	{
		{INPUT_EVENT::OK,{
			{PEIPHERAL_TYPE::KEYBOARD, KEY_INPUT_SPACE},
			{PEIPHERAL_TYPE::GAMEPAD, PAD_INPUT_B},//B�{�^��
			{PEIPHERAL_TYPE::X_ANALOG, (int)ANALOG_INPUT_TYPE::NONE}
	}},
		{INPUT_EVENT::CANCEL,{
			{PEIPHERAL_TYPE::KEYBOARD, KEY_INPUT_RETURN},
			{PEIPHERAL_TYPE::GAMEPAD, PAD_INPUT_A},	//A�{�^��
			{PEIPHERAL_TYPE::X_ANALOG, (int)ANALOG_INPUT_TYPE::NONE},	//�E�g���K�[
	}},
		{INPUT_EVENT::PAUSE,{
			{PEIPHERAL_TYPE::KEYBOARD, KEY_INPUT_P},
			{PEIPHERAL_TYPE::GAMEPAD, PAD_INPUT_R},	//�X�^�[�g�{�^��
			{PEIPHERAL_TYPE::X_ANALOG, (int)ANALOG_INPUT_TYPE::NONE}
	}},
		{INPUT_EVENT::RIGHT,{
			{PEIPHERAL_TYPE::KEYBOARD, KEY_INPUT_Z},
			{PEIPHERAL_TYPE::GAMEPAD, PAD_INPUT_RIGHT},	//�\���E�{�^��
			{PEIPHERAL_TYPE::X_ANALOG, (int)ANALOG_INPUT_TYPE::L_RIGHT}
	}},
		{INPUT_EVENT::LEFT,{
			{PEIPHERAL_TYPE::KEYBOARD, KEY_INPUT_X},
			{PEIPHERAL_TYPE::GAMEPAD, PAD_INPUT_LEFT},	//�\�����{�^��
			{PEIPHERAL_TYPE::X_ANALOG, (int)ANALOG_INPUT_TYPE::L_LEFT},
	}},
		{INPUT_EVENT::UP,{
			{PEIPHERAL_TYPE::KEYBOARD, KEY_INPUT_DOWN},
			{PEIPHERAL_TYPE::GAMEPAD, PAD_INPUT_DOWN},	//�\����{�^��
			{PEIPHERAL_TYPE::X_ANALOG, (int)ANALOG_INPUT_TYPE::L_UP}
	}},
		{INPUT_EVENT::DOWN,{
			{PEIPHERAL_TYPE::KEYBOARD, KEY_INPUT_UP},
			{PEIPHERAL_TYPE::GAMEPAD, PAD_INPUT_UP},	//�\�����{�^��
			{PEIPHERAL_TYPE::X_ANALOG, (int)ANALOG_INPUT_TYPE::L_DOWN},
	}},
	};
}

float InputManagerS::GetLStickDeg(InputManager::JOYPAD_NO no) const
{
	float deg = 0.0f;
	Vector2 knockSize = GetKnockLStickSize(no);
	if (knockSize.x == 0.0f && knockSize.y == 0.0f)
	{
		return deg;
	}
	auto rad = std::atan2(knockSize.y, knockSize.x);
	deg = rad * (180.0f / DX_PI_F);
	deg += 90.0f;
	deg = deg < 0 ? deg + 360 : deg;
	return deg;
}

float InputManagerS::GetRStickDeg(InputManager::JOYPAD_NO no) const
{
	float deg = 0.0f;
	Vector2 knockSize = GetKnockRStickSize(no);
	if (knockSize.x == 0.0f && knockSize.y == 0.0f)
	{
		return deg;
	}
	auto rad = std::atan2(knockSize.y, knockSize.x);
	deg = rad * (180.0f / DX_PI_F);
	deg += 90.0f;
	deg = deg < 0 ? deg + 360 : deg;
	return deg;
}

Vector2 InputManagerS::GetKnockLStickSize(InputManager::JOYPAD_NO no) const
{
	auto padInfo = InputManager::GetInstance().GetJPadInputState(no);
	return Vector2(padInfo.AKeyLX, padInfo.AKeyLY);
}

Vector2 InputManagerS::GetKnockRStickSize(InputManager::JOYPAD_NO no) const
{
	auto padInfo = InputManager::GetInstance().GetJPadInputState(no);
	return Vector2(padInfo.AKeyRX, padInfo.AKeyRY);
}

InputManagerS::InputManagerS()
{
}
