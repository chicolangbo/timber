#pragma once
#include "GameObject.h"

// <SpriteGo is a GameObject>
// <SpriteGo has a Sprite>
// ���� : �̹��� ǥ�� Ŭ����
// 1. �ؽ�ó�� �̹��� ��ü�� �Ҵ� & �¿� �� ��� ���ϴ��� Ȯ��
// 2. �̹��� ��ü �ø�
// 3. �̹��� ��ü�� ������ ��ȯ(�ʺ�,����)

class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite; // Sprite : �̹��� �Ǵ� �ؽ�ó�� ǥ���ϱ� ���� Ŭ����
	sf::Vector2f spriteDir; // <- : -1 /  -> : 1

public:
	SpriteGo(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	virtual ~SpriteGo() override; // �Ҹ��ڰ� virtual�� ���� : �ܺο��� �ش� ��ü�� �Ҹ�� �� �ߺ����� �ʵ���

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

