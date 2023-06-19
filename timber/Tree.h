#pragma once
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "SpriteGo.h"
#include "Branch.h"
#include "EffectGo.h"

// <Tree is a SpriteGo>
// <Tree has a Branch>
// 역할 : 
//

class Tree : public SpriteGo
{
protected:
	const int countOfBranches; // 나뭇가지 개수
	std::vector<Branch*> branches; // Branch* 객체 동적 배열
	std::vector<sf::Vector2f> branchPositions; // 나뭇가지 월드 좌표 동적 배열
	int currentBranch;
	sf::Texture texBranch;
	Sides branchSide;

	std::list<EffectGo*> logPool; // EffectGo* 통나무 객체 링크드 리스트
	std::list<EffectGo*> logEffects; // EffectGo* 통나무 효과 객체 링크드 리스트

	sf::Texture texLog;

public:
	Tree(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	~Tree() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void UpdateBranches();
	void ShowEffectLog(Sides side, sf::Vector2f position);

	Sides GetBranchSide();
};

