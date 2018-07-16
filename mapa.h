
class mapa
{
    BITMAP *scroll[3]={load_bitmap("machu.bmp",NULL),load_bitmap("machu2.bmp",NULL),load_bitmap("machu.bmp",NULL)};
    BITMAP *grass=load_bitmap("grass.bmp",NULL);
    BITMAP *bloque=load_bitmap("bloque.bmp",NULL);
    BITMAP *spike=load_bitmap("spike.bmp",NULL);
    BITMAP *canon=load_bitmap("canon.bmp",NULL);
    BITMAP *terra=load_bitmap("terra.bmp",NULL);
    BITMAP *coin=load_bitmap("coin.bmp",NULL);
    BITMAP *trampa=load_bitmap("trampa.bmp",NULL);
    BITMAP *GameOver=load_bitmap("Game.bmp",NULL);
    BITMAP *GameBe=load_bitmap("inicio.bmp",NULL);
    BITMAP *win=load_bitmap("win.bmp",NULL);


    int filas=31;
    int columnas=8;
    bool P_inicio=true;

public:
    BITMAP *buffer=create_bitmap(scroll[0]->w,screen->h);
    int num_mapa=0;
    int num_monedas=5;
    void vida_extra(int &monedas,int &vidas)
    {
        if(num_monedas==monedas){
            vidas++;
            monedas=0;
        }
    }
    void destruir(){
        destroy_bitmap(scroll[0]);
        destroy_bitmap(scroll[1]);
        destroy_bitmap(grass);
        destroy_bitmap(bloque);
        destroy_bitmap(spike);
        destroy_bitmap(canon);
        destroy_bitmap(terra);
        destroy_bitmap(coin);
        destroy_bitmap(GameOver);
        destroy_bitmap(GameBe);
        destroy_bitmap(win);

    }

    char block1[6][32]={
    "oooooooooooooooooooooooooooooo",
    "oooooooooooogoooooooooooooooom",
    "ooooooooooooooooooooooooooooog",
    "oooooooooooooooooooooooooooogt",
    "ooooooooogogogooooookoooocoott",
    "gggggsggsssssssggggggggggggggg"
    };
    char block2[6][32]={
    "oooooooooooooooooooooooooooooo",
    "oooooooooooooooooooooooooooooo",
    "oooooooooooooooooooooosooooooo",
    "oooooomooggggooooooooooooooooo",
    "ooooosgsgttttsmoooookoooocmoog",
    "ggggggggtttttggggggggggsgsgggt"
    };
    char block3[6][32]={
    "oooooooooooooooooooooooooooooo",
    "oooooooooooooooooooooooooooooo",
    "oooooooooooooooooooooosooooooo",
    "oooooomooggggooooooooooooooooo",
    "ooooosgsgttttsmoooookooooomoog",
    "ggggggggtttttggggggggggsgsgggt"
    };
    char (*block)[32]=block1;
    void cambio_mapa(){
        if (num_mapa==1)
        {
        block=block2;
        }
        if (num_mapa==2)
        {
        block=block3;
        }
    }


    void fondo(int x){draw_sprite(buffer,scroll[x],0,0);}
    void reset(){
        for(int i=0;i<columnas;i++)
        {
            for(int j=0;j<filas;j++)
            {
                if(block[i][j]=='M')
                    block[i][j]='m';
            }
        }

    }
    void GameWin(){
        while(!key[KEY_ESC]){
            draw_sprite(buffer,win,0,0);
            blit(buffer,screen,0,0,0,0,ancho,alto);
        }
    }
    void inicio(){
        while(P_inicio)
        {
            draw_sprite(buffer,GameBe,0,0);
            blit(buffer,screen,0,0,0,0,ancho,alto);
            if(xbox[LSTICK_DOWN] || key[KEY_F])
                P_inicio=false;
        }
    }

    bool GameOv(int vidas){
        if(vidas<1 || (milisegundos/1000)>5){
            while(vidas<1 || (milisegundos/1000)>60)
            {
                draw_sprite(buffer,GameOver,0,0);
                blit(buffer,screen,0,0,0,0,ancho-1,alto-1);
                if(key[KEY_R])
                    return true;
            }
        }
        return false;
    }
    void dibujar_bloques(){
            for(int i=0;i<columnas;i++)
            {
                for(int j=0;j<filas;j++)
                {
                    if(block[i][j]=='g'){
                        draw_sprite(buffer,grass,j*80, i*80);
                    }
                    else if (block[i][j]=='b'){
                        draw_sprite(buffer,bloque,j*80, i*80);
                    }
                    else if (block[i][j]=='s'){
                        draw_sprite(buffer,spike,j*80, i*80);
                    }
                    else if (block[i][j]=='c'){
                        draw_sprite(buffer,canon,j*80, i*80);
                    }
                    else if (block[i][j]=='t'){
                        draw_sprite(buffer,terra,j*80, i*80);
                    }
                    else if (block[i][j]=='m'){
                        draw_sprite(buffer,coin,j*80, i*80);
                    }
                    else if (block[i][j]=='r'){
                        draw_sprite(buffer,trampa,j*80, i*80);
                    }

                }
            }

    }

};
