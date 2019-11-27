//PennyBoki @ </dream.in.code>
#include <stdio.h>
#include <stdlib.h>

int main()
{
     float A[3][3];// the matrix that is entered by user
     float B[3][3];//the transpose of a matrix A 
     float C[3][3];//the adjunct matrix of transpose of a matrix A not adjunct of A
     double X[3][3];//the inverse
     int i,j;
     float x,n=0;//n is the determinant of A
     
     printf("========== Enter matrix A =============================================\n");
     for(i=0;i<3;i++)
     {     printf("\n");
          for(j=0;j<3;j++)
          {     
               printf(" A[%d][%d]= ",i,j);
               scanf_s("%f", &A[i][j]);
               B[i][j]=0;
               C[i][j]=0;
          }
     }
     
     
          for(i=0,j=0;j<3;j++)
          {     
               if(j==2) 
               n+=A[i][j]*A[i+1][0]*A[i+2][1];
               else if(j==1)
               n+=A[i][j]*A[i+1][j+1]*A[i+2][0];
               else 
               n+=A[i][j]*A[i+1][j+1]*A[i+2][j+2];
          }
          for(i=2,j=0;j<3;j++)
          {     
               if(j==2) 
               n-=A[i][j]*A[i-1][0]*A[i-2][1];
               else if(j==1)
               n-=A[i][j]*A[i-1][j+1]*A[i-2][0];
               else
               n-=A[i][j]*A[i-1][j+1]*A[i-2][j+2];
          }


     printf("\n========== The matrix A is ==========================================\n");     
     for(i=0;i<3;i++)
     {
          printf("\n");
          for(j=0;j<3;j++)
          {     
               printf(" A[%d][%d]= %.2f  ",i,j,A[i][j]);
          }
     }
     printf("\n \n");
     
     printf("=====================================================================\n\n");
     printf("The determinant of matrix A is %.2f ",n);
     printf("\n\n=====================================================================\n");
     
     if(n!=0) x=1.0/n;
     else 
     {
          printf("Division by 0, not good!\n");
          printf("=====================================================================\n\n");
          return 0;
     }
     printf("\n========== The transpose of a matrix A ==============================\n");     
     for(i=0;i<3;i++)
     {
          printf("\n");
          for(j=0;j<3;j++)
          {     
                    
               B[i][j]=A[j][i];
               printf(" B[%d][%d]= %.2f  ",i,j,B[i][j]);
               
          }
     }
     printf("\n\n");


     C[0][0]=B[1][1]*B[2][2]-(B[2][1]*B[1][2]);
     C[0][1]=(-1)*(B[1][0]*B[2][2]-(B[2][0]*B[1][2]));
     C[0][2]=B[1][0]*B[2][1]-(B[2][0]*B[1][1]);
     
     C[1][0]=(-1)*(B[0][1]*B[2][2]-B[2][1]*B[0][2]);
     C[1][1]=B[0][0]*B[2][2]-B[2][0]*B[0][2];
     C[1][2]=(-1)*(B[0][0]*B[2][1]-B[2][0]*B[0][1]);

     C[2][0]=B[0][1]*B[1][2]-B[1][1]*B[0][2];
     C[2][1]=(-1)*(B[0][0]*B[1][2]-B[1][0]*B[0][2]);
     C[2][2]=B[0][0]*B[1][1]-B[1][0]*B[0][1];


     printf("\n========== The adjunct matrix of transpose of the matrix A ==========\n");     
     for(i=0;i<3;i++)
     {
          printf("\n");
          for(j=0;j<3;j++)
          {     
               printf("C[%d][%d]= %.2f",i,j,C[i][j]);
               
          }
     }
     printf("\n\n");

     
     for(i=0;i<3;i++)
     {
          for(j=0;j<3;j++)
          {     
               X[i][j]=C[i][j]*x;
               
          }
     }



     printf("\n========== The inverse matrix of the matrix you entered!!! ==========\n");
     for(i=0;i<3;i++)
     {     printf("\n");
          for(j=0;j<3;j++)
          {     
               printf(" X[%d][%d]= %.2f",i,j,X[i][j]);
          
          }
     }
     printf("\n\n");
     

return 0;
} 