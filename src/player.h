#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float velocity_y;
    int shield = 0;
    int shield2 = 0;
    int score = 1500;
    int semicircularmotion = 0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
};

#endif // PLAYER_H
