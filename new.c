/*C implementation of Kim Kim Suzuki Grain Growth Model on one processor
 *Outputs data into folders at desired time intervals
 *Uses a function to tessellate and simulates grain growth on the resulting domain
 */

//Import all the libraries required
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include"set.h"                           //Contains functions to handle linked lists
#include"voronoi.h"                       //Contains the Tessellation function


void main(){

                                            //Declaration of variables//
  int i,j,k,l,num_x,t,temp_q,a,b;
  int index1,index2,index3;
  int num_grains; //Number of grains present in the domain
  char name[200]; //Used to contain the path of output data files
  char cwd[1024];
  char cwd1[1024];
  char cwd2[1024];
  char cwd3[1024];
  char gnu1[100];
  struct Node **phi; //phi contains the phase fields at each point in the domain
  struct Track* tracker = NULL;
  float mphi,del_x,del_t,alpha,w,eps,lambda,temp_val;
  float phi1,phi2,phi3,phi4,phi5,laplacian,some,p1,p2,p3;
  float updated,total;
  double time_total,time_elapsed;
  int data_out; //Variable to indicate after how many time steps the data should be printed
  int time_steps;
  //Files
  FILE * file_temp;
  FILE *info;
  FILE *input;
  FILE *plots;

  getcwd(cwd1,sizeof(cwd1));
  getcwd(cwd2,sizeof(cwd2));
  getcwd(cwd3,sizeof(cwd3));

  input = fopen("Input_Data.txt","r");
  fscanf(input,"Number of grains = %d\nNumber of grids = %d\nPrint after %d time steps\nTotal number of time steps = %d",&num_grains,&num_x,&data_out,&time_steps);
  fclose(input);

  //values to be changed
  //num_grains = 3;
  //data_out = 500;
  //num_x = 100;
  //time_steps = 2;

  // Stores the values of phi of all the phases at a given point.
  // To be used in normalization part of the code
  float p[num_grains];

  clock_t begin = clock(); //Begin the clock

                                            //Initializing parameter values//

  mphi = 1.0;
  del_x = 1.0;
  del_t = 0.001; //previous=0.001
  alpha = 4.0;
  w = 2/3;
  eps = 4*sqrt(3)/3.14;
  lambda = mphi*del_t*eps*eps/(del_x*del_x);

  //CARRY OUT VORONOI TESSELLATION
  phi = Tesselate(num_grains,num_x);
  printf("Domain is successfully TESSELLATED\n");


                                              /*==============================================*/
                                              /*====================SOLVER====================*/
                                              /*==============================================*/

  t =0; //Count the number of time steps
  while(t<time_steps){
    /*time_elapsed = clock()/CLOCKS_PER_SEC;
    if((int)time_elapsed%900 == 0){
      printf("Time elapsed: %lf \n",time_elapsed);
    }*/
                                            /*PART 1: CALCULATING PHI VALUE OF EACH PHASES AND UPDATING THE DOMAIN*/
    for(i=1;i<=num_x;i++){
      for(j=1;j<=num_x;j++){
        for(k=1;k<=num_grains;k++){
          //Phi values around the point to be calculated
          phi1 = crawl(phi[i*(num_x+2)+j],k);
          phi2 = crawl(phi[(i-1)*(num_x+2)+j],k);
          phi3 = crawl(phi[i*(num_x+2)+j-1],k);
          phi4 = crawl(phi[(i+1)*(num_x+2)+j],k);
          phi5 = crawl(phi[i*(num_x+2)+j+1],k);

          //Calculation of laplacian at that point so that only those points
          //with non-zero laplacian will be calculated
          laplacian = (phi2 -2*phi1 +phi4)/(del_x*del_x) + (phi5 -2*phi1 +phi3)/(del_x*del_x);

                                //Record the changes to be made//

          if(laplacian != 0.0){
              temp_q = k;
              temp_val = phi1 + lambda*(phi2+phi3-4*phi1+phi4+phi5) - mphi*del_t*del_x*del_x*(1 - 2*phi1);
              if(temp_val > 0){
                tracker = append(tracker,i,j,temp_q,temp_val); // Tracker variable records the chanes one by one
              }
            }
          }
        }
      }

                                            //Implement the tracked changes//

    struct Track* move = tracker; // Move is a variable to crawl through tracker linked list
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


                                           /*PART 2: FIXING THE PROPORTIONS OF PHASES IN EACH GRID*/

    for(i=1;i<=num_x;i++){
      for(j=1;j<=num_x;j++){
        for(a=0;a<num_grains;a++){
          p[a] = crawl(phi[i*(num_x+2)+j],a+1); //Store all the phi values in p
        }
        total = 0;
        for(a=0;a<num_grains;a++){
          total += p[a];  //Calculate the total for use in normalization in the next step
        }
        for(a=0;a<num_grains;a++){
        change(phi[i*(num_x+2)+j],a+1,p[a]/total);  // Normalize each phase
      }
      }
    }

  //Notify progress on the terminal
  if(t%1000 == 0){
    printf("Done with %d time steps\n",t);
  }

                                            /*PART 3: OUTPUT DATA AT REQUIRED TIME STEPS*/
  if(t % data_out == 0){
  getcwd(cwd,sizeof(cwd));
  sprintf(name,"/your_data/data%d.dat",t); //Assign the path of the data files to the string name
  strcat(cwd,name);
  file_temp = fopen(cwd,"w");
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


                                                        /*PART 4: FREE ALLOCATED SPACE*/
for(i=0;i<num_x+2;i++){
  for(j=0;j<num_x+2;j++){
    phi[i*(num_x)+j] = clear(phi[i*(num_x+2)+j]);
  }
}
free(phi);

                                            //Calculate and output time taken to run the program//

  clock_t end = clock(); // End of the clock
  time_total = (end-begin)/CLOCKS_PER_SEC; // Calculate total time in seconds
  printf("total time taken = %lf\n",time_total);


                                            //Making a file containing details of the program//
  strcat(cwd1,"/your_data/details.txt");
  info = fopen(cwd1,"w");
  fprintf(info,"Number of grains = %d\n",num_grains);
  fprintf(info,"Grid size : %d\n",num_x);
  fprintf(info,"Number of time steps: %d\n",t+1);
  fprintf(info,"Delta t: %f\n",del_t);
  fprintf(info,"Ouputs data after %d time steps\n",data_out);
  fprintf(info,"Total time taken(in sec): %lf\n",time_total);
  fprintf(info,"Total time taken(in min):%lf\n",time_total/60);
  fprintf(info,"Total time taken(in hours):%lf\n",time_total/3600);
  fclose(info);

                                            //Making a file for plots
  strcat(cwd2,"/your_data/plot.plt");
  plots = fopen(cwd2,"w");
  fprintf(plots,"set term jpeg\n");
  fprintf(plots,"set pm3d map\n");
  fprintf(plots,"do for [i=0:%d]{\n",time_steps-1);
  fprintf(plots,"if(i %% %d == 0){\n",data_out);
  sprintf(gnu1,"out_file = sprintf('%s/your_data/plots/img%%04d.jpeg',i/1000)",cwd3);
  fprintf(plots,"%s\n",gnu1);
  fprintf(plots,"set output out_file\n");
  fprintf(plots,"splot 'data'.i.'.dat'\n");
  fprintf(plots,"}\n}\n");
  fclose(plots);

} //END OF PROGRAM
