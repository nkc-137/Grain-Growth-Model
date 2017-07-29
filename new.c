#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"set.h"                           //Contains functions to handle linked lists
#include"voronoi.h"                       //Contains the Tessellation function

void main(){

                                            //Declaration of variables//
  int i,j,k,l,num_x,t,temp_q,a,b;
  int index1,index2,index3;
  int num_grains;
  char name[200];
  struct Node **phi;
  struct Track* tracker = NULL;
  float mphi,del_x,del_t,alpha,w,eps,lambda,temp_val;
  float phi1,phi2,phi3,phi4,phi5,laplacian,some,p1,p2,p3;
  float updated,total;
  double time_total,time_elapsed;
  int data_out;
  clock_t begin = clock();

  //Files
  FILE *fa,*fb,*fc,*data,*ft;
  FILE * file_temp;
  FILE *info;
  num_grains = 10;

  float p[num_grains];

  data_out = 500;

                                            //Initializing parameter values//
  num_x = 200;
  mphi = 1.0;
  del_x = 1.0;
  del_t = 0.001; //previous=0.001
  alpha = 4.0;
  w = 2/3;
  eps = 4*sqrt(3)/3.14;
  lambda = mphi*del_t*eps*eps/(del_x*del_x);

  //CARRY OUT VORONOI TESSELLATION
  phi = Tesselate(num_grains,num_x);

                                              /*==============================================*/
                                              /*====================SOLVER====================*/
                                              /*==============================================*/

  t =0; //Number of time steps
  while(t<1){ //250000
    /*time_elapsed = clock()/CLOCKS_PER_SEC;
    if((int)time_elapsed%900 == 0){
      printf("Time elapsed: %lf \n",time_elapsed);
    }*/
    for(i=1;i<=num_x;i++){
      for(j=1;j<=num_x;j++){
        for(k=1;k<=num_grains;k++){
          phi1 = crawl(phi[i*(num_x+2)+j],k);
          phi2 = crawl(phi[(i-1)*(num_x+2)+j],k);
          phi3 = crawl(phi[i*(num_x+2)+j-1],k);
          phi4 = crawl(phi[(i+1)*(num_x+2)+j],k);
          phi5 = crawl(phi[i*(num_x+2)+j+1],k);
          laplacian = (phi2 -2*phi1 +phi4)/(del_x*del_x) + (phi5 -2*phi1 +phi3)/(del_x*del_x);

                                //Record the changes to be made//

          if(laplacian != 0.0){
              temp_q = k;
              temp_val = phi1 + lambda*(phi2+phi3-4*phi1+phi4+phi5) - mphi*del_t*del_x*del_x*(1 - 2*phi1);
              if(temp_val > 0){
                tracker = append(tracker,i,j,temp_q,temp_val);
              }
            }
          }
        }
      }

                                            //Implement the tracked changes//

    struct Track* move = tracker;  //Variable to crawl through tracker linked list
    while(move != NULL){
      index1 = move->i;
      index2 = move->j;
      index3 = move->grain;
      updated = move->val;
      if(crawl(phi[index1*(num_x+2)+index2],index3) == 0.0){
        phi[index1*(num_x+2)+index2] = attach(phi[index1*(num_x+2)+index2],index3,updated);
      }
      else{
        change(phi[index1*(num_x+2)+index2],index3,updated);
      }
      move = move->link;
    }

    //Clear all memory in tracker
    tracker = flush(tracker);

                                           //Fixing the proprtions of phases in each grid//
    for(i=1;i<=num_x;i++){
      for(j=1;j<=num_x;j++){
        for(a=0;a<num_grains;a++){
          p[a] = crawl(phi[i*(num_x+2)+j],a+1);
        }
        total = 0;
        for(a=0;a<num_grains;a++){
          total += p[a];
        }
        for(a=0;a<num_grains;a++){
        change(phi[i*(num_x+2)+j],a+1,p[a]/total);
      }
      }
    }

  //Notify progress on the terminal
  if(t%1000 == 0){
    printf("Done with %d time steps\n",t);
  }

                                            //Plotting at each time step//
  if(t % data_out == 0){
  sprintf(name,"/home/kapil/IISC/data4/data%d.dat",t);
  file_temp = fopen(name,"w");
  for(i=1;i<=num_x;i++){
    for(j=1;j<=num_x;j++){
      fprintf(file_temp,"%d %d %d\n",i,j,colorize(phi[i*(num_x+2)+j]));
    }
    fprintf(file_temp,"\n");
  }
  fclose(file_temp);
  }

    t++;
} //END WHILE LOOP
tracker = flush(tracker); //Clear memory in tracker for safety




                                                         //FREE ALLOCATED SPACE//
for(i=0;i<num_x+2;i++){
  for(j=0;j<num_x+2;j++){
    phi[i*(num_x)+j] = clear(phi[i*(num_x+2)+j]);
  }
}
free(phi);

                                            //Calculate and output time taken to run the program//

  clock_t end = clock();
  time_total = (end-begin)/CLOCKS_PER_SEC;
  printf("total time taken = %lf\n",time_total);


                                            //Making a file containing details of the program//
  info = fopen("/home/kapil/IISC/data4/details.txt","w");
  fprintf(info,"Number of grains = %d\n",num_grains);
  fprintf(info,"Grid size : %d\n",num_x);
  fprintf(info,"Number of time steps: %d\n",t+1);
  fprintf(info,"Delta t: %f\n",del_t);
  fprintf(info,"Ouputs data after %d time steps\n",data_out);
  fprintf(info,"Total time taken(in sec): %lf\n",time_total);
  fprintf(info,"Total time taken(in min):%lf\n",time_total/60);
  fclose(info);

} //END OF PROGRAM
