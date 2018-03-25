#include <SPI.h>
#include <Gamebuino.h>

Gamebuino gb;


void setGameTitle()
{
  gb.titleScreen(F("Mastermind"));
}

void setup()
{
  gb.begin();
  setGameTitle();
}

void input()
{
  if(gb.buttons.pressed(BTN_C))
  {
    setGameTitle();
  }
}

void update()
{
  
}

void draw()
{
  
}


void loop()
{
  if(gb.update())
  {
    input();
    update();
    draw();
  }
}

