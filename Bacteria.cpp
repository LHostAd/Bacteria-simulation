#include "Bacteria.h"

//nb aleatoire entre 0 et 1 : nombre = (double)rand() / (double)RAND_MAX;

//===========================Constructors===============================
Bacteria :: Bacteria(){
  ptr_ = new concentration;
  ptr_->A=0;
  ptr_->B=0;
  ptr_->C=0;
  genotype_ = gB;
  Wmin_ = 0.001;
  alive_=true;
  divided_ = false;
  Pmut_ = 0;
  Pdeath_ = 0.02;
}

Bacteria :: Bacteria(double Wmin, double Pmut, double Pdeath){
  ptr_ = new concentration;
  ptr_->A=0;
  ptr_->B=0;
  ptr_->C=0;
  genotype_ = gB;
  Wmin_ = Wmin;
  alive_=true;
  divided_ = false;
  Pmut_ = Pmut;
  Pdeath_ = Pdeath;
}


Bacteria :: Bacteria(const Bacteria& copied){
  genotype_ = copied.getGen();
  alive_ = copied.isAlive();
  divided_ = copied.didDivide();
  Pmut_ = copied.getPmut();
  Pdeath_ = copied.getPdeath();
  ptr_ = new concentration;
  ptr_->A = copied.getPtrA();
  ptr_->B = copied.getPtrB();
  ptr_->C = copied.getPtrC();
  Wmin_ = copied.getWmin();
}

Bacteria :: Bacteria(std::string file){
  std :: ifstream f(file.c_str() , std::ios::in);
  std :: string P6;
  f >> Wmin_ >> Pmut_ >> Pdeath_;
  f.get(); //il sait passer a la ligne grace a get apres
  ptr_ = new concentration;
  ptr_->A = 0;
  ptr_->B = 0;
  ptr_->C = 0;
  genotype_ = gB;
  alive_ = true;
  divided_ = false;
  }



//===========================Operators==================================
const Bacteria& Bacteria :: operator=(const Bacteria& copied){
  if (&copied != this){
    genotype_ = copied.getGen();
    alive_ = copied.isAlive();
    divided_ = copied.didDivide();
    Pmut_ = copied.getPmut();
    Pdeath_ = copied.getPdeath();
    ptr_->A = copied.getPtrA();
    ptr_->B = copied.getPtrB();
    ptr_->C = copied.getPtrC();
    Wmin_ = copied.getWmin();
  }
  return *this;
}




//=============================Methods==================================
void Bacteria :: mutation(){
  double nb = (double)rand() / (double)RAND_MAX;
  if (nb < Pmut_){
    if (genotype_ == gB){
      genotype_ = gA;
    }
    else{
      genotype_ = gB;
    }
  }
}

double Bacteria :: fitness(){
  double f = 0;
  if (genotype_ == gA){
    f = ptr_->B;
  }
  else {
    f = ptr_->C;
  }
  if (!alive_ || f < Wmin_){
    f = 0;
  }
  return f;
}

void Bacteria :: death(){
  double nb = (double)rand() / (double)RAND_MAX;
  if (nb < Pdeath_){
    alive_ = false;
  }
}

void Bacteria :: mother(){
  ptr_->A *= 0.5;
  ptr_->B *= 0.5;
  ptr_->C *= 0.5;
  divided_ = true;
}



//===========================Destructors================================
Bacteria :: ~Bacteria(){
  delete ptr_;
}
