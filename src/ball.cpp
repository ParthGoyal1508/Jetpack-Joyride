#include "ball.h"
#include "main.h"
using namespace std;

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);

    const int n = 360;
    const int reqd = n * 9;
    GLfloat vertex_buffer_data5[reqd] = {};

    double angle = 0;
    double radius = 0.03;
    const double pi = M_PI;
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

    this->object = create3DObject(GL_TRIANGLES, 3 * n, vertex_buffer_data5, COLOR_BLACK, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::move_left(float speed) {
    this->position.x -= speed;
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}



