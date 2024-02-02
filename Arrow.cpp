#include "Arrow.hpp"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

Arrow::Arrow(int startSq, int endSq){
    this->startSq = startSq;
    this->endSq = endSq;

    int startX = (7 - (startSq % 8)) * 100;
    int startY = (7 - (startSq / 8)) * 100;
    int endX = (7 - (endSq % 8)) * 100;
    int endY = (7 - (endSq / 8)) * 100;
    int bodySize = abs(sqrt(pow(endY - startY, 2) + pow(endX - startX, 2))) - 40;
    int offSetY;
    int offSetX;

    float angle_rad = atan2(endY - startY, endX - startX);
    float angle_deg = 0 - (180.0 / M_PI) * angle_rad;

    if(startX <= endX && startY >= endY){
        offSetX = 1;
        offSetY = -1;
        angle_deg = -angle_deg;
    } else if (startX >= endX && startY >= endY){
        offSetX = 1;
        offSetY = -1;
        angle_deg = -angle_deg;
    } else if (startX <= endX && startY <= endY){
        offSetX = 1;
        offSetY = -1;
        angle_deg = -angle_deg;
    } else if (startX >= endX && startY <= endY){
        offSetX = 1;
        offSetY = -1;
        angle_deg = -angle_deg;
    }

    body = new RectangleShape(Vector2f(bodySize, 30));
    head = new CircleShape(30, 3);

    body->setOrigin(0, 15);
    head->setOrigin(head->getRadius(), head->getRadius() * 2 - 15);
    head->rotate(90 + angle_deg);
    body->rotate(angle_deg);
    head->setPosition(Vector2f(startX + (bodySize * cos(angle_rad) + 50) * offSetX, startY - (bodySize * sin(angle_rad) + 50) * offSetY));
    body->setPosition(Vector2f(startX + 50, startY + 50));

    head->setFillColor(Color(229, 158, 35, 200));
    body->setFillColor(Color(229, 158, 35, 200));
}

Arrow::~Arrow(){
    delete head;
    delete body;
}