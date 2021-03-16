#include <graphics.h>
#include <process.h>
#include <cmath>
using namespace std;

int WIN_HEIGHT = 700;
int WIN_WIDTH = 1200;
int STD_RADIUS = 15;
const double PI = 3.1415926535897932384626433832795;


class GraphicsSubsystem{
    public:
        void StartGraphics(int winx = WIN_WIDTH,int winy = WIN_HEIGHT){
            // int gd = DETECT,gm;
            // initgraph(&gd,&gm,NULL);
            initwindow(winx,winy);
        }

        void Circle(int x,int y, int radius){
            fillellipse(x,y,radius,radius);
        }

        void TerminateGraphics(){
            closegraph();
        }

        void ConsoleWrite(string text,int posx = 200,int posy = 200){
            settextstyle(4,HORIZ_DIR,2);
            outtextxy(posx,posy,&text[0]);
        }

        void DrawLine(){
            setlinestyle(0, 0, 9); 
            line(800,300,800,700);
        }

};


class Ball{
    private:
        int xpos;
        int ypos;
        int radius;
        int xvelocity;
        int yvelocity;
    public:

        Ball(){
            xpos = 0;
            ypos = 0;
            radius = STD_RADIUS;
            xvelocity = 0;
            yvelocity = 0;
        }
        Ball(int xinit,int yinit,int vxinit,int vyinit){
            xpos = xinit;
            ypos = yinit;
            xvelocity = vxinit;
            yvelocity = vyinit;    
            radius = STD_RADIUS;        
        }

        void SetBallPosition(int newx,int newy){
            this->xpos = newx;
            this->ypos = newy;
        }

        void SetBallVelocoity(int newvx,int newvy){
            this->xvelocity = newvx;
            this->yvelocity = newvy;
        }

        void WriteBallPosition(GraphicsSubsystem &g,int x,int y,int wx = 0,int wy = 0){
            string pos = "("+to_string(x)+", "+to_string(y);
            g.ConsoleWrite(pos,wx,wy);
        }

        void DrawBall(GraphicsSubsystem &g){
            g.Circle(this->xpos,this->ypos,this->radius);
            cleardevice();
            delay(10);
        }

        void BounceVertically(GraphicsSubsystem &g){
            ypos = WIN_HEIGHT>>1+2;
            yvelocity = - radius;
            while(ypos<=WIN_HEIGHT-radius and ypos>=(WIN_HEIGHT>>1)){
                if(ypos==WIN_HEIGHT-radius){
                    yvelocity = -yvelocity;
                }
                DrawBall(g);
                ypos+=yvelocity;
            }
            delay(2000);

        }


};


class ExecutionEngine{
    public:
        void Simulateball(GraphicsSubsystem &g){
            Ball b;
            b.SetBallPosition(WIN_WIDTH>>1,WIN_HEIGHT>>1);
            b.DrawBall(g);
            delay(2000);
        }

        
        


       
            

};


int main(){
    GraphicsSubsystem g;
    
    g.StartGraphics();
    ExecutionEngine e;
    e.Simulateball(g);
    
    g.TerminateGraphics();
    return 0;
}

/*
    g++ Pong.cpp -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
    ./a.exe
*/