#include "MovingBgObj.h"
#include "Utils.h"

MovingBgObj::MovingBgObj(
	sf::Texture& tex,
	sf::Vector2f spriteDir,
	const std::string& n,
	const sf::Vector2f p)
	: SpriteGo(tex, spriteDir, n, p), accumTime (0.f), widthY(0.f), heightY(0.f)
{
}

MovingBgObj::~MovingBgObj()
{
}

void MovingBgObj::Init()
{
	SpriteGo::Init();

	accumTime = 0.f;

	speed = Utils::RandomRange(speedRange.x, speedRange.y); // 스피드 랜덤화
	sf::Vector2f randomPos(
		Utils::RandomRange(posXRange.x, posXRange.y), // x좌표 랜덤화
		Utils::RandomRange(posYRange.x, posYRange.y)); // y좌표 랜덤화

	int rnd = Utils::RandomRange(0, 2); // 0 : 왼쪽->오른쪽 / 1 : 오른쪽->왼쪽
	if (rnd == 0)
	{
		originalPos = leftPos + randomPos; // 왼쪽 시작점(경계점) + 랜덤값
		SetPosition(originalPos);
		direction = sf::Vector2f(1.f, 0.f); // 객체가 오른쪽으로 이동
		SetFlipX(spriteDir.x > 0);
	}
	else
	{
		originalPos = rightPos + randomPos;
		SetPosition(originalPos);
		direction = sf::Vector2f(-1.f, 0.f); // 객체가 왼쪽으로 이동
		SetFlipX(spriteDir.x < 0);
	}
}

void MovingBgObj::Release()
{
	SpriteGo::Release();
}

void MovingBgObj::Update(float dt)
{
	SpriteGo::Update(dt);

	accumTime += dt; // 포물선을 그리기 위한 시간 누적 변수

	sf::Vector2f pos = GetPosition();
	pos += direction * speed * dt; // 속도 * 이전 프레임 기준 경과 시간 => 프레임 단위 이동 거리 누적

	pos.y = originalPos.y + sin(accumTime * widthY)* heightY;
	// accumTime 존재 이유 : 시간에 따라 변동되는 값을 통해 sin 값을 주기적으로 변동시키기 위함(widthY는 고정값)
	// widthY의 의미 : 웨이브 가로폭을 조절. sin 안에 꼭 각도를 계산해서 넣어야 한다는 강박 갖지 말기!!!
	// heightY의 의미 : 웨이브 세로폭을 조절

	SetPosition(pos);

	if (pos.x < leftPos.x || pos.x > rightPos.x)
	{
		Init();
	}
}

void MovingBgObj::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void MovingBgObj::SetSpeedRange(sf::Vector2f sRange)
{
	speedRange = sRange;
}

void MovingBgObj::SetLRPos(sf::Vector2f left, sf::Vector2f right)
{
	leftPos = left;
	rightPos = right;
}

void MovingBgObj::SetPosXRange(float min, float max)
{
	posXRange.x = min;
	posXRange.y = max;
}

void MovingBgObj::SetPosYRange(float min, float max)
{
	posYRange.x = min;
	posYRange.y = max;
}

void MovingBgObj::SetMoveY(float w, float h)
{
	widthY = w;
	heightY = h;
}

