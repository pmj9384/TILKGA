#pragma once
class GameObject
{
protected:
	bool active = true;
	sf::Vector2f position;

public:
	GameObject() = default;
	virtual ~GameObject() = default;


	bool IsActive() const { return active; }
	void SetActive(bool a) { active = a; }

	sf::Vector2f GetPosition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }

	virtual void Init();
	virtual void Release();

	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);
};

