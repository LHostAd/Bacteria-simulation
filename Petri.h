#ifndef PETRI_H__
#define PETRI_H__

#include <vector>
#include <utility> //pair
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Concentration.h"
#include "Bacteria.h"




class Petri{
 public:
  //Constructors
  Petri();
  Petri(std::string file);
  
  //Getters
  inline Bacteria* getBact(int i, int j) const;
  inline void getDeaths() const;
  inline int getNbDeaths() const;
  inline double getPtrA(int i, int j) const;
  inline double getPtrB(int i, int j) const;
  inline double getPtrC(int i, int j) const;

  
  //Setters
  
  //Methods
  void diffusion();
  void kill();
  void all_eating();
  void eating(int i, int j);
  void make_babies();
  //void division(int X, int Y, std::pair <int,int> max_pos, double max_fitness  );
  //void maj_death_pos();
  void reset();
  void reset_bact();
  void simulation();
  void conservation(int a, int T, int Tsimul);
  int state();
  void diagram(int a);
  void opt_diagram(int a);
  int most_frequent_state(std::vector< int > V );
  int amountofgA();
  int amountofgB();
  
  
  //Destructor
  ~Petri();
  
  
  
 protected:
  concentration** ptr_;
  Bacteria** bact_;
  std::vector< std::pair <int,int> > deaths_position_;
  unsigned int W_;
  unsigned int H_;
  int amount_of_deaths;
  double Raa_;
  double Rab_;
  double Rbb_;
  double Rbc_;
  double D_;
  double Ainit_;
  int T_;
  int T_simul_;
  double Wmin_;
  double Pmut_;
  double Pdeath_;
  
};


  //Inline functions 

  //Getters
inline Bacteria* Petri :: getBact(int i, int j) const{
  return & bact_[i][j];
}

inline double Petri :: getPtrA(int i, int j) const{
  return ptr_[i][j].A;
}

inline double Petri :: getPtrB(int i, int j) const{
  return ptr_[i][j].B;
}

inline double Petri :: getPtrC(int i, int j) const{
  return ptr_[i][j].C;
}

/*inline void Petri :: getDeaths() const{
  for (int i=0;i<sizeof(deaths_position_);i++){
    int X = std::get<0>(deaths_position_[i]);
    int Y = std::get<1>(deaths_position_[i]);
    std::cout<<"(" << X << ", " << Y << ")";
  }
}*/

inline int Petri :: getNbDeaths() const{
  return amount_of_deaths;
}



#endif
