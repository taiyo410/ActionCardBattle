#include "FontManager.h"
#include <DxLib.h>
#include "../Application.h"

const std::wstring FontManager::FONT_DOT = L"�x�X�g�e��DOT";
const std::wstring FontManager::FONT_BOKUTATI = L"�ڂ������̃S�V�b�N";

FontManager::FontManager()
{
	//������
	for (int i = 0; i < static_cast<int>(FONT_TYPE::MAX); i++)
	{
		fontPath_[i] = L"null";
	}
}

void FontManager::Init()
{
	//�t�H���g�o�^���s��
	// �t�H���g�p�X������
	fontPath_[static_cast<int>(FONT_TYPE::DOT)] = L"FontDot.otf";
	fontPath_[static_cast<int>(FONT_TYPE::BOKUTATI)] = L"bokutachi.otf";

	// �t�H���g���V�X�e���ɓo�^
	for (int i = 0; i < FONT_TYPES; i++)
	{
		if (AddFontResourceEx(
			(Application::PATH_FONT + fontPath_[i]).c_str(),
			FR_PRIVATE,
			NULL)
			== -1)
		{
			return;
		}
	}
}

void FontManager::Destroy()
{
	// �t�H���g�o�^����
	for (int i = 0; i < FONT_TYPES; i++)
	{
		if (RemoveFontResourceEx(
			(Application::PATH_FONT + fontPath_[i]).c_str(),
			FR_PRIVATE,
			NULL)
			== -1)
		{
			return;
		}
	}
}