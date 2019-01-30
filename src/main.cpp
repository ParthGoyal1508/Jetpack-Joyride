#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "timer.h"
#include "ball.h"
#include "coin.h"
#include "platform.h"
#include "player.h"
#include "magnet.h"
#include "enemy.h"
#include "enemy1.h"
#include "shield.h"
#include "morecoins.h"
#include "enemy3.h"
#include "ring.h"
#include "dragon.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

vector<Ball> ball;
vector<Platform> platform;
Player player;
vector<Coin> coin;
Magnet m1;
Enemy1 e1;
Enemy e2;
Enemy3 e3;
Shield s;
Morecoins m;
Ring r;
vector<Coin> balloon;
Dragon d;
vector<Coin> bullet;


float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(0.5 / 60);

void platform_draw(glm::mat4 VP) {
    platform[0].draw(VP);
    platform[1].draw(VP);
    for(int i=0;i<16;i++){
        ball[i].draw(VP);
    }
}

void coin_draw(glm::mat4 VP){
    for(int i=0;i<coin.size();i++)
        coin[i].draw(VP);
}

void C_coin_create(double radius, double x, double y, color_t color){
    for(int i=0;i<5;i++){
        coin.push_back(Coin(x,y+i*2*radius,radius,color));
    }
    for(int i=1;i<4;i++){
        coin.push_back(Coin(x+i*2*radius,y,radius,color));
        coin.push_back(Coin(x+i*2*radius,y+8*radius,radius,color));
    }
}

void O_coin_create(double radius, double x, double y, color_t color){
    for(int i=0;i<5;i++){
        coin.push_back(Coin(x,y+i*2*radius,radius,color));
        coin.push_back(Coin(x+6*radius,y+i*2*radius,radius,color));
    }
    for(int i=1;i<3;i++){
        coin.push_back(Coin(x+i*2*radius,y,radius,color));
        coin.push_back(Coin(x+i*2*radius,y+8*radius,radius,color));
    }
}

void I_coin_create(double radius, double x, double y, color_t color){
    for(int i=0;i<5;i++){
        coin.push_back(Coin(x,y+i*2*radius,radius,color));
    }
}

void N_coin_create(double radius, double x, double y, color_t color){
    for(int i=0;i<5;i++){
        coin.push_back(Coin(x,y+i*2*radius,radius,color));
        coin.push_back(Coin(x+8*radius,y+i*2*radius,radius,color));
    }
    for(int i=1;i<4;i++){
        coin.push_back(Coin(x+i*2*radius,y+(8-(2*i))*radius,radius,color));
    }
}

void S_coin_create(double radius, double x, double y, color_t color){
    for(int i=0;i<4;i++){
        coin.push_back(Coin(x+2*i*radius,y,radius,color));
        coin.push_back(Coin(x+2*i*radius,y+4*radius,radius,color));
        coin.push_back(Coin(x+2*i*radius,y+8*radius,radius,color));
    }
        coin.push_back(Coin(x,y+6*radius,radius,color));
        coin.push_back(Coin(x+6*radius,y+2*radius,radius,color));
}

