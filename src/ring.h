#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, color_t color, float rotation);
    glm::vec3 position;
    float rotation;
    int alive;
    int start_time;
    int end_time;
    void draw(glm::mat4 VP);
    void tick();
    void move_ring(double x);
    void set_position(float x, float y);
    bounding_circle_t bounding_circle();
private:
    VAO *object;
};

#endif //RING_H
