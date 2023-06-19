#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>

#include "Utils.h"
#include "MovingBgObj.h"
#include "InputMgr.h"
#include "Tree.h"
#include "Player.h"

int main()
{
    bool isPause = true;
    int score = 0;

    int screenWidth = 1920;
    int screenHeight = 1080;

    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    sf::Text textMessage;
    textMessage.setFont(font);
    textMessage.setString("PRESS ENTER TO START!");
    textMessage.setCharacterSize(75);
    textMessage.setFillColor(sf::Color::White);
    Utils::SetOrigin(textMessage, Origins::MC);
    textMessage.setPosition(screenWidth * 0.5f, screenHeight * 0.5f);

    sf::Text textScore;
    textScore.setFont(font);
    textScore.setString("SCORE: ");
    textScore.setCharacterSize(100);
    textScore.setFillColor(sf::Color::White);
    Utils::SetOrigin(textScore, Origins::TL);
    textScore.setPosition(20.f, 20.f);

    float uiTimerWidth = 400.f;
    float uiTimerHeight = 80.f;

    float duration = 6.f;
    float timer = duration;

    sf::RectangleShape uiTimer;
    uiTimer.setSize(sf::Vector2f(uiTimerWidth, uiTimerHeight));
    Utils::SetOrigin(uiTimer, Origins::BC);
    uiTimer.setPosition(screenWidth * 0.5f, screenHeight - 50.f);
    uiTimer.setFillColor(sf::Color::Red);

    sf::RectangleShape uiTimerBg;
    uiTimerBg.setSize(sf::Vector2f(400.f, 80.f));
    Utils::SetOrigin(uiTimerBg, Origins::BC);
    uiTimerBg.setPosition(screenWidth * 0.5f, screenHeight - 50.f);
    uiTimerBg.setFillColor(sf::Color::White);

    sf::Texture texBackground;
    texBackground.loadFromFile("graphics/background.png");
    sf::Texture texTree;
    texTree.loadFromFile("graphics/tree.png");
    sf::Texture texCloud;
    texCloud.loadFromFile("graphics/cloud.png");
    sf::Texture texBee;
    texBee.loadFromFile("graphics/bee.png");
    sf::Texture texPlayer;
    texPlayer.loadFromFile("graphics/player.png");
    sf::SoundBuffer soundBufferTimeOut;
    soundBufferTimeOut.loadFromFile("sound/out_of_time.wav");
    sf::Sound soundTimeOut;
    soundTimeOut.setBuffer(soundBufferTimeOut);

    std::vector<GameObject*> gameObjects; // GameObject*형 객체들로 이뤄진 동적 배열 생성
    gameObjects.push_back(new SpriteGo(texBackground, sf::Vector2f(1.f, 0.f), "BG", {0, 0}));

    for (int i = 0; i < 3; ++i)
    {
        MovingBgObj* newGo = new MovingBgObj(texCloud, sf::Vector2f(-1.f, -1.f), "Cloud");
        newGo->SetSpeedRange(sf::Vector2f(300.f, 600.f));
        newGo->SetLRPos(sf::Vector2f(-200.f, 1080.f / 2.f), // 왼쪽 시작점(경계점) 세팅
            sf::Vector2f(1920.f + 200.f, 1080.f / 2.f)); // 오른쪽 시작점(경계점) 세팅
        newGo->SetPosXRange(0, 0); // 화면에서 사라진 후 화면 중간에서 리스폰 되는 걸 방지
        newGo->SetPosYRange(-400, -100);
        gameObjects.push_back(newGo);
    }

    Tree* tree = new Tree(texTree, sf::Vector2f(1.f, 0.f), "Tree");
    tree->SetOrigin(Origins::TC);
    tree->SetPosition(screenWidth * 0.5f, 0.f);
    gameObjects.push_back(tree);

    Player* player = new Player(texPlayer, sf::Vector2f(-1.f, -1.f), "Player", sf::Vector2f(0.f, 900.f));
    player->SetTree(tree);
    gameObjects.push_back(player);

    MovingBgObj* newGo = new MovingBgObj(texBee, sf::Vector2f(-1.f, -1.f), "Bee");
    newGo->SetSpeedRange(sf::Vector2f(100.f, 200.f));
    newGo->SetLRPos(sf::Vector2f(-200.f, 1080.f / 2.f),
        sf::Vector2f(1920.f + 200.f, 1080.f / 2.f));
    newGo->SetPosXRange(0, 0);
    newGo->SetPosYRange(0, 300);
    newGo->SetMoveY(2.f, 50.f); // 웨이브 가로폭, 세로폭 세팅

    gameObjects.push_back(newGo);




    for (auto obj : gameObjects)
    {
        obj->Init();
    }

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Timber!", sf::Style::Default);

    sf::Clock clock;
    while (window.isOpen())
    {
        InputMgr::Clear();

        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            InputMgr::Update(event);

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        // 2. Update
        if (!isPause)
        {
            timer -= dt;

            if (timer < 0.f)
            {
                textMessage.setString("OUT OF TIME");
                Utils::SetOrigin(textMessage, Origins::MC);
                isPause = true;
                soundTimeOut.play();
            }
            else if (!player->GetAlive())
            {
                isPause = true;
                textMessage.setString("YOU DIE");
                Utils::SetOrigin(textMessage, Origins::MC);
            }
            else
            {

                float normTime = timer / duration;
                float timeSizeX = uiTimerWidth * normTime;
                if (player->GetPlusTime() != 0) // chop 실행 시
                {
                    timer += player->GetPlusTime();
                    if (timer > duration)
                    {
                        timer = duration;
                    }
                }
                uiTimer.setSize(sf::Vector2f(timeSizeX, uiTimerHeight));

                for (auto obj : gameObjects)
                {
                    if (obj->GetActive())
                    {
                        obj->Update(dt);
                    }
                }

                score = player->GetChopCount();
                std::stringstream ss;
                ss << "SCORE: " << score;
                textScore.setString(ss.str());
            }
        }
        else
        {
            if (InputMgr::GetKeyDown(sf::Keyboard::Return))
            {
                isPause = false;
                timer = duration;
                score = 0;
                for (auto obj : gameObjects)
                {
                    obj->Init();
                }
            }
        }

        window.clear();

        // 3. Draw
        for (auto obj : gameObjects)
        {
            if (obj->GetActive())
            {
                obj->Draw(window);
            }
        }

        window.draw(textScore);
        window.draw(uiTimerBg);
        window.draw(uiTimer);

        if (isPause)
        {
            window.draw(textMessage);
        }
        window.display();
    }

    for (auto obj : gameObjects)
    {
        obj->Release();
        delete obj;
    }

    return 0;
}