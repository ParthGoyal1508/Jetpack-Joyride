#include "dragon.h"
#include "main.h"
using namespace std;

Dragon::Dragon(float x, float y) {
    this->position = glm::vec3(x, y, 0);

    GLfloat vertex_buffer_data[] = {
        -1.00f, 1.25f, 0.0f, //vertical line1
        -1.00f, 0.60f, 0.0f,
        -0.40f, 0.60f, 0.0f,

        -0.40f, 0.60f, 0.0f,
         0.70f, 0.60f, 0.0f,
         0.70f, 0.00f, 0.0f,

        -0.40f, 0.60f, 0.0f,
         0.70f, 0.00f, 0.0f,
        -0.40f, 0.00f, 0.0f,

        -0.40f, 0.00f, 0.0f,
        -0.40f, -1.0f, 0.0f,
         0.15f, 0.00f, 0.0f,

         0.15f, 0.00f, 0.0f,
         0.70f, 0.00f, 0.0f,
         0.70f, -1.00f, 0.0f,

        -0.40f, -1.00f, 0.0f,
        -0.6f, -1.0f, 0.0f,
        -0.6f, -1.25f, 0.0f,

        -0.40f, -1.00f, 0.0f,
        -0.4, -1.25f, 0.0f,
        -0.6f, -1.25f, 0.0f,

        0.7f, -1.0f, 0.0f,
        0.9f, -1.0f, 0.0f,
        0.9f, -1.25f, 0.0f,

        0.7f, -1.0f, 0.0f,
        0.7f, -1.25f, 0.0f,
        0.9f, -1.25f, 0.0f,

        0.7f, 0.6f, 0.0f,
        0.7f, 0.3f, 0.0f,
        1.0f, 0.0f, 0.0f   
    };



    this->object = create3DObject(GL_TRIANGLES, 10 * 3, vertex_buffer_data, COLOR_ENEMY_4, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
     Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Dragon::move_left(float x) {
    this->position.x -= x;
}


void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}



