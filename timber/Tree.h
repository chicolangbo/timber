#pragma once
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "SpriteGo.h"
#include "Branch.h"
#include "EffectGo.h"

// <Tree is a SpriteGo>
// <Tree has a Branch>
// ���� : 
//

class Tree : public SpriteGo
{
protected:
	const int countOfBranches; // �������� ����
	std::vector<Branch*> branches; // Branch* ��ü ���� �迭
	std::vector<sf::Vector2f> branchPositions; // �������� ���� ��ǥ ���� �迭
	int currentBranch;
	sf::Texture texBranch;
	Sides branchSide;

	std::list<EffectGo*> logPool; // EffectGo* �볪�� ��ü ��ũ�� ����Ʈ
	std::list<EffectGo*> logEffects; // EffectGo* �볪�� ȿ�� ��ü ��ũ�� ����Ʈ

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

