
class soldado{
    int pos_ini;
    int pos_x;
    int pos_y;
    int velocidad=3;
    int pasos=0;
    int derecha=1;
    BITMAP *sold=load_bitmap("soldado.bmp",NULL);

public:
    bool muerto=false;
    soldado(char block[][32]){
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<32;j++)
            {
                 if (block[i][j]=='k'){
                    pos_x=(j*80)+10;
                    pos_ini=pos_x;
                    pos_y=(i*80)-40;
                }
            }
        }
    }
    int getpos(){
        return pos_x;
    }
    int getpos_y(){
        return pos_y;
    }
    void setpos(){
        pos_x=pos_ini;
    }
    void dibujar_sold(BITMAP *buffer,int pos_xini,int pos_yini){

        if (collision(pos_x, pos_y, 40, 90, pos_xini, pos_yini, 40, 40)==false && muerto==false){
            if(derecha==-1){
                draw_sprite(buffer,sold,pos_x,pos_y);
                pos_x-=velocidad;
                pasos+=velocidad;
            }
            else
            {
                draw_sprite_h_flip(buffer,sold,pos_x,pos_y);
                pasos+=velocidad;
                pos_x+=velocidad;
            }
            if (pasos>400)
            {
                derecha=derecha*(-1);
                pasos=0;
            }
        }
        else{
            muerto=true;
            pos_x=-200;
            //allegro_message("muerto");
        }
   }

};
