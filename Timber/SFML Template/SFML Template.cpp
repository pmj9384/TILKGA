#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>

enum class Sides
{
	Left,
	Right,
	None,
};

int main()
{
	srand(time(NULL));

	sf::VideoMode vm(1920, 1080);
	sf::RenderWindow window(vm, "Timber!!!", sf::Style::Default);

	sf::Vector2u windowSize = window.getSize();
	sf::Vector2f windowCenterPos = (sf::Vector2f)(windowSize / 2u);

	sf::Texture texBackgrond;
	texBackgrond.loadFromFile("graphics/background.png");
	sf::Texture texCloud;
	texCloud.loadFromFile("graphics/cloud.png");
	sf::Texture texBee;
	texBee.loadFromFile("graphics/bee.png");
	sf::Texture texTree;
	texTree.loadFromFile("graphics/tree.png");
	sf::Texture texBranch;
	texBranch.loadFromFile("graphics/branch.png");
	sf::Texture texPlayer;
	texPlayer.loadFromFile("graphics/player.png");
	sf::Texture texRip;
	texRip.loadFromFile("graphics/rip.png");

	const int numOfBranches = 6;
	Sides sideBranches[numOfBranches];
	sf::Sprite spriteBranches[numOfBranches];
	sf::Vector2f originBranch;
	originBranch.x = -(texTree.getSize().x * 0.5f);
	originBranch.y = texBranch.getSize().y * 0.5f;
	sf::Vector2f posBranch(windowCenterPos.x, 780.f);

	for (int i = 0; i < numOfBranches; ++i)
	{
		sideBranches[i] = (i == 0) ? Sides::None : (Sides)(rand() % 3); // 첫 번째 가지는 None으로 설정
		spriteBranches[i].setTexture(texBranch);
		spriteBranches[i].setOrigin(originBranch);
		spriteBranches[i].setPosition(posBranch);
		posBranch.y -= 150.f;
		spriteBranches[i].setScale(sideBranches[i] == Sides::Right ? 1.f : -1.f, 1.f);
	}


	sf::Vector2f playerPosArray[2];
	playerPosArray[0].x = windowCenterPos.x - texTree.getSize().x;
	playerPosArray[0].y = texTree.getSize().y - 50;
	playerPosArray[1].x = windowCenterPos.x + texTree.getSize().x;
	playerPosArray[1].y = texTree.getSize().y - 50;

	sf::Vector2f playerScaleArray[2];
	playerScaleArray[0] = { -1.f, 1.f };
	playerScaleArray[1] = { 1.f, 1.f };

	Sides sidePlayer = Sides::Right;
	sf::Sprite spritePlayer;
	spritePlayer.setTexture(texPlayer);
	spritePlayer.setOrigin({ texPlayer.getSize().x * 0.5f, (float)texPlayer.getSize().y });
	spritePlayer.setScale(playerScaleArray[(int)sidePlayer]);
	spritePlayer.setPosition(playerPosArray[(int)sidePlayer]);

	sf::Sprite spriteBackground;
	spriteBackground.setTexture(texBackgrond);
	sf::Sprite spriteTree;
	spriteTree.setTexture(texTree);
	spriteTree.setOrigin(texTree.getSize().x * 0.5f, 0.f);
	spriteTree.setPosition(windowCenterPos.x, 0.f);

	float leftX = 0 - 200;
	float rightX = 1920 + 200;
	sf::Vector2f speedCloudRange(100.f, 200.f);
	sf::Vector2f scaleCloudRange(0.5f, 2.f);
	sf::Vector2f yCloudRange(0.f, 400.f);

	sf::Sprite spriteClouds[3];
	sf::Vector2f speedClouds[3];

	for (int i = 0; i < 3; ++i)
	{
		float dirX = (rand() % 2 == 0) ? -1.f : 1.f;
		spriteClouds[i].setTexture(texCloud);
		speedClouds[i].x = dirX;
		speedClouds[i].y = 0.f;
		speedClouds[i] *= (rand() % (int)(speedCloudRange.y - speedCloudRange.x)) + speedCloudRange.x;
		sf::Vector2f scale(-dirX, 1.f);
		scale *= (rand() / (float)RAND_MAX) * (scaleCloudRange.y - scaleCloudRange.x) + scaleCloudRange.x;
		spriteClouds[i].setScale(scale);
		spriteClouds[i].setPosition(dirX > 0 ? leftX : rightX,
			(rand() % (int)(yCloudRange.y - yCloudRange.x)) + yCloudRange.x);
	}

	sf::Vector2f speedBeeRange(100.f, 200.f);
	sf::Sprite spriteBee;
	spriteBee.setTexture(texBee);
	sf::Vector2f initBeePosition(0.f, 800.f);
	spriteBee.setPosition(initBeePosition);
	spriteBee.setScale(-1.f, 1.f);
	sf::Vector2f speedBee(100.f, 0.f);  // v = d / t

	sf::Sprite spriteRip;
	spriteRip.setTexture(texRip);
	spriteRip.setOrigin({ texRip.getSize().x * 0.5f, (float)texRip.getSize().y });
	spriteRip.setPosition(playerPosArray[(int)Sides::Right]); // 초기 위치 설정

	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score = 0");
	scoreText.setCharacterSize(100);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10.f, 10.f);

	sf::Text messageText;
	messageText.setFont(font);
	messageText.setString("Press Space to Start!");
	messageText.setCharacterSize(100);
	messageText.setFillColor(sf::Color::White);
	sf::FloatRect bounds = messageText.getLocalBounds();
	messageText.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
	messageText.setPosition(windowCenterPos);

	sf::Text gameoverText;
	gameoverText.setFont(font);
	gameoverText.setString("Game Over...");
	gameoverText.setCharacterSize(100);
	gameoverText.setFillColor(sf::Color::White);
	sf::FloatRect bounds2 = gameoverText.getLocalBounds();
	gameoverText.setOrigin(bounds2.width * 0.5f, bounds2.height * 0.5f);
	gameoverText.setPosition(windowCenterPos);

	float timeBarWidth = 400;
	float timeBarHeight = 80;

	sf::RectangleShape timeBar;
	timeBar.setSize({ timeBarWidth, timeBarHeight });
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setPosition({ windowCenterPos.x - (timeBarWidth * 0.5f), 950.f });

	int score = 0;

	float timerBarDuration = 3.f;
	float timerBarSpeed = timeBarWidth / timerBarDuration;
	float timerAddTime = 0.5f;

	sf::Clock clock;
	float accumTime = 0.f;
	float timeScale = 1.f;

	bool isPause = true;

	bool isLeftKey = false;
	bool isRightKey = false;

	bool isLeftKeyDown = false;
	bool isRightKeyDown = false;

	// 추가된 변수
	bool isGameOver = false;

	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		float deltaTime = dt.asSeconds();
		deltaTime *= timeScale;
		accumTime += deltaTime;

		isLeftKeyDown = false;
		isRightKeyDown = false;

		sf::Event ev;
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				switch (ev.key.code)
				{
				case sf::Keyboard::Left:
					isLeftKey = false;
					break;
				case sf::Keyboard::Right:
					isRightKey = false;
				}
				break;
			case sf::Event::KeyPressed:
				switch (ev.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Return:
					score = 0;
					scoreText.setString("SCORE: " + std::to_string(score));  // 스코어 텍스트 업데이트
					isPause = true;
					isGameOver = false;

					// 가지 초기화
					posBranch.y = 650.f;
					for (int i = 0; i < numOfBranches; ++i) {
						sideBranches[i] = (i == 0) ? Sides::None : (Sides)(rand() % 3);
						spriteBranches[i].setScale(sideBranches[i] == Sides::Right ? 1.f : -1.f, 1.f);
					}

					// 플레이어 초기화
					spritePlayer.setScale(playerScaleArray[(int)Sides::Right]);
					spritePlayer.setPosition(playerPosArray[(int)Sides::Right]);
					spritePlayer.setColor(sf::Color::White);
					// 메시지 초기화
					messageText.setString("Press Space to Start!!");
					{
						sf::FloatRect bounds = messageText.getLocalBounds();
						messageText.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
						messageText.setPosition(windowCenterPos); // 중앙 위치 설정
					}
					// 타이머 초기화
					timeBar.setSize({ timeBarWidth, timeBarHeight });
					accumTime = 0.f;  // 시간 누적 초기화
					timerBarDuration = 3.f;  // 초기화할 타이머 지속시간
					timerBarSpeed = timeBarWidth / timerBarDuration;  // 타이머 속도 초기화
					
					break;
			
			
				case sf::Keyboard::Space:
					isPause = !isPause;
					if (isPause)
					{
						messageText.setString("Press Space to Start!"); // 메시지 설정
						
						sf::FloatRect bounds = messageText.getLocalBounds();
						messageText.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
						messageText.setPosition(windowCenterPos); // 중앙 위치 설정
					}
					else
					{
						messageText.setString("");
					}
				
					break;
					
				case sf::Keyboard::Num1:

					break;
				case sf::Keyboard::Num2:
				
					break;
				case sf::Keyboard::Left:
				
					if (!isLeftKey)
					{
						score += 10;
						isLeftKeyDown = true;
					}
					isLeftKey = true;
					break;
				case sf::Keyboard::Right:
					
					if (!isRightKey)
					{
						score += 10;
						isRightKeyDown = true;
					}
					isRightKey = true;
					break;
				}
				break;
			default:
				break;
			}
		}

		if (!isPause && !isGameOver) // 게임이 일시정지 상태가 아니고 게임 오버가 아닐 때만 실행
		{
			if (isLeftKeyDown || isRightKeyDown)
			{
				for (int i = 1; i < numOfBranches; ++i)
				{
					sideBranches[i - 1] = sideBranches[i];
				}
				sideBranches[numOfBranches - 1] = (Sides)(rand() % 3);
				for (int i = 0; i < numOfBranches; ++i)
				{
					spriteBranches[i].setScale(
						sideBranches[i] == Sides::Right ? 1.f : -1.f, 1.f);
				}

				sidePlayer = isLeftKeyDown ? Sides::Left : Sides::Right;
				spritePlayer.setScale(playerScaleArray[(int)sidePlayer]);
				spritePlayer.setPosition(playerPosArray[(int)sidePlayer]);

				if (sidePlayer == sideBranches[0])
				{
					isGameOver = true; // 게임 오버 상태 설정
					messageText.setString("Game Over!"); // 게임 오버 메시지 설정
					sf::FloatRect bounds = messageText.getLocalBounds();  // 게임오버 메세지 중앙에 나오게하기
					messageText.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f); // 게임오버 메세지 중앙에 나오게하기
					messageText.setPosition(windowCenterPos); // 게임오버 메세지 중앙에 나오게하기

					spritePlayer.setColor(sf::Color::Transparent); // 플레이어 스프라이트를 투명하게 설정
					spriteRip.setPosition(playerPosArray[(int)sidePlayer]); // RIP 위치 설정
				}
				else
				{
					sf::Vector2f timerBarSize = timeBar.getSize();
					timerBarSize.x += timerBarSpeed * timerAddTime;
					if (timerBarSize.x > timeBarWidth)
					{
						timerBarSize.x = timeBarWidth;
					}
					timeBar.setSize(timerBarSize);
				}
			}

			// 비와 구름의 움직임을 업데이트
			sf::Vector2f beePos = spriteBee.getPosition();
			beePos.x += speedBee.x * deltaTime;
			beePos.y = initBeePosition.y + 10.f * sin(accumTime * 1.f);
			spriteBee.setPosition(beePos);

			for (int i = 0; i < 3; ++i)
			{
				sf::Vector2f pos = spriteClouds[i].getPosition();
				pos += speedClouds[i] * deltaTime;
				spriteClouds[i].setPosition(pos);

				// 경계 검사 + 초기화
				if ((speedClouds[i].x > 0) ? (rightX < pos.x) : (leftX > pos.x))
				{
					float dirX = (rand() % 2 == 0) ? -1.f : 1.f;
					speedClouds[i].x = dirX;
					speedClouds[i].y = 0.f;
					speedClouds[i] *= (rand() % (int)(speedCloudRange.y - speedCloudRange.x)) + speedCloudRange.x;
					sf::Vector2f scale(-dirX, 1.f);
					scale *= (rand() / (float)RAND_MAX) * (scaleCloudRange.y - scaleCloudRange.x) + scaleCloudRange.x;
					spriteClouds[i].setScale(scale);
					spriteClouds[i].setPosition(dirX > 0 ? leftX : rightX,
						(rand() % (int)(yCloudRange.y - yCloudRange.x)) + yCloudRange.x);
				}
			}

			scoreText.setString("SCORE: " + std::to_string(score));

			sf::Vector2f size = timeBar.getSize();
			size.x -= timerBarSpeed * deltaTime;
			if (size.x <= 0.f) // 타임 오버 조건
			{
				size.x = 0.f;
				isGameOver = true; // 게임 오버 상태 설정
				messageText.setString("Time Over!"); // 타임 오버 메시지 설정
				// 메시지를 중앙에 위치시키기
				sf::FloatRect bounds = messageText.getLocalBounds();
				messageText.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
				messageText.setPosition(windowCenterPos);

				spritePlayer.setColor(sf::Color::Transparent); // 플레이어 스프라이트를 투명하게 설정
				spriteRip.setPosition(playerPosArray[(int)sidePlayer]); // RIP 위치 설정
			}
			timeBar.setSize(size);
		}
		window.clear();

		window.draw(spriteBackground);
		for (const sf::Sprite& cloud : spriteClouds)
		{
			window.draw(cloud);
		}
		window.draw(spriteTree);
		for (int i = 0; i < numOfBranches; ++i)
		{
			if (sideBranches[i] != Sides::None)
			{
				window.draw(spriteBranches[i]);
			}
		}


		if (isGameOver) {
			window.draw(spriteRip); // 게임 오버 시 RIP 스프라이트를 그리기
		}
		else {
			window.draw(spritePlayer); // 플레이어 스프라이트가 살아 있을 때만 그리기
		}

		window.draw(spriteBee);

		window.draw(scoreText);
		window.draw(messageText);
		window.draw(timeBar);
		window.display();
	}
	return 0;
}