void coin_create(double radius, double x, double y,color_t color){
    C_coin_create(radius,x+0,y+0,color);
    O_coin_create(radius,x+2,y+0,color);
    I_coin_create(radius,x+4,y+0,color);
    N_coin_create(radius,x+5,y+0,color);
    S_coin_create(radius,x+7,y+0,color);
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int coin1_time = 10;
int coin2_time = 15;


void insert_coin(){
    double curr_time = glfwGetTime();
    int cur = round(curr_time);
    if(cur == coin1_time){
        coin1_time += 10;
        double a = fRand(6.00, 12.00);
        double b = fRand(-2.00, 2.00);
        coin_create(0.15, a, b, COLOR_YELLOW);
    }
    if(cur == coin2_time){
        coin2_time += 10;
        double a = fRand(6.00, 12.00);
        double b = fRand(-1.00, 2.00);
        coin_create(0.075, a, b, COLOR_BLUE);
    }
}

void reinsert_platform(){
    if(platform[0].position.x < -7.8){
        platform.erase(platform.begin()+0);
        platform.push_back(Platform(8.0,0.00, COLOR_RED));
        for(int i=0;i<8;i++){
            ball.erase(ball.begin()+0);
        }
        double x = platform[1].position.x - 2.05;
        for(int i=8;i<16;i+=2){
            ball.push_back(Ball(x, -2.60, COLOR_BLACK));
            ball.push_back(Ball(x, -2.68, COLOR_BLACK));
            x += 2.00;
        }
    }
}

void magnet_player_attraction(){
    if(player.position.x > m1.position.x)
        player.position.x -= 0.02;
    if(player.position.x < m1.position.x)
        player.position.x += 0.02;

    if(player.position.y < m1.position.y){
        player.position.y += 0.2;
        player.velocity_y = 0;
        if(player.position.y > 3.75){
            player.position.y = 3.75;
        }
    }
    if(player.position.y > m1.position.y){
        player.position.y -= 0.02;
        if(player.position.y <= -1.65)
            player.position.y = -1.65;
    }
}

void magnet_draw(glm::mat4 VP){
    double curr_time = glfwGetTime();
    int cur = round(curr_time);
    if(cur == m1.start_time ){
        m1.alive = 1;
    }
    if(m1.alive == 1){
            m1.draw(VP);
            magnet_player_attraction();
    }
    if(cur == m1.end_time){
        m1.start_time += 20;
        m1.end_time += 20;
        m1.alive = 0;
        double x = fRand(-2.00,2.00);
        double y = fRand(-2.00,3.00);
        m1.move_magnet(x, y);
    }
}

bool detect_enemy1_collision(){
    for(float r=-1.00;r<=1.00;r+=0.01){
        float x = e1.position.x+r*cos(e1.rotation);
        float y = e1.position.y+r*sin(e1.rotation);
        if(x >=player.position.x && x <= player.position.x+0.25 && y<= player.position.y && y>=player.position.y-0.85)
            return true;
    }
    return false;
}

void enemy1_draw(glm::mat4 VP){
    int cur = round(glfwGetTime());
    
    if(cur == e1.start_time){
        e1.alive = 1;
    }

    if(e1.alive == 1){
        e1.draw(VP);
        if(detect_enemy1_collision() && player.shield == 0 && player.shield2 ==0){
            player.score -= 1;
            if(player.score <= 0 ){
                cout <<"GAMEOVER, YOU ARE DEAD\n";
                quit(window);
            }
        }
    }

    if(cur == e1.end_time){
        e1.start_time += 10;
        e1.end_time += 10;
        e1.alive = 0;
        // double x = fRand(-2.00,2.00);
        // double y = fRand(-2.00,3.00);
        e1.set_position(12.00, 2.00);
        double rotn = fRand(-90.00, 90.00);
        e1.rotation = rotn;
    }
}

bool detect_enemy2_collision(){
    if(e2.line1_alive == 1){
        bool a = abs((player.position.x+0.125) - (e2.position.x)) * 2 < (5.5+0.25);
        bool b = abs((player.position.y-0.425) - (e2.position.y -1.85)) * 2 < (0.85+0.2);
        return a && b; 
    }
     if(e2.line2_alive == 1){
        bool a = abs((player.position.x+0.125) - (e2.position.x)) * 2 < (5.5+0.25);
        bool b = abs((player.position.y-0.425) - (e2.position.y +0.75)) * 2 < (0.85+0.2);
        return a && b; 
    }
     if(e2.line3_alive == 1){
        bool a = abs((player.position.x+0.125) - (e2.position.x)) * 2 < (5.5+0.25);
        bool b = abs((player.position.y-0.425) - (e2.position.y +3.35)) * 2 < (0.85+0.2);
        return a && b; 
    }
    return false;
}

void enemy2_draw(glm::mat4 VP){
    double curr_time = glfwGetTime();
    int cur = round(curr_time);

    if(cur == e2.start_time){
        e2.alive = 1;
    }

    if(cur == e2.start_time + 1){
        e2.triangle1_alive = 1;
    }

    if(cur == e2.start_time + 2){
        e2.line1_alive = 1;
    }

    if(cur == e2.start_time + 4){
        e2.line1_alive = 0;
        e2.triangle1_alive = 0;
        e2.triangle2_alive = 1;
    }

    if(cur == e2.start_time + 5){
        e2.line2_alive = 1;
    }

    if(cur == e2.start_time + 7){
        e2.line2_alive = 0;
        e2.triangle2_alive = 0;
        e2.triangle3_alive = 1;
    }

    if(cur == e2.start_time + 8){
        e2.line3_alive = 1;
    }

    if(cur == e2.start_time + 10){
        e2.line3_alive = 0;
        e2.triangle3_alive = 0;
        e2.alive = 0;
    }

    if(e2.alive == 1){
        e2.draw(VP);
        if(detect_enemy2_collision() && player.shield == 0 && player.shield2 ==0 ){
            player.score -= 2;
            if(player.score <=0){
                cout <<"GAMEOVER, YOU ARE DEAD\n";
                quit(window);
            }
        }
    } 
    
    if(cur == e2.end_time){
        e2.alive = 0;
        e2.start_time += 60;
        e2.end_time += 60;
    }
}


bool shield_collision(){
    return (abs(player.position.x - s.position.x) * 2 < (0.25 + 0.4)) &&
           (abs(player.position.y - s.position.y) * 2 < (0.85 + 1));
}

void shield_draw(glm::mat4 VP){
    double curr_time = glfwGetTime();
    int cur = round(curr_time);

    if( cur == s.start_time){
        s.alive = 1;
        s.start_time += 40; 
    }
    
    if(cur == s.time + 10){
        player.shield = 0;
    }

    if(s.alive == 1){
        s.move();
        s.draw(VP);
        if(shield_collision()){
            system( "aplay -c 1 -t wav -q ./sound/achievement_complete.wav&");
            player.shield = 1;
            s.time = round(glfwGetTime());
            s.alive = 0;
        }
    }

    if(cur == s.end_time){
        s.end_time += 40;
        s.alive = 0;
        s.set_position(-3.75,2.0);
    }
}


bool morecoins_collision(){
    return (abs(player.position.x + 0.125 - m.position.x) * 2 < (0.25 + 0.8)) &&
           (abs(player.position.y -0.425 - m.position.y) * 2 < (0.85 + 1));
}

void morecoins_draw(glm::mat4 VP){
    double curr_time = glfwGetTime();
    int cur = round(curr_time);

    if(cur == m.start_time){
        m.alive = 1;
        m.start_time += 50;
    }

    if(m.alive == 1){
        m.move();
        m.draw(VP);
        if(morecoins_collision()){
            system( "aplay -c 1 -t wav -q ./sound/coin_pickup_1.wav&");
            player.score = player.score + 100;
            m.alive = 0;
        }
    }   

    if(cur == m.end_time){
        m.alive = 0;
        m.end_time += 50;
        m.set_position(-3.60,-2.0);
    }
}

bool enemy3_detectcollision(){
    return (abs(player.position.x + 0.125 - e3.position.x) * 2 < (0.25 + 0.4)) &&
           (abs(player.position.y -0.425 - e3.position.y) * 2 < (0.85 + 0.5));
}

void enemy3_draw(glm::mat4 VP){
    double curr_time = glfwGetTime();
    int cur = round(curr_time);

    if(cur == e3.start_time){
        e3.alive = 1;
        e3.start_time += 55;
    }

    if(e3.alive == 1){
        e3.move();
        e3.draw(VP);
        if(enemy3_detectcollision() && player.shield == 0 && player.shield2 == 0){
            player.score -= 5;
            if(player.score <= 0){
                cout <<"GAMEOVER, YOU ARE DEAD\n";
                quit(window);
            }
        }
    }

    if(cur == e3.end_time){
        e3.alive = 0;
        e3.end_time += 55;
        e3.set_position(3.6,3.4);
    }
}


bool detect_ring_collision(){
    bool x_collision;
    bool y_collision;
   
    if((player.position.x + 0.05 > r.position.x-1.1) && (player.position.x + 0.275 > r.position.x-1.1))
        x_collision = false;
    else if((player.position.x + 0.05 < r.position.x-1.35) && (player.position.x + 0.275 < r.position.x-1.35))
        x_collision = false;
    else 
        x_collision = true;
   
    if(player.position.y-0.85 > r.position.y)
        y_collision = false;
    else if(player.position.y < r.position.y - 0.02 )
        y_collision = false;
    else
        y_collision = true;
    
    if(x_collision && y_collision)
        return true;
    else
        return false;

}

void player_ring_motion(){
    if(player.position.x +0.05 >= r.position.x + 1.1){
        player.semicircularmotion = 0;
        player.shield2 = 0;
    }
    if (player.semicircularmotion == 1){
        player.position.x += 0.03;
        player.position.y = r.position.y - sqrt((1.1)*(1.1) -(player.position.x - r.position.x) * (player.position.x - r.position.x)) + 0.15;
    }
} 

void ring_draw(glm::mat4 VP){
    double curr_time = glfwGetTime();
    int cur = round(curr_time);

    if(detect_ring_collision()){
        player.position.x = r.position.x -1.10 - 0.05;
        player.position.y = r.position.y + 0.85 ;
        player.shield2 = 1;
        player.semicircularmotion = 1;
    }
    r.draw(VP);

    if(cur == r.end_time){
        r.start_time += 60;
        r.end_time += 60;
        r.set_position(8,-0.7);
    }
}

bool detect_collision(Player a, Coin b) {
    return (abs(a.position.x - b.position.x) * 2 < (0.25 + 2*b.radius)) &&
           (abs(a.position.y - b.position.y) * 2 < (0.85 + 2*b.radius));
}

void coin_collect(){
    for(int i=0;i<coin.size();i++){
        bool val = detect_collision (player, coin[i]);
        if(val){
            if(coin[i].radius >= 0.1){
                player.score += 1;
            }
            else if(coin[i].radius >= 0.07 && coin[i].radius < 0.1){
                player.score += 2;
            }
            coin.erase(coin.begin()+i);
        }
    }
}

void platform_moveleft(){
    platform[0].position.x -= 0.02;
    platform[1].position.x -= 0.02;
    for(int i=0; i<16;i++)
        ball[i].move_left(0.02);
    for(int i=0;i<coin.size();i++)
        coin[i].move_left(0.02);
    e1.move_left(0.02);
    r.move_ring(0.02);
    if(d.alive == 1)
        d.move_left(0.01);
}

bool check_collision_enemy1(Coin balloon){
    if((balloon.position.x >= e1.position.x - 1.0) && (balloon.position.x <= e1.position.x + 1.0 )){
        if((balloon.position.y >= e1.position.y - 1.0) &&(balloon.position.y <= e1.position.y + 1.0 )){
            float m = tan(e1.rotation);
            if( abs(m *(balloon.position.x) - (balloon.position.y) +(e1.position.y) - (m * e1.position.x))/ sqrt(m*m + 1) <= 0.2)
                return true;
        }
    }
    return false;
}

void balloon_enemy1_collision(){
    for(int i=0;i<balloon.size();i++){
        if(e1.alive == 1 && check_collision_enemy1(balloon[i])){
            e1.alive = 0;
            balloon.erase(balloon.begin()+i);
        }
    }
}

bool enemy_balloon_line1collision(Coin ballon){
        bool x_collision = false;    
        bool y_collision = false;
        if((ballon.position.x >= e2.position.x -2.95) && (ballon.position.x <= e2.position.x +2.95))
            x_collision = true;
        if((ballon.position.y <= e2.position.y - 1.65) && (ballon.position.y >= e2.position.y - 1.95))
            y_collision = true;  
        return (x_collision && y_collision);  
}

bool enemy_balloon_line2collision(Coin ballon){
        bool x_collision = false;    
        bool y_collision = false;
        if((ballon.position.x >= e2.position.x -2.95) && (ballon.position.x <= e2.position.x +2.95))
            x_collision = true;
        if((ballon.position.y <= e2.position.y + 0.95) && (ballon.position.y >= e2.position.y + 0.55))
            y_collision = true;  
        return (x_collision && y_collision);  
}

bool enemy_balloon_line3collision(Coin ballon){
        bool x_collision = false;    
        bool y_collision = false;
        if((ballon.position.x >= e2.position.x -2.95) && (ballon.position.x <= e2.position.x +2.95))
            x_collision = true;
        if((ballon.position.y <= e2.position.y + 3.55) && (ballon.position.y >= e2.position.y + 3.15))
            y_collision = true;  
        return (x_collision && y_collision);  
}

void balloon_enemy2_collision(){
    for(int i=0;i<balloon.size();i++){
        if(e2.line1_alive == 1 && enemy_balloon_line1collision(balloon[i])){
            e2.line1_alive = 0;
            balloon.erase(balloon.begin()+i);
        }
        if(e2.line2_alive == 1 && enemy_balloon_line2collision(balloon[i])){
            e2.line2_alive = 0;
            balloon.erase(balloon.begin()+i);
        }
        if(e2.line3_alive == 1 && enemy_balloon_line3collision(balloon[i])){
            e2.line3_alive = 0;    
            balloon.erase(balloon.begin()+i);
        }
    }
}

void balloon_draw(glm::mat4 VP){
    for(int i=0;i<balloon.size();i++){
        balloon[i].draw(VP);
    }
}

void bullet_draw(glm::mat4 VP){
    for(int i=0;i<bullet.size();i++){
        bullet[i].move_left(0.01) ;
        bullet[i].draw(VP);
    }
}

void dragon_move(){
    if(player.position.y > d.position.y){
        d.position.y += 0.01;
        if(d.position.y > 2.75)
            d.position.y =2.75;
    }
    else{
        d.position.y -= 0.01;
        if(d.position.y < -1.24)
            d.position.y = -1.24;
    }
    if(player.position.x < d.position.x){
        d.position.x -= 0.01;
    }
}

void dragon_release_bullet(){
    if(d.position.x > player.position.x && d.position.x < 4.0){
        Coin ball =Coin(d.position.x - 0.95, d.position.y+0.95, 0.1, COLOR_BLACK);
        ball.velocity_x = 0.05;
        ball.velocity_y = 0.05;
        bullet.push_back(ball);
    }
}

int release_time;
void dragon_draw(glm::mat4 VP){
    double curr_time = glfwGetTime();
    int cur = round(curr_time);

    if(cur == d.start_time){
        d.alive = 1;
        release_time = cur;
        d.start_time += 90; 
    }

    if(d.alive == 1){
        d.draw(VP);
        dragon_move();
        if( cur == release_time){
            release_time += 1;
            dragon_release_bullet();
        }
    }

    if(cur == d.end_time){
        d.end_time += 90;
        d.alive = 0;
        d.set_position(8, 0);
    }
    
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (0, 0, 1 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    
    platform_draw(VP);
    coin_draw(VP);
    magnet_draw(VP);
    enemy1_draw(VP);
    enemy2_draw(VP);
    shield_draw(VP);
    morecoins_draw(VP);
    enemy3_draw(VP);
    ring_draw(VP);
    balloon_draw(VP);
    dragon_draw(VP);
    bullet_draw(VP);
    player.draw(VP);
}



void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int b = glfwGetKey(window, GLFW_KEY_B);

    if (left) {
        if(player.position.x > -3.84){
            player.position.x -= 0.02;
        }
    }
    if (right) {
        if(player.position.x <= 0 ){
            player.position.x += 0.02;
        }
        else if(player.position.x > 0){
           platform_moveleft();
        }
    }
    if (space) {
        system( "aplay -c 1 -t wav -q ./sound/pig_coin_1.wav&");
        if(player.position.y < 3.75){
            player.position.y += 0.2;
            player.velocity_y = 0.02;
        }
        else if(player.position.y >= 3.75){
           platform_moveleft();
        }
    }
    if (b) {
        Coin ball =Coin(player.position.x+0.125, player.position.y, 0.1, COLOR_BLUE);
        ball.velocity_x = 0.1;
        ball.velocity_y = 0.05;
        balloon.push_back(ball);
    }
}



void player_gravity(){
    if(player.position.y > -1.64){
        player.position.y -= player.velocity_y;
        player.velocity_y += 0.005;
        platform_moveleft();
        if(player.position.y < -1.65){
            player.position.y =-1.65;
        }
    }
}

void balloon_gravity(){
    for(int i=0;i<balloon.size();i++){
        balloon[i].position.x += balloon[i].velocity_x;
        if(balloon[i].position.y > -2.50){
            balloon[i].position.y += balloon[i].velocity_y;
            balloon[i].velocity_y -= 0.005;
        }
        if(balloon[i].position.y < -2.50){
            balloon.erase(balloon.begin()+i);
        }
    }
}

void bullet_gravity(){
    for(int i=0;i<bullet.size();i++){
        bullet[i].position.x -= bullet[i].velocity_x;
        if(bullet[i].position.y > -2.50){
            bullet[i].position.y += bullet[i].velocity_y;
            bullet[i].velocity_y -= 0.005;
        }
        if(bullet[i].position.y < -2.50){
            bullet.erase(bullet.begin()+i);
        }
    }
}

bool player_bullet_collision(Coin bullet){

    if((bullet.position.x >= player.position.x -0.1) && (bullet.position.x <=player.position.x + 0.1 + 0.25)){
        if((bullet.position.y <= player.position.y + 0.1) && (bullet.position.y >= player.position.y - 0.85 - 0.1))
            return true;
    }
    return false;
}

void bullet_player_collision(){
    for(int i=0;i<bullet.size();i++){
        if(player_bullet_collision(bullet[i]) && player.shield == 0 && player.shield2 == 0){
                player.score -= 20;
                if(player.score <=0){
                cout <<"GAMEOVER, YOU ARE DEAD\n";
                quit(window);
                bullet.erase(bullet.begin()+i);
            }
        }
    }
}

bool dragon_player_collison(){
    if((player.position.x >= d.position.x -1 -0.25) && (player.position.x <= d.position.x +1)){
        if((player.position.y >= d.position.y - 1.25 -0.85) && (player.position.y <= d.position.y +1.25))
            return true;
    }
    return false;
}

void player_dragon_collision(){
    if(d.alive==1 && player.shield == 0 && player.shield2 ==0){
        if(dragon_player_collison()){
            player.score -= 5;
            if(player.score <=0){
            cout <<"GAMEOVER, YOU ARE DEAD\n";
            quit(window);
            }   
        }
    }
}

void tick_elements() {
    if(player.semicircularmotion == 0)
        player_gravity();
    coin_collect();
    reinsert_platform();
    player_ring_motion();
    balloon_gravity();
    balloon_enemy1_collision();
    balloon_enemy2_collision();
    bullet_player_collision();
    player_dragon_collision();
    insert_coin();
    bullet_gravity();
    draw();
}

void create_platform(){
    platform.push_back(Platform(0.00, 0.00, COLOR_RED)); 
    platform.push_back(Platform(8.00, 0.00, COLOR_RED)); 
    double x =platform[0].position.x -2.05;
    for(int i=0;i<8;i+=2){
        ball.push_back(Ball(x, -2.60, COLOR_BLACK));
        ball.push_back(Ball(x, -2.68, COLOR_BLACK));
        x += 2.00;
    }
    x = platform[1].position.x -2.05;
    for(int i=8;i<16;i+=2){
        ball.push_back(Ball(x, -2.60, COLOR_BLACK));
        ball.push_back(Ball(x, -2.68, COLOR_BLACK));
        x += 2.00;
    }
    double a = fRand(0.00, 9.45);
    double b = fRand(-0.5, 1.5);
    coin_create(0.15, a, b, COLOR_YELLOW);

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    create_platform();

    player = Player(-2.00,-1.65, COLOR_BLUE);

    m1 = Magnet(0, 0, COLOR_MAGNET, -90);
    m1.start_time = 8;
    m1.end_time = 11;

    e1 = Enemy1(0,1, COLOR_BROWN, 45);
    e1.start_time = 5;
    e1.end_time = 9;
    // cout << e1.position.x -cos(e1.rotation) << e1.position.x + cos(e1.rotation) <<endl;
    // cout << e1.position.y -sin(e1.rotation) << e1.position.y + sin(e1.rotation) <<endl;
    
    e2= Enemy(0,0, COLOR_BLACK);
    e2.start_time = 12;
    e2.end_time = 22;

    s = Shield(-3.75,2.0,COLOR_CYAN);
    s.start_time = 28;
    s.end_time = 32;

    m = Morecoins(-3.6, -2.0);
    m.start_time = 42;
    m.end_time = 46;

    e3 = Enemy3(3.6, 3.4);
    e3.start_time = 30;
    e3.end_time = 39;

    r = Ring(8,-0.7,COLOR_BLUE,0);
    
    d= Dragon(8,0);
    d.start_time = 50;
    d.end_time = 70;


    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (0.5f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}



int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1500;
    int height = 900;

    window = initGLFW(width, height);

    initGL (window, width, height);


    

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands

            tick_elements();
            
            char str1[30];
            sprintf(str1, "%d", player.score % 500);
            char final_str[120] = "Score : ";
            strcat(final_str, str1);

            char str2[10];
            sprintf(str2, "%d", (player.score / 500));
            strcat(final_str, "      Lives : ");
            strcat(final_str, str2);

            glfwSetWindowTitle(window, final_str);

            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // update();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}



void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
