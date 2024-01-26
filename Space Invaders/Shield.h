#pragma once
#include "Entity.h"

class Shield :
    public Entity
{
public:
    Shield(float offsetX);
    void Draw();

private:
    //position offsets, moves the entire shield along x and y axis
    float offsetX;
    float offsetY;

    //main rectangle
    float recX;
    float recY;
    float recWidth;
    float recHeight;
    Rectangle rec;
    Vector2 recOrigin;
    float rotation;
    Color recColor;

    //shared corner rectangle variables
    float cornerY;
    float cornerWidth;
    float cornerHeight;
    Vector2 cornerOrigin;
    Color cornerColor;

    //right corner
    float cornerRightX;
    Rectangle cornerRight;
    float cornerRightRotation;

    //left corner
    float cornerLeftX;
    Rectangle cornerLeft;
    float cornerLeftRotation;

    //semi-circle
    Vector2 center;
    float radius;
    float startAngle;
    float endAngle;
    int segments;
    Color circleColor;
};