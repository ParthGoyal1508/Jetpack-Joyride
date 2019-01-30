#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    int start_time;
    int end_time;
    float vertical_speed = 0.01;
    int alive = 0;
    int line1_alive = 0;
    int line2_alive = 0;
    int line3_alive = 0;
    int triangle1_alive = 0;
    int triangle2_alive = 0;
    int triangle3_alive = 0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_left(float speed);
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;
    VAO *object9;
    VAO *object10;
};

#endif // ENEMY_H
