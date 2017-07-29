int random_int(int max,int min){
  int diff = max - min;
  return (int)(((double)(diff+1)/RAND_MAX)*rand() + min);
}
int nearest_q(struct Pivot* head,int i,int j){
  struct Pivot* temp = head;
  float d,new;
  int k;
  d = dist(i,j,temp->x,temp->y);
  k = temp->q;
  while(temp != NULL){
    new = dist(i,j,temp->x,temp->y);
    if(new < d){
      d = new;
      k = temp->q;
    }
    temp = temp->next;
  }
  return k;
}
float minimum_dist(struct Pivot* head,int i,int j){
  struct Pivot* temp = head;
  float min,new;
  min = dist(i,j,temp->x,temp->y);
  while(temp != NULL){
    new = dist(i,j,temp->x,temp->y);
    if(new < min){
      min = new;
    }
    temp = temp->next;
  }
  return min;
}
float maximum_dist(struct Pivot* head,int i,int j){
  struct Pivot* temp = head;
  float max,new;
  max = dist(i,j,temp->x,temp->y);
  while(temp != NULL){
    new = dist(i,j,temp->x,temp->y);
    if(new > max){
      max = new;
    }
    temp = temp->next;
  }
  return max;
}
struct Node** Tesselate(int n,int num_x){
  int i,j,k,l,g1,g2,c;
  struct Node** dom;
  struct Pivot* grains = NULL;
  struct Pivot* tem;
  float min_dist,max_dist,disp,span;
  span = dist(0,0,num_x,num_x);
  max_dist = sqrt(span)/2;
  min_dist = sqrt(span)/n;
  //min_dist = 0;
  //printf("%f %f\n",min_dist,max_dist);
  dom = (struct Node**)malloc((num_x+2)*(num_x+2)*sizeof(struct Node*));
  srand(time(NULL));
  for(i=0;i<num_x+2;i++){
    for(j=0;j<num_x+2;j++){
      dom[i*(num_x+2)+j] = NULL;
    }
  }
  //Initializing grain centers
  c=1;
  while(c<=n){
    //g1 = random_int(num_x/2-num_x/(log(num_x/3)*n),num_x/2+num_x/(log(num_x/3)*n));
    //g2 = random_int(num_x/2-num_x/(log(num_x/3)*n),num_x/2+num_x/(log(num_x/3)*n));
    g1 = random_int(1,num_x);
    g2 = random_int(1,num_x);
    if(c != 1){
      //printf("%f %f\n",min_dist,minimum_dist(grains,g1,g2));
    }

    if(c == 1){
      grains = stick(grains,g1,g2,c);
      c++;
    }
    else if(minimum_dist(grains,g1,g2)>=min_dist || maximum_dist(grains,g1,g2)<=max_dist){
      grains = stick(grains,g1,g2,c);
      c++;
    }
    else{
      //g1 = random_int(num_x/2-num_x/(log(num_x/3)*n),num_x/2+num_x/(log(num_x/3)*n));
      //g2 = random_int(num_x/2-num_x/(log(num_x/3)*n),num_x/2+num_x/(log(num_x/3)*n));
      g1 = random_int(1,num_x);
      g2 = random_int(1,num_x);
    }
  }
  //Check the distances
  tem = grains;
  i = tem->x;
  j = tem->y;
  while(tem != NULL){
    //printf("%f\n",dist(i,j,tem->x,tem->y));
    tem = tem->next;
  }
  //Grain allocation
  for(i=1;i<num_x+1;i++){
    for(j=1;j<num_x+1;j++){
      c = nearest_q(grains,i,j);
      //printf("%d\n",c);
      dom[i*(num_x+2)+j] = attach(dom[i*(num_x+2)+j],c,1.0);
    }
  }
return dom;
}//End of function
