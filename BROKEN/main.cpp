#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <ctime>
#include <fstream>
#include <SDL2/SDL_mixer.h>


using namespace std;


void bring_image(SDL_Renderer *Renderer,SDL_Texture *img_texture,string name, int alpha,int x,int y,int W,int H );
void key_click();
int mouse_click(int x1,int x2,int y1,int y2);
string username(SDL_Renderer *m_renderer);
void print_image(SDL_Renderer *m_renderer,SDL_Texture *img_texture, int x,int y,int w,int h);
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian );
void print_bricks(SDL_Renderer *m_renderer,int w,int h,SDL_Texture *img_brick11,SDL_Texture *img_brick12,SDL_Texture *img_brick13,SDL_Texture *img_brick21,SDL_Texture *img_brick22,
     SDL_Texture *img_brick23,SDL_Texture *img_brick31,SDL_Texture *img_brick32,SDL_Texture *img_brick33,SDL_Texture *img_brick41,SDL_Texture *img_brick42,SDL_Texture *img_brick43,
     SDL_Texture *img_brick51,SDL_Texture *img_brick52,SDL_Texture *img_brick53,SDL_Texture *img_brick61,SDL_Texture *img_brick62,SDL_Texture *img_brick63,SDL_Texture *img_gift,
     SDL_Texture *img_bomb,SDL_Texture *img_life,SDL_Texture *img_death,SDL_Texture *img_missile,SDL_Texture *img_pizza);
int racket_mover(SDL_Renderer *m_renderer,SDL_Texture *img_pause,int racket_w,string name_user,int level,int score,int lives,
                 int x,double teta,int I,int J,Mix_Chunk *click);
void username_checker(SDL_Renderer *m_renderer, string username, int log_or_sign);
string int_to_char(int a);
void stats(SDL_Renderer *m_renderer, int level, int score, int lives);
void gameover(SDL_Renderer *m_renderer, string username, int score);
void pause(SDL_Renderer *m_renderer, SDL_Texture *img_pause,
        string name, int level, int score, int lives, int x, double teta, int I, int J,Mix_Chunk *click);
void save(string name, int level, int score, int lives, int x, double teta, int I, int J);
void load(string name);
void print_one_digit(SDL_Renderer *renderer,int X,int Y,int R);
int tedad_ragham(int a);
void stats2(SDL_Renderer *m_renderer,SDL_Texture *img_number0,SDL_Texture *img_number1,SDL_Texture *img_number2,
            SDL_Texture *img_number3,SDL_Texture *img_number4,SDL_Texture *img_number5,SDL_Texture *img_number6,
            SDL_Texture *img_number7,SDL_Texture *img_number8,SDL_Texture *img_number9,int level,int score,int lives);



    double teta=0;
    int brick_matris[14][8];
    int flag_not_valid=0 ,flag_not_valid_signup=0;
    int lives=3,score=0,level=1,I=1,J=1;
    int x = 585;
    int game_difficulty=2; // 1---> easy , 2----> medium , 3---->hard ******
    int racket_type=1,ball_type=1;
    int ball_damage=1;
int main( int argc, char * argv[] )
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    Mix_Music *backgsound = Mix_LoadMUS("Stranger Things.mp3");
    Mix_Music *backgsound_2 = Mix_LoadMUS("29. Dispatch.mp3");
    Mix_Chunk *brick_break = Mix_LoadWAV("brick_break.wav");
    Mix_Chunk *tnt = Mix_LoadWAV("tnt.wav");
    Mix_Chunk *death = Mix_LoadWAV("death.wav");
    Mix_Chunk *health = Mix_LoadWAV("health.wav");
    Mix_Chunk *Score = Mix_LoadWAV("score.wav");
    Mix_Chunk *missile = Mix_LoadWAV("missile.wav");
    Mix_Chunk *bounce = Mix_LoadWAV("bounce.wav");
    Mix_Chunk *crack = Mix_LoadWAV("crack.wav");
    Mix_Chunk *click = Mix_LoadWAV("click.wav");
    Mix_Chunk *click_start = Mix_LoadWAV("click_start.wav");
    Mix_Chunk *fall = Mix_LoadWAV("fall.wav");
    Mix_PlayMusic(backgsound,-1);
    Mix_VolumeMusic(75);
    SDL_Delay(2000);

    int i,a,b,c,d,k,v=20, flag_ball=0, flag_ball_damage=0, flag_tnt=0, flag_tntx, flag_tnty, flag_missile=0,flag_missilex,flag_missiley ;
    int w,h;
    int counter_1,counter_2;
    int flag_brick=0;

    SDL_Texture *img_racket_1, *img_brick ,*img_backg,*img_ball_1, *img_menu, *img_start,*img_first_page, *img_press,
     *img_log_in, *img_new_game, *img_username, *img_brick11, *img_brick12, *img_brick13, *img_brick21, *img_brick22,
     *img_brick23, *img_brick31, *img_brick32, *img_brick33, *img_brick41, *img_brick42, *img_brick43, *img_brick51,
     *img_brick52, *img_brick53, *img_brick61, *img_brick62, *img_brick63, *img_gameover, *img_gift, *img_bomb,
     *img_life, *img_death, *img_missile, *img_pizza, *img_ball_2, *img_ball_3, *img_racket_2, *img_racket_3, *img_pause,
     *img_1,*img_2,*img_3,*img_4,*img_5,*img_6,*img_7,*img_8,*img_9,*mTexture,*img_number0,*img_number1,*img_number2,*img_number3,
     *img_number4,*img_number5,*img_number6,*img_number7,*img_number8,*img_number9,*img_m1,*img_m2,*img_m3,*img_m4;

    int W = 800;
    int L = 1200;
    string name_user="";
    char ch;

    srand(time(NULL));

    teta=137;

    //brick matris=0
    for (i=0;i<14;i++)
    {
        for (k=0;k<8;k++)
        {
            brick_matris[i][k]=0;
            //cout<<brick_matris[i][k]<<" ";
        }
        //cout<<endl;
    }
    for (k=0;k<8;k++)
   {
       if (flag_brick<2)
       {
            brick_matris[0][k]=rand()%(level+1);
            if (brick_matris[0][k]==0)
                flag_brick++;
       }
       else
       {
           brick_matris[0][k]=rand()%level+1;
       }
   }

