#pragma once
#include <map>
#include <string>
#include "../../Template/Singleton.h"
#include "Resource.h"

class ResourceManager : public Singleton<ResourceManager>
{

	friend class Singleton<ResourceManager>;

public:

	/// <summary>
	/// ���\�[�X��
	/// </summary>
	enum class SRC
	{
		NONE,
		TEST,
	};

	/// <summary>
	/// ������
	/// </summary>
	/// <param name=""></param>
	void Init(void);

	/// <summary>
	/// ���(�V�[���ؑ֎��Ɉ�U���)
	/// </summary>
	/// <param name=""></param>
	void SceneChangeRelease(void);

	/// <summary>
	/// ���\�[�X�̊��S���
	/// </summary>
	/// <param name=""></param>
	void Release(void);

	/// <summary>
	/// ���\�[�X�̃��[�h
	/// </summary>
	/// <param name="src">�ǂݍ��ރ��\�[�X</param>
	/// <returns>���\�[�X</returns>
	const Resource& Load(SRC src);

	/// <summary>
	/// ���\�[�X�̕������[�h(���f���p)
	/// </summary>
	/// <param name="src">�������������\�[�X</param>
	/// <returns>�����������\�[�X</returns>
	int LoadModelDuplicate(SRC src);

private:

	// ���\�[�X�Ǘ��̑Ώ�
	std::map<SRC, std::unique_ptr<Resource>> resourcesMap_;

	// �ǂݍ��ݍς݃��\�[�X
	std::map<SRC, Resource&> loadedMap_;

	Resource dummy_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	ResourceManager(void);
	~ResourceManager(void) = default;

	// �������[�h
	Resource& _Load(SRC src);

};
