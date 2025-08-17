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
	//コンストラクタ
	CardBase(const int _pow);
	//デストラクタ
	virtual~CardBase(void);

	virtual void Execute(void);

	//カードの威力の取得
	inline const int GetPow(void)const { return pow_; }

protected:
	int pow_;
	CARD_TYPE type_;
private:
};

