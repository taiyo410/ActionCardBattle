#pragma once
#include <string>
#include <unordered_map>
#include "SceneBase.h"

class PauseScene : public SceneBase
{
public:

	enum class LIST
	{
		RESUME,  // ������
		TITLE,   // �^�C�g���ɖ߂�
		MAX
	};

	//���X�g
	static constexpr int LIST_MAX = static_cast<int>(LIST::MAX);

	// �R���X�g���N�^
	PauseScene(void);

	// �f�X�g���N�^
	~PauseScene(void) override;

	//�ǂݍ��ݏ���
	void Load(void)override;

	//����������
	void Init(void)override;

	//�X�V�֐�
	void NormalUpdate(void)override;

	//�`��֐�
	void NormalDraw(void)override;

private:
	
	//��ʂ̃A���t�@�l
	static constexpr int PAUSE_ALPHA = 128; 

	//�t�H���g�T�C�Y
	static constexpr int FONT_SIZE = 32;
	static constexpr int FONT_THICK = 3; // �t�H���g�̑���

	int imgTest_;

	//�|�[�Y�t�H���g
	int pauseFont_; 	

	//�|�[�Y���X�g�̑I��
	int selectIndex_;

	//�I�����X�g
	std::wstring pasueList_[LIST_MAX] =
	{
		L"�Â���",
		L"�^�C�g���֖߂�"
	};

	//���X�g�I���e�[�u��
	std::unordered_map<LIST, std::function<void()>> listFuncTable_;
};

