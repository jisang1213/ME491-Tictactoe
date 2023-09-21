#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>

/// DO NOT CHANGE THE NAME AND FORMAT OF THIS FUNCTION
double getOptimalValue(Eigen::Matrix3d state){
  /*To store the state of a 3x3 matrix, we will use binary representation where the 
  first two bits represents the entry at i=1,j=1 and the next two bits represent the 
  entry i=1,j=2, etc. Since there are three different possible entries (-1,0,1), 0 will 
  be represented by 00, 1 will be represented by 01, and -1 will be represented by 10.
  To guarantee a one-to-one mapping between each matrix state and binary representation, we 
  will simply shift each value to the left by 2*(3i+j-4) and sum them to get an int 
  value
  
  Hence the Bellman Equation boils down to v*(s) = max(a)(gamma*E[v*(s')]) where gamma = 0.98
  That is, v*(s) is the maximum over all actions of the expectation of v*(s') given that
  p(s'|s,a) is uniform over all possible s'.

  We will implement a depth-first recursive method to compute the optimal value for the given state*/

  int freespaces = 0;
  //Find and count number of free spaces
  for(int i=1; i<=3; i++){
    for(int j=1; j<=3; j++){
      if(state.coeff(i,j) == 0){
        freespaces++;
      }
    }
  }

  // return optimal value
  return getOptimalValuerecursive(state, 1, freespaces);
}

double getOptimalValuerecursive(Eigen::Matrix3d state, double gamma, int freespaces){
  int maxvalue;

  //check if the game has ended (base case)
  //check rows
  for(int i=1; i<=3; i++){
    if(state.coeff(i,1) == state.coeff(i,2) && state.coeff(i,2) == state.coeff(i,3)){
      if(state.coeff(i,1)==1){
        return 1;   //return 1 if winner
      }
      else{
        return 0;   //return 0 if looser
      }
    }
  }
  //check columns
  for(int j=1; j<=3; j++){
    if(state.coeff(1,j) == state.coeff(2,j) && state.coeff(2,j) == state.coeff(3,j)){
      if(state.coeff(1,j)==1){
        return 1;   //return 1 if winner
      }
      else{
        return 0;   //return 0 if looser
      }
    }
  }
  //check diagonals-"\"
  if(state.coeff(1,1) == state.coeff(2,2) && state.coeff(2,2) == state.coeff(3,3)){
    if(state.coeff(1,1)==1){
      return 1;   //return 1 if winner
    }
    else{
      return 0;   //return 0 if looser
    }
  }
  //check diagonals-"/"
  if(state.coeff(1,3) == state.coeff(2,2) && state.coeff(2,2) == state.coeff(3,1)){
    if(state.coeff(1,3)==1){
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

  //find the max value function of the next state over all actions

  Eigen::Matrix3d nextstate = state;

}

