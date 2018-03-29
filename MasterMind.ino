#include <SPI.h>
#include <Gamebuino.h>


/*************MENU DECLARATION******************/
#define MENULENGTH 4
#define UNSELECTED -1
#define STARTGAME 0
#define HIGHSCORES 1
#define OPTIONS 2
#define CREDITS 3
//1. Start Game
//2. Highscores
//3. Options
//4. Credits
const char strStartGame[] PROGMEM   = "Start game";
const char strHighScores[] PROGMEM  = "Highscores";
const char strOptions[] PROGMEM     = "Options";
const char strCredits[] PROGMEM     = "Credits";

const char* const menu[MENULENGTH] PROGMEM = {
  strStartGame,
  strHighScores,
  strOptions,
  strCredits, 
};

/*************GAMEBUINO OBJECT DECLARATION********************/
Gamebuino gb;

/*************INGAME CLASSES DEFINITION**********************/
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
  gb.display.drawChar(this->x_ - 1, this->y_ - 2, this->char_, 1);
  
}


/**************GAME LOGIC********************/
CircleChar crArray[] = {CircleChar(6 , 41, 4, '2'),
                        CircleChar(18, 41, 4, '2'),
                        CircleChar(30, 41, 4, '2'),
                        CircleChar(42, 41, 4, '2'),
                        CircleChar(54, 41, 4, '2'),
                        CircleChar(6 , 29, 4, '2'),
                        CircleChar(6 , 17, 4, '2'),
                        CircleChar(6 , 5, 4, '2'),
                      };
int crArrayCount = 8;

void setup()
{
  Serial.begin(9600);//FOR DEBUGGING
  gb.begin();
  goToGameTitle();
}


void loop()
{
  switch(gb.menu(menu, MENULENGTH))
  {
    case UNSELECTED:
      goToGameTitle();
      break;
    case STARTGAME:
      game();
      break;
    case HIGHSCORES:
      break;
    case OPTIONS:
      break;
    case CREDITS:
      break;
    default:
      break;
  
  }
}


void goToGameTitle()
{
  gb.titleScreen(F("Mastermind"));
}


void game()
{
  boolean win = false;
  while(win == false)
  {
    if(gb.update())
    {
      draw();  
    }
    
  }
}

//84x48 
void draw()
{
  Serial.println(F("DRAWING"));
  for(int i = 0; i < crArrayCount; i++)
  {
    
    crArray[i].draw();
  }
  drawGameMesh();
  drawScores();
  
}

void drawGameMesh()
{
  Serial.println(F("DRAWING MESH"));
  gb.display.setColor(GRAY);
  gb.display.drawFastHLine(0, 35, 84);
  gb.display.drawFastHLine(0, 23, 84);
  gb.display.drawFastHLine(0, 11, 84);
  gb.display.drawFastVLine(60, 0, 48);
}

void drawScores()
{
  gb.display.setColor(BLACK);
  gb.display.drawChar(62, 39, '+', 1);
  gb.display.drawChar(65, 39, '1', 1);
  gb.display.drawChar(69, 39, '-', 1);
  gb.display.drawChar(72, 39, '1', 1);
  gb.display.drawChar(77, 39, '?', 1);
  gb.display.drawChar(80, 39, '1', 1);
}


