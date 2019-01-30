#include "enemy.h"
#include "main.h"
using namespace std;

Enemy::Enemy(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);

    
    GLfloat vertex_buffer_data[] = {
        -3.25f, 3.5f, 0.0f, //vertical line1
        -3.25f, -2.0f, 0.0f,
        -3.10f, -2.0f, 0.0f,
        -3.25f, 3.5f, 0.0f,
        -3.10f, 3.5f, 0.0f,
        -3.10f, -2.0f, 0.0f,

        3.25f, 3.5f, 0.0f, //vertical line2
        3.25f, -2.0f, 0.0f,
        3.10f, -2.0f, 0.0f,
        3.25f, 3.5f, 0.0f,
        3.10f, 3.5f, 0.0f,
        3.10f, -2.0f, 0.0f,

    };
     GLfloat vertex_buffer_data2[] = {
        -3.10f, -2.0f, 0.0f, //triangle1
        -3.10f, -1.70f, 0.0f,
        -2.95f, -1.85f, 0.0f,

        3.10f, -2.0f, 0.0f, //triangle4
        3.10f, -1.70f, 0.0f,
        2.95f, -1.85f, 0.0f,
    };
     GLfloat vertex_buffer_data3[] = {
        -3.10f, 0.6f, 0.0f, //triangle3
        -3.10f, 0.9f, 0.0f,
        -2.95f, 0.75f, 0.0f,

        3.10f, 0.6f, 0.0f, //triangle6
        3.10f, 0.9f, 0.0f,
        2.95f, 0.75f, 0.0f,

     };
     GLfloat vertex_buffer_data4[] = {
        -3.10f, 3.5f, 0.0f, //triangle2
        -3.10f, 3.2f, 0.0f,
        -2.95f, 3.35f, 0.0f,

        3.10f, 3.5f, 0.0f, //triangle5
        3.10f, 3.2f, 0.0f,
        2.95f, 3.35f, 0.0f,
     };
     
     GLfloat vertex_buffer_data5[] = {
        -2.95f, -1.95f, 0.0f, //horizontal 1
        -2.95f, -1.75f, 0.0f,
        2.95f, -1.75f, 0.0f,
        -2.95f, -1.95f, 0.0f,
        2.95f, -1.95f, 0.0f,
        2.95f, -1.75f, 0.0f,

     };
     GLfloat vertex_buffer_data6[] = {
        -2.95f, 0.85f, 0.0f, //horizontal 2
        -2.95f, 0.65f, 0.0f,
        2.95f, 0.65f, 0.0f,
        -2.95f, 0.85f, 0.0f,
        2.95f, 0.85f, 0.0f,
        2.95f, 0.65f, 0.0f,
     };
     GLfloat vertex_buffer_data7[] = {
        -2.95f, 3.45f, 0.0f, //horizontal 3
        -2.95f, 3.25f, 0.0f,
        2.95f, 3.25f, 0.0f,
        -2.95f, 3.45f, 0.0f,
        2.95f, 3.45f, 0.0f,
        2.95f, 3.25f, 0.0f,

     };

    this->object = create3DObject(GL_TRIANGLES, 4 * 3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data2, COLOR_ENEMY_5, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data3, COLOR_ENEMY_5, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data4, COLOR_ENEMY_5, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data5, COLOR_RED, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data6, COLOR_RED, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data7, COLOR_RED, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    this->position.y += this->vertical_speed;
    if(this->position.y < -0.25)
        this->vertical_speed = 0.01;
    else if(this->position.y > 0.25)
        this->vertical_speed = -0.01;

    draw3DObject(this->object);

    if(this->triangle1_alive == 1)
        draw3DObject(this->object2);
    if(this->line1_alive == 1)
        draw3DObject(this->object5);

    if(this->triangle2_alive == 1)
        draw3DObject(this->object3);
    if(this->line2_alive == 1)
        draw3DObject(this->object6);

    if(this->triangle3_alive == 1)
        draw3DObject(this->object4);
    if(this->line3_alive == 1)
        draw3DObject(this->object7);
}

void Enemy::move_left(float speed) {
    this->position.x -= speed;
}

void Enemy::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}



