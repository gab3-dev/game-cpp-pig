#include "PIG.h"

PIGEvento evento;
PIGTeclado meuTeclado;

int timerDesenho;
int timerTeclado;
int timerFall;

class retangulo
{
public:
    double x, y, largura, altura;
    PIGCor cor;
    retangulo(double x, double y, double largura, double altura, PIGCor cor)
    {
        this->x = x;
        this->y = y;
        this->largura = largura;
        this->altura = altura;
        this->cor = cor;
    }
    void desenha()
    {
        IniciaDesenho();
        DesenhaRetangulo(x, y, largura, altura, cor);
        EncerraDesenho();
    }

    void jump()
    {
        if (meuTeclado[PIG_TECLA_BARRAESPACO] && this->altura <= 100 && this->largura <= 100)
        {
            this->altura += 1;
            this->largura += 1;
        } else if (this->altura >= 100 && this->largura >= 100 || this->altura >= 50 && this->largura >= 50)
        {
            this->altura -= 0.3;
            this->largura -= 0.3;
        }
    }

    void move()
    {
        if (meuTeclado[PIG_TECLA_w])
        {
            this->y += 0.6;
        }
        if (meuTeclado[PIG_TECLA_s])
        {
            this->y -= 0.6;
        }
        if (meuTeclado[PIG_TECLA_a])
        {
            this->x -= 0.6;
        }
        if (meuTeclado[PIG_TECLA_d]) {
            this->x += 0.6;
        }
        if (evento.tipoEvento == PIG_EVENTO_TECLADO){
            if (evento.teclado.tecla == PIG_TECLA_ESC)
            {
                FinalizaJogo();
            }
        }
    }
};

void initialSettings()
{
    CriaJogo("Joguinho");
    meuTeclado = GetTeclado();
    PIGCor corFundo = {0, 0, 0, 255};
    timerDesenho = CriaTimer();
    timerTeclado = CriaTimer();
    timerFall = CriaTimer();
};

retangulo player(100, 100, 50, 50, {255, 255, 255, 255});

int main()
{

    initialSettings();

    while (JogoRodando())
    {
        evento = GetEvento();

        if (TempoDecorrido(timerTeclado) >= 600 / 10000)
        {
            player.move();
            player.jump();
            ReiniciaTimer(timerTeclado);
        }

        if (TempoDecorrido(timerDesenho) >= 600 / 1000)
        {
            player.desenha();
            ReiniciaTimer(timerDesenho);
        }
    }

    FinalizaJogo();

    return 0;
}
