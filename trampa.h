class trampa{

    int pos_x;
    int pos_y;
    int velocidad=4;
    bool caer=false;
    int block_i=0;
    int block_j=0;


public:
    BITMAP *S_trampa=load_bitmap("trampa.bmp",NULL);

    trampa(char block[][32]){
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<32;j++)
                {
                    if (block[i][j]=='r'){
                        pos_x=j*80;
                        pos_y=i*80;
                       // block_i=i;
                        //block_
                    }
            }
        }
    }
    void dibujar(BITMAP* buffer,int pos_x1,char block[][32])
    {
        if(pos_x1>pos_x){
            caer=true;
            block[pos_y/80][pos_x/80]='R';
        }
        if(caer)
        {
            draw_sprite(buffer,S_trampa,pos_x,pos_y+velocidad);
            velocidad+=4;
        }
        if(velocidad>240)
            caer=false;
    }

};
