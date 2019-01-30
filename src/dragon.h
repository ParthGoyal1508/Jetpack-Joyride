#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void move_left(float x);
    int alive = 0;
    int start_time;
    int end_time;
    void set_position(float x, float y);
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
};

#endif // DRAGON
