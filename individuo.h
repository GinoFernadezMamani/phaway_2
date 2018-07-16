
class individuo
{

    bool derecha=true;
    bool derecha_p=false;
    bool no_salto=false;
    bool disparo=false;

    int velocidad_y=0,velocidad_x=5;
    int gravedad=1;
    int jumpspeed=17;
    int longDis=0;
    int death_long=0;
    int ang,gravedad_dis;
    int muertox,muertoy;
    int camara_pos=0;
    int num_frames=4,frame;
    int tiempo_frame = 100;
    SAMPLE* coin_s = load_sample("efeito.wav");
    BITMAP* rip = load_bitmap("rip.bmp",NULL);
    BITMAP* fantasma = load_bitmap("fantasma_inca.bmp",NULL);
    BITMAP* sprite[4]={load_bitmap("sprite_0.bmp", NULL),load_bitmap("sprite_1.bmp", NULL),load_bitmap("sprite_2.bmp", NULL),load_bitmap("sprite_3.bmp", NULL)};


public:
    bool death=false;
    int pos_xini;
    int pos_yini;
    int monedas=0;
    int vidas=3;
    void reset(){
        vidas=3;
        monedas=0;
    }
    void destruir(){
    destroy_bitmap(sprite[0]);
    destroy_bitmap(sprite[1]);
    destroy_bitmap(sprite[2]);
    destroy_bitmap(sprite[3]);
    }

    int pos_x,pos_y;

    int getVidas(){return vidas;}

    void setvidas(int x){vidas=x;}

    void setpos(int x,int y){pos_x=x,pos_y=y;}



    bool salto_t(){
    if (contador>500){
            contador=0;
            return true;
    }
    else
        return false;
    }
    bool cambio_mapa(BITMAP *buffer){
        if(pos_x>buffer->w+sprite[0]->w){
            pos_x=0;
            pos_y=0;
            return true;
            }
        else
            return false;
    }
    void muerto(BITMAP* buffer){
        //allegro_message("estas muerto!!!");
        muertox=pos_x;
        muertoy=pos_y;
      //  pos_x=0;
      //  pos_y=0;
        death=true;

    }
    void dibujar_fantasma(BITMAP* buffer)
    {
            draw_sprite(buffer,fantasma,pos_x,pos_y);

            if(death_long<150){
                death_long++;
                pos_y--;
            }
            else{
                death_long=0;
                death=false;
                pos_x=0;
                pos_y=0;
            }
    }
    void tumba(BITMAP* buffer)
    {
        draw_sprite(buffer,rip,muertox,muertoy+30);
    }


    void puntaje(BITMAP *buffer){
        textprintf_ex(buffer, font, camara_pos+10, 10, makecol(255, 255, 255), 0, "PHAWAY", pos_x);
        textprintf_ex(buffer, font,camara_pos+10, 30, makecol(255,255,255), 0, "Vidas: %d", vidas);
        textprintf_ex(buffer, font,camara_pos+10, 50, makecol(255,255,255), 0, "Monedas: %d", monedas);
        textprintf_ex(buffer, font,camara_pos+10, 70, makecol(255,255,255), 0, "Tiempo: %d", milisegundos/1000);
    }
    int camara(BITMAP *buffer){

        camara_pos=-(ancho/2.5)+pos_x;
        if (camara_pos<0)
            camara_pos=0;
        if (camara_pos > buffer->w - ancho)
            camara_pos = buffer->w - ancho;

        return camara_pos;
    }

    void disparar(BITMAP *buffer){
        if (!disparo){
            pos_xini=pos_x+60;
            pos_yini=pos_y+50;
            longDis=0;
            ang=0;
            if (derecha)
                derecha_p=true;
            else
                derecha_p=false;
            gravedad_dis=2;
            }
        if(xbox[BUTTON_B])
            disparo=true;
        if(disparo){
                if (derecha_p){
                    pos_xini+=longDis;
                    circlefill(buffer,pos_xini,pos_yini, 20,makecol(90,50,0));
                    }
                else{
                    pos_xini-=longDis;
                    circlefill(buffer,pos_xini,pos_yini, 20,makecol(90,50,0));
                    }
            ang-=gravedad_dis;
            pos_yini+=ang;
            longDis+=1;

        }
        if (ang<-10)
        {
            gravedad_dis=gravedad_dis*(-1);
        }
        if(longDis>25){
            disparo=false;
            }
    }

    void colision_enem(BITMAP *buffer,int canon_x,int canon_y,int sold_x,int sold_y)
    {
        if (collision(pos_x, pos_y+50, 40, 120, canon_x-20, canon_y, 40, 40))
        {
            muerto(buffer);
            vidas--;
        }
        if (collision(pos_x, pos_y, 40, 90, sold_x, sold_y, 40, 80))
        {
            muerto(buffer);
            vidas--;
        }

    }

    void movimiento(BITMAP *buffer,char block[][32]){
        xbox_input();

        frame = (milisegundos/tiempo_frame)%num_frames;

        disparar(buffer);

        if (!xbox[LSTICK_RIGHT])
        {
            if (derecha==true)
                draw_sprite(buffer,sprite[0],pos_x,pos_y);
        }

        if (xbox[LSTICK_RIGHT])
        {
           if(block[(pos_y+122)/80][(pos_x+69)/80]!='g' )
                pos_x += velocidad_x;

            draw_sprite(buffer,sprite[frame],pos_x,pos_y);
            derecha=true;

        }
        else if(xbox[LSTICK_LEFT])
        {
            if(block[(pos_y+122)/80][(pos_x)/80]!='g')
                pos_x -= velocidad_x;
            draw_sprite_h_flip(buffer,sprite[frame],pos_x,pos_y);
            derecha=false;
            if (pos_x<0)
                pos_x+=velocidad_x;

        }

        if (!xbox[LSTICK_LEFT])
        {
            if (derecha==false)
                draw_sprite_h_flip(buffer,sprite[0],pos_x,pos_y);

        }

        if((xbox[BUTTON_Y]) && no_salto && salto_t())
        {
            velocidad_y=-jumpspeed;
            no_salto=false;
        }

        if(block[(pos_y+125+velocidad_y)/80][(pos_x+50)/80]=='g' || block[(pos_y+125+velocidad_y)/80][(pos_x+15)/80]=='g'){
            no_salto=true;
        }
        else
        {
            no_salto=false;
        }

        if (!no_salto)
        {
            velocidad_y+=gravedad;
            pos_y+=velocidad_y;

        }

        else if (no_salto)
        {
            velocidad_y=0;
        }


        if(block[(pos_y+80)/80][(pos_x+30)/80]=='s')
        {
            muerto(buffer);
            vidas--;
        }

        else if(block[(pos_y+80)/80][(pos_x+30)/80]=='m')
        {
            block[(pos_y+80)/80][(pos_x+30)/80]='M';
            play_sample(coin_s, 500, 128, 1000, FALSE);
            monedas++;
        }
        tumba(buffer);
        rest(1);

    }


};
