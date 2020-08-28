/*
SNAKE IN C++ 
Originally for TurboC++ on the DOSBox emulator

REFERENCE:
27 ESC
72 UP    75LEFT   77RIGHT   80DOWN
*/

#include <iostream.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <math.h>
#include <dos.h>

void run();

class Vect
{
public:
  float xvec;
  float yvec;
  Vect() {}
  Vect(float x, float y)
  {
    xvec = x;
    yvec = y;
  }
};

class Snake
{
public:
  float x, y;
  int total;
  int xspeed, yspeed;
  Vect tail[30];
  Snake()
  {
    for (int i = 0; i < 30; i++)
    {
      tail[i].xvec = -20;
      tail[i].yvec = -20;
    }
    x = 200;
    y = 200;
    xspeed = 1;
    yspeed = 0;
    total = 1;
  }
  void sUpdate();
  void sShow();
  void sDeath();
  void changeDir();
  void dir(int x1, int y1);
  int sEat(Vect io);
};

Vect food(300, 300);
void generateFood();
void border();
int scl = 20;
int rows = 440 / scl;
int cols = 600 / scl;

void Snake::sUpdate()
{
  x += xspeed * scl;
  y += yspeed * scl;
  for (int i = 0; i < 29; i++)
  {
    tail[i] = tail[i + 1];
  }
  if (total >= 1)
  {
    tail[total - 1] = Vect(x, y);
  }
  if (x < 20)
  {
    x = 20;
    xspeed = 0;
  }
  if (x > 620)
  {
    x = 620;
    xspeed = 0;
  }
  if (y < 20)
  {
    y = 20;
    yspeed = 0;
  }
  if (y > 460)
  {
    y = 460;
    yspeed = 0;
  }
}

int Snake::sEat(Vect io)
{
  float d = sqrt(pow(io.xvec - x, 2) + pow(io.yvec - y, 2));
  if (d < 2)
  {
    total++;
    return 1;
  }
  else
  {
    return 0;
  }
}

void Snake::sShow()
{
  setfillstyle(SOLID_FILL, WHITE);
  for (int i = 0; i <= total; i++)
  {
    rectangle(tail[i].xvec, tail[i].yvec, tail[i].xvec + scl, tail[i].yvec + scl);
  }

  rectangle(x, y, x + scl, y + scl);
}

void Snake::sDeath()
{
  for (int i = 2; i < total; i++)
  {
    if (sqrt(pow((x - tail[i].xvec), 2) + pow((y - tail[i].yvec), 2)) < 3)
    {
      total = 0;
      cout << "You Died";
    }
  }
}

void generateFood()
{
  food.xvec = floor((random(cols)) * scl);
  food.yvec = floor((random(rows)) * scl);
  if (food.xvec < 20)
  {
    food.xvec = 20;
  }
  if (food.xvec > 620)
  {
    food.xvec = 620;
  }
  if (food.yvec < 20)
  {
    food.yvec = 20;
  }
  if (food.yvec > 460)
  {
    food.yvec = 460;
  }
}

void Snake::changeDir()
{
  char c;
  if (kbhit())
  {
    c = getch();
  }
  switch (c)
  {
  case 72: //UP
    xspeed = 0;
    yspeed = -1;
    break;

  case 80:
    xspeed = 0;
    yspeed = 1;
    break;

  case 75:
    xspeed = -1;
    yspeed = 0;
    break;

  case 77:
    xspeed = 1;
    yspeed = 0;
    break;
  }
}

void border()
{
  setcolor(13);
  setlinestyle(0, 1, 2);
  line(10, 10, 630, 10);
  line(10, 470, 630, 470);
  line(10, 10, 10, 470);
  line(630, 10, 630, 470);

  setcolor(1);
  setlinestyle(3, 1, 2);
  line(15, 15, 625, 15);
  line(15, 465, 625, 465);
  line(15, 15, 15, 465);
  line(625, 15, 625, 465);

  setcolor(3);
  setlinestyle(0, 1, 3);
  line(20, 20, 620, 20);
  line(20, 460, 620, 460);
  line(20, 20, 20, 460);
  line(620, 20, 620, 460);

  setcolor(1);
}

void run()
{
  Snake snake;
  char escp;

  while (1)
  {
    border();
    // snake.sDeath();
    setlinestyle(0, 0, 3);
    snake.sUpdate();
    snake.sShow();
    snake.changeDir();
    if (snake.sEat(food))
    {
      generateFood();
    }

    setcolor(4);
    rectangle(food.xvec, food.yvec, food.xvec + 20, food.yvec + 20);
    setcolor(9);
    delay(150);
    cleardevice();

    if (kbhit())
    {
      escp = getch();
      if (escp == 27)
      {
        break;
      }
    }
  }
  return;
}

int main()
{
  char ch;
  int gd = DETECT, gm, running = 1;
  initgraph(&gd, &gm, "C://TURBOC3//BGI");
  while (running == 1)
  {
    border();
    setcolor(11);
    settextstyle(10, HORIZ_DIR, 9);
    outtextxy(70, 10, "SNAKE");
    settextstyle(10, HORIZ_DIR, 2);
    outtextxy(180, 200, "PRESS P TO  PLAY.");
    outtextxy(180, 240, "PRESS I  FOR INFO.");
    outtextxy(180, 280, "PRESS E TO  EXIT.");

    if (kbhit())
    {
      ch = getch();
    }

    if (ch == 112)
    {
      run();
    }
    else if (ch == 105)
    {
      cleardevice();
      border();
      settextstyle(10, HORIZ_DIR, 1);
      setcolor(11);
      outtextxy(140, 160, "THE CLASSIC SNAKE GAME");
      outtextxy(140, 200, "  RECREATED IN C++ !");
      outtextxy(140, 240, "MADE BY DENNIS JOHNSON");
      delay(4000);
      cleardevice();
    }
    else if (ch == 101)
    {
      cleardevice();
      border();
      outtextxy(250, 200, "EXITING....");
      delay(2000);
      running = 0;
    }
    ch = 0;
  }
  closegraph();
  return 0;
}
