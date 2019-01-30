#include "coin.h"
#include "main.h"
#include "math.h"
using namespace std;

Coin::Coin(float x, float y, float radius, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->radius= radius;
    const int n = 360;
    const int reqd = n * 9;
    GLfloat vertex_buffer_data5[reqd] = {};

    double angle = 0;
    // double radius = 0.15;
    const double pi = 4 * atan(1);
    double diff = (2 * pi) / (double)n;
    int cur = 0;

    for (int i = 0; i < n; i++)
    {
        //Origin
        vertex_buffer_data5[cur++] = 0.0f;
        vertex_buffer_data5[cur++] = 0.0f;
        vertex_buffer_data5[cur++] = 0.0f;

        //Point with lower angle
        vertex_buffer_data5[cur++] = radius * cos(angle);
        vertex_buffer_data5[cur++] = radius * sin(angle);
        vertex_buffer_data5[cur++] = 0.0f;

        //Point with higher angle
        angle += diff;
        vertex_buffer_data5[cur++] = radius * cos(angle);
        vertex_buffer_data5[cur++] = radius * sin(angle);
        vertex_buffer_data5[cur++] = 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, 3 * n, vertex_buffer_data5, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coin::move_left(float speed) {
    this->position.x -= speed;
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}



