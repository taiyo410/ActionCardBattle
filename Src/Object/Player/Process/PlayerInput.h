#pragma once
#include<DxLib.h>
#include<memory>
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/Generic/InputManagerS.h"
#include"../Utility/Utility3D.h"
#include"./InputBase.h"
//#define DEBUG_ON
class PlayerBase;
class PlayerInput:public InputBase
{
public:
    //*************************************************
    //�e�A�N�V��������{�^��
    //*************************************************]
    using JOYPAD_BTN = InputManager::JOYPAD_BTN;
    //�ړ�
    static constexpr int MOVE_FRONT_KEY = KEY_INPUT_W;
    static constexpr int MOVE_LEFT_KEY = KEY_INPUT_A;
    static constexpr int MOVE_BACK_KEY = KEY_INPUT_S;
    static constexpr int MOVE_RIGHT_KEY = KEY_INPUT_D;

    //�J�[�h�I��
    //�E
    static constexpr int CARD_MOVE_RIGHT_KEY = KEY_INPUT_E;
    static constexpr JOYPAD_BTN CARD_MOVE_RIGHT_BTN = JOYPAD_BTN::R_BUTTON;
    static constexpr int CARD_MOVE_LEFT_KEY = KEY_INPUT_Q;
    static constexpr JOYPAD_BTN CARD_MOVE_LEFT_BTN = JOYPAD_BTN::L_BUTTON;
    //�J�[�h�g�p�L�[
    static constexpr int CARD_USE_KEY = KEY_INPUT_F;
    static constexpr JOYPAD_BTN CARD_USE_BTN = JOYPAD_BTN::RIGHTBUTTON_RIGHT;

    //�J�[�h�`���[�W
    static constexpr int CARD_CHARGE_KEY = KEY_INPUT_R;
    static constexpr JOYPAD_BTN CARD_CHARGE_BTN = JOYPAD_BTN::LEFTBUTTON_TOP;

    //�ړ�����ɂȂ�X�e�B�b�N�̑傫��
    static constexpr int STICK_MOVE_SIZE_MIN = 200;

    //�_�b�V��
    //static constexpr int DASH_KEY = KEY_INPUT_L;

    ////�p���`
    //static constexpr int PUNCH_KEY = KEY_INPUT_RETURN;
    //static constexpr InputManager::JOYPAD_BTN PUNCH_BTN = InputManager::JOYPAD_BTN::RIGHTBUTTON_LEFT;

    ////�W�����v
    //static constexpr int JUMP_KEY = KEY_INPUT_SPACE;
    //static constexpr InputManager::JOYPAD_BTN JUMP_BTN = InputManager::JOYPAD_BTN::RIGHTBUTTON_RIGHT;

    static constexpr float STICK_MARGIN_DEG = 90.0f;

    //�p�x�֘A
    static constexpr float FLONT_DEG = 0.0f;
    static constexpr float LEFT_DEG = 270.0f;
    static constexpr float BACK_DEG = 180.0f;
    static constexpr float RIGHT_DEG = 90.0f;

    //�f���^�^�C��
    static constexpr float DELTA_TIME = 1.0f / 60.0f;

    ////�A�N�V�����{�^���̎��
    //enum class ACT_CNTL
    //{
    //    NONE            //�������Ă��Ȃ��Ƃ�
    //    , MOVE          //�ړ�
    //    , DASHMOVE      //�_�b�V��
    //    , PUNCH         //�p���`
    //    , JUMP          //�W�����v
    //    , CARD_CHARGE   //�J�[�h�`���[�W
    //    ,_CARD_USE      //�J�[�h�g�p
    //    ,CARD_MOVE_LEFT //�J�[�h��
    //    ,CARD_MOVE_RIGHT//�J�[�h�E
    //};

    enum class CNTL
    {
        NONE,
        KEYBOARD,
        PAD
    };
    //�V���O���g�������邽�߂ɊO���Ő�������Ȃ��悤�ɂ���
    PlayerInput(InputManager::JOYPAD_NO _padNum, InputManager::CONTROLL_TYPE _cntl);
    ~PlayerInput(void)override;

    //�ύX���̏�����
	void Init(void)override;

    void Update(void)override;

    ////�R���g���[������
    //bool CheckAct(ACT_CNTL _actCntl) { return actCntl_ == _actCntl ? true : false; }
#ifdef _DEBUG
#endif // _DEBUG_ON

 

    //�Q�b�^
    //----------------------------------------------------------------
    ACT_CNTL GetAct(void) { return actCntl_; }
    float GetStickDeg(void){ return stickDeg_; }
    float GetMoveDeg(void) { return moveDeg_; }
    VECTOR GetDir(void) { return moveDir_; }
private:
    //�����o�֐�
    void InputKeyBoard(void);
    void InputAll(void);
    void InputPad(void);

    void KeyBoard(void);
    void Pad(void);

    //�����o�ϐ�
    //-----------------------------------------------------------------------
    float leftStickX_;          //�X�e�B�b�N�̊p�xX
    float leftStickY_;          //�X�e�B�b�N�̊p�xY

    //�X�e�B�b�N�̊p�x(0�`1000��Ԃ�)
    Vector2 LStickAngleSize_;



    float stickDeg_;            //�p�b�h�̃X�e�B�b�N�̊p�x
    float moveDeg_;             //�ړ�����
    VECTOR moveDir_;            //�ړ�����

    InputManager::CONTROLL_TYPE cntl_;                 //���̓f�o�C�X
    InputManager::JOYPAD_NO padNum_;                //�p�b�h�ԍ�

    std::map<InputManager::CONTROLL_TYPE, std::function<void(void)>>inputUpdates_;


};

