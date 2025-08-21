#include<DxLib.h>
#include "CardBase.h"
#include "CardDeck.h"

CardDeck::CardDeck(Vector2& _centerPos):
	drawPile_(),
	currentNum_(0),
	nextNum_(0),
	prevNum_(0),
	centerPos_(_centerPos)
{
	currentNum_ = 0;
	nextNum_ = 0;
	prevNum_ = 0;
}

CardDeck::~CardDeck(void)
{
}

void CardDeck::Init(void)
{
	//for (int i = 0; i < CARD_NUM_MAX; i++)
	//{
	//	std::unique_ptr<CardBase> card = std::make_unique<CardBase>(CARD_POWS[i]);
	//	drawPile_.emplace_back(std::move(card));
	//}
	currentNum_ = 0;
	nextNum_ = currentNum_ + 1;
	prevNum_ = CARD_NUM_MAX - 1;

	Vector2 pos = centerPos_;
}

void CardDeck::CardUse(void)
{
	drawPile_[currentNum_]->Execute();
}

void CardDeck::CardCharge(void)
{
	int i = 0;
}

void CardDeck::DisCard(void)
{
}

void CardDeck::CardMoveRight(void)
{
	//�w�߂̓v���C���[��G�l�~�[����o��
	currentNum_++;
	nextNum_ = currentNum_ + 1;
	prevNum_ = currentNum_ - 1;
	//�J�[�h����
	CardMoveLimit();
}

void CardDeck::CardMoveLeft(void)
{
	//�w�߂̓v���C���[��G�l�~�[����o��
	currentNum_--;
	nextNum_ = currentNum_ + 1;
	prevNum_ = currentNum_ - 1;
	//�J�[�h����
	CardMoveLimit();
}

void CardDeck::Update(void)
{
}

void CardDeck::Draw(void)
{
	int currentCardPow = drawPile_[currentNum_]->GetPow();
	int nextCardPow = drawPile_[nextNum_]->GetPow();
	int prevCardPow = drawPile_[prevNum_]->GetPow();

	const float DISTANCE_X = 40;

	DrawFormatString(centerPos_.x-DISTANCE_X, centerPos_.y, 0xffffff,L"(%d)", prevCardPow);
	DrawFormatString(centerPos_.x, centerPos_.y, 0xffffff,L"(%d)", currentCardPow);
	DrawFormatString(centerPos_.x + DISTANCE_X, centerPos_.y, 0xffffff,L"(%d)", nextCardPow);
}

void CardDeck::Release(void)
{
}

void CardDeck::AddDrawPile(const int _pow)
{
	std::unique_ptr<CardBase>card = std::make_unique<CardBase>(_pow);
	drawPile_.emplace_back(std::move(card));
}

void CardDeck::CardMoveLimit(void)
{
	if (currentNum_ < 0)
	{
		currentNum_ = CARD_NUM_MAX - 1;
	}
	else if (currentNum_ >= CARD_NUM_MAX)
	{
		currentNum_ = 0;
	}
	if (nextNum_ > CARD_NUM_MAX - 1)
	{
		nextNum_ = 0;
	}
	if (prevNum_ < 0)
	{
		prevNum_ = CARD_NUM_MAX - 1;
	}
}
