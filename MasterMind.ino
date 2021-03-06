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


class Circle: 
public Figure
{
public:
  Circle(): 
  x_(0), y_(), r_(0){
  }
  Circle(int x, int y, int r): 
  x_(x), y_(y), r_(r){
  }
  void draw();
  int x();
  int y();
  int r();
protected:
  int x_, y_, r_;
};


void Circle::draw()
{
  gb.display.setColor(BLACK);
  gb.display.drawCircle(this->x_, this->y_, this->r_);
}

int Circle::x()
{
  return this->x_; 
}

int Circle::y()
{
  return this->y_; 
}

int Circle::r()
{
  return this->r_; 
}


class CircleChar: 
public Circle
{
public:
  CircleChar(): 
  Circle(), char_(0){
  }
  CircleChar(int x, int y, int r, int chara): 
  Circle(x, y, r), char_(chara){
  }
  void draw();
  int getChar();
  void setChar(int char_);
private:
  int char_;
};

void CircleChar::draw()
{
  Circle::draw();
  gb.display.drawChar(this->x_ - 1, this->y_ - 2, this->char_, 1);
}

int CircleChar::getChar()
{
  return this->char_; 
}

void CircleChar::setChar(int char_)
{
  this->char_ = char_; 
}


/**************GAME LOGIC********************/
#define crRows 4
#define crColumns 5

CircleChar crArray[crRows][crColumns] = {
  {
    CircleChar(6 , 41, 4, '0'),
    CircleChar(18, 41, 4, '2'),
    CircleChar(30, 41, 4, '2'),
    CircleChar(42, 41, 4, '2'),
    CircleChar(54, 41, 4, '9'),
  }
  ,
  {  
    CircleChar(6 , 29, 4, '2'),

  }
  ,
  {  
    CircleChar(6 , 17, 4, '2'),
  }
  ,
  {  
    CircleChar(6 , 5, 4, '2'),  
  }
};


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
    highscores();
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

/***********GAME_BLOCK***************/
int cursor = 0;

void game()
{
  boolean win = false;
  boolean exit = false;


  while(win == false && exit == false)
  {
    if(gb.update())
    {
      switch(pressedButton())
      {
      case BTN_C:
        exit = true;
        break;
      case BTN_LEFT:
        moveCursorLeft();
        break;
      case BTN_RIGHT:
        moveCursorRight();
        break;
      case BTN_UP:
        increaseNumberAtPos(cursor);
        break;
      case BTN_DOWN:
        decreaseNumberAtPos(cursor);
        break;
      default:
        break; 
      }

      draw(); 
    }

  }
}

void increaseNumberAtPos(int position)
{
  int positionChar = crArray[0][position].getChar();
  Serial.print(positionChar);
  if(positionChar < 56)
  {
    positionChar++;
    crArray[0][position].setChar(positionChar); 
  }
}

void decreaseNumberAtPos(int position)
{
  int positionChar = crArray[0][position].getChar();
  Serial.print(positionChar);
  if(positionChar > 48)
  {
    positionChar--;
    crArray[0][position].setChar(positionChar); 
  }

}

void moveCursorLeft()
{
  if(cursor > 0)
  {
    cursor--; 
  }
}

void moveCursorRight()
{
  if(cursor < 4)
  {
    cursor++; 
  }
}


//84x48 
void draw()
{
  //Serial.println(F("DRAWING"));
  for(int i = 0; i < crRows; i++)
  {
    for(int j = 0; j < crColumns; j++)
    {
      crArray[i][j].draw();
    }


  }
  drawCursor();
  drawGameMesh();
  drawScores();

}

void drawCursor()
{
  int x_pos = crArray[0][0].x();
  int y_pos = crArray[0][0].y();
  int delta = crArray[0][1].x() - x_pos;
  Circle cursorCircle(x_pos + (cursor * delta), y_pos, 5);
  cursorCircle.draw();
}

void drawGameMesh()
{
  //Serial.println(F("DRAWING MESH"));
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

/*************HIGHSCORES_BLOCK*************/

void highscores()
{
  boolean exit = false;
  Serial.println(F("BEGIN"));
  while(exit == false)
  {
    Serial.println(F("WHILE"));
    if(gb.update())
    {
      Serial.println(F("IF"));
      switch(pressedButton())
      {
      case BTN_C:
        Serial.println(F("EXITING"));
        exit=true;
        break;
      default:
        break;

      }

    } 
  }
}

/***********OPTIONS_BLOCK*************/

void options()
{
  boolean exit = false;
  while(exit == false)
  {
    if(gb.update())
    {
      switch(pressedButton())
      {
      case BTN_C:
        exit = true;
        break;
      default:
        break;
      }
    } 
  }
}

/************CREDITS_BLOCK*******************/
void credits()
{
  boolean exit = false;
  while(exit == false)
  {
    if(gb.update())
    {
      switch(pressedButton())
      {
      case BTN_C:
        exit = true;
        break;
      default:
        break;
      }
    } 
  }

}

/********UTILS_BLOCK**********/

int pressedButton()
{
  if(gb.buttons.pressed(BTN_A))
  {
    return BTN_A; 
  }
  else if(gb.buttons.pressed(BTN_B))
  {
    return BTN_B;
  }
  else if(gb.buttons.pressed(BTN_C))
  {
    return BTN_C; 
  }
  else if(gb.buttons.pressed(BTN_UP))
  {
    return BTN_UP; 
  }
  else if(gb.buttons.pressed(BTN_DOWN))
  {
    return BTN_DOWN; 
  }
  else if(gb.buttons.pressed(BTN_LEFT))
  {
    return BTN_LEFT;
  }
  else if(gb.buttons.pressed(BTN_RIGHT))
  {
    return BTN_RIGHT;
  }
  else
  {
    return -1; 
  }
}












