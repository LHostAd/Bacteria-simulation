#ifndef BACTERIA_H__
#define BACTERIA_H__

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Concentration.h"




  class Bacteria {
    
    enum genotype
    {
    gB = 0, gA = 1
    };
    
   public:
    //Constructors
    Bacteria();
    Bacteria(const Bacteria& copied);
    Bacteria(std::string file);
    Bacteria(double Wmin, double Pmut, double Pdeath);
    
    
    //Operators
    const Bacteria& operator=(const Bacteria&);

    //Getters
    inline bool getGen() const;
    inline bool isAlive() const;
    inline bool didDivide() const;
    inline double getPtrA() const;
    inline double getPtrB() const;
    inline double getPtrC() const;
    inline double getWmin() const;
    inline double getPmut() const;
    inline double getPdeath() const;



    inline concentration* getPtr();
    
    
    //Setters
    inline void setGen(bool);
    inline void setDivide(bool);

    
    //Methods
    void mutation();
    double fitness();
    void death();
    void mother();
    
    //Destructors
    ~Bacteria();
    
   protected:
    bool genotype_;   //gB=0 ou gA=1
    bool alive_;
    bool divided_;
    concentration* ptr_;
    double Wmin_;
    double Pmut_;
    double Pdeath_;

    
  
  
};
  
//Inline functions 

  //Getters
  inline bool Bacteria :: getGen() const{
    return genotype_;
  }
    
  inline bool Bacteria :: isAlive() const{
    return alive_;
  }
  
  inline bool Bacteria :: didDivide() const{
    return divided_;
  }

  inline concentration* Bacteria :: getPtr() {
    return ptr_;
  }
  
  inline double Bacteria :: getPtrA() const{
    return ptr_->A;
  }

  inline double Bacteria :: getPtrB() const{
    return ptr_->B;
  }
  
  inline double Bacteria :: getPtrC() const{
    return ptr_->C;
  }
  
  inline double Bacteria :: getWmin() const{
    return Wmin_;
  }
  
  inline double Bacteria :: getPmut() const{
    return Pmut_;
  }
    
  inline double Bacteria :: getPdeath() const{
    return Pdeath_;
  }


  //Setters
  inline void Bacteria :: setGen(bool a){
    genotype_ = a;
  }
  
  inline void Bacteria :: setDivide(bool a){
    divided_ = a;
  }
    


#endif
