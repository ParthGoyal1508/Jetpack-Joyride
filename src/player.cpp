#include "player.h"
#include "main.h"
using namespace std;

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);

    static const GLfloat vertex_buffer_data[]={
        0.0f, 0.0f, 0.0f,//first triangle
        0.0f, -0.25f, 0.0f,
        0.25f, 0.0f, 0.0f,

        0.05f, -0.75f, 0.0f,//leg
        0.05f, -0.85f, 0.0f,
        0.125f, -0.85f, 0.0f,
        0.05f, -0.75f, 0.0f,
        0.125f, -0.85f, 0.0f,
        0.125f, -0.75f, 0.0f,

        0.20f, -0.75f, 0.0f,//leg
        0.20f, -0.85f, 0.0f,
        0.275f, -0.85f, 0.0f,
        0.20f, -0.75f, 0.0f,
        0.275f, -0.85f, 0.0f,
        0.275f, -0.75f, 0.0f,
    };

    static const GLfloat vertex_buffer_data2[]={
        0.05f, -0.35f, 0.0f,//square
        0.05f, -0.55f, 0.0f,
        0.20f, -0.55f, 0.0f,
        0.05f, -0.35f, 0.0f,
        0.20f, -0.55f, 0.0f,
        0.20f, -0.35f, 0.0f,

    };

    static const GLfloat vertex_buffer_data3[]={
        0.05f, -0.55f, 0.0f,//two triangle
        0.05f, -0.75f, 0.0f,
        0.125f, -0.55f, 0.0f,

        0.125f, -0.55f, 0.0f,
        0.20f, -0.75f, 0.0f,
        0.20f, -0.55f, 0.0f,
    };


    static const GLfloat vertex_buffer_data4[]={
        0.05f, -0.20f, 0.0f,//second triangle
        0.20f, -0.20f, 0.0f,
        0.20f, -0.05f, 0.0f,

        0.100f, -0.2f, 0.0f,//rectangle
        0.100f, -0.35f, 0.0f,
        0.150f, -0.35f, 0.0f,
        0.100f, -0.2f, 0.0f,
        0.150f, -0.35f, 0.0f,
        0.150f, -0.2f, 0.0f,

       

    };

    static const GLfloat vertex_buffer_data5[]={
        0.05f, -0.45f, 0.0f,//jetpack
        0.05f, -0.55f, 0.0f,
        -0.02f, -0.55f, 0.0f,
        -0.02f, -0.55f, 0.0f,
        -0.02f, -0.45f, 0.0f,
        0.05f, -0.45f, 0.0f,

        -0.02f, -0.4f, 0.0f,
        -0.02f, -0.6f, 0.0f,
        -0.15f, -0.6f, 0.0f,
        -0.02f, -0.4f, 0.0f,
        -0.15f, -0.4f, 0.0f,
        -0.15f, -0.6f, 0.0f,
    };

    static const GLfloat vertex_buffer_data6[]={
        -0.15f, -0.6f, 0.0f,//fire from jetpack
        -0.15f, -0.7f, 0.0f,
        -0.085f, -0.6f, 0.0f,
        -0.085f, -0.6f, 0.0f,
        -0.02f, -0.6f, 0.0f,
        -0.02f, -0.7f, 0.0f,
    };

    static const GLfloat vertex_buffer_data7[]={
        -0.15f, 0.2f, 0.0f, //shield 
        -0.15f, -0.85f, 0.0f, 
        0.275f, -0.85f, 0.0f, 
        -0.15f, 0.2f, 0.0f, 
        0.275f, 0.2f, 0.0f, 
        0.275f, -0.85f, 0.0f, 
    };


    this->object = create3DObject(GL_TRIANGLES, 5 * 3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data2, COLOR_BLUE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data3, COLOR_MAGNET, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3 * 3, vertex_buffer_data4, COLOR_ORANGE, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 4 * 3, vertex_buffer_data5, COLOR_ENEMY_3, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data6, COLOR_YELLOW, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data7, COLOR_SHIELD, GL_FILL);



}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->shield == 1 || this->shield2 == 1){
        draw3DObject(this->object7);
    }
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    if(this->position.y > -1.64){
        draw3DObject(this->object6);
    }
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}



