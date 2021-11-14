//Write a Program to implement Type checking
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n,i,flag=0;
    char variable[15],type[15],b[15],c;
    printf("Enter the number of variables: ");
    scanf("%d",&n);
    n > 0 ? printf("Enter single character variables and types (float-f,int-i) \n",n) : n;
    for(i=0;i<n;i++)
    {
        printf("variable[%d]: ",i);
        getchar();
        scanf("%c",&variable[i]);
        printf("variable-type[%d]: ",i);
        getchar();
        scanf("%c",&type[i]);
        printf("\n");
        if(type[i]=='f')
            flag=1;
    }
    printf("Enter the Expression(add $ at the end): ");
    i=0;
    getchar();
    while((c=getchar())!='$')
    {
        b[i]=c;
        i++;  
    }
    int k=i;
    for(i=0;i<k;i++)
    {
        if(b[i]=='/')
        {
            flag=1;
            break;  
        }  
    }
    for(i=0;i<n;i++)
    {
        if(b[0]==variable[i])
        {
            if(flag==1)
            {
                if(type[i]=='f')
                {  
                    printf("\nAll datatypes are properly defined..!\n");
                    break;  
                }
                else
                {  
                    printf("Identifier %c must be float type..!\n",variable[i]);
                    break;  
                }  
            }
            else
            {  
                printf("\nAll datatypes are properly defined..!\n");
                break;  
            }  
        }
    }
    return 0;
}