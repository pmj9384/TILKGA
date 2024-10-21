#include "stdafx.h"
#include "Framework.h"
#include "SpriteGo.h"
void Framework::Init(int width, int height, const std::string& name)
{
	window.create(sf::VideoMode(width,height), name);
}

void Framework::Do()
{
    TEXTURE_MGR.Load("graphics/background.png");
    SpriteGo go("graphics/background.png");
    go.Init();
    go.Reset();

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        deltaTime = deltaTime = dt.asSeconds();
        deltaTime *= timeScale;
        realTime += realDeltaTime;
        time += deltaTime;


        // 이벤트 루프
        InputMgr::Clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            InputMgr::UpdateEvent(event);
        }

        // Update
        if (InputMgr::GetKey(sf::Keyboard::Num1))
        {
            std::cout << "Num 1 Pressed" << std::endl;
        }
        if (InputMgr::GetKeyUp(sf::Keyboard::Num1))
        {
            std::cout << "Num 1 Up" << std::endl;
        }
        if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
        {
            std::cout << "Num 1 Down" << std::endl;
        }

        if (InputMgr::GetMouse(sf::Mouse::Left))
        {
            std::cout << "Mouse Pressed" << std::endl;


        }
        if (InputMgr::GetMouseUp(sf::Mouse::Left))
        {
            std::cout << "Mouse Up" << std::endl;
        }
        if (InputMgr::GetMouseDown(sf::Mouse::Left))
        {
            std::cout << "Mouse Down" << std::endl;
        }



        // 업데이트
        go.Update(deltaTime);

        window.clear();
        // 드로우
        go.Draw(window);
        window.display();
    }

    go.Release();
}

void Framework::Release()
{
}
