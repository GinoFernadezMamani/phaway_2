class canonn{
    int pos_ini;
    int pos_x;
    int pos_y;
    int velocidad=4;
    SAMPLE* disparo = load_sample("disparo.wav");

public:
    int getpos(){
        return pos_x;
    }
    int getpos_y(){
        return pos_y;
    }
    canonn(char block[][32]){
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<32;j++)
            {
                 if (block[i][j]=='c'){
                    pos_x=(j*80)+10;
                    pos_ini=pos_x;
                    pos_y=(i*80)+27;}
            }
        }
    }
    void dibujar_bala(BITMAP *buffer, int pos){
        if(pos_x-pos<720 && pos_ini-pos>-100){
                circlefill(buffer,pos_x,pos_y, 20,makecol(0,0,0));
                pos_x-=velocidad;

        if (canon_cont>2){
            pos_x=pos_ini;
            canon_cont=0;
            play_sample(disparo, 500, 128, 1000, FALSE);}
        }

   }

};
