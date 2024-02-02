#pragma once

#include <SFML/Graphics.hpp>
#include <bitset>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

class Arrow {
    public:
        Arrow* next = nullptr;
        CircleShape* head;
        RectangleShape* body;
        int startSq;
        int endSq;
        
    public:
        Arrow(int startSq, int endSq);
        ~Arrow();
};