#pragma once
#include<vector>
#include<memory>
class CardBase;
class CardDeck
{
public:
	//�J�[�h�ő喇��
	static constexpr int CARD_NUM_MAX = 20;
	static constexpr int CARD_POWS[20] = {0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9};
	//static constexpr int CARD_POWS[20] = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9};
	CardDeck(void);
	~CardDeck(void);

	//������
	void Init(void);
	//�J�[�h�g�p
	void CardUse(void);
	//�J�[�h�`���[�W
	void CardCharge(void);
	//�J�[�h���̂ĎD��
	void DisCard(void);
	//�J�[�h�I��
	void CardMoveLeft(void);
	void CardMoveRight(void);
	void Update(void);
	//�`��
	void Draw(void);
	void Release(void);

	/// <summary>
	/// �R�D�ɃJ�[�h�ǉ�
	/// </summary>
	/// <param name="_pow">�ǉ��������J�[�h�̋���</param>
	void AddDrawPile(const int _pow);
private:
	//�����o�֐�
	void CardMoveLimit(void);
	//�D�֘A
	//�R�D
	//std::vector<std::unique_ptr<CardBase>>drawPile_;
	std::vector<std::unique_ptr<CardBase>>drawPile_;
	//���g���Ă���J�[�h
	std::vector<std::unique_ptr<CardBase>>hand_;
	//std::vector<CardBase&>hand_;
	//�`���[�W���J�[�h
	std::vector<std::unique_ptr<CardBase>>chargeCard_;
	//�̂ĎD
	std::vector<std::unique_ptr<CardBase>>disCard_;

	//���ݑI�𒆂̃J�[�h
	int currentNum_;
	//���̃J�[�h�ԍ�
	int nextNum_;
	//�ЂƂO
	int prevNum_;
};

