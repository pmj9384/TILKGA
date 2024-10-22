#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

class CloudGen
{
public:
    CloudGen(int count, const char* tex_path, int w, int h);
    ~CloudGen() = default;

    void    Gen();
    void    Move(float dt);
    void    Update(float dt);
    int     size();
    bool    hasCount(int count);
    void    reset(int i);
    bool    isEnd(int i);
    int     flagCount();

    sf::Sprite& operator[](int i);
    const sf::Sprite& operator[](int i) const;

private:
    std::vector<bool>           m_flags;
    sf::Texture                 m_texture;
    std::vector<sf::Sprite>     m_objects;
    std::vector<float>          m_speeds;
    int                         m_winWidth;
    int                         m_winHeight;
};