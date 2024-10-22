#include "CloudGen.h"
#include <random>

// �־��� �������� ������ ������ ��ȯ�ϴ� �Լ�.
int GetRandom(int start, int end)
{
    std::random_device rd; // ���� �ѹ� ������ ���� �õ�.
    std::mt19937 gen(rd()); // Mersenne Twister ���� �ѹ� ������.
    std::uniform_int_distribution<int> dis(start, end); // [start, end] ������ ����.
    return dis(gen); // ���� �ѹ� ���� �� ��ȯ.
}

// CloudGen Ŭ������ ������.
CloudGen::CloudGen(int count, const char* tex_path, int w, int h)
    : m_flags(count, false) // �� ������ ���� �÷��׸� false�� �ʱ�ȭ.
    , m_texture() // ������ �ؽ�ó.
    , m_objects() // ������ ��������Ʈ ��ü.
    , m_speeds(count) // �� ������ �ӵ�.
    , m_winWidth(w) // â�� �ʺ�.
    , m_winHeight(h) // â�� ����.
{
    m_texture.loadFromFile(tex_path); // ���Ͽ��� �ؽ�ó�� �ε�.

    // ��� ���� ��������Ʈ �ʱ�ȭ.
    for (int i = 0; i < count; ++i)
        m_objects.push_back(sf::Sprite(m_texture)); // �� ������ ���� ��������Ʈ ����.

    // ù �� ���� ���� ��ġ �� ������ ���� (���ʿ��� �̵�).
    for (int i = 0; i < 3; ++i)
    {
        m_objects[i].setPosition(-300.0f, i * 150.0f); // ȭ�� �ۿ� ��ġ ����.
        m_objects[i].setScale(1.0f, 0.5f + static_cast<float>(GetRandom(0, 100) / 200.0f)); // ������ ���� ������.
    }

    // ������ ���� ��ġ �� ������ ���� (�����ʿ��� �̵�).
    for (int i = 3; i < m_objects.size(); ++i)
    {
        m_objects[i].setPosition(m_winWidth + 300, (i - 3) * 150.0f); // ȭ�� �ۿ� ��ġ ����.
        m_objects[i].setScale(-1.0f, 0.5f + static_cast<float>(GetRandom(0, 100) / 200.0f)); // ������ ���� �����ϰ� ���� ����.
    }
}

// Ȱ�� ������ 3�� �̸��� �� ������ �����ϴ� �Լ�.
void CloudGen::Gen()
{
    while (this->flagCount() < 3) // Ȱ�� ������ 3�� �̸��� ��.
    {
        int i = GetRandom(0, 5); // �����ϰ� ���� �ε��� ����.
        if (m_flags[i] == false) // �ش� ������ ��Ȱ�� ���¶��.
        {
            m_flags[i] = true; // ������ Ȱ��ȭ.
            m_speeds[i] = GetRandom(50, 150); // ������ �ӵ� ���� ����.
        }
    }
}

// ������ �ӵ��� ���� �̵���Ű�� �Լ�.
void CloudGen::Move(float dt)
{
    int size = m_objects.size(); // ������ ���� ��������.
    for (int i = 0; i < size; ++i)
    {
        // ������ ���µ��� �ʾҴٸ� �̵�.
        if (this->isEnd(i) == false)
        {
            // �������� �̵��ϴ� ����.
            if (i < 3 && m_flags[i])
            {
                sf::Vector2f cloudPos = m_objects[i].getPosition();
                cloudPos.x += m_speeds[i] * dt; // ���������� �̵�.
                m_objects[i].setPosition(cloudPos); // ��ġ ������Ʈ.
            }
            // ���������� �̵��ϴ� ����.
            else if (m_flags[i])
            {
                sf::Vector2f cloudPos = m_objects[i].getPosition();
                cloudPos.x -= m_speeds[i] * dt; // �������� �̵�.
                m_objects[i].setPosition(cloudPos); // ��ġ ������Ʈ.
            }
        }
    }
}

