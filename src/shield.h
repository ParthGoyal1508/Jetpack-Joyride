#include "main.h"

#ifndef SHIELD_H
#define SHIELD_H


class Shield {
public:
    Shield() {}
    Shield(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void move();
    int alive = 0;
    int start_time;
    int end_time;
    int time;
    void set_position(float x, float y);
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
};

#endif // SHIELD_H