//    for (k=0;k<13;k++)
//    {
//        brick_matris[k][0]=rand()%level+1;
//        brick_matris[k][7]=rand()%level+1;
//    }
//brick_matris[5][5]=1;
//brick_matris[3][3]=1;
//brick_matris[4][7]=1;
//brick_matris[1][2]=1;
    //cout<<teta<<endl;
    SDL_Rect ball;
    ball.h=30;
    ball.w=30;
    ball.x=600-(ball.w/2);
    ball.y=700;

    //text
    char * text ="";
    //textRGBA(m_renderer,50,50,text,font,24,200,200,200,200);
    // 1 for lazy.ttf , 2 for arial.ttf , 3 for B Roya.ttf

    //NO touching
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;//| SDL_WINDOW_FULLSCREEN_DESKTOP;//SDL_WINDOW_BORDERLESS ;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( L, W, WND_flags, &m_window, &m_renderer );

    SDL_RaiseWindow(m_window);

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    //

    //sound
    //PlaySound(TEXT("02.wav"),NULL,SND_LOOP|SND_ASYNC);

    int flag_click_1=1,flag_click_2=1,flag_click_3=1,flag_click_4=1,flag_click_5=1,flag_click_new_game=1,flag_click_username=1;

    bring_image(m_renderer,img_first_page,"broken.jpg",0,0,0,1200,800);
    SDL_Delay(2000);
    bring_image(m_renderer,img_first_page,"press.png",1,300,420,600,400);
    key_click();
    while(flag_click_1==1)
    {

            bring_image(m_renderer,img_first_page,"log in.png",0,0,0,1200,800);
            flag_click_2=1;
            flag_click_username=1;
            if(mouse_click(400,700,325,440)==1)
            {
                Mix_PlayChannel(-1,click,0);
                while(flag_click_username==1)
                {
                    bring_image(m_renderer,img_first_page,"user name.png",0,0,0,1200,800);
                    flag_click_2=1;
                    flag_click_new_game=1;
                    flag_click_3=1;
                    while(flag_click_2==1)
                    {
                       if(mouse_click(470,940,385,450)==1)
                       {
                            int x_flasher=485;
                            thickLineRGBA(m_renderer,x_flasher,395,x_flasher,440,4,198,87,33,250);
                            SDL_RenderPresent(m_renderer);
                            //user name input
                            name_user = username(m_renderer);
                            // chap 5 natije akhar
                            username_checker(m_renderer,name_user,1);
                            if (flag_not_valid==1)
                                flag_click_new_game=0;
                            else
                                key_click();
                                Mix_PlayChannel(-1,click,0);
                            //SDL_Delay(2000); // andaki sabr ta bebine oon 5 natije akhar ro
                            while(flag_click_new_game==1)
                            {
                                flag_click_3=1;
                                flag_click_4=1;
                                flag_click_5=1;
                                bring_image(m_renderer,img_first_page,"new game.png",0,0,0,1200,800);
                                while(flag_click_3==1)
                                {
                                   if(mouse_click(445,725,320,420)==1)
                                    {
                                           Mix_PlayChannel(-1,click,0);
                                           bring_image(m_renderer,img_first_page,"setting.png",0,0,0,1200,800);
                                           rectangleRGBA(m_renderer,505,380,655,435,198,87,33,250);
                                           SDL_RenderPresent(m_renderer);
                                           while(flag_click_4==1)
                                           {
                                               flag_click_5=1;

                                               if(mouse_click(345,445,380,435)==1)
                                               {
                                                   Mix_PlayChannel(-1,click,0);
                                                   bring_image(m_renderer,img_first_page,"setting.png",0,0,0,1200,800);
                                                   rectangleRGBA(m_renderer,345,380,455,435,198,87,33,250);
                                                   SDL_RenderPresent(m_renderer);
                                                   game_difficulty=1;
                                               }
                                               else if(mouse_click(505,655,380,435)==1)
                                               {
                                                   Mix_PlayChannel(-1,click,0);
                                                   bring_image(m_renderer,img_first_page,"setting.png",0,0,0,1200,800);
                                                   rectangleRGBA(m_renderer,505,380,655,435,198,87,33,250);
                                                   SDL_RenderPresent(m_renderer);
                                                   game_difficulty=2;
                                               }
                                               else if(mouse_click(710,815,380,435)==1)
                                               {
                                                   Mix_PlayChannel(-1,click,0);
                                                   bring_image(m_renderer,img_first_page,"setting.png",0,0,0,1200,800);
                                                   rectangleRGBA(m_renderer,710,380,815,435,198,87,33,250);
                                                   SDL_RenderPresent(m_renderer);
                                                   game_difficulty=3;
                                               }
                                               else if(mouse_click(480,680,500,585)==1)
                                               {
                                                   Mix_PlayChannel(-1,click,0);
                                                   bring_image(m_renderer,img_first_page,"rackets.png",0,0,0,1200,800);
                                                   rectangleRGBA(m_renderer,210,460,410,640,198,87,33,250);
                                                    SDL_RenderPresent(m_renderer);
                                                    while(flag_click_5==1)
                                                    {
                                                            if(mouse_click(210,410,460,640)==1)
                                                            {
                                                                Mix_PlayChannel(-1,click,0);
                                                                bring_image(m_renderer,img_first_page,"rackets.png",0,0,0,1200,800);
                                                                rectangleRGBA(m_renderer,210,460,410,640,198,87,33,250);
                                                                SDL_RenderPresent(m_renderer);
                                                                racket_type=1;
                                                            }
                                                            else if(mouse_click(485,685,460,640)==1)
                                                            {

                                                                Mix_PlayChannel(-1,click,0);
                                                                bring_image(m_renderer,img_first_page,"rackets.png",0,0,0,1200,800);
                                                                rectangleRGBA(m_renderer,485,460,685,640,198,87,33,250);
                                                                SDL_RenderPresent(m_renderer);
                                                                racket_type=2;
                                                            }
                                                            else if(mouse_click(760,960,460,640)==1)
                                                            {
                                                                Mix_PlayChannel(-1,click,0);
                                                                bring_image(m_renderer,img_first_page,"rackets.png",0,0,0,1200,800);
                                                                rectangleRGBA(m_renderer,760,460,960,640,198,87,33,250);
                                                                SDL_RenderPresent(m_renderer);
                                                                racket_type=3;
                                                            }
                                                            else if(mouse_click(10,130,735,780)==1)
                                                            {
                                                                Mix_PlayChannel(-1,click,0);
                                                                bring_image(m_renderer,img_first_page,"setting.png",0,0,0,1200,800);
                                                                if(game_difficulty==1)
                                                                {
                                                                    rectangleRGBA(m_renderer,345,380,455,435,198,87,33,250);
                                                                    SDL_RenderPresent(m_renderer);
                                                                }
                                                                else if(game_difficulty==2)
                                                                {
                                                                    rectangleRGBA(m_renderer,505,380,655,435,198,87,33,250);
                                                                    SDL_RenderPresent(m_renderer);
                                                                }
                                                                else if(game_difficulty==3)
                                                                {
                                                                    rectangleRGBA(m_renderer,710,380,815,435,198,87,33,250);
                                                                    SDL_RenderPresent(m_renderer);
                                                                }
                                                                flag_click_5=0;
                                                            }
                                                     }

                                                }
                                                else if(mouse_click(490,660,650,720)==1)
                                                {
                                                     Mix_PlayChannel(-1,click,0);
                                                     bring_image(m_renderer,img_first_page,"balls.png",0,0,0,1200,800);
                                                      rectangleRGBA(m_renderer,210,460,410,640,198,87,33,250);
                                                      SDL_RenderPresent(m_renderer);


                                                       while(flag_click_5==1)
                                                       {
                                                               if(mouse_click(210,410,460,640)==1)
                                                               {
                                                                   Mix_PlayChannel(-1,click,0);
                                                                   bring_image(m_renderer,img_first_page,"balls.png",0,0,0,1200,800);
                                                                   rectangleRGBA(m_renderer,210,460,410,640,198,87,33,250);
                                                                   SDL_RenderPresent(m_renderer);
                                                                    ball_type=1;
                                                               }
                                                               else if(mouse_click(485,685,460,640)==1)
                                                               {

                                                                   Mix_PlayChannel(-1,click,0);
                                                                    bring_image(m_renderer,img_first_page,"balls.png",0,0,0,1200,800);
                                                                   rectangleRGBA(m_renderer,485,460,685,640,198,87,33,250);
                                                                   SDL_RenderPresent(m_renderer);
                                                                    ball_type=2;
                                                               }
                                                               else if(mouse_click(760,960,460,640)==1)
                                                               {
                                                                   Mix_PlayChannel(-1,click,0);
                                                                   bring_image(m_renderer,img_first_page,"balls.png",0,0,0,1200,800);
                                                                   rectangleRGBA(m_renderer,760,460,960,640,198,87,33,250);
                                                                   SDL_RenderPresent(m_renderer);
                                                                   ball_type=3;
                                                               }
                                                               else if(mouse_click(10,130,735,780)==1)
                                                               {
                                                                   Mix_PlayChannel(-1,click,0);
                                                                   bring_image(m_renderer,img_first_page,"setting.png",0,0,0,1200,800);
                                                                   if(game_difficulty==1)
                                                                   {
                                                                       rectangleRGBA(m_renderer,345,380,455,435,198,87,33,250);
                                                                       SDL_RenderPresent(m_renderer);
                                                                   }
                                                                   else if(game_difficulty==2)
                                                                   {
                                                                       rectangleRGBA(m_renderer,505,380,655,435,198,87,33,250);
                                                                       SDL_RenderPresent(m_renderer);
                                                                   }
                                                                   else if(game_difficulty==3)
                                                                   {
                                                                      rectangleRGBA(m_renderer,710,380,815,435,198,87,33,250);
                                                                      SDL_RenderPresent(m_renderer);
                                                                   }
                                                                   flag_click_5=0;
                                                               }
                                                      }
                                                  }
                                                  else if(mouse_click(1060,1190,725,790)==1)
                                                  {
                                                      Mix_PlayChannel(-1,click_start,0);
                                                      flag_click_1=0;
                                                      flag_click_2=0;
                                                      flag_click_3=0;
                                                      flag_click_4=0;
                                                      flag_click_5=0;
                                                      flag_click_new_game=0;
                                                      flag_click_username=0;
                                                  }
                                                  else if(mouse_click(10,130,735,780)==1)
                                                  {
                                                      Mix_PlayChannel(-1,click,0);
                                                      flag_click_3=0;
                                                      flag_click_4=0;
                                                      flag_click_5=0;
                                                  }
                                        }
                                    }
                                    else if (mouse_click(445,725,460,560)==1)
                                    {
                                        Mix_PlayChannel(-1,click_start,0);
                                        load(name_user);
                                        flag_click_1=0;
                                        flag_click_2=0;
                                        flag_click_3=0;
                                        flag_click_4=0;
                                        flag_click_5=0;
                                        flag_click_new_game=0;
                                        flag_click_username=0;
                                    }
                                    else if (mouse_click(10,130,735,780)==1)
                                    {
                                        Mix_PlayChannel(-1,click,0);
                                        flag_click_2=0;
                                        flag_click_3=0;
                                        flag_click_new_game=0;
                                    }
                                }
                            }
                       }
                       else if(mouse_click(10,130,735,780)==1)
                       {
                           Mix_PlayChannel(-1,click,0);
                           flag_click_2=0;
                           flag_click_username=0;
                       }
                    }
                }
            }
            else if(mouse_click(400,700,455,570)==1)
            {
               Mix_PlayChannel(-1,click,0);
               while(flag_click_username==1)
                {

                    bring_image(m_renderer,img_first_page,"user name.png",0,0,0,1200,800);
                    flag_click_2=1;
                    flag_click_new_game=1;
                    flag_click_3=1;
                    while(flag_click_2==1)
                    {
                       if(mouse_click(470,940,385,450)==1)
                       {
                            int x_flasher=485;
                            thickLineRGBA(m_renderer,x_flasher,395,x_flasher,440,4,198,87,33,250);
                            SDL_RenderPresent(m_renderer);
                            //user name input
                            name_user = username(m_renderer);
                            // chap 5 natije akhar
                            username_checker(m_renderer,name_user,2);
                            if (flag_not_valid_signup==1)
                                flag_click_new_game=0;
                            //SDL_Delay(2000); // andaki sabr ta bebine oon 5 natije akhar ro
                            while(flag_click_new_game==1)
                            {
                                flag_click_3=1;
                                flag_click_4=1;
                                flag_click_5=1;
                                bring_image(m_renderer,img_first_page,"new game_2.png",0,0,0,1200,800);
                                while(flag_click_3==1)
                                {
                                   if(mouse_click(445,725,320,420)==1)
                                    {
                                           Mix_PlayChannel(-1,click,0);
                                           bring_image(m_renderer,img_first_page,"setting.png",0,0,0,1200,800);
                                           rectangleRGBA(m_renderer,505,380,655,435,198,87,33,250);
                                           SDL_RenderPresent(m_renderer);
                                           while(flag_click_4==1)
                                           {
                                               flag_click_5=1;

                                               if(mouse_click(345,445,380,435)==1)
                                               {
                                                   Mix_PlayChannel(-1,click,0);
                                                   bring_image(m_renderer,img_first_page,"setting.png",0,0,0,1200,800);
                                                   rectangleRGBA(m_renderer,345,380,455,435,198,87,33,250);
                                                   SDL_RenderPresent(m_renderer);
                                                   game_difficulty=1;
                                               }
                                               else if(mouse_click(505,655,380,435)==1)
                                               {
                                                   Mix_PlayChannel(-1,click,0);
                                                   bring_image(m_renderer,img_first_page,"setting.png",0,0,0,1200,800);
                                                   rectangleRGBA(m_renderer,505,380,655,435,198,87,33,250);
                                                   SDL_RenderPresent(m_renderer);
                                                   game_difficulty=2;
                                               }
                                               else if(mouse_click(710,815,380,435)==1)
                                               {
                                                   Mix_PlayChannel(-1,click,0);
                                                   bring_image(m_renderer,img_first_page,"setting.png",0,0,0,1200,800);
                                                   rectangleRGBA(m_renderer,710,380,815,435,198,87,33,250);
                                                   SDL_RenderPresent(m_renderer);
                                                   game_difficulty=3;
                                               }
                                               else if(mouse_click(480,680,500,585)==1)
                                               {
                                                   Mix_PlayChannel(-1,click,0);
                                                   bring_image(m_renderer,img_first_page,"rackets.png",0,0,0,1200,800);
                                                   rectangleRGBA(m_renderer,210,460,410,640,198,87,33,250);
                                                    SDL_RenderPresent(m_renderer);
                                                    while(flag_click_5==1)
                                                    {
                                                            if(mouse_click(210,410,460,640)==1)
                                                            {
                                                                Mix_PlayChannel(-1,click,0);
                                                                bring_image(m_renderer,img_first_page,"rackets.png",0,0,0,1200,800);
                                                                rectangleRGBA(m_renderer,210,460,410,640,198,87,33,250);
                                                                SDL_RenderPresent(m_renderer);
                                                                racket_type=1;
                                                            }
                                                            else if(mouse_click(485,685,460,640)==1)
                                                            {

                                                                Mix_PlayChannel(-1,click,0);
                                                                bring_image(m_renderer,img_first_page,"rackets.png",0,0,0,1200,800);
                                                                rectangleRGBA(m_renderer,485,460,685,640,198,87,33,250);
                                                                SDL_RenderPresent(m_renderer);
                                                                racket_type=2;
                                                            }
                                                            else if(mouse_click(760,960,460,640)==1)
                                                            {
                                                                Mix_PlayChannel(-1,click,0);
                                                                bring_image(m_renderer,img_first_page,"rackets.png",0,0,0,1200,800);
                                                                rectangleRGBA(m_renderer,760,460,960,640,198,87,33,250);
                                                                SDL_RenderPresent(m_renderer);
                                                                racket_type=3;
                                                            }
                                                            else if(mouse_click(10,130,735,780)==1)
                                                            {
                                                                Mix_PlayChannel(-1,click,0);
                                                                bring_image(m_renderer,img_first_page,"setting.png",0,0,0,1200,800);
                                                                if(game_difficulty==1)
                                                                {
                                                                    rectangleRGBA(m_renderer,345,380,455,435,198,87,33,250);
                                                                    SDL_RenderPresent(m_renderer);
                                                                }
                                                                else if(game_difficulty==2)
                                                                {
                                                                    rectangleRGBA(m_renderer,505,380,655,435,198,87,33,250);
                                                                    SDL_RenderPresent(m_renderer);
                                                                }
                                                                else if(game_difficulty==3)
                                                                {
                                                                    rectangleRGBA(m_renderer,710,380,815,435,198,87,33,250);
                                                                    SDL_RenderPresent(m_renderer);
                                                                }
                                                                flag_click_5=0;
                                                            }
                                                     }

                                                }
                                                else if(mouse_click(490,660,650,720)==1)
                                                {
                                                     Mix_PlayChannel(-1,click,0);
                                                     bring_image(m_renderer,img_first_page,"balls.png",0,0,0,1200,800);
                                                      rectangleRGBA(m_renderer,210,460,410,640,198,87,33,250);
                                                      SDL_RenderPresent(m_renderer);


                                                       while(flag_click_5==1)
                                                       {
                                                               if(mouse_click(210,410,460,640)==1)
                                                               {
                                                                   Mix_PlayChannel(-1,click,0);
                                                                   bring_image(m_renderer,img_first_page,"balls.png",0,0,0,1200,800);
                                                                   rectangleRGBA(m_renderer,210,460,410,640,198,87,33,250);
                                                                   SDL_RenderPresent(m_renderer);
                                                                    ball_type=1;
                                                               }
                                                               else if(mouse_click(485,685,460,640)==1)
                                                               {

                                                                   Mix_PlayChannel(-1,click,0);
                                                                   bring_image(m_renderer,img_first_page,"balls.png",0,0,0,1200,800);
                                                                   rectangleRGBA(m_renderer,485,460,685,640,198,87,33,250);
                                                                   SDL_RenderPresent(m_renderer);
                                                                    ball_type=2;
                                                               }
                                                               else if(mouse_click(760,960,460,640)==1)
                                                               {
                                                                   Mix_PlayChannel(-1,click,0);
                                                                   bring_image(m_renderer,img_first_page,"balls.png",0,0,0,1200,800);
                                                                   rectangleRGBA(m_renderer,760,460,960,640,198,87,33,250);
                                                                   SDL_RenderPresent(m_renderer);
                                                                   ball_type=3;
                                                               }
                                                               else if(mouse_click(10,130,735,780)==1)
                                                               {
                                                                   Mix_PlayChannel(-1,click,0);
                                                                   bring_image(m_renderer,img_first_page,"setting.png",0,0,0,1200,800);
                                                                   if(game_difficulty==1)
                                                                   {
                                                                       rectangleRGBA(m_renderer,345,380,455,435,198,87,33,250);
                                                                       SDL_RenderPresent(m_renderer);
                                                                   }
                                                                   else if(game_difficulty==2)
                                                                   {
                                                                       rectangleRGBA(m_renderer,505,380,655,435,198,87,33,250);
                                                                       SDL_RenderPresent(m_renderer);
                                                                   }
                                                                   else if(game_difficulty==3)
                                                                   {
                                                                      rectangleRGBA(m_renderer,710,380,815,435,198,87,33,250);
                                                                      SDL_RenderPresent(m_renderer);
                                                                   }
                                                                   flag_click_5=0;
                                                               }
                                                      }
                                                  }
                                                  else if(mouse_click(1060,1190,725,790)==1)
                                                  {
                                                      Mix_PlayChannel(-1,click_start,0);
                                                      flag_click_1=0;
                                                      flag_click_2=0;
                                                      flag_click_3=0;
                                                      flag_click_4=0;
                                                      flag_click_5=0;
                                                      flag_click_new_game=0;
                                                      flag_click_username=0;
                                                  }
                                                  else if(mouse_click(10,130,735,780)==1)
                                                  {
                                                      Mix_PlayChannel(-1,click,0);
                                                      flag_click_3=0;
                                                      flag_click_4=0;
                                                      flag_click_5=0;
                                                  }

                                        }
                                    }
                                    else if (mouse_click(10,130,735,780)==1)
                                    {
                                        Mix_PlayChannel(-1,click,0);
                                        flag_click_2=0;
                                        flag_click_3=0;
                                        flag_click_new_game=0;
                                    }
                                }
                            }
                       }
                       else if(mouse_click(10,130,735,780)==1)
                       {
                           Mix_PlayChannel(-1,click,0);
                           flag_click_2=0;
                           flag_click_username=0;
                       }
                    }
                }
            }
            else if (mouse_click(10,130,735,780)==1)
            {
                Mix_PlayChannel(-1,click,0);
                SDL_DestroyWindow( m_window );
                SDL_DestroyRenderer( m_renderer );
                SDL_Quit();
                return 0;
            }
    }

    //lives deciding
    switch(game_difficulty)
    {
    case 1:
        lives=4;
        break;
    case 2:
        lives=3;
        break;
    case 3:
        lives=2;
        break;
    }

    //racket length
    int racket_w;
    switch(game_difficulty)
    {
    case 1:
        racket_w=140;
        break;
    case 2:
        racket_w=120;
        break;
    case 3:
        racket_w=100;
        break;
    }


    img_backg = IMG_LoadTexture( m_renderer,"back ground.png");
    img_ball_1 = IMG_LoadTexture( m_renderer,"ball_1.png");
    img_ball_2 = IMG_LoadTexture( m_renderer,"ball_2.png");
    img_ball_3 = IMG_LoadTexture( m_renderer,"ball_3.png");
    img_brick = IMG_LoadTexture( m_renderer,"brick1.png");
    img_racket_1 = IMG_LoadTexture( m_renderer,"racket_1.png");
    img_racket_2 = IMG_LoadTexture( m_renderer,"racket_2.jpg");
    img_racket_3 = IMG_LoadTexture( m_renderer,"racket_3.png");
    img_brick11 = IMG_LoadTexture( m_renderer,"brick11.png");
    img_brick12 = IMG_LoadTexture( m_renderer,"brick12.png");
    img_brick13 = IMG_LoadTexture( m_renderer,"brick13.png");
    img_brick21 = IMG_LoadTexture( m_renderer,"brick21.png");
    img_brick22 = IMG_LoadTexture( m_renderer,"brick22.png");
    img_brick23 = IMG_LoadTexture( m_renderer,"brick23.png");
    img_brick31 = IMG_LoadTexture( m_renderer,"brick31.png");
    img_brick32 = IMG_LoadTexture( m_renderer,"brick32.png");
    img_brick33 = IMG_LoadTexture( m_renderer,"brick33.png");
    img_brick41 = IMG_LoadTexture( m_renderer,"brick41.png");
    img_brick42 = IMG_LoadTexture( m_renderer,"brick42.png");
    img_brick43 = IMG_LoadTexture( m_renderer,"brick43.png");
    img_brick51 = IMG_LoadTexture( m_renderer,"brick51.png");
    img_brick52 = IMG_LoadTexture( m_renderer,"brick52.png");
    img_brick53 = IMG_LoadTexture( m_renderer,"brick53.png");
    img_brick61 = IMG_LoadTexture( m_renderer,"brick61.png");
    img_brick62 = IMG_LoadTexture( m_renderer,"brick62.png");
    img_brick63 = IMG_LoadTexture( m_renderer,"brick63.png");
    img_gameover = IMG_LoadTexture( m_renderer,"game over.png");
    img_bomb = IMG_LoadTexture( m_renderer,"bomb.png");
    img_life = IMG_LoadTexture( m_renderer,"life.png");
    img_missile = IMG_LoadTexture( m_renderer,"missile.png");
    img_pizza = IMG_LoadTexture( m_renderer,"pizza.png");
    img_death = IMG_LoadTexture( m_renderer,"death.png");
    img_gift = IMG_LoadTexture( m_renderer,"gift.png");
    img_pause = IMG_LoadTexture( m_renderer,"pause.png");
    img_1 = IMG_LoadTexture( m_renderer,"1.png");
    img_2 = IMG_LoadTexture( m_renderer,"2.png");
    img_3 = IMG_LoadTexture( m_renderer,"3.png");
    img_4 = IMG_LoadTexture( m_renderer,"4.png");
    img_5 = IMG_LoadTexture( m_renderer,"5.png");
    img_6 = IMG_LoadTexture( m_renderer,"6.png");
    img_7 = IMG_LoadTexture( m_renderer,"7.png");
    img_8 = IMG_LoadTexture( m_renderer,"8.png");
    img_9 = IMG_LoadTexture( m_renderer,"9.png");
    img_number0 = IMG_LoadTexture( m_renderer,"n0.png");
    img_number1 = IMG_LoadTexture( m_renderer,"n1.png");
    img_number2 = IMG_LoadTexture( m_renderer,"n2.png");
    img_number3 = IMG_LoadTexture( m_renderer,"n3.png");
    img_number4 = IMG_LoadTexture( m_renderer,"n4.png");
    img_number5 = IMG_LoadTexture( m_renderer,"n5.png");
    img_number6 = IMG_LoadTexture( m_renderer,"n6.png");
    img_number7 = IMG_LoadTexture( m_renderer,"n7.png");
    img_number8 = IMG_LoadTexture( m_renderer,"n8.png");
    img_number9 = IMG_LoadTexture( m_renderer,"n9.png");
    img_m1 = IMG_LoadTexture( m_renderer,"m1.png");
    img_m2 = IMG_LoadTexture( m_renderer,"m2.png");
    img_m3 = IMG_LoadTexture( m_renderer,"m3.png");
    img_m4 = IMG_LoadTexture( m_renderer,"m4.png");


    Mix_FreeMusic(backgsound);
    Mix_PlayMusic(backgsound_2,-1);
    Mix_VolumeMusic(50);

    int flag_TETA=0;
    SDL_Event TETA;
    //PlaySound(TEXT("01.wav"),NULL,SND_LOOP|SND_ASYNC);
    x=600-(racket_w/2);
    while (flag_TETA==0)
    {
        //background
        print_image(m_renderer,img_backg,0,0,1200,800);
        //racket
        switch(racket_type)
        {
        case 1:
            print_image(m_renderer,img_racket_1,x,750,racket_w,15);
            break;
        case 2:
            print_image(m_renderer,img_racket_2,x,750,racket_w,15);
            break;
        case 3:
            print_image(m_renderer,img_racket_3,x,750,racket_w,15);
            break;
        }
        //bricks
        print_bricks(m_renderer,120,30,img_brick11,img_brick12,img_brick13,img_brick21,img_brick22,img_brick23,img_brick31
                     ,img_brick32,img_brick33,img_brick41,img_brick42,img_brick43,img_brick51,img_brick52,img_brick53
                     ,img_brick61,img_brick62,img_brick63,img_gift,img_bomb,img_life,img_death,img_missile,img_pizza);
        //pointer line
        aalineRGBA(m_renderer,x+(racket_w/2),715,x+(racket_w/2)+75*cos(teta/100),700-75*sin(teta/100),255,255,255,255);
        //ball
        ball.x=x+(racket_w/2)-(ball.w/2);
        ball.y=700;
        ball.w=30;
        ball.h=30;
        switch(ball_type)
        {
        case 1:
            SDL_QueryTexture(img_ball_1, NULL, NULL,&w,&h);
            SDL_RenderCopy(m_renderer,img_ball_1 ,NULL,&ball);
            break;
        case 2:
            SDL_QueryTexture(img_ball_2, NULL, NULL,&w,&h);
            SDL_RenderCopy(m_renderer,img_ball_2 ,NULL,&ball);
            break;
        case 3:
            SDL_QueryTexture(img_ball_3, NULL, NULL,&w,&h);
            SDL_RenderCopy(m_renderer,img_ball_3 ,NULL,&ball);
            break;
        }

        //level score lives
        //stats(m_renderer,level,score,lives);
        stats2(m_renderer,img_number0,img_number1,img_number2,img_number3,img_number4,img_number5,img_number6,img_number7,
               img_number8,img_number9,level,score,lives);
        SDL_RenderPresent(m_renderer);

        while(SDL_PollEvent(&TETA))
        {
            if (TETA.type==SDL_KEYDOWN)
            {
                switch( TETA.key.keysym.sym )
                {
                    case SDLK_w:
                        if (teta+20<=257)
                            teta+=20;
                        if (teta==157)
                            teta+=20;
                        break;

                    case SDLK_s:
                        if (teta-20>=57)
                            teta-=20;
                            if (teta==157)
                            teta-=20;
                        break;

                    case SDLK_a:
                        if (x-20>=0)
                            x-=20;
                        break;

                    case SDLK_d:
                        if (x+20<=(1200-racket_w))
                            x+=20;
                        break;

                    case SDLK_SPACE:
                        flag_TETA=1;
                        break;

                    case SDLK_p:
                        Mix_PlayChannel(-1,click,0);
                        pause(m_renderer,img_pause,name_user,level,score,lives,x,teta,I,J,click);
                        break;
                }
            }
        }
    }
    teta/=100;

    int flag_gameover=0,flag_tnt_counter=0,flag_missile_counter=0;
    SDL_Rect racket;

    while(flag_gameover==0 && lives>0)
    {
        flag_ball=0;

        //background
        print_image(m_renderer,img_backg,0,0,1200,800);
        //level score lives
        //stats(m_renderer,level,score,lives);
        stats2(m_renderer,img_number0,img_number1,img_number2,img_number3,img_number4,img_number5,img_number6,img_number7,
               img_number8,img_number9,level,score,lives);
        //bricks
        print_bricks(m_renderer,120,30,img_brick11,img_brick12,img_brick13,img_brick21,img_brick22,img_brick23,img_brick31
                     ,img_brick32,img_brick33,img_brick41,img_brick42,img_brick43,img_brick51,img_brick52,img_brick53
                     ,img_brick61,img_brick62,img_brick63,img_gift,img_bomb,img_life,img_death,img_missile,img_pizza);

        //tnt animation
        if (flag_tnt==1)
        {
            flag_tnt_counter++;
            switch(flag_tnt_counter)
            {
            case 1:
                print_image(m_renderer,img_1,flag_tntx-40,flag_tnty-80,200,200);
                break;
            case 2:
                print_image(m_renderer,img_2,flag_tntx-40,flag_tnty-80,200,200);
                break;
            case 3:
                print_image(m_renderer,img_3,flag_tntx-40,flag_tnty-80,200,200);
                break;
            case 4:
                print_image(m_renderer,img_4,flag_tntx-40,flag_tnty-80,200,200);
                break;
            case 5:
                print_image(m_renderer,img_5,flag_tntx-40,flag_tnty-80,200,200);
                break;
            case 6:
                print_image(m_renderer,img_6,flag_tntx-40,flag_tnty-80,200,200);
                break;
            case 7:
                print_image(m_renderer,img_7,flag_tntx-40,flag_tnty-80,200,200);
                break;
            case 8:
                print_image(m_renderer,img_8,flag_tntx-40,flag_tnty-80,200,200);
                break;
            case 9:
                print_image(m_renderer,img_9,flag_tntx-40,flag_tnty-80,200,200);
                break;
            }
            if (flag_tnt_counter==20)
            {
                flag_tnt=0;
            }
        }
        else
        {
            flag_tnt_counter=0;
        }

        //missile animation
        if (flag_missile==1)
        {
            flag_missile_counter++;
            switch(flag_missile_counter)
            {
            case 1:
                print_image(m_renderer,img_m1,flag_missilex-40,flag_missiley-30,200,200);
                break;

            case 2:
                print_image(m_renderer,img_m2,flag_missilex-40,flag_missiley-30,200,200);
                break;

            case 3:
                print_image(m_renderer,img_m3,flag_missilex-40,flag_missiley-30,200,200);
                break;

            case 4:
                print_image(m_renderer,img_m4,flag_missilex-40,flag_missiley-30,200,200);
                break;
            }
            if (flag_missile_counter==10)
            {
                flag_missile=0;
            }
        }
        else
        {
            flag_missile_counter=0;
        }

        //racket
        switch(racket_type)
        {
        case 1:
            print_image(m_renderer,img_racket_1,x,750,racket_w,15);
            break;
        case 2:
            print_image(m_renderer,img_racket_2,x,750,racket_w,15);
            break;
        case 3:
            print_image(m_renderer,img_racket_3,x,750,racket_w,15);
            break;
        }
        racket.x=x;

        SDL_RenderPresent(m_renderer);

        //ball
        if (ball_damage>0)
        {
            //racket mirror
            switch(ball_type)
            {
            case 1:
                SDL_QueryTexture(img_ball_1, NULL, NULL,&w,&h);
                break;
            case 2:
                SDL_QueryTexture(img_ball_2, NULL, NULL,&w,&h);
                break;
            case 3:
                SDL_QueryTexture(img_ball_3, NULL, NULL,&w,&h);
                break;
            }
            if (ball.x<=(racket.x+racket_w-(ball.w/2)+10) && ball.x>=(racket.x-(ball.w/2)-10) && ball.y>=(750-(ball.h)-10) && ball.y<=(750-(ball.h)+10))
            {
                Mix_PlayChannel(-1,bounce,0);
                J*=-1;
            }

            //bricks mirror
            for (i=0;i<14;i++)
            {
                for (k=0;k<8;k++)
                {
                    if(brick_matris[i][k]%100>0)
                    {
                        if (ball.x>=(40+(k*140)-(ball.w/2)) && ball.x<=(40+((k+1)*140)-(ball.w/2)))
                        {
                            if (ball.y>=(30+(i*50)-(ball.h/2)) && ball.y<=(70+(i*50)-(ball.h/2)))
                            {
                                if (ball_damage >= brick_matris[i][k])
                                {
                                    score+=brick_matris[i][k]*level;
                                }
                                else
                                {
                                    score+=ball_damage*level;
                                }
                                flag_ball_damage=ball_damage;
                                ball_damage-=(brick_matris[i][k])%100;
                                if (ball_damage<0)
                                {
                                    ball_damage=0;
                                }
                                if ((brick_matris[i][k]%100)-flag_ball_damage<=0)
                                {
                                    //Mix_PlayChannel(-1,brick_break,0);
                                    switch(brick_matris[i][k]/100)
                                    {
                                    case 1:
                                        Mix_PlayChannel(-1,tnt,0);
                                        flag_tnt=1;
                                        flag_tntx=50+(140*k);
                                        flag_tnty=50*(i+1);
                                        for (counter_1=i-1;counter_1<=i+1;counter_1++)
                                        {
                                            for (counter_2=k-1;counter_2<=k+1;counter_2++)
                                            {
                                                if (counter_1>=0 && counter_1<=13 && counter_2>=0 && counter_2<=7)
                                                {
                                                    score+=(brick_matris[counter_1][counter_2]%100)*level;
                                                    brick_matris[counter_1][counter_2]=0;
                                                }
                                            }
                                        }
                                        break;
                                    case 2:
                                        Mix_PlayChannel(-1,missile,0);
                                        flag_missile=1;
                                        flag_missilex=50+(140*k);
                                        flag_missiley=50*(i+1);
                                        for (counter_1=0;counter_1<8;counter_1++)
                                        {
                                            score+=(brick_matris[i][counter_1]%100)*level;
                                            brick_matris[i][counter_1]=0;
                                        }
                                        break;
                                    case 3:
                                        Mix_PlayChannel(-1,health,0);
                                        lives++;
                                        break;
                                    case 4:
                                        Mix_PlayChannel(-1,death,0);
                                        lives--;
                                        break;
                                    case 5:
                                        Mix_PlayChannel(-1,Score,0);
                                        score+=200;
                                        break;
                                    case 6:
                                        int T;
                                        T=rand()%6;
                                        switch(T)
                                        {
                                        case 0:
                                            Mix_PlayChannel(-1,brick_break,0);
                                            brick_matris[i][k]=0;
                                            break;
                                        case 1:
                                            Mix_PlayChannel(-1,tnt,0);
                                            flag_tnt=1;
                                            flag_tntx=50+(140*k);
                                            flag_tnty=50*(i+1);
                                            for (counter_1=i-1;counter_1<=i+1;counter_1++)
                                            {
                                                for (counter_2=k-1;counter_2<=k+1;counter_2++)
                                                {
                                                    if (counter_1>=0 && counter_1<=13 && counter_2>=0 && counter_2<=7)
                                                    {
                                                        score+=(brick_matris[counter_1][counter_2]%100)*level;
                                                        brick_matris[counter_1][counter_2]=0;
                                                    }
                                                }
                                            }
                                            break;
                                        case 2:
                                            Mix_PlayChannel(-1,missile,0);
                                            flag_missile=1;
                                            flag_missilex=50+(140*k);
                                            flag_missiley=50*(i+1);
                                            for (counter_1=0;counter_1<8;counter_1++)
                                            {
                                                brick_matris[i][counter_1]=0;
                                            }
                                            break;
                                        case 3:
                                            Mix_PlayChannel(-1,health,0);
                                            lives++;
                                            break;
                                        case 4:
                                            Mix_PlayChannel(-1,death,0);
                                            lives--;
                                            break;
                                        case 5:
                                            Mix_PlayChannel(-1,Score,0);
                                            score+=200;
                                            break;
                                        }
                                        break;
                                    default :
                                        Mix_PlayChannel(-1,brick_break,0);
                                        brick_matris[i][k]=0;
                                        break;
                                    }
                                    brick_matris[i][k]=0;
                                }
                                else if ((brick_matris[i][k]%100)-flag_ball_damage>0)
                                {
                                    Mix_PlayChannel(-1,crack,0);
                                    brick_matris[i][k]-=flag_ball_damage;
                                }
                                J*=-1;
                                //flag_ball=1;
                            }
                            else if (ball.y>=(10+((i+1)*50)-(ball.h/2)) && ball.y<=(50+((i+1)*50)-(ball.h/2)))
                            {
                                if (ball_damage >= brick_matris[i][k])
                                {
                                    score+=brick_matris[i][k]*level;
                                }
                                else
                                {
                                    score+=ball_damage*level;
                                }
                                flag_ball_damage=ball_damage;
                                ball_damage-=(brick_matris[i][k])%100;
                                if (ball_damage<0)
                                {
                                    ball_damage=0;
                                }
                                if ((brick_matris[i][k]%100)-flag_ball_damage<=0)
                                {
                                    //Mix_PlayChannel(-1,brick_break,0);
                                    switch(brick_matris[i][k]/100)
                                    {
                                    case 1:
                                        Mix_PlayChannel(-1,tnt,0);
                                        flag_tnt=1;
                                        flag_tntx=50+(140*k);
                                        flag_tnty=50*(i+1);
                                        for (counter_1=i-1;counter_1<=i+1;counter_1++)
                                        {
                                            for (counter_2=k-1;counter_2<=k+1;counter_2++)
                                            {
                                                if (counter_1>=0 && counter_1<=13 && counter_2>=0 && counter_2<=7)
                                                {
                                                    score+=(brick_matris[counter_1][counter_2]%100)*level;
                                                    brick_matris[counter_1][counter_2]=0;
                                                }
                                            }
                                        }
                                        break;
                                    case 2:
                                        Mix_PlayChannel(-1,missile,0);
                                        flag_missile=1;
                                        flag_missilex=50+(140*k);
                                        flag_missiley=50*(i+1);
                                        for (counter_1=0;counter_1<8;counter_1++)
                                        {
                                            score+=(brick_matris[i][counter_1]%100)*level;
                                            brick_matris[i][counter_1]=0;
                                        }
                                        break;
                                    case 3:
                                        Mix_PlayChannel(-1,health,0);
                                        lives++;
                                        break;
                                    case 4:
                                        Mix_PlayChannel(-1,death,0);
                                        lives--;
                                        break;
                                    case 5:
                                        Mix_PlayChannel(-1,Score,0);
                                        score+=200;
                                        break;
                                    case 6:
                                        int T;
                                        T=rand()%6;
                                        switch(T)
                                        {
                                        case 0:
                                            Mix_PlayChannel(-1,brick_break,0);
                                            brick_matris[i][k]=0;
                                            break;
                                        case 1:
                                            Mix_PlayChannel(-1,tnt,0);
                                            flag_tnt=1;
                                            flag_tntx=50+(140*k);
                                            flag_tnty=50*(i+1);
                                            for (counter_1=i-1;counter_1<=i+1;counter_1++)
                                            {
                                                for (counter_2=k-1;counter_2<=k+1;counter_2++)
                                                {
                                                    if (counter_1>=0 && counter_1<=13 && counter_2>=0 && counter_2<=7)
                                                    {
                                                        score+=(brick_matris[counter_1][counter_2]%100)*level;
                                                        brick_matris[counter_1][counter_2]=0;
                                                    }
                                                }
                                            }
                                            break;
                                        case 2:
                                            Mix_PlayChannel(-1,missile,0);
                                            flag_missile=1;
                                            flag_missilex=50+(140*k);
                                            flag_missiley=50*(i+1);
                                            for (counter_1=0;counter_1<8;counter_1++)
                                            {
                                                brick_matris[i][counter_1]=0;
                                            }
                                            break;
                                        case 3:
                                            Mix_PlayChannel(-1,health,0);
                                            lives++;
                                            break;
                                        case 4:
                                            Mix_PlayChannel(-1,death,0);
                                            lives--;
                                            break;
                                        case 5:
                                            Mix_PlayChannel(-1,Score,0);
                                            score+=200;
                                            break;
                                        }
                                        break;
                                    default :
                                        Mix_PlayChannel(-1,brick_break,0);
                                        brick_matris[i][k]=0;
                                        break;
                                    }
                                    brick_matris[i][k]=0;
                                }
                                else if ((brick_matris[i][k]%100)-flag_ball_damage>0)
                                {
                                    Mix_PlayChannel(-1,crack,0);
                                    brick_matris[i][k]-=flag_ball_damage;
                                }
                                J*=-1;
                                //flag_ball=1;
                            }
                        }
                        else if (ball.y>=(40+(i*50)-(ball.h/2)) && ball.y<=(40+((i+1)*50)-(ball.h/2)))
                        {
                            if (ball.x>=(30+(k*140)-(ball.w/2)) && ball.x<=(70+(k*140)-(ball.w/2)))
                            {
                                if (ball_damage >= brick_matris[i][k])
                                {
                                    score+=brick_matris[i][k]*level;
                                }
                                else
                                {
                                    score+=ball_damage*level;
                                }
                                flag_ball_damage=ball_damage;
                                ball_damage-=(brick_matris[i][k])%100;
                                if (ball_damage<0)
                                {
                                    ball_damage=0;
                                }
                                if ((brick_matris[i][k]%100)-flag_ball_damage<=0)
                                {
                                    //Mix_PlayChannel(-1,brick_break,0);
                                    switch(brick_matris[i][k]/100)
                                    {
                                    case 1:
                                        Mix_PlayChannel(-1,tnt,0);
                                        flag_tnt=1;
                                        flag_tntx=50+(140*k);
                                        flag_tnty=50*(i+1);
                                        for (counter_1=i-1;counter_1<=i+1;counter_1++)
                                        {
                                            for (counter_2=k-1;counter_2<=k+1;counter_2++)
                                            {
                                                if (counter_1>=0 && counter_1<=13 && counter_2>=0 && counter_2<=7)
                                                {
                                                    score+=(brick_matris[counter_1][counter_2]%100)*level;
                                                    brick_matris[counter_1][counter_2]=0;
                                                }
                                            }
                                        }
                                        break;
                                    case 2:
                                        Mix_PlayChannel(-1,missile,0);
                                        flag_missile=1;
                                        flag_missilex=50+(140*k);
                                        flag_missiley=50*(i+1);
                                        for (counter_1=0;counter_1<8;counter_1++)
                                        {
                                            score+=(brick_matris[i][counter_1]%100)*level;
                                            brick_matris[i][counter_1]=0;
                                        }
                                        break;
                                    case 3:
                                        Mix_PlayChannel(-1,health,0);
                                        lives++;
                                        break;
                                    case 4:
                                        Mix_PlayChannel(-1,death,0);
                                        lives--;
                                        break;
                                    case 5:
                                        Mix_PlayChannel(-1,Score,0);
                                        score+=200;
                                        break;
                                    case 6:
                                        int T;
                                        T=rand()%6;
                                        switch(T)
                                        {
                                        case 0:
                                            Mix_PlayChannel(-1,brick_break,0);
                                            brick_matris[i][k]=0;
                                            break;
                                        case 1:
                                            Mix_PlayChannel(-1,tnt,0);
                                            flag_tnt=1;
                                            flag_tntx=50+(140*k);
                                            flag_tnty=50*(i+1);
                                            for (counter_1=i-1;counter_1<=i+1;counter_1++)
                                            {
                                                for (counter_2=k-1;counter_2<=k+1;counter_2++)
                                                {
                                                    if (counter_1>=0 && counter_1<=13 && counter_2>=0 && counter_2<=7)
                                                    {
                                                        score+=(brick_matris[counter_1][counter_2]%100)*level;
                                                        brick_matris[counter_1][counter_2]=0;
                                                    }
                                                }
                                            }
                                            break;
                                        case 2:
                                            Mix_PlayChannel(-1,missile,0);
                                            flag_missile=1;
                                            flag_missilex=50+(140*k);
                                            flag_missiley=50*(i+1);
                                            for (counter_1=0;counter_1<8;counter_1++)
                                            {
                                                brick_matris[i][counter_1]=0;
                                            }
                                            break;
                                        case 3:
                                            Mix_PlayChannel(-1,health,0);
                                            lives++;
                                            break;
                                        case 4:
                                            Mix_PlayChannel(-1,death,0);
                                            lives--;
                                            break;
                                        case 5:
                                            Mix_PlayChannel(-1,Score,0);
                                            score+=200;
                                            break;
                                        }
                                        break;
                                    default :
                                        Mix_PlayChannel(-1,brick_break,0);
                                        brick_matris[i][k]=0;
                                        break;
                                    }
                                    brick_matris[i][k]=0;
                                }
                                else if ((brick_matris[i][k]%100)-flag_ball_damage>0)
                                {
                                    Mix_PlayChannel(-1,crack,0);
                                    brick_matris[i][k]-=flag_ball_damage;
                                }
                                I*=-1;
                            }
                            else if (ball.x>=(10+((k+1)*140)-(ball.w/2)) && ball.x<=(50+((k+1)*140)-(ball.w/2)))
                            {
                                if (ball_damage >= brick_matris[i][k])
                                {
                                    score+=brick_matris[i][k]*level;
                                }
                                else
                                {
                                    score+=ball_damage*level;
                                }
                                flag_ball_damage=ball_damage;
                                ball_damage-=(brick_matris[i][k])%100;
                                if (ball_damage<0)
                                {
                                    ball_damage=0;
                                }
                                if ((brick_matris[i][k]%100)-flag_ball_damage<=0)
                                {
                                    //Mix_PlayChannel(-1,brick_break,0);
                                    switch(brick_matris[i][k]/100)
                                    {
                                    case 1:
                                        Mix_PlayChannel(-1,tnt,0);
                                        flag_tnt=1;
                                        flag_tntx=50+(140*k);
                                        flag_tnty=50*(i+1);
                                        for (counter_1=i-1;counter_1<=i+1;counter_1++)
                                        {
                                            for (counter_2=k-1;counter_2<=k+1;counter_2++)
                                            {
                                                if (counter_1>=0 && counter_1<=13 && counter_2>=0 && counter_2<=7)
                                                {
                                                    score+=(brick_matris[counter_1][counter_2]%100)*level;
                                                    brick_matris[counter_1][counter_2]=0;
                                                }
                                            }
                                        }
                                        break;
                                    case 2:
                                        Mix_PlayChannel(-1,missile,0);
                                        flag_missile=1;
                                        flag_missilex=50+(140*k);
                                        flag_missiley=50*(i+1);
                                        for (counter_1=0;counter_1<8;counter_1++)
                                        {
                                            score+=(brick_matris[i][counter_1]%100)*level;
                                            brick_matris[i][counter_1]=0;
                                        }
                                        break;
                                    case 3:
                                        Mix_PlayChannel(-1,health,0);
                                        lives++;
                                        break;
                                    case 4:
                                        Mix_PlayChannel(-1,death,0);
                                        lives--;
                                        break;
                                    case 5:
                                        Mix_PlayChannel(-1,Score,0);
                                        score+=200;
                                        break;
                                    case 6:
                                        int T;
                                        T=rand()%6;
                                        switch(T)
                                        {
                                        case 0:
                                            Mix_PlayChannel(-1,brick_break,0);
                                            brick_matris[i][k]=0;
                                            break;
                                        case 1:
                                            Mix_PlayChannel(-1,tnt,0);
                                            flag_tnt=1;
                                            flag_tntx=50+(140*k);
                                            flag_tnty=50*(i+1);
                                            for (counter_1=i-1;counter_1<=i+1;counter_1++)
                                            {
                                                for (counter_2=k-1;counter_2<=k+1;counter_2++)
                                                {
                                                    if (counter_1>=0 && counter_1<=13 && counter_2>=0 && counter_2<=7)
                                                    {
                                                        score+=(brick_matris[counter_1][counter_2]%100)*level;
                                                        brick_matris[counter_1][counter_2]=0;
                                                    }
                                                }
                                            }
                                            break;
                                        case 2:
                                            Mix_PlayChannel(-1,missile,0);
                                            flag_missile=1;
                                            flag_missilex=50+(140*k);
                                            flag_missiley=50*(i+1);
                                            for (counter_1=0;counter_1<8;counter_1++)
                                            {
                                                brick_matris[i][counter_1]=0;
                                            }
                                            break;
                                        case 3:
                                            Mix_PlayChannel(-1,health,0);
                                            lives++;
                                            break;
                                        case 4:
                                            Mix_PlayChannel(-1,death,0);
                                            lives--;
                                            break;
                                        case 5:
                                            Mix_PlayChannel(-1,Score,0);
                                            score+=200;
                                            break;
                                        }
                                        break;
                                    default :
                                        Mix_PlayChannel(-1,brick_break,0);
                                        brick_matris[i][k]=0;
                                        break;
                                    }
                                    brick_matris[i][k]=0;
                                }
                                else if ((brick_matris[i][k]%100)-flag_ball_damage>0)
                                {
                                    Mix_PlayChannel(-1,crack,0);
                                    brick_matris[i][k]-=flag_ball_damage;
                                }
                                I*=-1;
                            }
                        }
                    }
                }
            }

            //vertical walls mirror
            if ((ball.x+(v*cos(teta)*I))<=1170 && (ball.x+(v*cos(teta)*I))>=-10)
            {
                ball.x=ball.x+(v*cos(teta)*I);
            }
            else
            {
                I*=-1;
                //cout<<I<<endl;
            }

            //horizontal wall mirror
            if ((ball.y-(v*sin(teta)*J))<=770 && (ball.y-(v*sin(teta)*J))>=-10)
            {
                ball.y=ball.y-(v*sin(teta)*J);
            }
            else
            {
                J*=-1;
                //cout<<J<<endl;
            }

            //life lower
            if (ball.y>=750)
            {
                Mix_PlayChannel(-1,fall,0);
                SDL_Delay(1000);
                lives--;
                teta=137;
                flag_TETA=0;
                x=600-(racket_w/2);
                if (lives!=0)
                {
                    x=600-(racket_w/2);
                    while (flag_TETA==0)
                    {
                        //background
                        print_image(m_renderer,img_backg,0,0,1200,800);

                        //level score lives
                        //stats(m_renderer,level,score,lives);
                        stats2(m_renderer,img_number0,img_number1,img_number2,img_number3,img_number4,img_number5,img_number6,img_number7,
                            img_number8,img_number9,level,score,lives);

                        //racket
                        switch(racket_type)
                        {
                        case 1:
                            print_image(m_renderer,img_racket_1,x,750,racket_w,15);
                            break;
                        case 2:
                            print_image(m_renderer,img_racket_2,x,750,racket_w,15);
                            break;
                        case 3:
                            print_image(m_renderer,img_racket_3,x,750,racket_w,15);
                            break;
                        }
                        //bricks
                        print_bricks(m_renderer,120,30,img_brick11,img_brick12,img_brick13,img_brick21,img_brick22,img_brick23,img_brick31
                                     ,img_brick32,img_brick33,img_brick41,img_brick42,img_brick43,img_brick51,img_brick52,img_brick53
                                     ,img_brick61,img_brick62,img_brick63,img_gift,img_bomb,img_life,img_death,img_missile,img_pizza);
                        //pointer line
                        aalineRGBA(m_renderer,x+(racket_w/2),(750-ball.w/2),x+(racket_w/2)+75*cos(teta/100),750-ball.w-75*sin(teta/100),255,255,255,255);
                        //ball
                        ball.x=x+(racket_w/2)-(ball.w/2);
                        ball.y=750-ball.w;
                        ball.w=30;
                        ball.h=30;
                        switch(ball_type)
                        {
                        case 1:
                            SDL_QueryTexture(img_ball_1, NULL, NULL,&w,&h);
                            SDL_RenderCopy(m_renderer,img_ball_1 ,NULL,&ball);
                            break;
                        case 2:
                            SDL_QueryTexture(img_ball_2, NULL, NULL,&w,&h);
                            SDL_RenderCopy(m_renderer,img_ball_2 ,NULL,&ball);
                            break;
                        case 3:
                            SDL_QueryTexture(img_ball_3, NULL, NULL,&w,&h);
                            SDL_RenderCopy(m_renderer,img_ball_3 ,NULL,&ball);
                            break;
                        }

                        SDL_RenderPresent(m_renderer);

                        while(SDL_PollEvent(&TETA))
                        {
                            if (TETA.type==SDL_KEYDOWN)
                            {
                                switch( TETA.key.keysym.sym )
                                {
                                    case SDLK_w:
                                        if (teta+20<=257)
                                            teta+=20;
                                        if (teta==157)
                                            teta+=20;
                                        break;

                                    case SDLK_s:
                                        if (teta-20>=57)
                                            teta-=20;
                                        if (teta==157)
                                            teta-=20;
                                        break;

                                    case SDLK_a:
                                        if (x-20>=0)
                                            x-=20;
                                        break;

                                    case SDLK_d:
                                        if (x+20<=(1200-racket_w))
                                            x+=20;
                                        break;

                                    case SDLK_SPACE:
                                        flag_TETA=1;
                                        break;

                                    case SDLK_p:
                                        Mix_PlayChannel(-1,click,0);
                                        pause(m_renderer,img_pause,name_user,level,score,lives,x,teta,I,J,click);
                                        break;
                                }
                            }
                        }
                    }
                    teta/=100;
                }

                ball.x=x+(racket_w/2)-(ball.w/2);
                ball.y=700;
                I=1;
                J=1;
            }
            ball.w=30;
            ball.h=30;
            switch(ball_type)
            {
            case 1:
                SDL_RenderCopy(m_renderer,img_ball_1 ,NULL,&ball);
                break;
            case 2:
                SDL_RenderCopy(m_renderer,img_ball_2 ,NULL,&ball);
                break;
            case 3:
                SDL_RenderCopy(m_renderer,img_ball_3 ,NULL,&ball);
                break;
            }
            SDL_RenderPresent(m_renderer);

            //ball speed by delay
            switch(game_difficulty)
            {
            case 1:
                SDL_Delay(35);
                break;
            case 2:
                SDL_Delay(30);
                break;
            case 3:
                SDL_Delay(25);
                break;
            }
        }
        //next level
        else
        {
            //bricks shift
            for (i=13;i>=0;i--)
            {
                for (k=0;k<8;k++)
                {
                    brick_matris[i][k]=brick_matris[i-1][k];
                }
            }

            //bricks strength
            flag_brick=0;
            int flag_difficulty;
            switch(game_difficulty)
            {
            case 1:
                flag_difficulty=30;
                break;
            case 2:
                flag_difficulty=40;
                break;
            case 3:
                flag_difficulty=50;
                break;
            }
            for (k=0;k<8;k++)
            {
                brick_matris[0][k]=(rand()%flag_difficulty)+1;
                brick_matris[0][k]*=100;
                if (flag_brick<2)
                {
                    brick_matris[0][k]+=rand()%(level+1);
                    if ((brick_matris[0][k]%100)==0)
                    {
                        flag_brick++;
                    }
                }
                else
                {
                    brick_matris[0][k]+=(rand()%level)+1;
                }
                //cout<<brick_matris[0][k]<<" ";
            }
            //cout<<endl;

            SDL_Delay(1000);
            level++;
            ball_damage=level;

            flag_TETA=0;
            teta=137;

            x=600-(racket_w/2);
            while (flag_TETA==0)
            {
                //background
                print_image(m_renderer,img_backg,0,0,1200,800);

                //level score lives
                //stats(m_renderer,level,score,lives);
                stats2(m_renderer,img_number0,img_number1,img_number2,img_number3,img_number4,img_number5,img_number6,img_number7,
                    img_number8,img_number9,level,score,lives);

                //racket
                switch(racket_type)
                {
                case 1:
                    print_image(m_renderer,img_racket_1,x,750,racket_w,15);
                    break;
                case 2:
                    print_image(m_renderer,img_racket_2,x,750,racket_w,15);
                    break;
                case 3:
                    print_image(m_renderer,img_racket_3,x,750,racket_w,15);
                    break;
                }
                //bricks
                print_bricks(m_renderer,120,30,img_brick11,img_brick12,img_brick13,img_brick21,img_brick22,img_brick23,img_brick31
                             ,img_brick32,img_brick33,img_brick41,img_brick42,img_brick43,img_brick51,img_brick52,img_brick53
                             ,img_brick61,img_brick62,img_brick63,img_gift,img_bomb,img_life,img_death,img_missile,img_pizza);
                //pointer line
                aalineRGBA(m_renderer,x+(racket_w/2),(750-ball.w/2),x+(racket_w/2)+75*cos(teta/100),750-ball.w-75*sin(teta/100),255,255,255,255);
                //ball
                ball.x=x+(racket_w/2)-(ball.w/2);
                ball.y=750-ball.w;
                ball.w=30;
                ball.h=30;
                switch(ball_type)
                {
                case 1:
                    SDL_QueryTexture(img_ball_1, NULL, NULL,&w,&h);
                    SDL_RenderCopy(m_renderer,img_ball_1 ,NULL,&ball);
                    break;
                case 2:
                    SDL_QueryTexture(img_ball_2, NULL, NULL,&w,&h);
                    SDL_RenderCopy(m_renderer,img_ball_2 ,NULL,&ball);
                    break;
                case 3:
                    SDL_QueryTexture(img_ball_3, NULL, NULL,&w,&h);
                    SDL_RenderCopy(m_renderer,img_ball_3 ,NULL,&ball);
                    break;
                }

                SDL_RenderPresent(m_renderer);

                while(SDL_PollEvent(&TETA))
                {
                    if (TETA.type==SDL_KEYDOWN)
                    {
                        switch( TETA.key.keysym.sym )
                        {
                            case SDLK_w:
                                if (teta+20<=257)
                                    teta+=20;
                                if (teta==157)
                                    teta+=20;
                                break;

                            case SDLK_s:
                                if (teta-20>=57)
                                    teta-=20;
                                if (teta==157)
                                    teta-=20;
                                break;

                            case SDLK_a:
                                if (x-20>=0)
                                    x-=20;
                                break;

                            case SDLK_d:
                                if (x+20<=(1200-racket_w))
                                    x+=20;
                                break;

                            case SDLK_SPACE:
                                flag_TETA=1;
                                break;

                            case SDLK_p:
                                Mix_PlayChannel(-1,click,0);
                                pause(m_renderer,img_pause,name_user,level,score,lives,x,teta,I,J,click);
                                break;
                        }
                    }
                }
            }
            teta/=100;

            ball.x=x+(racket_w/2)-(ball.w/2);
            ball.y=700;
            I=1;
            J=1;
        }

        //keyboard hit racket mover
        x=racket_mover(m_renderer,img_pause,racket_w,name_user,level,score,lives,x,teta,I,J,click);

        //Game over checking
        for (i=0;i<8;i++)
        {
            if ((brick_matris[13][i]%100)>0)
            {
                if ((brick_matris[13][i]/100)==0 || (brick_matris[13][i]/100)>6)
                {
                    flag_gameover=1;
                }
            }
        }
    }

    //final score divided by difficulty
    switch(game_difficulty)
    {
    case 1:
        score*=1;
        break;
    case 2:
        score*=5;
        score/=4;
        break;
    case 3:
        score*=3;
        score/=2;
        break;
    }

    //end of the game
    Mix_FreeMusic(backgsound_2);
    SDL_Delay(300);
    Mix_PlayChannel(-1,death,0);
    gameover(m_renderer, name_user, score);
    string SCORE=int_to_char(score);
    print_image(m_renderer, img_gameover,0,0,1200,800);
    textRGBA(mTexture,m_renderer,600,528,SCORE.c_str(),2,80,226,119,23,255);
    SDL_RenderPresent(m_renderer);
    SDL_Delay(3000);
    SDL_Event f;
    while(f.type != SDL_KEYDOWN)
    {
        print_image(m_renderer, img_gameover,0,0,1200,800);
        textRGBA(mTexture,m_renderer,600,528,SCORE.c_str(),2,80,226,119,23,255);
        SDL_RenderPresent(m_renderer);
        SDL_DestroyTexture(img_gameover);
        SDL_PollEvent(&f);
    }
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
	SDL_Quit();
    return 0;

}
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian )
{
    SDL_Rect rectangle ;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;


    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
    if (fill_boolian==1)
        SDL_RenderFillRect(Renderer, &rectangle);
    SDL_RenderDrawRect(Renderer, &rectangle);
    SDL_RenderPresent(Renderer);

}
void bring_image(SDL_Renderer *Renderer,SDL_Texture *img_texture,string name, int alpha,int x,int y,int W,int H )
{
    int w,h;
    const char* name_0=name.c_str();
    if (alpha==0)
    {
       img_texture = IMG_LoadTexture( Renderer,name_0);
       SDL_Rect location;
       location.x=x;
       location.y=y;
       location.w=W;
       location.h=H;
       SDL_QueryTexture(img_texture, NULL, NULL,&w,&h);
       SDL_RenderCopy(Renderer,img_texture,NULL,&location);
       SDL_RenderPresent(Renderer);
       SDL_DestroyTexture(img_texture);
    }
    else
    {
       int i=0;
       img_texture = IMG_LoadTexture( Renderer,name_0);
       SDL_Rect location;
       location.x=x;
       location.y=y;
       location.w=W;
       location.h=H;
       for(i=0;i<=220;i+=1)
        {
        SDL_SetTextureAlphaMod(img_texture,i);
        SDL_QueryTexture(img_texture, NULL, NULL,&w,&h);
        SDL_RenderCopy(Renderer,img_texture,NULL,&location);
        SDL_RenderPresent(Renderer);
        SDL_Delay(5);
        }
        SDL_DestroyTexture(img_texture);
    }
}
void key_click()
{
    SDL_Event f;
    while(f.type != SDL_KEYDOWN)
        SDL_PollEvent(&f);
}
int mouse_click(int x1,int x2,int y1,int y2)
{
   int xx,yy;
   SDL_Event e;
   SDL_PollEvent(&e);
        if(e.type==SDL_MOUSEBUTTONDOWN)
        {
            xx=e.button.x;
            yy=e.button.y;
            if(xx<=x2 && xx>=x1 && yy<=y2 && yy>=y1)
                return 1;
            else
                return 0;
        }
}
string username(SDL_Renderer *m_renderer)
{
    //username
    Mix_Chunk *click_key= Mix_LoadWAV("click_key.wav");
    Mix_VolumeChunk(click_key,50);
    Mix_Chunk *click = Mix_LoadWAV("click.wav");
    SDL_Event user;
    int distance=17, distance_digit=14 ,x_user=500;
    int flag_username=0, user_timer=0;
    int font=2;
    // 1 for lazy.ttf , 2 for arial.ttf , 3 for B Roya.ttf

    string name_user="";

    //warning
    textRGBA(mTexture,m_renderer,330,250,"WARNING! Backspace is not available!",font,30,255,0,0,255);

    while (user.key.keysym.sym != 13)
    {
        flag_username=1;
        if (user.type==SDL_KEYDOWN)
        {
            switch( user.key.keysym.sym )
            {
                case SDLK_0:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"0",font,24,200,200,200,200);
                    user_timer+=distance_digit;
                    name_user+= "0";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_1:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"1",font,24,200,200,200,200);
                    user_timer+=distance-5;
                    name_user+= "1";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_2:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"2",font,24,200,200,200,200);
                    user_timer+=distance_digit;
                    name_user+= "2";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_3:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"3",font,24,200,200,200,200);
                    user_timer+=distance_digit;
                    name_user+= "3";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_4:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"4",font,24,200,200,200,200);
                    user_timer+=distance_digit;
                    name_user+= "4";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_5:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"5",font,24,200,200,200,200);
                    user_timer+=distance_digit;
                    name_user+= "5";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_6:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"6",font,24,200,200,200,200);
                    user_timer+=distance_digit;
                    name_user+= "6";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_7:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"7",font,24,200,200,200,200);
                    user_timer+=distance_digit;
                    name_user+= "7";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_8:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"8",font,24,200,200,200,200);
                    user_timer+=distance_digit;
                    name_user+= "8";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_9:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"9",font,24,200,200,200,200);
                    user_timer+=distance_digit;
                    name_user+= "9";
                    //cout<<name_user<<endl;
                    break;


                case SDLK_SPACE:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405," ",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= " ";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_a:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"A",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "a";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_b:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"B",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "b";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_c:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"C",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "c";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_d:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"D",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "d";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_e:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"E",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "e";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_f:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"F",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "f";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_g:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"G",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "g";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_h:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"H",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "h";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_i:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"I",font,24,200,200,200,200);
                    user_timer+=distance-8;
                    name_user+= "i";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_j:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"J",font,24,200,200,200,200);
                    user_timer+=distance-5;
                    name_user+= "j";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_k:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"K",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "k";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_l:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"L",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "l";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_m:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"M",font,24,200,200,200,200);
                    user_timer+=distance+4;
                    name_user+= "m";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_n:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"N",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "n";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_o:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"O",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "o";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_p:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"P",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "p";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_q:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"Q",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "q";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_r:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"R",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "r";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_s:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"S",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "s";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_t:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"T",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "t";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_u:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"U",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "u";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_v:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"V",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "v";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_w:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"W",font,24,200,200,200,200);
                    user_timer+=distance+4;
                    name_user+= "w";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_x:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"X",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "x";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_y:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"Y",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "y";
                    //cout<<name_user<<endl;
                    break;

                case SDLK_z:
                    Mix_PlayChannel(-1,click_key,0);
                    textRGBA(mTexture,m_renderer,x_user + user_timer,405,"Z",font,24,200,200,200,200);
                    user_timer+=distance;
                    name_user+= "z";
                    //cout<<name_user<<endl;
                    break;
            }
            SDL_RenderPresent(m_renderer);
        }
        SDL_PollEvent(&user);
    }
    Mix_PlayChannel(-1,click,0);
    return(name_user);
}
void print_image(SDL_Renderer *m_renderer,SDL_Texture *img_texture, int x,int y,int w,int h)
{
    int W,H;
    SDL_QueryTexture(img_texture, NULL, NULL,&W,&H);
    SDL_Rect img;
    img.x=x;
    img.y=y;
    img.w=w;
    img.h=h;
    SDL_RenderCopy(m_renderer,img_texture ,NULL,&img);
}
void print_bricks(SDL_Renderer *m_renderer,int w,int h,SDL_Texture *img_brick11,SDL_Texture *img_brick12,SDL_Texture *img_brick13,SDL_Texture *img_brick21,SDL_Texture *img_brick22,
     SDL_Texture *img_brick23,SDL_Texture *img_brick31,SDL_Texture *img_brick32,SDL_Texture *img_brick33,SDL_Texture *img_brick41,SDL_Texture *img_brick42,SDL_Texture *img_brick43,
     SDL_Texture *img_brick51,SDL_Texture *img_brick52,SDL_Texture *img_brick53,SDL_Texture *img_brick61,SDL_Texture *img_brick62,SDL_Texture *img_brick63,SDL_Texture *img_gift,
     SDL_Texture *img_bomb,SDL_Texture *img_life,SDL_Texture *img_death,SDL_Texture *img_missile,SDL_Texture *img_pizza)
{
    int W,H;
    int i,k;
    SDL_QueryTexture(img_brick11, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick12, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick13, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick21, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick22, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick23, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick31, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick32, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick33, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick41, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick42, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick43, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick51, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick52, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick53, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick61, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick62, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_brick63, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_bomb, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_life, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_death, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_missile, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_pizza, NULL, NULL,&W,&H);
    SDL_QueryTexture(img_gift, NULL, NULL,&W,&H);

    for (k=0;k<14;k++)
    {
        for (i=0;i<8;i++)
        {
            SDL_Rect brick;
            brick.x=50 + (i*140);
            brick.y=50 + (k*50);
            brick.w=120;
            brick.h=30;
            if ((brick_matris[k][i]%100)>0)
            {
                switch (brick_matris[k][i]%100)
                {
                case 1:
                    SDL_RenderCopy(m_renderer,img_brick13 ,NULL,&brick);
                    break;
                case 2:
                    SDL_RenderCopy(m_renderer,img_brick12 ,NULL,&brick);
                    break;
                case 3:
                    SDL_RenderCopy(m_renderer,img_brick11 ,NULL,&brick);
                    break;
                case 4:
                    SDL_RenderCopy(m_renderer,img_brick23 ,NULL,&brick);
                    break;
                case 5:
                    SDL_RenderCopy(m_renderer,img_brick22 ,NULL,&brick);
                    break;
                case 6:
                    SDL_RenderCopy(m_renderer,img_brick21 ,NULL,&brick);
                    break;
                case 7:
                    SDL_RenderCopy(m_renderer,img_brick33 ,NULL,&brick);
                    break;
                case 8:
                    SDL_RenderCopy(m_renderer,img_brick32 ,NULL,&brick);
                    break;
                case 9:
                    SDL_RenderCopy(m_renderer,img_brick31 ,NULL,&brick);
                    break;
                case 10:
                    SDL_RenderCopy(m_renderer,img_brick43 ,NULL,&brick);
                    break;
                case 11:
                    SDL_RenderCopy(m_renderer,img_brick42 ,NULL,&brick);
                    break;
                case 12:
                    SDL_RenderCopy(m_renderer,img_brick41 ,NULL,&brick);
                    break;
                case 13:
                    SDL_RenderCopy(m_renderer,img_brick53 ,NULL,&brick);
                    break;
                case 14:
                    SDL_RenderCopy(m_renderer,img_brick52 ,NULL,&brick);
                    break;
                case 15:
                    SDL_RenderCopy(m_renderer,img_brick51 ,NULL,&brick);
                    break;
                case 16:
                    SDL_RenderCopy(m_renderer,img_brick63 ,NULL,&brick);
                    break;
                case 17:
                    SDL_RenderCopy(m_renderer,img_brick62 ,NULL,&brick);
                    break;
                case 18:
                    SDL_RenderCopy(m_renderer,img_brick61 ,NULL,&brick);
                    break;
                }
                switch (brick_matris[k][i]/100)
                {
                case 1:
                    SDL_RenderCopy(m_renderer,img_bomb ,NULL,&brick);
                    break;
                case 2:
                    SDL_RenderCopy(m_renderer,img_missile ,NULL,&brick);
                    break;
                case 3:
                    SDL_RenderCopy(m_renderer,img_life ,NULL,&brick);
                    break;
                case 4:
                    SDL_RenderCopy(m_renderer,img_death ,NULL,&brick);
                    break;
                case 5:
                    SDL_RenderCopy(m_renderer,img_pizza ,NULL,&brick);
                    break;
                case 6:
                    SDL_RenderCopy(m_renderer,img_gift ,NULL,&brick);
                    break;
                }
            }
        }
    }
}
int racket_mover(SDL_Renderer *m_renderer,SDL_Texture *img_pause,int racket_w,string name_user,int level,int score,int lives,
                 int x,double teta,int I,int J,Mix_Chunk *click)
{
    SDL_Event K;
        while(SDL_PollEvent(&K))
        {
            if (K.type==SDL_KEYDOWN)
            {
                switch( K.key.keysym.sym )
                {

                    case SDLK_a:
                        if (x-20>=0)
                            x-=20;
                        break;

                    case SDLK_d:
                        if (x+20<=(1200-racket_w))
                            x+=20;
                        break;
                    case SDLK_p:
                        Mix_PlayChannel(-1,click,0);
                        pause(m_renderer,img_pause,name_user,level,score,lives,x,teta,I,J,click);
                        break;
                }
            }
        }
    return(x);
}
void username_checker(SDL_Renderer *m_renderer, string username, int log_or_sign)
{
    int flag_username=0,file_size=0, i=0, k=0 , Max=0, flag_signup=0;
    fstream usernames;
    string name,help, score="Score : ", flag_score="";
    if (log_or_sign==1)
    {
        usernames.open("usernames.txt");
        while (getline(usernames,name) && flag_username==0)
        {
            //cout<<name<<endl;
            if (name==username)
            {
                username+=".txt";
                ifstream score_file;
                score_file.open(username.c_str());
                while (getline(score_file,help))
                {
                    file_size++;
                }
                score_file.close();
                score_file.open(username.c_str());
                while (getline(score_file,help))
                {
                    if (stoi(help)>Max)
                    {
                        Max=stoi(help);
                    }
                    i++;
                    if (file_size>=5)
                    {
                        if (i<=file_size && i>=(file_size-4))
                        {
                            k++;
                            flag_score=score+help;
                            textRGBA(mTexture,m_renderer,500,500+(k*30),"Score :",2,20,239,110,52,255);
                            textRGBA(mTexture,m_renderer,580,500+(k*30),help.c_str(),2,20,239,110,52,255);
                            //cout<<help<<endl;
                        }
                    }
                    else
                    {
                        if (k<=file_size)
                        {
                            k++;
                            flag_score=score+help;
                            textRGBA(mTexture,m_renderer,500,500+(k*30),"Score :",2,20,239,110,52,255);
                            textRGBA(mTexture,m_renderer,580,500+(k*30),help.c_str(),2,20,239,110,52,255);
                            //cout<<help<<endl;
                        }
                    }
                }
                //best score
                if (file_size>=1)
                {
                    string HELP;
                    HELP=int_to_char(Max);
                    textRGBA(mTexture,m_renderer,500,500,"Best Score :",2,20,239,110,52,255);
                    textRGBA(mTexture,m_renderer,625,500,HELP.c_str(),2,20,239,110,52,255);
                }
                SDL_RenderPresent(m_renderer);
                //SDL_Delay(1000);
                //cout<<endl<<file_size;
                flag_username=1;
            }
        }
        if (flag_username==0)
        {
            flag_not_valid=1;
            textRGBA(mTexture,m_renderer,450,330,"Username not valid!",2,30,255,0,0,255);
            SDL_RenderPresent(m_renderer);
            //SDL_Delay(1000);
        }
        else if (flag_username==1)
        {
            flag_not_valid=0;
        }
    }
    else if (log_or_sign==2)
    {
        usernames.open("usernames.txt");
        while (getline(usernames,name))
        {
            if (name==username)
            {
                flag_signup=1;
            }
        }
        usernames.close();
        if (flag_signup==0)
        {
            usernames.open("usernames.txt",ios::app);
            usernames<<endl<<username;
            help=username;
            help+=".txt";
            ofstream username_score(help.c_str());
            help=username;
            help+="_save.txt";
            ofstream username_save(help.c_str());
            usernames.close();
        }
        else if (flag_signup==1)
        {
            flag_not_valid_signup=1;
            textRGBA(mTexture,m_renderer,370,330,"Username available please log in!",2,30,255,0,0,255);
            SDL_RenderPresent(m_renderer);
            //SDL_Delay(1000);
        }
    }
}
string int_to_char(int a)
{
    int i,k=0,b=0,c=1,q;
    string s="";
    char ch;
    b=a;
    while (a>0)
    {
        a/=10;
        k++;
    }
    if (b==0)
    {
        ch=48;
        s+=ch;
    }
    else
    {
        for (i=k;i>=1;i--)
        {
            for (q=1;q<=i-1;q++)
            {
                c*=10;
            }
            ch=48+(b/c);
            s+=ch;
            b%=c;
            c=1;
        }
    }
    return(s);
}
void stats(SDL_Renderer *m_renderer, int level, int score, int lives)
{
    string LIVES,LEVEL,SCORE;
    LIVES = int_to_char(lives);
    LEVEL = int_to_char(level);
    SCORE = int_to_char(score);
    textRGBA(mTexture,m_renderer,245,550,LEVEL.c_str(),2,30,88,53,38,255);
    textRGBA(mTexture,m_renderer,625,550,SCORE.c_str(),2,30,88,53,38,255);
    textRGBA(mTexture,m_renderer,1010,550,LIVES.c_str(),2,30,88,53,38,255);
}
void gameover(SDL_Renderer *m_renderer, string username, int score)
{
    fstream save_file;
    username+=".txt";
    save_file.open(username.c_str(),ios::app);
    save_file<<score<<endl;
    save_file.close();
}
void pause(SDL_Renderer *m_renderer, SDL_Texture *img_pause,
        string name, int level, int score, int lives, int x, double teta, int I, int J,Mix_Chunk *click)
{
    print_image(m_renderer,img_pause,300,100,600,500);
    SDL_RenderPresent(m_renderer);
    int flag_pause=0;
    SDL_Event P;
    while(flag_pause==0)
    {
        if (mouse_click(500,720,240,285)==1)
        {
            Mix_PlayChannel(-1,click,0);
            flag_pause=1;
        }
        if (mouse_click(520,670,320,360)==1)
        {
            Mix_PlayChannel(-1,click,0);
            textRGBA(mTexture,m_renderer,680,320,"GAME SAVED!",2,30,245,105,47,255);
            SDL_RenderPresent(m_renderer);
            SDL_Delay(1000);
            print_image(m_renderer,img_pause,300,100,600,500);
            SDL_RenderPresent(m_renderer);

            save(name,level,score,lives,x,teta,I,J);
        }
        if (mouse_click(560,645,390,430)==1)
        {
            SDL_Delay(500);
            //SDL_DestroyWindow( m_window );
            SDL_DestroyRenderer( m_renderer );
            SDL_Quit();
        }
    }
}
void save(string name, int level, int score, int lives, int x, double teta, int I, int J)
{
    string help;
    int i,k;
    help=name;
    help+="_save.txt";
    ofstream name_save(help.c_str(),ios::app);
    for (i=0;i<14;i++)
    {
        for (k=0;k<8;k++)
        {
            name_save<<brick_matris[i][k]<<" ";
        }
        name_save<<endl;
    }
    name_save<<game_difficulty<<" "<<racket_type<<" "<<ball_type<<endl<<level<<" "<<score<<" "<<lives<<endl<<ball_damage<<endl;
    name_save.close();
}
void load(string name)
{
    int i,k,filesize=0,t=1;
    string help;
    name+="_save.txt";
    ifstream save_file_size(name.c_str());
    if (save_file_size.good())
        //cout<<"YES"<<endl;
    while (getline(save_file_size,help))
    {
        filesize++;
    }
    save_file_size.close();
    ifstream save_file(name.c_str());
    if (save_file.good())
        //cout<<"YES"<<endl;
    while (getline(save_file,help) && t<=(filesize-18))
    {
        t++;
    }
    for (i=0;i<14;i++)
    {
        for (k=0;k<8;k++)
        {
            save_file>>brick_matris[i][k];
            //cout<<brick_matris[i][k]<<" ";
        }
        //cout<<endl;
    }
    save_file>>game_difficulty>>racket_type>>ball_type>>level>>score>>lives>>ball_damage;
    //cout<<game_difficulty<<" "<<racket_type<<" "<<ball_type<<endl<<level<<" "<<score<<" "<<lives<<endl;
    save_file.close();
}
void stats2(SDL_Renderer *m_renderer,SDL_Texture *img_number0,SDL_Texture *img_number1,SDL_Texture *img_number2,
            SDL_Texture *img_number3,SDL_Texture *img_number4,SDL_Texture *img_number5,SDL_Texture *img_number6,
            SDL_Texture *img_number7,SDL_Texture *img_number8,SDL_Texture *img_number9,int level,int score,int lives)
{
    int tedad,help=1,counter=0,i,k,R,R_h=45,R_y=545;
    //level
    tedad=tedad_ragham(level);
    for (i=tedad;i>0;i--)
    {
        help=1;
        for (k=1;k<i;k++)
        {
            help*=10;
        }
        R=(level/help)%10;
        switch(R)
        {
        case 0:
            print_image(m_renderer,img_number0,245+counter,R_y,30,R_h);
            break;
        case 1:
            print_image(m_renderer,img_number1,245+counter,R_y,30,R_h);
            break;
        case 2:
            print_image(m_renderer,img_number2,245+counter,R_y,30,R_h);
            break;
        case 3:
            print_image(m_renderer,img_number3,245+counter,R_y,30,R_h);
            break;
        case 4:
            print_image(m_renderer,img_number4,245+counter,R_y,30,R_h);
            break;
        case 5:
            print_image(m_renderer,img_number5,245+counter,R_y,30,R_h);
            break;
        case 6:
            print_image(m_renderer,img_number6,245+counter,R_y,30,R_h);
            break;
        case 7:
            print_image(m_renderer,img_number7,245+counter,R_y,30,R_h);
            break;
        case 8:
            print_image(m_renderer,img_number8,245+counter,R_y,30,R_h);
            break;
        case 9:
            print_image(m_renderer,img_number9,245+counter,R_y,30,R_h);
            break;
        }
        counter+=20;
    }

    //score
    help=1;
    counter=0;
    tedad=tedad_ragham(score);
    for (i=tedad;i>0;i--)
    {
        help=1;
        for (k=1;k<i;k++)
        {
            help*=10;
        }
        R=(score/help)%10;
        switch(R)
        {
        case 0:
            print_image(m_renderer,img_number0,625+counter,R_y,30,R_h);
            break;
        case 1:
            print_image(m_renderer,img_number1,625+counter,R_y,30,R_h);
            break;
        case 2:
            print_image(m_renderer,img_number2,625+counter,R_y,30,R_h);
            break;
        case 3:
            print_image(m_renderer,img_number3,625+counter,R_y,30,R_h);
            break;
        case 4:
            print_image(m_renderer,img_number4,625+counter,R_y,30,R_h);
            break;
        case 5:
            print_image(m_renderer,img_number5,625+counter,R_y,30,R_h);
            break;
        case 6:
            print_image(m_renderer,img_number6,625+counter,R_y,30,R_h);
            break;
        case 7:
            print_image(m_renderer,img_number7,625+counter,R_y,30,R_h);
            break;
        case 8:
            print_image(m_renderer,img_number8,625+counter,R_y,30,R_h);
            break;
        case 9:
            print_image(m_renderer,img_number9,625+counter,R_y,30,R_h);
            break;
        }
        counter+=20;
    }

    //lives
    help=1;
    counter=0;
    tedad=tedad_ragham(lives);
    for (i=tedad;i>0;i--)
    {
        help=1;
        for (k=1;k<i;k++)
        {
            help*=10;
        }
        R=(lives/help)%10;
        switch(R)
        {
        case 0:
            print_image(m_renderer,img_number0,1010+counter,R_y,30,R_h);
            break;
        case 1:
            print_image(m_renderer,img_number1,1010+counter,R_y,30,R_h);
            break;
        case 2:
            print_image(m_renderer,img_number2,1010+counter,R_y,30,R_h);
            break;
        case 3:
            print_image(m_renderer,img_number3,1010+counter,R_y,30,R_h);
            break;
        case 4:
            print_image(m_renderer,img_number4,1010+counter,R_y,30,R_h);
            break;
        case 5:
            print_image(m_renderer,img_number5,1010+counter,R_y,30,R_h);
            break;
        case 6:
            print_image(m_renderer,img_number6,1010+counter,R_y,30,R_h);
            break;
        case 7:
            print_image(m_renderer,img_number7,1010+counter,R_y,30,R_h);
            break;
        case 8:
            print_image(m_renderer,img_number8,1010+counter,R_y,30,R_h);
            break;
        case 9:
            print_image(m_renderer,img_number9,1010+counter,R_y,30,R_h);
            break;
        }
        counter+=20;
    }
}
int tedad_ragham(int a)
{
    int i=0;
    if (a==0)
        return(1);
    else
    {
        while (a>0)
        {
            i++;
            a/=10;
        }
        return(i);
    }
}
