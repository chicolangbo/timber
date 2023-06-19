#pragma once
#include "SpriteGo.h"

// <MovingBgObj is a SpriteGo>
// 역할 : 움직이는 배경 오브젝트 총괄(구름, 벌)
// 1. 배경 오브젝트 리스폰 위치&방향, 스피드, 포물선 움직임 랜덤 세팅
// 2. 드로우

class MovingBgObj : public SpriteGo
{
protected:
	float speed;
	sf::Vector2f speedRange;
	sf::Vector2f leftPos; // 왼쪽 시작점(경계점)
	sf::Vector2f rightPos; // 오른쪽 시작점(경계점)
	sf::Vector2f posXRange; // 시작점 + 랜덤값 => 랜덤값.x
	sf::Vector2f posYRange; // 시작점 + 랜덤값 => 랜덤값.y
	sf::Vector2f direction; // 이미지 객체의 방향(이동 방향 X)

	float widthY; // 웨이브 가로폭
	float heightY; // 웨이브 세로폭
	float accumTime; // dt 누적 시간

	sf::Vector2f originalPos; // 시작 화면에서의 객체 위치

public:
	MovingBgObj(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });

	~MovingBgObj() override; // MovingBgObj 소멸!

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

