#pragma once
#include <memory>
#include <chrono>
#include <list>
#include "../../Template/Singleton.h"
#include "../../Common/Fader.h"

// �������܂��񂪁A�ǂ����Ă��g����������
#define mainCamera SceneManager::GetInstance().GetCamera().lock()

class SceneBase;
class Fader;
class Camera;

class SceneManager : public Singleton<SceneManager>
{
	//�V���O���g���ɂ������L����
	friend class Singleton<SceneManager>; 

public:

	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		GAME
	};

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// 3D�֘A�̏�����
	/// </summary>
	void Init3D();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���\�[�X�̔j��
	/// </summary>
	void Release();

	/// <summary>
	/// �擪�́iUpdata���Ă΂��j�V�[����؂�ւ���
	/// </summary>
	/// <param name="scene">�؂�ւ���̃V�[��</param>
	void CreateScene(std::shared_ptr<SceneBase> scene);

	/// <summary>
	/// ���ׂẴV�[����؂�ւ���
	/// </summary>
	/// <param name="scene">�؂�ւ���̃V�[��</param>
	void ChangeAllScene(std::shared_ptr<SceneBase> scene);

	/// <summary>
	/// �V�[�����v�b�V������B�X�^�b�N�̐���������
	/// ��ԏ�̃V�[����Updata�����Ă΂�܂���B
	/// </summary>
	/// <param name="scene">�ςރV�[��</param>
	void PushScene(std::shared_ptr<SceneBase> scene);

	/// <summary>
	/// �X�^�b�N�̓��̃V�[�����폜����B
	/// �������A�X�^�b�N��ɃV�[����������Ȃ��ꍇ�́A�폜���Ȃ��B
	/// </summary>
	void PopScene();

	/// <summary>
	/// �V�[���J��
	/// </summary>
	/// <param name="nextId">�ύX��̃V�[��</param>
	void ChangeScene(SCENE_ID nextId);
	
	/// <summary>
	/// �t�F�[�h���n�߂�
	/// </summary>
	void StartFadeIn();

	/// <summary>
	/// ���݂̃V�[��ID��Ԃ�
	/// </summary>
	/// <returns>���݂̃V�[��ID</returns>
	inline SCENE_ID GetSceneID() const { return sceneId_; }

	/// <summary>
	/// �f���^�^�C����Ԃ�
	/// </summary>
	/// <returns>�f���^�^�C��</returns>
	inline float GetDeltaTime() const { return deltaTime_; }

	/// <summary>
	/// �o�ߎ��Ԃ�Ԃ�
	/// </summary>
	/// <returns>�o�ߎ���</returns>
	inline float GetTotalTime() const { return totalTime_; }

	/// <summary>
	/// �J������Ԃ�
	/// </summary>
	/// <returns>�J����</returns>
	std::weak_ptr<Camera> GetCamera() const { return camera_; }

private:

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// �e��V�[��
	std::list<std::shared_ptr<SceneBase>> scenes_;

	// �t�F�[�h
	std::unique_ptr<Fader> fader_;

	// �J����
	std::shared_ptr<Camera> camera_;

	// �V�[���J�ڒ�����
	bool isSceneChanging_;

	// �f���^�^�C��
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	//�o�ߎ���
	float totalTime_;
	
	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SceneManager();

	// �f�X�g���N�^�����l
	~SceneManager() = default;

	// �f���^�^�C�������Z�b�g����
	void ResetDeltaTime();

	// �V�[���J��
	void DoChangeScene(SCENE_ID sceneId);

	// �t�F�[�h
	void Fade();

};
