#include "CloudGen.h"
#include <random>

// 주어진 범위에서 랜덤한 정수를 반환하는 함수.
int GetRandom(int start, int end)
{
    std::random_device rd; // 랜덤 넘버 생성을 위한 시드.
    std::mt19937 gen(rd()); // Mersenne Twister 랜덤 넘버 생성기.
    std::uniform_int_distribution<int> dis(start, end); // [start, end] 범위의 분포.
    return dis(gen); // 랜덤 넘버 생성 및 반환.
}

// CloudGen 클래스의 생성자.
CloudGen::CloudGen(int count, const char* tex_path, int w, int h)
    : m_flags(count, false) // 각 구름에 대한 플래그를 false로 초기화.
    , m_texture() // 구름의 텍스처.
    , m_objects() // 구름의 스프라이트 객체.
    , m_speeds(count) // 각 구름의 속도.
    , m_winWidth(w) // 창의 너비.
    , m_winHeight(h) // 창의 높이.
{
    m_texture.loadFromFile(tex_path); // 파일에서 텍스처를 로드.

    // 모든 구름 스프라이트 초기화.
    for (int i = 0; i < count; ++i)
        m_objects.push_back(sf::Sprite(m_texture)); // 각 구름에 대한 스프라이트 생성.

    // 첫 세 개의 구름 위치 및 스케일 설정 (왼쪽에서 이동).
    for (int i = 0; i < 3; ++i)
    {
        m_objects[i].setPosition(-300.0f, i * 150.0f); // 화면 밖에 위치 설정.
        m_objects[i].setScale(1.0f, 0.5f + static_cast<float>(GetRandom(0, 100) / 200.0f)); // 랜덤한 수직 스케일.
    }

    // 나머지 구름 위치 및 스케일 설정 (오른쪽에서 이동).
    for (int i = 3; i < m_objects.size(); ++i)
    {
        m_objects[i].setPosition(m_winWidth + 300, (i - 3) * 150.0f); // 화면 밖에 위치 설정.
        m_objects[i].setScale(-1.0f, 0.5f + static_cast<float>(GetRandom(0, 100) / 200.0f)); // 랜덤한 수직 스케일과 수평 반전.
    }
}

// 활성 구름이 3개 미만일 때 구름을 생성하는 함수.
void CloudGen::Gen()
{
    while (this->flagCount() < 3) // 활성 구름이 3개 미만일 때.
    {
        int i = GetRandom(0, 5); // 랜덤하게 구름 인덱스 선택.
        if (m_flags[i] == false) // 해당 구름이 비활성 상태라면.
        {
            m_flags[i] = true; // 구름을 활성화.
            m_speeds[i] = GetRandom(50, 150); // 구름의 속도 랜덤 설정.
        }
    }
}

// 구름을 속도에 따라 이동시키는 함수.
void CloudGen::Move(float dt)
{
    int size = m_objects.size(); // 구름의 개수 가져오기.
    for (int i = 0; i < size; ++i)
    {
        // 구름이 리셋되지 않았다면 이동.
        if (this->isEnd(i) == false)
        {
            // 왼쪽으로 이동하는 구름.
            if (i < 3 && m_flags[i])
            {
                sf::Vector2f cloudPos = m_objects[i].getPosition();
                cloudPos.x += m_speeds[i] * dt; // 오른쪽으로 이동.
                m_objects[i].setPosition(cloudPos); // 위치 업데이트.
            }
            // 오른쪽으로 이동하는 구름.
            else if (m_flags[i])
            {
                sf::Vector2f cloudPos = m_objects[i].getPosition();
                cloudPos.x -= m_speeds[i] * dt; // 왼쪽으로 이동.
                m_objects[i].setPosition(cloudPos); // 위치 업데이트.
            }
        }
    }
}

// 구름을 생성하고 이동시키는 업데이트 함수.
void CloudGen::Update(float dt)
{
    Gen(); // 필요 시 구름 생성.
    Move(dt); // 구름 이동.
}

// 구름 객체의 개수를 반환하는 함수.
int CloudGen::size()
{
    return m_objects.size(); // 구름 객체의 개수 반환.
}

// 활성 구름의 개수가 지정한 수와 일치하는지 확인하는 함수.
bool CloudGen::hasCount(int count)
{
    int size = m_flags.size(); // 플래그 개수 가져오기.
    int nc = 0; // 활성 구름 개수.
    for (int i = 0; i < size; ++i)
    {
        if (m_flags[i]) // 구름이 활성 상태라면.
            nc++; // 활성 개수 증가.
    }
    return (count == nc); // 활성 개수가 지정한 수와 일치하는지 반환.
}

// 구름이 화면 밖으로 나갔을 때 속성을 리셋하는 함수.
void CloudGen::reset(int i)
{
    if (i < 3) // 왼쪽으로 이동하는 구름.
    {
        m_objects[i].setPosition(-300.0f, i * 150.0f); // 위치를 화면 밖으로 리셋.
        m_objects[i].setScale(1.0f, 0.5f + static_cast<float>(GetRandom(0, 100) / 200.0f)); // 랜덤한 수직 스케일.
    }
    else // 오른쪽으로 이동하는 구름.
    {
        m_objects[i].setPosition(m_winWidth + 300, (i - 3) * 150.0f); // 위치를 화면 밖으로 리셋.
        m_objects[i].setScale(-1.0f, 0.5f + static_cast<float>(GetRandom(0, 100) / 200.0f)); // 랜덤한 수직 스케일과 수평 반전.
    }
    m_objects[i].setOrigin(0.0f, 0.0f); // 스케일을 위한 원점 설정.
    m_flags[i] = false; // 구름을 비활성화.
}

// 구름이 화면 밖으로 나갔는지 확인하고 리셋하는 함수.
bool CloudGen::isEnd(int i)
{
    bool result = false; // 결과 초기화.
    const auto& pos = m_objects[i].getPosition(); // 구름의 위치 가져오기.

    // 왼쪽으로 이동하는 구름.
    if (i < 3 && m_flags[i])
    {
        if ((int)pos.x > (int)(m_winWidth + 350)) // 오른쪽으로 나갔는지 확인.
        {
            reset(i); // 구름 리셋.
            result = true; // 끝났다고 표시.
        }
    }
    // 오른쪽으로 이동하는 구름.
    else if (m_flags[i])
    {
        if ((int)(pos.x) < -450) // 왼쪽으로 나갔는지 확인.
        {
            reset(i); // 구름 리셋.
            result = true; // 끝났다고 표시.
        }
    }
    return result; // 구름이 끝났는지 반환.
}

// 활성 구름의 개수를 세는 함수.
int CloudGen::flagCount()
{
    int size = m_flags.size(); // 플래그 개수 가져오기.
    int nc = 0; // 활성 구름 개수.
    for (int i = 0; i < size; ++i)
    {
        if (m_flags[i]) // 구름이 활성 상태라면.
            nc++; // 활성 개수 증가.
    }
    return (nc); // 개수 반환.
}

// 구름 스프라이트에 접근하기 위한 오버로딩된 연산자.
sf::Sprite& CloudGen::operator[](int i)
{
    return m_objects[i]; // 인덱스 i에 해당하는 스프라이트 반환.
}

// 상수 버전의 오버로딩된 연산자.
const sf::Sprite& CloudGen::operator[](int i) const
{
    return m_objects[i]; // 인덱스 i에 해당하는 스프라이트 반환.
}
