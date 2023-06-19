#include "SpriteGo.h"

SpriteGo::SpriteGo(sf::Texture& tex, sf::Vector2f spriteDir, const std::string& n, const sf::Vector2f p)
	: GameObject(n, p)
{
	sprite.setPosition(p); // sfml::Transformable::setPosition 함수 사용 : 객체의 월드 좌표 세팅
	SetTexture(tex, spriteDir);
}

SpriteGo::~SpriteGo()
{
}

void SpriteGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	sprite.setPosition(position);
}

void SpriteGo::SetPosition(const sf::Vector2f& p)
{
	position = p;
	sprite.setPosition(position);
}

void SpriteGo::SetOrigin(Origins origin)
{
	Utils::SetOrigin(sprite, origin);
}

void SpriteGo::SetOrigin(float x, float y)
{
	sprite.setOrigin(x, y);
}

sf::Vector2f SpriteGo::GetSize() const
{
	sf::FloatRect rect = sprite.getLocalBounds();
	return sf::Vector2f(rect.width, rect.height);
}

void SpriteGo::SetTexture(sf::Texture& tex, sf::Vector2f spriteDir)
{
	sprite.setTexture(tex); // Sprite::setTexture 함수 사용 : 이미지 소스를 담고 있는 객체를 해당 객체에 할당
	this->spriteDir = spriteDir;
}

void SpriteGo::Init()
{
}

void SpriteGo::Release()
{
}

void SpriteGo::Update(float dt)
{
}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void SpriteGo::SetFlipX(bool flip)
{
	sf::Vector2f scale = sprite.getScale(); // Sprite::getScale 함수 사용 : Vector2f형으로 기본 (1.f, 1.f) 값 반환
	scale.x = flip ? -abs(scale.x) : abs(scale.x);
	if (spriteDir.x < 0.f)
	{
		scale.x *= -1.f;
	}
	sprite.setScale(scale); // Sprite::setScale 함수 사용 : 바뀐 스케일 값으로 재 세팅
}

void SpriteGo::SetFlipY(bool flip)
{
	sf::Vector2f scale = sprite.getScale();
	scale.y = flip ? -abs(scale.y) : abs(scale.y);
	if (spriteDir.y > 0.f)
	{
		scale.y *= -1.f;
	}
	sprite.setScale(scale);
}