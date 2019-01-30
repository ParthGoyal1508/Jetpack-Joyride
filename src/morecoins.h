#include "main.h"

#ifndef MORECOINS_H
#define MORECOINS_H


class Morecoins {
public:
    Morecoins() {}
    Morecoins(float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void move();
    int start_time;
    int end_time;
    int time;
    int alive = 0;
    void set_position(float x, float y);
private:
    VAO *object;
    VAO *object2;
};

#endif // MORECOINS_H
