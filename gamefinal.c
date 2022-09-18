#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

const int width = 600;
const int height = 600;
const int waitTime = 50;
const int offSet = 50;

static int grid[10][10];

typedef struct Robot
{
  char *direction;
  int x;
  int y;
} Robot;

Robot *createRobot(char *direction, int x, int y)
{
  Robot *robot = (Robot *)malloc(sizeof(Robot));
  robot->direction = strdup(direction);
  robot->x = x;
  robot->y = y;
  return robot;
}

void fillGrid(Robot *robot1)
{
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      grid[i][j] = 0;
    }
  }

  int xblocks[4], yblocks[4];

  for (int i; i < 4; i++)
  {
    do
    {
      xblocks[i] = rand() % 10;
      yblocks[i] = rand() % 10;
    }

    // Making sure that the blocks are neither on top of the robot or each other
    while ((xblocks[i] == robot1->x && yblocks[i] == robot1->y) || (grid[yblocks[i]][xblocks[i]] == 1));
    grid[yblocks[i]][xblocks[i]] = 1;
  }

  int xmarker, ymarker;

  do
  {
    xmarker = rand() % 10;
    ymarker = rand() % 10;
  }
  // Making sure that marker is neither on top of the block or robot
  while ((grid[ymarker][xmarker] == 1) || (xmarker == robot1->x && ymarker == robot1->y));
  grid[ymarker][xmarker] = 2;
}

void drawBackground()
{
  background();
  for (int rows = 0; rows < 10; rows++)
  {
    for (int cols = 0; cols < 10; cols++)
    {
      switch (grid[rows][cols])
      {
      case 0: // Empty square
        setColour(gray);
        break;
      case 1: // Block
        setColour(red);
        fillRect(cols * 50 + offSet, rows * 50 + offSet, 50, 50);
        break;
      case 2: // Marker
        setColour(gray);
        fillRect(cols * 50 + offSet, rows * 50 + offSet, 50, 50);
        break;
      }
      drawRect(cols * 50 + offSet, rows * 50 + offSet, 50, 50);
    }
  }
}

// Robot has four drawing options in order to look pointed towards dedicated cardinal direction
void drawRobot(Robot *robot1)
{
  foreground();
  setColour(green);
  int x = robot1->x * 50 + offSet;
  int y = robot1->y * 50 + offSet;

  if (strcmp(robot1->direction, "south") == 0)
  {
    int xtriangle[3] = {x, x + 25, x + 50};
    int ytriangle[3] = {y, y + 50, y};
    drawPolygon(3, xtriangle, ytriangle);
    fillPolygon(3, xtriangle, ytriangle);
  }
  else if (strcmp(robot1->direction, "west") == 0)
  {
    int xtriangle[3] = {x, x + 50, x + 50};
    int ytriangle[3] = {y + 25, y, y + 50};
    drawPolygon(3, xtriangle, ytriangle);
    fillPolygon(3, xtriangle, ytriangle);
  }
  else if (strcmp(robot1->direction, "north") == 0)
  {
    int xtriangle[3] = {x, x + 25, x + 50};
    int ytriangle[3] = {y + 50, y, y + 50};
    drawPolygon(3, xtriangle, ytriangle);
    fillPolygon(3, xtriangle, ytriangle);
  }
  else if (strcmp(robot1->direction, "east") == 0)
  {
    int xtriangle[3] = {x, x, x + 50};
    int ytriangle[3] = {y, y + 50, y + 25};
    drawPolygon(3, xtriangle, ytriangle);
    fillPolygon(3, xtriangle, ytriangle);
  }
}

void forward(Robot *robot1)
{
  foreground();
  clear();
  if (strcmp(robot1->direction, "east") == 0)
  {
    robot1->x = robot1->x + 1;
  }
  else if (strcmp(robot1->direction, "south") == 0)
  {
    robot1->y = robot1->y + 1;
  }
  else if (strcmp(robot1->direction, "west") == 0)
  {
    robot1->x = robot1->x - 1;
  }
  else if (strcmp(robot1->direction, "north") == 0)
  {
    robot1->y = robot1->y - 1;
  }
  drawRobot(robot1);
  sleep(waitTime);
}

