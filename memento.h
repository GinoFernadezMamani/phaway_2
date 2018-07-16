class Memento
{
private:
    friend class individuo;
    int vida;
    int moneda;
public:
    Memento(int x=0,int y=0)
    {
        vida=x;
        moneda=y;
    }
    void setmemento(int x,int y){
        vida=x;
        moneda=y;
    }

    void getmemento(int &x,int &y)
    {
        x=vida;
        y=moneda;
    }
};
