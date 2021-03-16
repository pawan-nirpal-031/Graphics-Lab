#include <graphics.h>
#include <cmath>
using namespace std;

int WIN_HEIGHT = 900;
int WIN_WIDTH = 1600;
int STD_RADIUS = 15;
const double PI = 3.1415926535897932384626433832795;

class GraphicsEngine{
    public:
        void StartGraphics(int winx = WIN_WIDTH,int winy = WIN_HEIGHT){
            // int gd = DETECT,gm;
            // initgraph(&gd,&gm,NULL);
            initwindow(winx,winy);
        }

        int TerminateGraphics(){
            closegraph();
            return 0;
        }

        void ConsoleWrite(string text,int posx = 200,int posy = 200){
            settextstyle(4,HORIZ_DIR,2);
            outtextxy(posx,posy,&text[0]);
        }

        void DrawLine(int x1,int y1,int x2,int y2){
            setlinestyle(0, 0, 9); 
            line(x1,y1,x2,y2);
        }
};

class Enemy{

};

class Player{
    int peddle_width;
    int peddle_height;
    int pos_x;
    int pos_y;
    unsigned int score;
    unsigned int health;
    
    public:
        Player(){
            this->score =0;
            this->health=100;
            this->peddle_width = 60;
            this->peddle_height = 40;
            this->pos_x = (WIN_WIDTH>>1) - (peddle_width>>1);
            this->pos_y = (WIN_HEIGHT - 50);
        }

        void Shoot(GraphicsEngine &g){
            ShowPlayer();
            int beam_pos_x = pos_x+(peddle_width>>1);
            int beam_height = 20;
            int beam_top_y = pos_y-peddle_height-beam_height;
            while(beam_top_y>0){
                g.ConsoleWrite(to_string(beam_top_y),0,0);
                g.DrawLine(beam_pos_x,beam_top_y,beam_pos_x,beam_top_y+beam_height);
                beam_top_y-=10;
                cleardevice();
                delay(10);
            }
        }


        void ShowPlayer(){
            rectangle(pos_x,pos_y-peddle_height,pos_x+peddle_width,pos_y);
        }

};

int main(){
    GraphicsEngine e;
    e.StartGraphics();
    Player p;
    p.Shoot(e);
    delay(3000);
    return e.TerminateGraphics();
}

// compile :  g++ SpaceInvaders.cpp -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
// run : ./a.exe (on windows)