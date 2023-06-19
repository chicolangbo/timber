#pragma once
#include "SpriteGo.h"
#include "Defines.h"

// <Branch is a SpriteGo>
// 역할 : 나뭇가지 객체
// 1. SpriteGo로 넘기기 : 텍스쳐, 방향, 이름 / 위치는 Tree에서 세팅
// 2. 나뭇가지 객체의 로컬 좌표 기준점 세팅

class Branch : public SpriteGo
{
protected:
	SpriteGo* tree;
	Sides side;

public:
	Branch(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(1, 1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });

	~Branch() override;

	virtual void Init();

	void SetTree(SpriteGo* tree);
	void SetSide(Sides side);
	Sides GetSide() const;
};

