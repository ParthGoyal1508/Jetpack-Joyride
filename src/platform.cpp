#include "platform.h"
#include "main.h"
using namespace std;

Platform::Platform(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -4.0f,-2.75f,0.0f, // triangle 1 : begin
        -4.0f,-4.0f, 0.0f,
        4.0f, -4.0f, 0.0f, // triangle 1 : end
        4.0f, -4.0f, 0.0f, // triangle 1 : end
        -4.0f, -2.75f, 0.0f, 
        4.0f, -2.75f, 0.0f //triangle 2 : end
    };

    static const GLfloat vertex_buffer_data2[] = {
        -4.0f,-2.75f,0.0f, // triangle 1 : begin
        -4.0f,-2.50f, 0.0f,
        4.0f, -2.75f, 0.0f, // triangle 1 : end
        4.0f, -2.75f, 0.0f, // triangle 1 : end
        4.0f, -2.50f, 0.0f, 
        -4.0f, -2.50f, 0.0f //triangle 2 : end
    };

    static const GLfloat vertex_buffer_data3[] = {
        -2.10f, -2.75f, 0.0f, // triangle 1 : begin
        -2.10f, -2.50f, 0.0f,
        -2.00f, -2.75f, 0.0f, // triangle 1 : end
        -2.00f, -2.75f, 0.0f, // triangle 2 : begin
        -2.00f, -2.50f, 0.0f, 
        -2.10f, -2.50f, 0.0f, //triangle 2 : end
        -0.10f, -2.75f, 0.0f, // triangle 3 : begin
        -0.10f, -2.50f, 0.0f,
        0.00f, -2.75f, 0.0f, // triangle 3 : end
        0.00f, -2.75f, 0.0f, // triangle 4 : begin
        0.00f, -2.50f, 0.0f, 
        -0.10f, -2.50f, 0.0f, //triangle 4 : end
        1.90f, -2.75f, 0.0f, // triangle 5 : begin
        1.90f, -2.50f, 0.0f,
        2.00f, -2.75f, 0.0f, // triangle 5 : end
        2.00f, -2.75f, 0.0f, // triangle 6 : begin
        2.00f, -2.50f, 0.0f, 
        1.90f, -2.50f, 0.0f, //triangle 6 : end

        3.90f, -2.75f, 0.0f, // triangle 5 : begin
        3.90f, -2.50f, 0.0f,
        4.00f, -2.75f, 0.0f, // triangle 5 : end
        4.00f, -2.75f, 0.0f, // triangle 6 : begin
        4.00f, -2.50f, 0.0f, 
        3.90f, -2.50f, 0.0f //triangle 6 : end

    };

    static const GLfloat vertex_buffer_data4[] = {
        -3.80f,-2.55f,0.0f, // triangle 1 : begin
        -3.80f,-2.70f, 0.0f,
        -2.30f, -2.70f, 0.0f, // triangle 1 : end
        -3.80f, -2.55f, 0.0f, // triangle 2 : begin
        -2.30f, -2.70f, 0.0f, 
        -2.30f, -2.55f, 0.0f, //triangle 2 : end
        -1.80f,-2.55f,0.0f, // triangle 1 : begin
        -1.80f,-2.70f, 0.0f,
        -0.30f, -2.70f, 0.0f, // triangle 1 : end
        -1.80f, -2.55f, 0.0f, // triangle 2 : begin
        -0.30f, -2.70f, 0.0f, 
        -0.30f, -2.55f, 0.0f, //triangle 2 : end
         0.20f,-2.55f,0.0f, // triangle 1 : begin
         0.20f,-2.70f, 0.0f,
         1.70f, -2.70f, 0.0f, // triangle 1 : end
         1.70f, -2.55f, 0.0f, // triangle 2 : begin
         1.70f, -2.70f, 0.0f, 
         0.20f, -2.55f, 0.0f, //triangle 2 : end
         2.20f,-2.55f,0.0f, // triangle 1 : begin
         2.20f,-2.70f, 0.0f,
         3.70f, -2.70f, 0.0f, // triangle 1 : end
         2.20f, -2.55f, 0.0f, // triangle 2 : begin
         3.70f, -2.70f, 0.0f, 
         3.70f, -2.55f, 0.0f, //triangle 2 : end
    };

    static const GLfloat vertex_buffer_data5[] = {
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

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_GREY, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data3, COLOR_TRAMPOLINE, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data4, COLOR_BLACK, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 20 * 3, vertex_buffer_data5, COLOR_GREY, GL_FILL);

}

void Platform::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
}

