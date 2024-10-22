#pragma once
#include <list>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>


class InputMgr
{
private:
	static std::list<sf::Keyboard::Key> downList;
	static std::list<sf::Keyboard::Key> heldList;
	static std::list<sf::Keyboard::Key> upList;

	static std::list<sf::Mouse::Button> MdownList;
	static std::list<sf::Mouse::Button> MheldList;
	static std::list<sf::Mouse::Button> MupList;

public:

	static void Clear();
	static void UpdateEvent(const sf::Event& ev);

	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);


	static bool GetMouseDown(sf::Mouse::Button mus);
	static bool GetMouse(sf::Mouse::Button mus);
	static bool GetMouseUp(sf::Mouse::Button mus);

	
	
};

