#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>

/// DO NOT CHANGE THE NAME AND FORMAT OF THIS FUNCTION
double getOptimalValue(Eigen::Matrix3d state){
  /*
  For this problem, the Bellman Equation boils down to v*(s) = max(a)(gamma*E[v*(s')]) 
  where gamma = 0.98. That is, v*(s) is the maximum over all actions of the expectation 
  of v*(s') given that p(s'|s,a) is uniform over all possible s'.

  We will implement a depth-first recursive method to compute the optimal value for the given state*/

  int freespaces = 0;
  //Find and count number of free spaces
  for(int i=1; i<=3; i++){
    for(int j=1; j<=3; j++){
      if(state(i,j) == 0){
        freespaces++;
      }
    }
  }

  // return optimal value
  return getOptimalValuerecursive(state, freespaces);
}

//recursive helper function
double getOptimalValuerecursive(Eigen::Matrix3d state, int freespaces){
  double sum;
  double maxsum=0;
  double nextoptimalvalue;
  Eigen::Matrix3d stateaction;
  Eigen::Matrix3d nextstate;

  //check if the game has ended (base case)
  //check rows
  for(int i=1; i<=3; i++){
    if(state(i,1) == state(i,2) && state(i,2) == state(i,3)){
      if(state(i,1)==1){
        return 1;   //return 1 if winner
      }
      else{
        return 0;   //return 0 if looser
      }
    }
  }
  //check columns
  for(int j=1; j<=3; j++){
    if(state(1,j) == state(2,j) && state(2,j) == state(3,j)){
      if(state(1,j)==1){
        return 1;   //return 1 if winner
      }
      else{
        return 0;   //return 0 if looser
      }
    }
  }
  //check diagonals-"\"
  if(state(1,1) == state(2,2) && state(2,2) == state(3,3)){
    if(state(1,1)==1){
      return 1;   //return 1 if winner
    }
    else{
      return 0;   //return 0 if looser
    }
  }
  //check diagonals-"/"
  if(state(1,3) == state(2,2) && state(2,2) == state(3,1)){
    if(state(1,3)==1){
      return 1;   //return 1 if winner
    }
    else{
      return 0;   //return 0 if looser
    }
  }
  //return 0 if tie
  if(freespaces==0){
    return 0;
  }

  //find the max value function of the next state over all possible actions. 
  //Search for possible actions (free spaces)
  for(int i=1; i<=3; i++){
    for(int j=1; j<=3; j++){
      if(state(i,j) == 0){
        stateaction = state;
        stateaction(i,j) = 1; //do action
        sum = 0;

        //consider all s', take the sum
        for(int a=1; a<=3; a++){
          for(int b=1; b<=3; b++){
            if(stateaction(a,b) == 0){
              nextstate = stateaction;
              nextstate(a,b) = 1;
              sum = sum + getOptimalValuerecursive(nextstate, freespaces-2);
            }
          }
        }
        //update maxsum
        if(sum>maxsum){
          maxsum = sum;
        }
      }
    }
  }
  nextoptimalvalue = maxsum/(freespaces-1); //divide by number of s' to get the optimal value of the next state
  return 0.98*nextoptimalvalue;
}