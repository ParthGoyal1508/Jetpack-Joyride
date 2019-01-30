#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y, float radius, color_t color);
    glm::vec3 position;
    float radius;
    void draw(glm::mat4 VP);
    float velocity_x;
    float velocity_y;
    void set_position(float x, float y);
    void move_left(float speed);
private:
    VAO *object;
};

#endif // COIN_H
