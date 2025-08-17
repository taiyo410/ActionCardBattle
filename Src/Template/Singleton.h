#pragma once
#include <memory>
#include <cassert>

// �V���O���g���e���v���[�g�N���X
template <typename T>
class Singleton
{
public:

    /// <summary>
    /// �C���X�^���X�̐���
    /// </summary>
    static void CreateInstance()
    {
        if (!instance_)
        {
            instance_ = new T();
        }
    }

    /// <summary>
    /// �C���X�^���X�ւ̃A�N�Z�X
    /// </summary>
    /// <returns>�C���X�^���X</returns>
    static T& GetInstance()
    {
        assert(instance_ != nullptr && "�V���O���g���N���X����������Ă��Ȃ�");
        return *instance_;
    }


	/// <summary>
	/// �������
	/// </summary>
	static void Destroy()
	{
		if (instance_)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}   

    /// <summary>
    /// �R�s�[�R���X�g���N�^���폜
    /// </summary>
    /// <param name=""></param>
    Singleton(const Singleton&) = delete;

    /// <summary>
    /// �R�s�[������Z�q���폜
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Singleton& operator=(const Singleton&) = delete;

protected:

    /// <summary>
    /// �f�t�H���g�R���X�g���N�^�� protected �ɂ��ĊO��������h�~
    /// </summary>
    Singleton() = default;

    /// <summary>
    /// �f�X�g���N�^�� protected
    /// </summary>
    virtual ~Singleton() = default;

private:

    //�ÓI�����o������
    inline static T* instance_ = nullptr; 

};

