#include <stdio.h>
#include <stdlib.h>
/*
 * Compute how many point reduce
 *
 * @param segment the score that dart land
 * @param ring the ring that dart land
 * @return point the point will reduce
 */
int throw_point(int segment, char ring)
{
    int point=0;
    if(ring=='S')
    {
        point = segment * 1;
    }
    else if(ring=='D')
    {
        point=segment*2;
    }
    else if(ring=='T')
    {
        point=segment*3;
    }
    else if(ring=='O')
    {
        point=25;
    }
    else if(ring=='I')
    {
        point=50;
    }
    else
        point=0;
    return point;
}
/*
 * Compute how many point remain
 *
 * @param current the current point
 * @param segment the score that dart land
 * @param ring the ring that dart land
 * @param target the point we will reach
 * @return point the point will reduce
 */
int calculate(int current, int segment,char ring,int target)
{
    if(target==current&&ring!='D')
    {
        return current;
    }

    int point=throw_point(segment,ring);
    if((current-point)==0&&ring!='D')
    {
        return current;
    }
    if((current-point)<0)
    {
        return current;
    }
    if((current-point)==1)
    {
        return current;
    }
    return current-point;
}
int main()
{
    int target=0;
    printf("Target: ");
    scanf("%d",&target);
    int point=target;
    while(point!=0)
    {
        printf("Throw: ");
        int segment = 0;
        scanf("%d", &segment);
        char ring = ' ';
        scanf(" %c", &ring);
        point=calculate(point,segment,ring,target);
        printf("Points: %d\n",point);
    }
    return EXIT_SUCCESS;
}
