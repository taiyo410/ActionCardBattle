#pragma once
#include <memory>
#include "SceneBase.h"

class PauseScene;
class Enemy;
class GameScene : public SceneBase
{

public:
	
	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	//�ǂݍ��ݏ���
	void Load(void) override;

	//����������
	void Init(void) override;

private:

	int frame_;

	//�|�[�Y���
	std::shared_ptr<PauseScene> pauseScene_;

	//�G
	std::unique_ptr<Enemy>enemy_;

	//�X�V�֐�
	void NormalUpdate(void) override;

	//�`��֐�
	void NormalDraw(void) override;

	//�����̕ύX
	void ChangeNormal(void) override;
	
	//�f�o�b�O����
	void DebagUpdate(void);
	void DebagDraw(void);

};