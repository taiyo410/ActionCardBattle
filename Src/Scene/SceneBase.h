#pragma once
#include<functional>
#include "../Application.h"

class SceneManager;
class ResourceManager;
class InputManager;

class SceneBase
{

public:

	//�ŒჍ�[�f�B���O����
	static constexpr float LOADING_TIME = 2.0f;

	//�t�H���g�T�C�Y
	static constexpr int FONT_SIZE = 28;

	//���[�f�B���O
	static constexpr int COMMA_MAX_NUM = 7;											//�unow loading......�v�̃R���}�̐�
	static constexpr float COMMA_TIME = 0.5f;										//�unow loading......�v�̃R���}���𑝂₷����
	static constexpr int LOADING_STRING_POS_X = Application::SCREEN_SIZE_X - 300;	//�unow loading......�v�̍��WX
	static constexpr int LOADING_STRING_POS_Y = Application::SCREEN_SIZE_Y - 40;	//�unow loading......�v�̍��WY

	// �R���X�g���N�^
	SceneBase(void);

	// �f�X�g���N�^
	virtual ~SceneBase(void);

	// �ǂݍ��ݏ���
	virtual void Load(void);

	// ����������
	virtual void Init(void);

	// �X�V�X�e�b�v
	virtual void Update(void);

	// �`�揈��
	virtual void Draw(void);

protected:

	// ���\�[�X�Ǘ�
	ResourceManager& resMng_;
	InputManager& inputMng_;
	SceneManager& scnMng_;

	//�X�V�����Ǘ�
	std::function<void(void)> updataFunc_;
	std::function<void(void)> drawFunc_;

	//���[�f�B���O�o�ߎ���
	float loadingTime_;

	//�I���{�^���t�H���g�n���h��
	int buttnFontHandle_;

	//�X�V�֐�
	virtual void LoadingUpdate(void);
	virtual void NormalUpdate(void);

	//�`��֐�
	virtual void LoadingDraw(void);
	virtual void NormalDraw(void);

	//���[�f�B���O��������ʏ폈����
	virtual void ChangeNormal(void);
	
	//�unow loading......�v�̕`��
	void DrawNowLoading(void);

};