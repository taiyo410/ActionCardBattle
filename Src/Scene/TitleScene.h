#pragma once
#include "SceneBase.h"


class TitleScene : public SceneBase
{

public:

	// �R���X�g���N�^
	TitleScene(void);

	// �f�X�g���N�^
	~TitleScene(void);

	//�ǂݍ��ݏ���
	void Load(void) override;

	//����������
	void Init(void) override;

private:

	//�X�V�֐�
	void NormalUpdate(void) override;

	//�`��֐�
	void NormalDraw(void) override;

	//�����̕ύX
	void ChangeNormal(void) override;
};
