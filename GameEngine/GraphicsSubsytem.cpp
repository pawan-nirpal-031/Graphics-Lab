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


int main(){
    GraphicsSubsystem g;
    g.StartGraphics();
   
    
    
    g.TerminateGraphics();
    return 0;
}

/*
    g++ GraphicsSubsystem.cpp -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
    ./a.exe
*/