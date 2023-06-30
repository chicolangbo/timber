#include "Tree.h"
#include "Utils.h"
#include "InputMgr.h"

Tree::Tree(sf::Texture& tex, sf::Vector2f spriteDir, const std::string& n, const sf::Vector2f p)
	: SpriteGo(tex, spriteDir, n, p), countOfBranches(6), branches(countOfBranches), branchPositions(countOfBranches), currentBranch(0)
{
	texBranch.loadFromFile("graphics/branch.png");
	texLog.loadFromFile("graphics/log.png");

	for (auto& branch : branches)
	{
		branch = new Branch(texBranch, { 1.f, 1.f}, "Branch");
		branch->SetTree(this);
	}

	for (int i = 0; i < 100; ++i)
	{
		EffectGo* newGo = new EffectGo(texLog);
		newGo->SetActive(false);
		logPool.push_back(newGo);
	}
}

Tree::~Tree()
{

}

void Tree::Init()
{
	SpriteGo::Init();

	currentBranch = 0;
	branchSide = Sides::None;

	float x = GetPosition().x; // ���� ���� ��ǥ.x
	float y = 800.f; // ���� �Ʒ� ���������� ���� ��ǥ.y
	float offset = branches[0]->GetSize().y + 100; // ���������� ���� ����

	for (int i = 0; i < branchPositions.size(); ++i) // ���������� ���� ���� �ݿ��� ���� ��ǥ ���� �迭 ����
	{
		branchPositions[i].x = x;
		branchPositions[i].y = y;
		y -= offset;
	}

	for (int i = 0; i < branchPositions.size(); ++i) // �������� ���� ��ǥ ����
	{
		branches[i]->Init();
		branches[i]->SetPosition(branchPositions[i]);
		Sides side = (Sides)Utils::RandomRange(0, 1); // �¿� ���� ��ġ
		branches[i]->SetSide(side);
		if (i == 0)
		{
			branches[i]->SetSide(Sides::Left);
		}
	}
}

void Tree::Release()
{
	SpriteGo::Release();

	for (auto& branch : branches)
	{
		delete branch;
		branch = nullptr;
	}
	branches.clear();

	for (auto& effect : logPool)
	{
		delete effect;
		effect = nullptr;
	}
	logPool.clear();

	for (auto& effect : logEffects)
	{
		delete effect;
		effect = nullptr;
	}
	logEffects.clear();
}

void Tree::Update(float dt)
{
	SpriteGo::Update(dt);

	// TEST CODE
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		UpdateBranches();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		sf::Vector2f pos = GetPosition();
		pos.y = GetSize().y;
		ShowEffectLog(Sides::Left, pos);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		sf::Vector2f pos = GetPosition();
		pos.y = GetSize().y;
		ShowEffectLog(Sides::Right, pos);
	}

	// USING CODE
	auto it = logEffects.begin();
	while (it != logEffects.end()) // ������� ������
	{
		if ((*it)->GetActive())
		{
			(*it)->Update(dt);
			++it;
		}
		else
		{
			logPool.push_back(*it);
			it = logEffects.erase(it);
		}
	}
}

void Tree::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	for (auto branch : branches)
	{
		branch->Draw(window);
	}
	for (auto effect : logEffects)
	{
		effect->Draw(window);
	}
}

void Tree::UpdateBranches()
{
	currentBranch = (currentBranch + 1) % branches.size();
	// 1 -> 2 -> 3 -> 4 -> 5 -> 0 ���� ��ȸ
	for (int i = 0; i < branches.size(); ++i)
	{
		int index = (currentBranch + i) % branches.size(); // 1,2,3,4,5,0
		branches[index]->SetPosition(branchPositions[i]); // 1->0, 2->1, 3->2, ... 0->5 : ��ġ ������ �������� ��ȸ
		if (i == branches.size() - 1)
		{
			Sides side = (Sides)Utils::RandomRange(0, 1);
			branches[index]->SetSide(side);
		}
		if (i == 0)
		{
			branchSide = branches[index]->GetSide();
		}
	}
}

void Tree::ShowEffectLog(Sides side, sf::Vector2f position)
{
	if (logPool.empty())
	{
		std::cout << "Log Pool Empty" << std::endl;
		return;
	}

	EffectGo* log = logPool.front();
	logPool.pop_front();
	logEffects.push_back(log); // logEffects : Ȱ��ȭ / logPool : ��Ȱ��ȭ

	log->SetActive(true);
	log->Init();
	log->SetPosition(position); // ������ �߾� �Ʒ�
	log->Fire(sf::Vector2f(side == Sides::Left? 1000.f : -1000.f, -1000.f));
}

Sides Tree::GetBranchSide()
{
	return branchSide;
}

