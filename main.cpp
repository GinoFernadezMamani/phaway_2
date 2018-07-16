#include "global.h"
#include "mapa.h"
#include "individuo.h"
#include "soldado.h"
#include "canon.h"
#include "trampa.h"
//#include "mando.h"
int main()
{
    install();

    mapa B;
    B.dibujar_bloques();
    individuo A;
    A.setpos(0,0);

    MIDI* musica=load_midi("Craw.mid");
    MIDI* music=load_midi("the.mid");

    canonn C(B.block);
    soldado D(B.block);
    play_midi(musica,TRUE);
    trampa T(B.block);

    while(!key[KEY_ESC])
    {

        /*while(ticks>0 && !key[KEY_ESC])
        {

            ticks--;
            cout<<ticks<<endl;
        }*/
            B.inicio();

            if(A.cambio_mapa(B.buffer)){
                B.num_mapa++;
                stop_midi();
                play_midi(music,TRUE);
                B.reset();
                D.muerto=false;
                D.setpos();
                if (B.num_mapa>2)
                    B.GameWin();
            }
            B.fondo(B.num_mapa);
            A.puntaje(B.buffer);
            B.cambio_mapa();
     //       cout<<contador<<endl;
            B.dibujar_bloques();
            C.dibujar_bala(B.buffer,A.pos_x);
            D.dibujar_sold(B.buffer,A.pos_xini,A.pos_yini);
            B.vida_extra(A.monedas,A.vidas);
            if (A.death)
                A.dibujar_fantasma(B.buffer);
            else{
                A.movimiento(B.buffer,B.block);
//                T.dibujar(B.buffer,A.pos_x,B.block);
                A.colision_enem(B.buffer,C.getpos(),C.getpos_y(),D.getpos(),D.getpos_y());
                if(B.GameOv(A.getVidas())){
                    A.reset();
                    B.reset();
                    milisegundos=0;
                }
            }
            blit(B.buffer,screen,A.camara(B.buffer),0,0,0,ancho,alto);
            //rest(1);


    }
    B.destruir();
    A.destruir();
    stop_midi();
    return 0;
}
END_OF_MAIN();
