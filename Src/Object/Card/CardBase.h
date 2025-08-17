#pragma once
class CardBase
{
public:
	enum class CARD_TYPE
	{
		ATTACK
		,MAGIC
		,ITEM
	};
	//�R���X�g���N�^
	CardBase(const int _pow);
	//�f�X�g���N�^
	virtual~CardBase(void);

	virtual void Execute(void);

	//�J�[�h�̈З͂̎擾
	inline const int GetPow(void)const { return pow_; }

protected:
	int pow_;
	CARD_TYPE type_;
private:
};

