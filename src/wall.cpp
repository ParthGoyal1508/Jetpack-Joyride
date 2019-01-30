#include "wall.h"
#include "main.h"
using namespace std;

Wall::Wall(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);

    static const GLfloat vertex_buffer_data[] = {
        -3.0f, 3.0f, 0.0f,//block A
        -3.0f, -1.0f, 0.0f,
        0.0f, 3.0f, 0.0f,
        0.0f, 3.0f, 0.0f,
        -3.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,

        0.0f, 3.0f, 0.0f,//side triangle
        0.0f, 2.75f, 0.0f,
        0.25f, 2.75f, 0.0f,

        0.0f, -0.75f, 0.0f,//side triangle
        0.0f, -1.0f, 0.0f,
        0.25f, -0.75f, 0.0f,

        -3.25f, -0.75f, 0.0f,//side triangle
        -3.0f, -0.75f, 0.0f,
        -3.0f, -1.0f, 0.0f,

        -3.0f, 3.0f, 0.0f,//side triangle
        -3.0f, 2.75f, 0.0f,
        -3.25f, 2.75f, 0.0f,

        -3.25f, 2.75f, 0.0f,//rectangle
        -3.25f, -0.75f, 0.0f,
        -3.0f, -0.75f, 0.0f,
        
        -3.0f, 2.75f, 0.0f,
        -3.25f, 2.75f, 0.0f,
        -3.0f, -0.75f, 0.0f,

         0.0f, 2.75f, 0.0f,//rectangle
         0.0f, -0.75f, 0.0f,
         0.25f, -0.75f, 0.0f,
        
         0.25f, 2.75f, 0.0f,
         0.0f, 2.75f, 0.0f,
         0.25f, -0.75f, 0.0f,

        1.5f, 3.0f, 0.0f,//block B
        1.5f, -1.0f, 0.0f,
        2.5f, 3.0f, 0.0f,
        2.5f, 3.0f, 0.0f,
        1.5f, -1.0f, 0.0f,
        2.5f, -1.0f, 0.0f,

        2.5f, 3.0f, 0.0f,//side triangle
        2.5f, 2.75f, 0.0f,
        2.75f, 2.75f, 0.0f,

        2.5f, -0.75f, 0.0f,//side triangle
        2.5f, -1.0f, 0.0f,
        2.75f, -0.75f, 0.0f,

        1.25f, -0.75f, 0.0f,//side triangle
        1.5f, -0.75f, 0.0f,
        1.5f, -1.0f, 0.0f,

        1.5f, 3.0f, 0.0f,//side triangle
        1.5f, 2.75f, 0.0f,
        1.25f, 2.75f, 0.0f,

        1.25f, 2.75f, 0.0f,//rectangle
        1.25f, -0.75f, 0.0f,
        1.5f, -0.75f, 0.0f,
        
        1.5f, 2.75f, 0.0f,
        1.25f, 2.75f, 0.0f,
        1.5f, -0.75f, 0.0f,

        2.5f, 2.75f, 0.0f,//rectangle
        2.5f, -0.75f, 0.0f,
        2.75f, -0.75f, 0.0f,
        
        2.75f, 2.75f, 0.0f,
        2.5f, 2.75f, 0.0f,
        2.75f, -0.75f, 0.0f,

    };

    this->object = create3DObject(GL_TRIANGLES, 20 * 3, vertex_buffer_data, COLOR_GREY, GL_FILL);
}

void Wall::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Wall::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}



