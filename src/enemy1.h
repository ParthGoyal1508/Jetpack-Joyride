#include "main.h"

#ifndef ENEMY1_H
#define ENEMY1_H


class Enemy1 {
public:
    Enemy1() {}
    Enemy1(float x, float y, color_t color, float rotation);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void move_left(float speed);
    int alive = 0;
    int start_time;
    int end_time;
    void set_position(float x, float y);
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
};

#endif // ENEMY1_H
