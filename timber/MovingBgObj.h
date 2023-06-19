#pragma once
#include "SpriteGo.h"

// <MovingBgObj is a SpriteGo>
// ���� : �����̴� ��� ������Ʈ �Ѱ�(����, ��)
// 1. ��� ������Ʈ ������ ��ġ&����, ���ǵ�, ������ ������ ���� ����
// 2. ��ο�

class MovingBgObj : public SpriteGo
{
protected:
	float speed;
	sf::Vector2f speedRange;
	sf::Vector2f leftPos; // ���� ������(�����)
	sf::Vector2f rightPos; // ������ ������(�����)
	sf::Vector2f posXRange; // ������ + ������ => ������.x
	sf::Vector2f posYRange; // ������ + ������ => ������.y
	sf::Vector2f direction; // �̹��� ��ü�� ����(�̵� ���� X)

	float widthY; // ���̺� ������
	float heightY; // ���̺� ������
	float accumTime; // dt ���� �ð�

	sf::Vector2f originalPos; // ���� ȭ�鿡���� ��ü ��ġ

public:
	MovingBgObj(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });

	~MovingBgObj() override; // MovingBgObj �Ҹ�!

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetSpeedRange(sf::Vector2f sRange);

	void SetLRPos(sf::Vector2f left, sf::Vector2f right);
	void SetPosXRange(float min, float max);
	void SetPosYRange(float min, float max);
	void SetMoveY(float w, float h);
};

