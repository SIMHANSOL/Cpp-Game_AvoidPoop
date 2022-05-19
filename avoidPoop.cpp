#include < iostream >
#include < time.h >
#include < conio.h >
#include < Windows.h >
#include < math.h >

int poop_max = 20;
int x_max = 80;
int y_max = 28;
int player_speed = 2;
int collision_box = 1;
int random_range(int _x1, int _x2)
{
  int range = (_x2 - _x1) + 1;
  return (rand() % range) + _x1;
}

void goto_xy(int _x, int _y)
{
  COORD pos = {
      _x,
      _y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class player
{
public:
  int x;
  int y;
  player()
  {
    x = (int)(x_max / 2);
    y = y_max;
  }
};

class poop
{
public:
  int x;
  int y;
  poop()
  {
    x = random_range(0, x_max);
    y = 0;
  }
  void y_down()
  {
    if (y >= y_max)
    {
      x = random_range(0, x_max);
      y = 0;
    }
    else if (y != 0)
    {
      y += 1;
    }
    else if (random_range(1, 100) >= 95)
    {
      y = 1;
    }
  }
};

int main()
{
  srand(time(NULL));
  player player;
  poop *poop_ptr = new poop[poop_max];
re_game:
  int score = 0;
  int game_over = 0;
  while (1)
  {
    score++;
    goto_xy((int)x_max / 2, 0);
    printf("현재 점수: %d", score);
    int key = 0;
    if (_kbhit() == 1)
    {
      key = _getch();
    }
    switch (key)
    {
    case 75:
      player.x -= 2;
      break;
    case 77:
      player.x += 2;
      break;
    }
    goto_xy(player.x, player.y);
    printf("■");
    for (int i = 0; i < poop_max; i++)
    {
      poop_ptr[i].y_down();
      goto_xy(poop_ptr[i].x, poop_ptr[i].y);
      int x_collision = abs(player.x - poop_ptr[i].x);
      int y_collision = abs(player.y - poop_ptr[i].y);
      if ((x_collision <= collision_box) && (y_collision == 0))
      {
        game_over = 1;
        printf("※");
        goto_xy(poop_ptr[i].x - 2, poop_ptr[i].y);
        printf("♨");
        goto_xy(poop_ptr[i].x + 2, poop_ptr[i].y);
        printf("♨");
      }
      else if (poop_ptr[i].y != 0)
      {
        printf("●");
      }
    }
    goto_xy(0, y_max + 1);
    for (int i = 0; i < x_max; i++)
    {
      printf("-");
    }
    if (game_over == 1)
    {
      Sleep(4000);
      goto_xy((int)x_max / 2, (int)y_max / 2);
      printf("당신의 점수는요: %d", score);
      goto_xy((int)x_max / 2, ((int)y_max / 2) + 1);
      printf("재시도는 아무 키나 누르세요.");
      fflush(stdin);
      _getch();
      goto re_game;
    }
    system("cls");
  }
  return 0;
}