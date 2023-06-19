#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Defines.h"

// 1. 객체의 로컬 기준점 세팅
// 2. 난수 생성 함수 세팅
class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;

public:
	static int RandomRange(int min, int maxExclude); // static 함수 : 객체 생성 없이 클래스 외부에서 사용 가능
	static float RandomRange(float min, float max); // static 함수 : 클래스 내부의 static 멤버에만 접근 가능

	static void SetOrigin(sf::Sprite& sprite, Origins origin);
	static void SetOrigin(sf::Text& text, Origins origin);
	static void SetOrigin(sf::Shape& shape, Origins origin);

	static void SetOrigin(sf::Transformable& obj, Origins origin, const sf::FloatRect& rect);
};

