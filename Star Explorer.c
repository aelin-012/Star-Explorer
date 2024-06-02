#include <stdio.h>
#include <stdlib.h>

void arena(int,int,int[0][0]);
void printgrid(int,int,int[0][0]);
void finaldestinitialpos(int,int,int[0][0]);
void obstacles(int,int,int[0][0],int);
void pathplan(int,int,int[0][0],int);
void exit();

int main()
{
    printf("Welcome to Star Explorer. Let's start navigating!\n");
    printf("--------------------------------------------------");
    int rows, columns, size;
    printf("\nEnter size of the grid: ");
    printf("\nEnter number of rows: ");
    scanf("%d",&rows);
    printf("Enter number of columns: ");
    scanf("%d",&columns);
    int grid[rows][columns];
    size=(rows*columns);
    printf("--------------------------------------------------\n");
    printf("LEGEND:\nO---Empty matrix elements\nX---Obstacles\nS---Starting point\nF---Finish(represents position 1 according to pathplan)\nDecimal numbers---Paths\n");
    printf("--------------------------------------------------\n");
    //calling required functions
    arena(rows,columns,grid);
    finaldestinitialpos(rows,columns,grid);
    obstacles(rows,columns,grid,size);
    pathplan(rows,columns,grid,size);
}

void arena(int rows,int columns,int grid[rows][columns])
{
    int i, j;
    //initializing values for each array index
    int s=-1;
    for(i=1;i<=rows;i++)
    {
        for(j=1;j<=columns;j++)
        {
            grid[i][j]=s;
            s=s-1;
        }
    }
    printgrid(rows,columns,grid);
}

void printgrid(int rows,int columns,int grid[rows][columns])
{
    int i,j;
    for (i=1;i<=rows;i++)
    {
        for (j=1;j<=columns;j++)
        {
            if (grid[i][j]<0)
                printf("O\t");
            if (grid[i][j]==((rows*columns)+1))
                printf("X\t");
            if (grid[i][j]>1 && grid[i][j]<(rows*columns+1))
                printf("%d\t",grid[i][j]);
            if (grid[i][j]==0)
                printf("S\t");
            if (grid[i][j]==1)
                printf("F\t");
        }
        printf("\n");
    }
}

void finaldestinitialpos(int rows,int columns,int grid[rows][columns])
{
    int r1, c1, r2, c2, i, j;
    printf("--------------------------------------------------");
    
    //final destination (array index value will be 1)
    printf("\nEnter the final destination:\n");
    printf("Enter row: ");
    scanf("%d",&r1);
    printf("Enter column: ");
    scanf("%d",&c1);
    grid[r1][c1]=1;
    printgrid(rows,columns,grid);
    
    //initial position (array index value will be 0)
    printf("\nEnter the initial position:\n");
    printf("Enter row: ");
    scanf("%d",&r2);
    printf("Enter column: ");
    scanf("%d",&c2);
    grid[r2][c2]=0;
    printgrid(rows,columns,grid);
}

void obstacles(int rows,int columns,int grid[rows][columns],int size)
{
    int obs, i, j, a, b;
    printf("--------------------------------------------------");
    
    //obstacles in the grid (array index value will be (rows*columns)+1)
    printf("\nEnter the no. of obstacles: ");
    scanf("%d",&obs);
    printf("Please enter array index apart from final destination and initial position.\n");
    for (i=0;i<obs;i++)
    {
        printf("\nEnter the row for obstacle %d: ",(i+1));
        scanf("%d",&a);
        printf("Enter the column for obstacle %d: ",(i+1));
        scanf("%d",&b);
        grid[a][b]=size+1;
    }
    printgrid(rows,columns,grid);
    printf("--------------------------------------------------");
}

void pathplan (int rows,int columns,int grid[rows][columns], int size)
{
    struct matrix{ //structure
        int coordinates[rows][columns];
    };
    struct matrix *ptr; //pointer 
    ptr=(struct matrix*)malloc(sizeof(struct matrix));//struct variable
    for (int i=1;i<=rows;i++)
    {
        for(int j=1;j<=columns;j++)
        {
            ptr->coordinates[i][j]=grid[i][j]; //assigning grid values to struct 
        }
    }
    
    int g=1, i, j, h;
    printf("\nPossible Paths:\n");
    for (h=1; h<=size; h++)
    {
        for (i=1; i<=rows; i++)
        {
            for (j=1; j<=columns; j++)
            {
                if (ptr->coordinates[i][j]==g) //accessing struct
                {
                    //UP
                    
                    if (i-1>0)
                    {
                        if (ptr->coordinates[i-1][j]==0)
                        {
                            
                            printgrid(rows,columns,ptr->coordinates); //passing struct member coordinates[][] to printgrid
                            printf("\nInitial Position reached");
                            printf("\nFinal Path: The shortest path is from 2 to %d",g);
                            exit(0);
                        }
                        else if (ptr->coordinates[i-1][j]<0)
                        {
                            ptr->coordinates[i-1][j]=g+1;
                        }
                    }
                    
                    //LEFT
                        
                    if (j-1>0)
                    {
                        if (ptr->coordinates[i][j-1]==0)
                        {
                            
                            printgrid(rows,columns,ptr->coordinates);
                            printf("\nInitial Position reached");
                            printf("\nFinal Path: The shortest path is from 2 to %d",g);
                            exit(0);
                        }
                        else if (ptr->coordinates[i][j-1]<0)
                        {
                            ptr->coordinates[i][j-1]=g+1;
                        }
                    }
                    
                    //DOWN
                    
                    if (i+1<=rows)
                    {
                        if (ptr->coordinates[i+1][j]==0)
                        {
                           
                            printgrid(rows,columns,ptr->coordinates);
                            printf("\nInitial Position reached");
                            printf("\nFinal Path: The shortest path is from 2 to %d",g);
                            exit(0);
                        }
                        else if (ptr->coordinates[i+1][j]<0)
                        {
                            ptr->coordinates[i+1][j]=g+1;
                        }
                    }
                        
                    //RIGHT
                    
                    if (j+1<=columns)
                    {
                        if (ptr->coordinates[i][j+1]==0)
                        {
                            printgrid(rows,columns,ptr->coordinates);
                            printf("\nInitial Position reached");
                            printf("\nFinal Path: The shortest path is from 2 to %d",g);
                            exit(0);
                        }
                        else if (ptr->coordinates[i][j+1]<0)
                        {
                            ptr->coordinates[i][j+1]=g+1;
                        }
                    }
                    
                }
                
            }
        }
        g++;
    }
    printf("\nSince there are obstacles blocking all possible paths, the Robot won't reach the final destination.");
}