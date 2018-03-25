#include <SPI.h>
#include <Gamebuino.h>

Gamebuino gb;

class Circle
{
  public:
    Circle(): x_(0), y_(), r_(0){}
    Circle(int x, int y, int r): x_(x), y_(y), r_(r){}
    draw();
  private:
    int x_, y_, r_;
};

Circle::draw()
{
  gb.display.setColor(BLACK);
  gb.display.drawCircle(this->x_, this->y_, this->r_);
}

void setGameTitle()
{
  gb.titleScreen(F("Mastermind"));
}

Circle cr(10,10,5);

void setup()
{
  gb.begin();
  setGameTitle();
  cr.draw();
  
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
  cr.draw();
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

