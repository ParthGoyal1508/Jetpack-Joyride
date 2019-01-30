#include "ring.h"
#include "main.h"
#include "math.h"

Ring::Ring(float x, float y, color_t color, float rotation) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = rotation;

    float radius_1 = 1.2, radius_2 = 1.1;
    static GLfloat magnet_vertex_buffer_data[8000];
    int vertex_count = 0;
    float i = radius_1, j = 0.0f, a = radius_2, b = 0.0f, temp_a, temp_b, temp_i, temp_j;

    for (int k = 0; k < 180; k++)
    {
        temp_a = a, temp_b = b;
        a = radius_2 * cos((float)k * M_PI / 180);
        b = -radius_2 * sin((float)k * M_PI / 180);
        temp_i = i, temp_j = j;
        i = radius_1 * cos((float)k * M_PI / 180);
        j = -radius_1 * sin((float)k * M_PI / 180);

        magnet_vertex_buffer_data[vertex_count++] = temp_i;
        magnet_vertex_buffer_data[vertex_count++] = temp_j;
        magnet_vertex_buffer_data[vertex_count++] = 0.0f;

        magnet_vertex_buffer_data[vertex_count++] = temp_a;
        magnet_vertex_buffer_data[vertex_count++] = temp_b;
        magnet_vertex_buffer_data[vertex_count++] = 0.0f;

        magnet_vertex_buffer_data[vertex_count++] = a;
        magnet_vertex_buffer_data[vertex_count++] = b;
        magnet_vertex_buffer_data[vertex_count++] = 0.0f;

        magnet_vertex_buffer_data[vertex_count++] = temp_i;
        magnet_vertex_buffer_data[vertex_count++] = temp_j;
        magnet_vertex_buffer_data[vertex_count++] = 0.0f;

        magnet_vertex_buffer_data[vertex_count++] = i;
        magnet_vertex_buffer_data[vertex_count++] = j;
        magnet_vertex_buffer_data[vertex_count++] = 0.0f;

        magnet_vertex_buffer_data[vertex_count++] = a;
        magnet_vertex_buffer_data[vertex_count++] = b;
        magnet_vertex_buffer_data[vertex_count++] = 0.0f;
    }

        magnet_vertex_buffer_data[vertex_count++] = -radius_2; 
        magnet_vertex_buffer_data[vertex_count++] =  -0.02f;
        magnet_vertex_buffer_data[vertex_count++] =  0.0f;

        magnet_vertex_buffer_data[vertex_count++] =  -radius_2;
        magnet_vertex_buffer_data[vertex_count++] =  0.1f;
        magnet_vertex_buffer_data[vertex_count++] =  0.0f;

        magnet_vertex_buffer_data[vertex_count++] = -radius_2-0.25; 
        magnet_vertex_buffer_data[vertex_count++] =  0.1f;
        magnet_vertex_buffer_data[vertex_count++] =  0.0f;

        magnet_vertex_buffer_data[vertex_count++] = -radius_2; 
        magnet_vertex_buffer_data[vertex_count++] =  -0.02f;
        magnet_vertex_buffer_data[vertex_count++] =  0.0f;

        magnet_vertex_buffer_data[vertex_count++] =  -radius_2-0.25;
        magnet_vertex_buffer_data[vertex_count++] =  -0.02f;
        magnet_vertex_buffer_data[vertex_count++] =  0.0f;

        magnet_vertex_buffer_data[vertex_count++] = -radius_2-0.25; 
        magnet_vertex_buffer_data[vertex_count++] =  0.1f;
        magnet_vertex_buffer_data[vertex_count++] =  0.0f;


        magnet_vertex_buffer_data[vertex_count++] = radius_2; 
        magnet_vertex_buffer_data[vertex_count++] =  -0.02f;
        magnet_vertex_buffer_data[vertex_count++] =  0.0f;

        magnet_vertex_buffer_data[vertex_count++] =  radius_2;
        magnet_vertex_buffer_data[vertex_count++] =  0.1f;
        magnet_vertex_buffer_data[vertex_count++] =  0.0f;

        magnet_vertex_buffer_data[vertex_count++] = radius_2+0.25; 
        magnet_vertex_buffer_data[vertex_count++] =  0.1f;
        magnet_vertex_buffer_data[vertex_count++] =  0.0f;

        magnet_vertex_buffer_data[vertex_count++] = radius_2; 
        magnet_vertex_buffer_data[vertex_count++] =  -0.02f;
        magnet_vertex_buffer_data[vertex_count++] =  0.0f;

        magnet_vertex_buffer_data[vertex_count++] =  radius_2+0.25;
        magnet_vertex_buffer_data[vertex_count++] =  -0.02f;
        magnet_vertex_buffer_data[vertex_count++] =  0.0f;

        magnet_vertex_buffer_data[vertex_count++] = radius_2+0.25; 
        magnet_vertex_buffer_data[vertex_count++] =  0.1f;
        magnet_vertex_buffer_data[vertex_count++] =  0.0f;

    this->object = create3DObject(GL_TRIANGLES, vertex_count / 3, magnet_vertex_buffer_data, color, GL_FILL);
}

void Ring::move_ring(double x){
    this->position.x -= x;
}

void Ring:: set_position(float x, float y){
    this->position.x =x;
    this->position.y =y;
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}