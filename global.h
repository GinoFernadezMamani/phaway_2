#include <allegro.h>
#include <iostream>
#include "mando.h"
using namespace std;
int ancho=720,alto=480;

volatile int ticks=0;
void tick_counter() { ticks++; }
END_OF_FUNCTION(tick_counter)

int milisegundos;
void msec_counter() { milisegundos++; }
LOCK_VARIABLE(milisegundos)

int contador;
void salto_time(){contador++;}
LOCK_VARIABLE(contador);

int canon_cont;
void canon_time(){canon_cont++;}
LOCK_VARIABLE(canon_cont);


void install()
{
    allegro_init();
    install_keyboard();
    install_joystick(JOY_TYPE_AUTODETECT);
    install_timer();
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,ancho,alto,0,0);
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_window_title("PHAWAY");

    install_int_ex(msec_counter, MSEC_TO_TIMER(1));
    END_OF_FUNCTION(msec_counter);
    LOCK_FUNCTION(msec_counter);

    install_int_ex(salto_time, MSEC_TO_TIMER(1));
    END_OF_FUNCTION(salto_time);
    LOCK_FUNCTION(salto_time);

    install_int_ex(canon_time, SECS_TO_TIMER(1));
    END_OF_FUNCTION(canon_time);
    LOCK_FUNCTION(canon_time);

    LOCK_FUNCTION(tick_counter);
    LOCK_VARIABLE(ticks);
    install_int_ex(tick_counter, BPS_TO_TIMER(60));

}
bool collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h)
{
    if ((b1_x > b2_x + b2_w - 1) ||
        (b1_y > b2_y + b2_h - 1) ||
        (b2_x > b1_x + b1_w - 1) ||
        (b2_y > b1_y + b1_h - 1))
    {

        return false;
    }
    return true;
}



