#include <stdio.h>
#include <stdlib.h>
/*
 * Compute Manhattan distance
 *
 * @param x1 x position of park area
 * @param x2 x position of car
 * @param y1 y position of park area
 * @param y2 y position of car
 * @return distance
 */
int distance(int x1, int x2, int y1, int y2)
{
  int x =x1-x2;
  if(x<0)
  {
    x*=-1;
  }
  int y = y1-y2;
  if(y<0)
  {
    y*=-1;
  }
  return x+y;
}
int main()
{
  int area[50][50];//matrix for park area
  int cars[2500][2];//matrix for car positions
  int size;
  int car_number;
  int test=1;
  while(test)
  {
    printf("Size: ");
    scanf("%d", &size);
    if(size>50||size<1)//size can not be more than 50
    {
      printf("Size must be between 50 and 1\n");
      continue;
    }
    test=0;
  }

  printf("Cars: ");
  scanf("%d", &car_number);
  if(car_number>size*size||car_number<0)//car number can not be more than area and smaller than zero
  {
    return EXIT_FAILURE;
  }
  if(car_number==size*size)//if there is no park area for car
  {
    printf("Best Slot Found In: 0 0\n");
    return EXIT_SUCCESS;
  }
  for(int a=0;a<size;a++)
  {
    for(int b=0;b<size;b++)
    {
      area[a][b]=0;//to fill all area with zero
    }
  }

  for(int a=0;a<car_number;a++)
  {
    int x;
    int y;
    printf("Locations: ");
    scanf("%d", &x);
    scanf("%d", &y);
    if((x<size&&y<size)&&(x>0&&y>0))//if car location is in area
    {


      if(area[x-1][y-1]==0)//to check slot is empty
      {
        area[x-1][y-1]=1;//to change cars position to 1
        cars[a][0]=x-1;//add car positions to car array
        cars[a][1]=y-1;//add car positions to car array
      }
      else
      {
        car_number--;//if two car parked on same slot
      }
    }
    else//if car location is out of the area
    {
      car_number--;
    }
  }

  int rx;
  int ry;
  int dist3=0;
  for(int a=0;a<size;a++)
  {
    for(int b=0;b<size;b++)
    {
      if(area[a][b]==0)
      {
        int dist=100;//100 is max possible distance
        //int car=0;
        for(int c=0;c<car_number;c++)
        {

          int dist2=distance(a,cars[c][0],b,cars[c][1]);
          if(dist2<dist)//to find nearest car
          {
            dist=dist2;
          //  car=c;
          }

        }
        //printf("(%d, %d): %d, %d\n", a,b,car,dist);
        if(dist>dist3)//to find largest distance
        {
          rx=a;
          ry=b;
          dist3=dist;
        }
      }
    }
  }
  printf("Best Slot Found In: %d %d\n",rx+1,ry+1);
  return EXIT_SUCCESS;
}