void left(Robot *robot1)
{
  foreground();
  clear();
  if (strcmp(robot1->direction, "east") == 0)
  {
    robot1->direction = "north";
  }
  else if (strcmp(robot1->direction, "west") == 0)
  {
    robot1->direction = "south";
  }
  else if (strcmp(robot1->direction, "north") == 0)
  {
    robot1->direction = "west";
  }
  else if (strcmp(robot1->direction, "south") == 0)
  {
    robot1->direction = "east";
  }
  drawRobot(robot1);
  sleep(waitTime);
}

void right(Robot *robot1)
{
  foreground();
  clear();
  if (strcmp(robot1->direction, "east") == 0)
  {
    robot1->direction = "south";
  }
  else if (strcmp(robot1->direction, "south") == 0)
  {
    robot1->direction = "west";
  }
  else if (strcmp(robot1->direction, "west") == 0)
  {
    robot1->direction = "north";
  }
  else if (strcmp(robot1->direction, "north") == 0)
  {
    robot1->direction = "east";
  }
  drawRobot(robot1);
  sleep(waitTime);
}

int atMarker(Robot *robot1)
{
  if (grid[robot1->y][robot1->x] == 2)
  {
    return 1;
  }
  return 0;
}

// Checks if in front of the robot is either an end of the grid or a block
int canMoveForward(Robot *robot1)
{
  if (((strcmp(robot1->direction, "east") == 0) && robot1->x + 1 <= 9 && grid[robot1->y][robot1->x + 1] != 1) ||
      ((strcmp(robot1->direction, "south") == 0) && robot1->y + 1 <= 9 && grid[robot1->y + 1][robot1->x] != 1) ||
      ((strcmp(robot1->direction, "west") == 0) && robot1->x - 1 >= 0 && grid[robot1->y][robot1->x - 1] != 1) ||
      ((strcmp(robot1->direction, "north") == 0) && robot1->y - 1 >= 0 && grid[robot1->y - 1][robot1->x] != 1))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// Function checks if command arguments of the user are correct
void canRun(Robot *robot1)
{
  if ((robot1->x > 9) || (robot1->x < 0) || (robot1->y > 9) || (robot1->y < 0))
  {
    fprintf(stderr, "Position input to the program is not valid, please QUIT (CTRL + C)\n");
  }
  if (!((strcmp(robot1->direction, "south") == 0) || (strcmp(robot1->direction, "north") == 0) ||
        (strcmp(robot1->direction, "east") == 0) || (strcmp(robot1->direction, "west") == 0)))
  {
    fprintf(stderr, "Direction input to the program is not valid, please QUIT (CTRL + C)\n");
  }
}

// Algorithm uses random rotations of either left or right, which makes it possible to cover the entire grid
void algorithm(Robot *robot1)
{
  while (!atMarker(robot1))
  {
    if (canMoveForward(robot1))
    {
      forward(robot1);
    }
    int ranNum = rand() % 2;
    if (ranNum != 0)
    {
      right(robot1);
    }
    else
    {
      left(robot1);
    }
  }
}

int main(int argc, char **argv)
{
  time_t t;
  srand((unsigned)time(&t));
  setWindowSize(width, height);

  int initialX = 0;
  int initialY = 0;
  char *direction = "south";

  if (argc == 4)
  {
    initialX = atoi(argv[1]);
    initialY = atoi(argv[2]);
    direction = argv[3];
  }

  Robot *robot1 = createRobot(direction, initialX, initialY);
  fillGrid(robot1);
  canRun(robot1);

  drawBackground();
  drawRobot(robot1);
  sleep(waitTime);
  algorithm(robot1);
  free(robot1);

  return 0;
}