// ������ �����ϰ� �̵���Ű�� ������Ʈ �Լ�.
void CloudGen::Update(float dt)
{
    Gen(); // �ʿ� �� ���� ����.
    Move(dt); // ���� �̵�.
}

// ���� ��ü�� ������ ��ȯ�ϴ� �Լ�.
int CloudGen::size()
{
    return m_objects.size(); // ���� ��ü�� ���� ��ȯ.
}

// Ȱ�� ������ ������ ������ ���� ��ġ�ϴ��� Ȯ���ϴ� �Լ�.
bool CloudGen::hasCount(int count)
{
    int size = m_flags.size(); // �÷��� ���� ��������.
    int nc = 0; // Ȱ�� ���� ����.
    for (int i = 0; i < size; ++i)
    {
        if (m_flags[i]) // ������ Ȱ�� ���¶��.
            nc++; // Ȱ�� ���� ����.
    }
    return (count == nc); // Ȱ�� ������ ������ ���� ��ġ�ϴ��� ��ȯ.
}

// ������ ȭ�� ������ ������ �� �Ӽ��� �����ϴ� �Լ�.
void CloudGen::reset(int i)
{
    if (i < 3) // �������� �̵��ϴ� ����.
    {
        m_objects[i].setPosition(-300.0f, i * 150.0f); // ��ġ�� ȭ�� ������ ����.
        m_objects[i].setScale(1.0f, 0.5f + static_cast<float>(GetRandom(0, 100) / 200.0f)); // ������ ���� ������.
    }
    else // ���������� �̵��ϴ� ����.
    {
        m_objects[i].setPosition(m_winWidth + 300, (i - 3) * 150.0f); // ��ġ�� ȭ�� ������ ����.
        m_objects[i].setScale(-1.0f, 0.5f + static_cast<float>(GetRandom(0, 100) / 200.0f)); // ������ ���� �����ϰ� ���� ����.
    }
    m_objects[i].setOrigin(0.0f, 0.0f); // �������� ���� ���� ����.
    m_flags[i] = false; // ������ ��Ȱ��ȭ.
}

// ������ ȭ�� ������ �������� Ȯ���ϰ� �����ϴ� �Լ�.
bool CloudGen::isEnd(int i)
{
    bool result = false; // ��� �ʱ�ȭ.
    const auto& pos = m_objects[i].getPosition(); // ������ ��ġ ��������.

    // �������� �̵��ϴ� ����.
    if (i < 3 && m_flags[i])
    {
        if ((int)pos.x > (int)(m_winWidth + 350)) // ���������� �������� Ȯ��.
        {
            reset(i); // ���� ����.
            result = true; // �����ٰ� ǥ��.
        }
    }
    // ���������� �̵��ϴ� ����.
    else if (m_flags[i])
    {
        if ((int)(pos.x) < -450) // �������� �������� Ȯ��.
        {
            reset(i); // ���� ����.
            result = true; // �����ٰ� ǥ��.
        }
    }
    return result; // ������ �������� ��ȯ.
}

// Ȱ�� ������ ������ ���� �Լ�.
int CloudGen::flagCount()
{
    int size = m_flags.size(); // �÷��� ���� ��������.
    int nc = 0; // Ȱ�� ���� ����.
    for (int i = 0; i < size; ++i)
    {
        if (m_flags[i]) // ������ Ȱ�� ���¶��.
            nc++; // Ȱ�� ���� ����.
    }
    return (nc); // ���� ��ȯ.
}

// ���� ��������Ʈ�� �����ϱ� ���� �����ε��� ������.
sf::Sprite& CloudGen::operator[](int i)
{
    return m_objects[i]; // �ε��� i�� �ش��ϴ� ��������Ʈ ��ȯ.
}

// ��� ������ �����ε��� ������.
const sf::Sprite& CloudGen::operator[](int i) const
{
    return m_objects[i]; // �ε��� i�� �ش��ϴ� ��������Ʈ ��ȯ.
}
