#pragma once
#include "GameObject.h"

// <SpriteGo is a GameObject>
// <SpriteGo has a Sprite>
// 역할 : 이미지 표현 클래스
// 1. 텍스처를 이미지 객체에 할당 & 좌우 중 어디를 향하는지 확인
// 2. 이미지 객체 플립
// 3. 이미지 객체의 사이즈 반환(너비,높이)

class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite; // Sprite : 이미지 또는 텍스처를 표시하기 위한 클래스
	sf::Vector2f spriteDir; // <- : -1 /  -> : 1

public:
	SpriteGo(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	virtual ~SpriteGo() override; // 소멸자가 virtual인 이유 : 외부에서 해당 객체가 소멸될 때 중복되지 않도록

	virtual void SetPosition(float x, float y) override;
	virtual void SetPosition(const sf::Vector2f& p) override;

	virtual void SetOrigin(Origins origin) override;
	virtual void SetOrigin(float x, float y) override;

	sf::Vector2f GetSize() const;

	void SetTexture(sf::Texture& tex, sf::Vector2f spriteDir = sf::Vector2f(-1, -1));

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetFlipX(bool flip);
	void SetFlipY(bool flip);
};

