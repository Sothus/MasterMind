#include <SPI.h>
#include <Gamebuino.h>

Gamebuino gb;

class Figure
{
  virtual void draw() = 0;
};

class Circle: public Figure
{
  public:
    Circle(): x_(0), y_(), r_(0){}
    Circle(int x, int y, int r): x_(x), y_(y), r_(r){}
    void draw();
  protected:
    int x_, y_, r_;
};

void Circle::draw()
{
  gb.display.setColor(BLACK);
  gb.display.drawCircle(this->x_, this->y_, this->r_);
}

class CircleChar: public Circle
{
  public:
    CircleChar(): Circle(), char_(0){}
    CircleChar(int x, int y, int r, int chara): Circle(x, y, r), char_(chara){}
    void draw();
  private:
    int char_;
};

void CircleChar::draw()
{
  Circle::draw();
  gb.display.drawChar(this->x_ - 1, this->y_ - 2, this->char_,1);
  
}



void setGameTitle()
{
  gb.titleScreen(F("Mastermind"));
}

CircleChar crArray[] = {CircleChar(15, 15, 4, '1'),
                        CircleChar(8, 40, 5, '2'),
                        CircleChar(20, 40, 5, '2'),
                        CircleChar(32, 40, 5, '2'),
                        CircleChar(44, 40, 5, '2'),};
int crArrayCount = 5;

void setup()
{
  gb.begin();
  setGameTitle();
  crArray[0].draw();
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
  for(int i = 0; i < crArrayCount; i++)
  {
    crArray[i].draw();
  }
  
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

