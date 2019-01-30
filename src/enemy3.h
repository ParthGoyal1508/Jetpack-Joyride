#include "main.h"

#ifndef ENEMY3_H
#define ENEMY3_H


class Enemy3 {
public:
    Enemy3() {}
    Enemy3(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void move();
    int start_time;
    int end_time;
    int time;
    int alive;
    void set_position(float x, float y);
private:
    VAO *object;
    VAO *object2;
};

#endif // ENEMY3_H
