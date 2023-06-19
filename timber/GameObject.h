#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Utils.h"

// <추상 클래스>
// 역할 : 게임 오브젝트 총괄
// 1. 게임 오브젝트 명명
// 2. 게임 오브젝트 활성화 관리 -> 업데이트, 드로우 실행 여부 결정
// 3. 게임 오브젝트의 월드 좌표 세팅 & 로컬 좌표 세팅 (가상 함수)

class GameObject
{
protected:
	std::string name;
	sf::Vector2f position;
	bool isActive;	// 활성화: Update(), Draw()

public:
	GameObject(const std::string& n = "", const sf::Vector2f p = { 0, 0 });
	virtual ~GameObject();

	bool GetActive() const; // 현재 Active 되어 있는지 상태 반환
	void SetActive(bool active); // isActive 값 세팅

	std::string GetName();
	virtual void SetName(const std::string& n);

	sf::Vector2f GetPosition(); // 현재 객체의 월드좌표 반환

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void SetOrigin(Origins origin) {}
	virtual void SetOrigin(float x, float y) {}

	virtual void Init() = 0;
	virtual void Release() = 0;

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
};

