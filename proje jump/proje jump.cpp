#include <stdio.h>
#include<stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include <math.h>

float x = 120;
float y = 500;
float velocityX;
float velocityY = 0;
float acc = 9.8;
int r = 10;
int anahtarx1 = 520;
int anahtary1 = 550;

void setup() {

    al_draw_filled_circle(x, y, r, al_map_rgb(255, 255, 255));

}

void update_vel_pos0(double dt) {

  
    velocityY = velocityY + acc * dt;
    y = y + (velocityY * dt) + 0.5 * acc * (dt * dt);

}
void update_vel_pos1(double dt,float velocityX) {
    velocityX = 25;
    velocityY = velocityY + acc * dt;
    x = x + (velocityX * dt);
    y = y + (velocityY * dt) + 0.5 * acc * (dt * dt);

}

void update_vel_pos2(double dt) {
    velocityX = 25;
    velocityY = velocityY + acc * dt;
    x = x + (-velocityX * dt);
    y = y + (velocityY * dt) + 0.5 * acc * (dt * dt);
   
}


void collision() {

    if (y + 10 >= 600) {

        velocityY = -velocityY;
        
    }

}

void collision_up() {

    if (y - 10 >= 0) {

        velocityY = -velocityY;

    }

}

void destroy_wall(float x1,float y1,float x2,float y2) {


    for (int j = 0; j < 2; j++) {

        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 255, 255));


        if (y1-10 >= 0) {

            velocityY = -velocityY;

            float i;
            i = x2 - x1;
            x2 = x2 - (i / 3);
        }
         
    }

}
int main() {

    al_init_primitives_addon();

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* queue = NULL;


    al_init();
    al_install_keyboard();
    al_install_mouse();

    display = al_create_display(600, 600);
    queue = al_create_event_queue();
   

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    int direction = 1;
   
    double previous_time = 0;
    double current_time = al_current_time();


    while (1) {

        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);
      
        al_clear_to_color(al_map_rgb(0, 0, 0));
     

        previous_time = current_time;
        current_time = al_current_time();

        double dt = current_time - previous_time;

        if (dt > 0.005) {
            dt = 0.005;
        }

        float x1 = 80;
        float y1 = 590;
        float x2 = 160;
        float y2 = 600;

        float a1 = 180;
        float b1 = 590;
        float a2 = 260;
        float b2 = 600;

        float c1 = 280;
        float d1 = 590;
        float c2 = 360;
        float d2 = 600;

        float e1 = 380;
        float f1 = 590;
        float e2 = 460;
        float f2 = 600;

        do {
          
            destroy_wall(x1, y1, x2, y2);
            destroy_wall(a1, b1, a2, b2);
            destroy_wall(c1, d1, c2, d2);
            destroy_wall(e1, f1, e2, f2);
     
            update_vel_pos0(dt);
            collision();

            setup();

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));


            if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                update_vel_pos1(dt,velocityX);
                collision();
                setup();
                al_flip_display();

            }


            else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                update_vel_pos2(dt);
                collision();
                setup();
                al_flip_display();

            }

            else if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
                y -= 10;
                collision_up();
                setup();
                al_flip_display();

            }

            al_draw_filled_rectangle(anahtarx1, anahtary1, anahtarx1+20, anahtary1+20, al_map_rgb(255, 255, 255));

            if (anahtarx1 - r < 10 && anahtary1 - r < 10) {
                
                printf("end of the level");
                system("pause");
            }



        } while (al_is_event_queue_empty(queue));


       
        al_flip_display();
    }

    
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    return 0;
}