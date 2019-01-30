#include "shield.h"
#include "math.h"
#include "main.h"
using namespace std;

Shield::Shield(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);

    
    GLfloat vertex_buffer_data[] = {
        -0.20f, 0.25f, 0.0f,
        -0.20f, -0.25f, 0.0f,
        0.20f, -0.25f, 0.0f,
        -0.20f, 0.25f, 0.0f,
        0.20f, 0.25f, 0.0f,
        0.20f, -0.25f, 0.0f,

        -0.20f, 0.25f, 0.0f,
        0.20f, 0.25f, 0.0f,
        0.0f, 0.50f, 0.0f,  

        -0.20f, -0.25f, 0.0f,
        0.20f, -0.25f, 0.0f,
        0.0f, -0.50f, 0.0f,       
    };

    
    
    this->object = create3DObject(GL_TRIANGLES, 4 * 3, vertex_buffer_data, color, GL_FILL);
}

void Shield::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->alive == 1)
        draw3DObject(this->object);
}

void Shield::move() {
    this->position.x += 0.05;
    if(this->position.x < -1.25)
    this->position.y = 2 + sqrt((1.25)*(1.25)-(this->position.x+2.5)*(this->position.x+2.5));
    if(this->position.x < 1.25 && this->position.x > -1.25 )
    this->position.y = 2 - sqrt((1.25)*(1.25)-(this->position.x)*(this->position.x));
    if(this->position.x < 3.75 && this->position.x > 1.25)
    this->position.y = 2 + sqrt((1.25)*(1.25)-(this->position.x-2.5)*(this->position.x-2.5));
}


void Shield::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}



