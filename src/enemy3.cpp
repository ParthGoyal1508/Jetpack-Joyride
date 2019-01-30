#include "enemy3.h"
#include "math.h"
#include "main.h"
using namespace std;

Enemy3::Enemy3(float x, float y) {
   
    this->position = glm::vec3(x, y, 0);
    
    GLfloat vertex_buffer_data[] = {
        -0.2f, 0.25f, 0.0f,
        -0.2f, -0.25f, 0.0f,
        0.2f, -0.25f, 0.0f,
        
        -0.2f, 0.25f, 0.0f,
        0.2f, 0.25f, 0.0f,
        0.2f, -0.25f, 0.0f,

    };

    GLfloat vertex_buffer_data2[] = {
       -0.2f, 0.0f, 0.0f,
       0.2f, 0.0f, 0.0f,
       0.0f, 0.25f, 0.0f,

       -0.2f, 0.0f, 0.0f,
       0.2f, 0.0f, 0.0f,
       0.0f, -0.25f, 0.0f,

    };

    this->object = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, COLOR_ENEMY_3_1, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data2, COLOR_ENEMY_3_2, GL_FILL);
}

void Enemy3::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Enemy3::move() {
    this->rotation += 4;
    if(this->position.y >= 0.7 && this->position.x >=-1.2){
        this->position.x -= 0.062;
    }
    if(this-> position.x < -1.2){
        this->position.y -=0.02;
        this->position.x = -sqrt((2.7)*(2.7) - (this->position.y - 0.7)*(this->position.y - 0.7)) - 0.9;
    }
    if(this->position.y < 0.7 && this->position.x >=-1.2){
        this->position.x += 0.062;
    }
}


void Enemy3::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}



