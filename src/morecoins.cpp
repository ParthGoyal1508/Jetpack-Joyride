#include "morecoins.h"
#include "math.h"
#include "main.h"
using namespace std;

Morecoins::Morecoins(float x, float y) {
    this->position = glm::vec3(x, y, 0);

    
    GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        0.4f, 0.0f, 0.0f,
        0.4f, 0.5f, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.4f, 0.5f, 0.0f,

        0.0f, 0.0f, 0.0f,
        -0.4f, 0.0f, 0.0f,
        -0.4f, -0.5f, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.4f, -0.5f, 0.0f,

    };

    GLfloat vertex_buffer_data2[] = {
        0.0f, 0.0f, 0.0f,
        0.4f, 0.0f, 0.0f,
        0.4f, -0.5f, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.4f, -0.5f, 0.0f,

        0.0f, 0.0f, 0.0f,
        -0.4f, 0.0f, 0.0f,
        -0.4f, 0.5f, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
        -0.4f, 0.5f, 0.0f,

    };

    
    this->object = create3DObject(GL_TRIANGLES, 4 * 3, vertex_buffer_data, COLOR_MORECOIN1, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4 * 3, vertex_buffer_data2, COLOR_MORECOIN2, GL_FILL);
}

void Morecoins::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Morecoins::move() {
    if(this->position.x <=0){
        this->position.x += 0.04;
        this->position.y += 0.06;
    }
    if(this->position.x >=0){
        this->position.x += 0.04;
        this->position.y -= 0.06;
    }
}


void Morecoins::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}



