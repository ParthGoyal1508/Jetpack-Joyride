#include "enemy1.h"
#include "main.h"
using namespace std;

Enemy1::Enemy1(float x, float y, color_t color, float rotation) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = rotation;

    
    GLfloat vertex_buffer_data[] = {
        -1.00f, 0.10f, 0.0f, //vertical line1
        -1.00f, -0.10f, 0.0f,
        1.00f, -0.10f, 0.0f,
        -1.00f, 0.10f, 0.0f,
        1.00f, -0.10f, 0.0f,
        1.00f, 0.10f, 0.0f,
       
    };

    const int n = 360;
    const int reqd = n * 9;
    GLfloat vertex_buffer_data2[reqd] = {};

    double angle = 0;
    double radius = 0.15;
    const double pi = 4 * atan(1);
    double diff = (2 * pi) / (double)n;
    int cur = 0;

    for (int i = 0; i < n; i++)
    {
        //Origin
        vertex_buffer_data2[cur++] = 1.0f;
        vertex_buffer_data2[cur++] = 0.0f;
        vertex_buffer_data2[cur++] = 0.0f;

        //Point with lower angle
        vertex_buffer_data2[cur++] = 1.0f+radius * cos(angle);
        vertex_buffer_data2[cur++] = radius * sin(angle);
        vertex_buffer_data2[cur++] = 0.0f;

        //Point with higher angle
        angle += diff;
        vertex_buffer_data2[cur++] = 1.0f+radius * cos(angle);
        vertex_buffer_data2[cur++] = radius * sin(angle);
        vertex_buffer_data2[cur++] = 0.0f;
    }

    cur = 0;
    GLfloat vertex_buffer_data3[reqd] = {};
    for (int i = 0; i < n; i++)
    {
        //Origin
        vertex_buffer_data3[cur++] = -1.0f;
        vertex_buffer_data3[cur++] = 0.0f;
        vertex_buffer_data3[cur++] = 0.0f;

        //Point with lower angle
        vertex_buffer_data3[cur++] = -1.0f+radius * cos(angle);
        vertex_buffer_data3[cur++] = radius * sin(angle);
        vertex_buffer_data3[cur++] = 0.0f;

        //Point with higher angle
        angle += diff;
        vertex_buffer_data3[cur++] = -1.0f+radius * cos(angle);
        vertex_buffer_data3[cur++] = radius * sin(angle);
        vertex_buffer_data3[cur++] = 0.0f;
    }

    
    this->object = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n * 3, vertex_buffer_data2, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, n * 3, vertex_buffer_data3, color, GL_FILL);
}

void Enemy1::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Enemy1::move_left(float speed) {
    this->position.x -= speed;
}


void Enemy1::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}



