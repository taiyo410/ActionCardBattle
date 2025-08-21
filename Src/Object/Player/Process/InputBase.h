#pragma once
#include<DxLib.h>
class InputBase
{
public:
    //�A�N�V�����{�^���̎��
    enum class ACT_CNTL
    {
        NONE            //�������Ă��Ȃ��Ƃ�
        , MOVE          //�ړ�
        , DASHMOVE      //�_�b�V��
        , PUNCH         //�p���`
        , JUMP          //�W�����v
        , CARD_CHARGE   //�J�[�h�`���[�W
        , _CARD_USE      //�J�[�h�g�p
        , CARD_MOVE_LEFT //�J�[�h��
        , CARD_MOVE_RIGHT//�J�[�h�E
    };

    InputBase(void);
	virtual ~InputBase(void);
    //�ύX���̏�����
    virtual void Init(void) = 0;

    virtual void Update(void) = 0;

    //�R���g���[������
    bool CheckAct(ACT_CNTL _actCntl) { return actCntl_ == _actCntl ? true : false; }
protected:
	//�����o�ϐ�
	//-----------------------------------------------------------------------
	//����Ǘ��p
	ACT_CNTL actCntl_;

	float moveDeg_;             //�ړ��p�x
	VECTOR moveDir_;            //�ړ������x�N�g��
};

