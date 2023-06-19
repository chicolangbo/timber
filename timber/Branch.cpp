#include "Branch.h"

Branch::Branch(sf::Texture& tex,
    sf::Vector2f spriteDir,
    const std::string& n,
    const sf::Vector2f p)
    : SpriteGo(tex, spriteDir, n, p), side(Sides::None), tree(nullptr)
{
}

Branch::~Branch()
{
}

void Branch::Init()
{
    sf::Vector2f treeSize = tree->GetSize();
    sf::Vector2f branchSize = GetSize(); // SpriteGo까지 올라가서 sprite 객체로서 사이즈 반환
    sprite.setOrigin(-treeSize.x * 0.5f, branchSize.y * 0.5f); // 나뭇가지 로컬 좌표 기준점 : (나무 가로 중간, 나뭇가지 세로 중간)

    //SetPosition(tree->GetPosition());

}

void Branch::SetTree(SpriteGo* tree)
{
    this->tree = tree;
}

void Branch::SetSide(Sides side)
{
    this->side = side;
    switch (this->side)
    {
    case Sides::Left:
        SetFlipX(true);
        break;
    case Sides::Right:
        SetFlipX(false);
        break;
    }
}

Sides Branch::GetSide() const
{
    return side;
}
