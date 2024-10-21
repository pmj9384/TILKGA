#include "stdafx.h"

std::list<sf::Keyboard::Key> InputMgr::downList;
std::list<sf::Keyboard::Key> InputMgr::heldList;
std::list<sf::Keyboard::Key> InputMgr::upList;

std::list<sf::Mouse::Button> InputMgr::MdownList;
std::list<sf::Mouse::Button> InputMgr::MheldList;
std::list<sf::Mouse::Button> InputMgr::MupList;

void InputMgr::Clear()
{
	downList.clear();
	upList.clear();
	MdownList.clear();
	MupList.clear();
}

 
void InputMgr::UpdateEvent(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		if (std::find(heldList.begin(), heldList.end(), ev.key.code) == heldList.end());
		{
			heldList.push_back(ev.key.code);
			downList.push_back(ev.key.code);
		}
		break;
	case sf::Event::KeyReleased:
		heldList.remove(ev.key.code);
		upList.push_back(ev.key.code);
		break;


	case sf::Event::MouseButtonReleased:
	
			MheldList.remove(sf::Mouse::Left);
			MupList.push_back(sf::Mouse::Left);

		break;
	case sf::Event::MouseButtonPressed:
		if (ev.mouseButton.button == sf::Mouse::Left)
		{
			int mouseX = ev.mouseButton.x;
			int mouseY = ev.mouseButton.y;
			std::cout << "Mouse clicked at: (" << mouseX << ", " << mouseY << ")\n";

			if (std::find(MheldList.begin(), MheldList.end(), sf::Mouse::Left) == MheldList.end())
			{
				MheldList.push_back(sf::Mouse::Left);
				MdownList.push_back(sf::Mouse::Left);
			}
		}
		break;


	
	}
}


bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
	return std::find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
	return std::find(heldList.begin(), heldList.end(), key) != heldList.end();
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
	return std::find(upList.begin(), upList.end(), key) != upList.end();
}

bool InputMgr::GetMouseDown(sf::Mouse::Button mus)
{
	return std::find(MdownList.begin(), MdownList.end(), mus) != MdownList.end();
}

bool InputMgr::GetMouse(sf::Mouse::Button mus)
{
	return std::find(MheldList.begin(), MheldList.end(), mus) != MheldList.end();
}

bool InputMgr::GetMouseUp(sf::Mouse::Button mus)
{
	return std::find(MupList.begin(), MupList.end(), mus) != MupList.end();
}











