#include "Player.h"
#include "Tree.h"
#include "InputMgr.h"
#include "EffectGo.h"

Player::Player(sf::Texture& tex, sf::Vector2f spriteDir, const std::string& n, const sf::Vector2f p)
	: SpriteGo(tex, spriteDir, n, p), offsetX(100.f), isChopping(false), texPlayer(tex)
{
	texAxe.loadFromFile("graphics/axe.png");
	axe = new SpriteGo(texAxe);
	SetOrigin(Origins::BC);
	for (auto& position : playerPositions)
	{
		position = p;
	}

	texRip.loadFromFile("graphics/rip.png");

	soundBufferChop.loadFromFile("sound/chop.wav");
	soundBufferDeath.loadFromFile("sound/death.wav");
	// 필요한 사운드버퍼를 갈아끼울 수 있다? 근데 지금은 1:1로 매칭하겠다
	soundChop.setBuffer(soundBufferChop);
	soundDeath.setBuffer(soundBufferDeath);
}

Player::~Player()
{
}

void Player::SetTree(Tree* tree)
{
	this->tree = tree;
}

void Player::SetSide(Sides side)
{
	this->side = side;

	SetPosition(playerPositions[(int)this->side]); // 0 : 나무의 왼쪽 / 1 : 나무의 오른쪽
	SetFlipX(this->side == Sides::Right);

	axe->SetPosition(GetPosition());
	axe->SetFlipX(this->side == Sides::Right);
}

Sides Player::GetSide() const
{
	return side;
}

void Player::Chop(Sides side)
{
	plusTime += 1.f;
	chopCount++;
	SetSide(side);
	isChopping = true;

	// 통나무 날리는 연출
	tree->ShowEffectLog(side, sf::Vector2f(tree->GetPosition().x, tree->GetSize().y-50));
	tree->UpdateBranches();

	isCollide();
}

void Player::Die()
{
	chopCount--;
	isAlive = false;
	isChopping = false;

	SetTexture(texRip);
	SetOrigin(Origins::BC);
	SetFlipX(true);
}

void Player::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
}

void Player::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
}

void Player::Init()
{
	isAlive = true;
	SetTexture(texPlayer);
	SetOrigin(Origins::BC);

	isChopping = false;
	chopCount = 0;
	plusTime = 0;

	SpriteGo::Init();

	sf::Vector2f playerSize = GetSize();

	float treeHalfWidth = tree->GetSize().x * 0.5f;
	float playerHalfWidth = playerSize.x * 0.5f;
	float delta = treeHalfWidth + playerHalfWidth + offsetX;

	playerPositions[(int)Sides::Left].x = tree->GetPosition().x - delta;
	playerPositions[(int)Sides::Right].x = tree->GetPosition().x + delta;

	sf::Vector2f axeSize = axe->GetSize();
	axe->SetOrigin(axeSize.x + playerHalfWidth - 20.f, playerSize.y * 0.45f);

	axe->Init();
	axe->SetPosition(GetPosition());

	SetSide(Sides::Right);
}

void Player::Release()
{
	delete axe;
	axe = nullptr;

	SpriteGo::Release();
}

void Player::Update(float dt)
{
	//if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	//{
	//	Die();
	//}

	//if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
	//{
	//	Init();
	//}

	SpriteGo::Update(dt);
	plusTime = 0;

	if (!isChopping)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			Chop(Sides::Left);
			soundChop.play();
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			Chop(Sides::Right);
			soundChop.play();
		}
	}
	else
	{
		isCollide();
		if (GetSide() == Sides::Left &&
			InputMgr::GetKeyUp(sf::Keyboard::Left))
		{
			isChopping = false;
		}
		if (GetSide() == Sides::Right &&
			InputMgr::GetKeyUp(sf::Keyboard::Right))
		{
			isChopping = false;
		}
	}

	axe->Update(dt);
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

	if (isChopping)
	{
		axe->Draw(window);
	}
}

void Player::isCollide() // 충돌 체크 함수
{
	if (tree->GetBranchSide() == side)
	{
		Die();
		soundDeath.play();
	}
}

bool Player::GetAlive()
{
	return isAlive;
}

int Player::GetChopCount()
{
	return chopCount;
}

float Player::GetPlusTime()
{
	return plusTime;
}
