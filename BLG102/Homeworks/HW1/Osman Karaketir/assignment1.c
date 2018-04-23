#include <stdio.h>
#include <stdlib.h>
int main() {
    int q;
    int m;
    int j;
    int k;
    int endyear;
    int first_year;
    int year;
    int day;
    int month;

    printf("Enter date [year month day]: ");
    scanf("%d %d %d",&first_year,&month,&day);
    year=first_year;
    //VALIDATION
    if(day<1)
    {
        printf("Invalid date.\n");
        return EXIT_FAILURE;
    }
    if(month>12||month<1)
    {
        printf("Invalid date.\n");
        return EXIT_FAILURE;
    }
    if(year<0)
    {
        printf("Invalid date.\n");
        return EXIT_FAILURE;
    }
    if(month==2&&day>28)
    {
        printf("Invalid date.\n");
        return EXIT_FAILURE;
    }
    else if((month==4||month==6||month==9||month==11)&&day>30)
    {
        printf("Invalid date.\n");
        return EXIT_FAILURE;
    }
    else if((month==1||month==3||month==5||month==7||month==8||month==10||month==12)&&day>30)
    {
        printf("Invalid date.\n");
        return EXIT_FAILURE;
    }

    //END_VALIDATION
    printf("Enter end year: ");
    scanf("%d",&endyear);

    q=day;
    m=month;
    int y=year;
    if(month==1||month==2)
    {
        m+=12;
        y--;
    }
    j=y/100;
    k=y%100;





    int result=(q+(13*(m+1)/5)+k+(k/4)+(j/4)+5*j)%7;
    //scanf("%d",&result); for day test
    if(result==0)
    {
        printf("It's a Saturday.\n");
    }
    else if(result==1)
    {
        printf("It's a Sunday.\n");
    }
    else if(result==2)
    {
        printf("It's a Monday.\n");
    }
    else if(result==3)
    {
        printf("It's a Tuesday.\n");
    }
    else if(result==4)
    {
        printf("It's a Wednesday.\n");
    }
    else if(result==5)
    {
        printf("It's a Thursday.\n");
    }
    else if(result==6)
    {
        printf("It's a Friday.\n");
    }
    else
    {
        return  EXIT_FAILURE;
    }

    int first_result=result;
    int count=0;
    for(year=year+1;year<=endyear;year++)
    {
        q=day;
        m=month;
        int y=year;
        if(m==1||m==2)
        {
            m+=12;
            y--;
        }
        j=y/100;
        k=y%100;





        result=(q+(13*(m+1)/5)+k+(k/4)+(j/4)+5*j)%7;
        if(first_result==result)
        {
            count++;
        }
        //scanf("%d",&result); for day test


    }
    printf("Same day-and-month on same weekday between %d and %d: %d\n",first_year+1,endyear,count);
    return EXIT_SUCCESS;
}
