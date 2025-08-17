#define _CRTDBG_MAP_ALLOC
#include <DxLib.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include "Application.h"
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

// WinMain�֐�
//---------------------------------
int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ���������[�N�����o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �C���X�^���X�̐���
	Application::CreateInstance();	
	
	// �C���X�^���X�̎擾
	Application& instance = Application::GetInstance();

	// ������
	if (!instance.Init())
	{
		// ���������s
		return -1;
	}

	// ���s
	instance.Run();

	// ���\�[�X�̔j��
	if(!instance.Release())
	{
		// ���������s
		return -1;
	}

	// �C���X�^���X�̔j��
	instance.Destroy();

	return 0;
}
