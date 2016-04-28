#include <algorithm> // std::random_shuffle
#include "Petri.h"


//===========================Constructors===============================

//===============DEFAULT CONSTRUCTOR==============
Petri::Petri(){
  Wmin_ = 0.001;
  Pmut_ = 0;
  Pdeath_ = 0.02;
  W_ = 32;
  H_ = 32;
  D_ = 0.1;
  Ainit_=0;
  T_ = 1500;
  T_simul_ = 10000;
  ptr_ = new concentration*[W_];
  for (unsigned int i=0;i<W_;i++){
    ptr_[i] = new concentration[H_];
    for ( unsigned int j=0;j<H_;j++){
      ptr_[i][j].A = Ainit_;
      ptr_[i][j].B = 0;
      ptr_[i][j].C = 0;
    }
  }
  Raa_ = 0.1;
  Rab_ = 0.1;
  Rbb_ = 0.1;
  Rbc_ = 0.1;
  bact_ = new Bacteria*[W_];
  for ( unsigned int i=0;i<W_;i++){
    bact_[i] = new Bacteria[H_];
    for ( unsigned int j=0;j<H_;j++){
      Bacteria newone = Bacteria(Wmin_, Pmut_, Pdeath_);
      bact_[i][j] = newone;
    }
  }
  for ( unsigned int j=0;j<(W_ * H_ * 0.5);j++){
    int x = 0;
    int y = 0;
    while (bact_[x][y].getGen() != 0) {
      x = rand()%(32-0) +0;
      y = rand()%(32-0) +0;
    }
    bact_[x][y].setGen(1);
  }
  amount_of_deaths=0;
}

//===========CONSTRUCTOR TX TO A FILE============
Petri::Petri(std::string file){
  std :: ifstream f(file.c_str() , std::ios::in);
  std :: string P6;
  f >> Raa_ >> Rbb_ >> Rab_ >> Rbc_ >> W_ >> H_ >> D_ >> T_ >> Ainit_ >> T_simul_ >> Wmin_ >> Pmut_ >> Pdeath_;
  f.get(); //il sait passer a la ligne grace a get apres
  f.close();
  ptr_ = new concentration*[W_];
  for ( unsigned int i=0;i<W_;i++){
    ptr_[i] = new concentration[H_];
    for ( unsigned int j=0;j<H_;j++){
      ptr_[i][j].A = Ainit_;
      ptr_[i][j].B = 0;
      ptr_[i][j].C = 0;
    }
  }
  bact_ = new Bacteria*[W_];
  for ( unsigned int i=0;i<W_;i++){
    bact_[i] = new Bacteria[H_];
    for ( unsigned int j=0;j<H_;j++){
      Bacteria newone = Bacteria(Wmin_, Pmut_, Pdeath_);
      bact_[i][j] = newone;
    }
  }
  for ( unsigned int j=0;j<(W_ * H_ * 0.5);j++){
    int x = 0;
    int y = 0;
    while (bact_[x][y].getGen() != 0) {
      x = rand()%(32-0) +0;
      y = rand()%(32-0) +0;
    }
    bact_[x][y].setGen(1);
  }
  amount_of_deaths=0;
}



//===========================Destructors================================
Petri::~Petri(){
  for ( unsigned int i=0;i<W_;i++){
    delete[] ptr_[i];
    delete[] bact_[i];
  }
  delete[] bact_; 
  delete[] ptr_;
}


//=============================Methods==================================

//===================DIFFUSION==================
void Petri::diffusion(){
  /* Diffusion in the environment */
  if (D_ <= 0.1){
    concentration** copy_ = new concentration*[W_];
    for ( unsigned int i=0;i<W_;i++){
      copy_[i] = new concentration[H_];
      for ( unsigned int j=0;j<H_;j++){
        copy_[i][j].A = ptr_[i][j].A;
        copy_[i][j].B = ptr_[i][j].B;
        copy_[i][j].C = ptr_[i][j].C;
      }
    }
    for ( unsigned int X=0;X<W_;X++){
      for ( unsigned int Y=0;Y<H_;Y++){
        for (int i=-1;i<2;i++){
          for (int j=-1;j<2;j++){
            copy_[X][Y].A += D_ * ptr_[(W_+X+i)%W_][(H_+Y+j)%H_].A;
            copy_[X][Y].B += D_ * ptr_[(W_+X+i)%W_][(H_+Y+j)%H_].B;
            copy_[X][Y].C += D_ * ptr_[(W_+X+i)%W_][(H_+Y+j)%H_].C;
          }
        }
        copy_[X][Y].A -= 9 * D_ * ptr_[X][Y].A;
        copy_[X][Y].B -= 9 * D_ * ptr_[X][Y].B;
        copy_[X][Y].C -= 9 * D_ * ptr_[X][Y].C;
      }
    }
    for ( unsigned int X=0;X<W_;X++){
      for ( unsigned int Y=0;Y<H_;Y++){   
        ptr_[X][Y].A = copy_[X][Y].A ;
        ptr_[X][Y].B = copy_[X][Y].B ;
        ptr_[X][Y].C = copy_[X][Y].C ;
      }
    }
    for ( unsigned int i=0;i<W_;i++){
      delete[] copy_[i];
    }
    delete[] copy_;
  }
  else{
    std::cout<<"Taux de diffusion trop haut"<<std::endl;
  }
}


//=======================KILL=======================
void Petri :: kill(){
  /*For each bact : check if it is alive, submit it to B.death(), and 
  see if it died. If it did, update the concentrations*/
  for ( unsigned int i=0;i<W_;i++){
    for ( unsigned int j=0;j<H_;j++){
      if (bact_[i][j].isAlive()){
        bact_[i][j].death();
        if (!bact_[i][j].isAlive()){
          ptr_[i][j].A += bact_[i][j].getPtr()->A;
          ptr_[i][j].B += bact_[i][j].getPtr()->B;
          ptr_[i][j].C += bact_[i][j].getPtr()->C;
          bact_[i][j].getPtr()->A = 0;
          bact_[i][j].getPtr()->B = 0;
          bact_[i][j].getPtr()->C = 0;
          amount_of_deaths +=1;
        }
      }
    }
  }
}


//======================EATING======================
void Petri :: eating(int i, int j){
  /* metabolism action, differing with the bacteria genotype */ 
  if (bact_[i][j].getGen() == 1){
    for (int step=0;step<10;step++){
      bact_[i][j].getPtr()->B += 0.1 * (bact_[i][j].getPtr()->A * Rab_);
      bact_[i][j].getPtr()->A += 0.1 * (ptr_[i][j].A * Raa_ - bact_[i][j].getPtr()->A * Rab_);
      ptr_[i][j].A -= 0.1 * (ptr_[i][j].A * Raa_);  
      //std::cout<< ptr_[i][j].A << std::endl;        
          
      }
    }
  else{
    for (int step=0;step<10;step++){
      bact_[i][j].getPtr()->C += 0.1 * (bact_[i][j].getPtr()->B * Rbc_);
      bact_[i][j].getPtr()->B += 0.1 * (ptr_[i][j].B * Rbb_ - bact_[i][j].getPtr()->B * Rbc_);
      ptr_[i][j].B -= 0.1 * (ptr_[i][j].B * Rbb_);          
      }
    //std::cout<< bact_[i][j].getPtr()->C<<std::endl;
  }
}

void Petri :: all_eating(){
  /* make all bacteria eat */
  for ( unsigned int i=0;i<W_;i++){
    for ( unsigned int j=0;j<H_;j++){
      if (bact_[i][j].isAlive()){
        eating(i,j);
      }
    }
  }
}


//================AMOUNT OF BACT==================
int Petri :: amountofgA(){
  /* compute the amount of gA Bacteria in the environment */ 
  int nbA = 0;
  for ( unsigned int i=0;i<W_;i++){
    for ( unsigned int j=0;j<H_;j++){
      if (bact_[i][j].getGen() == 1 and bact_[i][j].isAlive()){
        nbA +=1;
      }
    }
  }
  return nbA;
}

int Petri :: amountofgB(){
  /* compute the amount of gB Bacteria in the environment */ 
  int nbB = 0;
  for ( unsigned int i=0;i<W_;i++){
    for ( unsigned int j=0;j<H_;j++){
      if (bact_[i][j].getGen() == 0 and bact_[i][j].isAlive()){
        nbB +=1;
      }
    }
  }
  return nbB;
}

//================REPRODUCTION====================
void Petri :: make_babies(){
  /* Division method : */
  /* Find a gap, compute the Bacteria's fitness around it */  
  for (size_t gap=0;gap<deaths_position_.size();gap++){
    std::pair <int,int> position = deaths_position_[gap];
    int X = std::get<0>(position);
    int Y = std::get<1>(position);
    std::pair <int,int> max_pos = std::make_pair(0,0);
    double max_fitness = 0;
    std::vector< std::pair <int,int> > max_positions;
    for (int i=-1;i<2;i++){
      for (int j=-1;j<2;j++){
        int x = (W_+X+i)%W_;
        int y = (H_+Y+j)%H_;
        double f = bact_[x][y].fitness();
        //std :: cout << max_fitness << ' ' << f << '|' ;
        if (f > max_fitness){
          if (!bact_[x][y].didDivide()){
            max_pos=std::make_pair(x,y);
            max_positions.clear();
            max_positions.push_back(std::make_pair(x,y));
            max_fitness = f;
          }
        }
        if (f == max_fitness){
          if (!bact_[x][y].didDivide()){
            max_positions.push_back(std::make_pair(x,y));
          }
        }
      }
    }
    /* if there is a best one : division */
    std::random_shuffle(max_positions.begin(),max_positions.end());
    if (max_fitness != 0){
      std::pair <int,int> selected_pos = max_positions[0];
      bact_[std::get<0>(selected_pos)][std::get<1>(selected_pos)].mother();
      bact_[X][Y] = Bacteria(bact_[std::get<0>(selected_pos)][std::get<1>(selected_pos)]);
      bact_[X][Y].mutation();
      bact_[std::get<0>(selected_pos)][std::get<1>(selected_pos)].mutation();
      amount_of_deaths -=1;
    }
  
  }
  /* update the deaths_position vector and reset the bacteria's divide_ argument */
  deaths_position_.clear();
  for ( unsigned int i=0;i<W_;i++){
    for ( unsigned int j=0;j<H_;j++){
      if (!bact_[i][j].isAlive()){
        deaths_position_.push_back(std::make_pair(i,j));
      }
      if (bact_[i][j].isAlive() and bact_[i][j].didDivide()){
        bact_[i][j].setDivide(false);
      }
    }
  }
  std::random_shuffle(deaths_position_.begin(),deaths_position_.end());
}


//==================RESET PETRI====================
void Petri :: reset(){
  /* reset the environment to the initial concentrations */ 
  for ( unsigned int i=0;i<W_;i++){
    for ( unsigned int j=0;j<H_;j++){
      ptr_[i][j].A = Ainit_;
      ptr_[i][j].B = 0;
      ptr_[i][j].C = 0;
    }
  }
}

void Petri :: reset_bact(){
  /* create new bacteria for a simulation */ 
  deaths_position_.clear();
  for ( unsigned int i=0;i<W_;i++){
    delete[] bact_[i];
  }
  for ( unsigned int i=0;i<W_;i++){
    bact_[i] = new Bacteria[H_];
  }
  for ( unsigned int i=0;i<W_;i++){
    for ( unsigned int j=0;j<H_;j++){
      //std :: cout << Wmin_ << " " << Pmut_ << " " << Pdeath_ << std::endl;
      Bacteria newone = Bacteria(Wmin_, Pmut_, Pdeath_);
      bact_[i][j] = newone;
    }
  }
  for ( unsigned int j=0;j<(W_ * H_ / 2);j++){
    int x = 0;
    int y = 0;
    while (bact_[x][y].getGen() != 0) {
      x = rand()%(32-0) +0;
      y = rand()%(32-0) +0;
    }
    bact_[x][y].setGen(1);
  }
}


//==================FINAL STATE====================
int Petri :: state(){
  /* returns the general bacteria's state : Exclusion, Cohabitation, Elimination */
  int nbA = 0;
  int nbB = 0;
  for ( unsigned int i=0;i<W_;i++){
    for ( unsigned int j=0;j<H_;j++){
      if (bact_[i][j].isAlive()){
        if (bact_[i][j].getGen() == 1){
          nbA +=1;
        }
        else{ 
          nbB +=1;
        }
      }
    }
  }
  if (nbB != 0 and nbA != 0){
    return 2; //Cohabitation
  }
  if (nbB == 0 and nbA != 0){
    return 1; //Exclusion
  }
  else{
    return 0; //Extinction
  }
}



//============SIMULATION & VISUALISATION===========
void Petri :: simulation(){
  reset();
  reset_bact();
  all_eating();
  for (int i=1;i<T_simul_+1;i++){
    if (deaths_position_.size() == (W_ * H_)){
      std::cout<<deaths_position_.size()<<std::endl;
      break;      
    }
    if (i % T_ == 0){
      reset();
    }
    diffusion();
    kill();
    make_babies();
    all_eating();
  }
}

void Petri :: diagram(int a){
  std::ofstream f;
  std::string name = "data"+std::to_string(a)+".txt";
  f.open(name,std::ios::out|std::ios::trunc);
  int Tmax = T_ +1;
  T_ = 1;
  for (float a=0;a<50;a++){
    int nb = 9;
    Ainit_ = a;
    int s = state();
    while (T_ < Tmax){
      simulation();
      s = state();
      int nba = amountofgA();
      int nbb = amountofgB();
      f<<Ainit_<<" "<<T_<<" "<< s << " "<< nba << " " << nbb << std::endl;
      T_ += nb;
      nb=10;
    }
    T_=1;
  }
  
  f.close();
  Ainit_ = 0;
  T_ = Tmax-1;
}


void Petri :: opt_diagram(int a){
  std::ofstream f;
  std::string name = "data"+std::to_string(a)+"_opt.txt";
  f.open(name,std::ios::out|std::ios::trunc);
  int Tmax = T_ +1;
  T_ = 1;
  for (float a=0;a<50;a++){
    int nb = 10;
    Ainit_ = a;
    int s = state();
    int p_state = 0; //previous state
    while (T_ < Tmax){
      if (T_ == 1){
        simulation();
        s = state();
        p_state = s;
        f<<Ainit_<<" "<<T_<<" "<< s << std::endl;
        T_ +=(nb-1);
      }
      else {
        p_state = s;
        simulation();
        s = state();
        f<<Ainit_<<" "<<T_<<" "<< s << std::endl;
        if (p_state != s){
          T_ -= nb;
          std::vector< int > diff_states;
          int t_state = 0;
          for (int i=1;i<nb;i++){
            T_ +=i;
            for(int j=0;j<6;j++){
              simulation();
              diff_states.push_back(state());
            }
            t_state = most_frequent_state(diff_states);
            f<<Ainit_<<" "<<T_<<" "<< t_state << std::endl;
            diff_states.clear();
            T_ -=i;
          }
          T_ +=nb;
        }
        T_ +=nb;
      }
    }
    T_=1;
  }
  f.close();
  Ainit_ = 0;
  T_ = Tmax-1;
}

int Petri :: most_frequent_state(std::vector< int > V ){
  int count0 = 0;
  int count1 = 0;
  int count2 = 0;
  for (size_t vals=0;vals<V.size();vals++){
    if (V[vals] == 0){
      count0 +=1;
    }
    if (V[vals] == 1){
      count1 +=1;
    }
    if (V[vals] == 2){
      count2 +=1;
    }
  }
  if ((count0 > count1) and (count0 > count2)){
    return 0;
  }
  if ((count1 > count0) and (count1 > count2)){
    return 1;
  }
  else{
    return 2;
  }
}



void Petri :: conservation(int a, int T, int Tsimul){
  std::ofstream f;
  std::ofstream g;
  std::ofstream h;
  
  f.open("conservation.txt",std::ios::out|std::ios::trunc);
  g.open("evolpop.txt",std::ios::out|std::ios::trunc);
  h.open("evolfood.txt",std::ios::out|std::ios::trunc);

  Ainit_ = a;
  T_ = T;
  T_simul_ = Tsimul;
  reset();
  reset_bact();
  all_eating();
  //reset();
  for (int i=1;i<T_simul_+1;i++){
    //std::cout<<deaths_position_.size()<<std::endl;
    //if (deaths_position_.size() == (W_ * H_)){
      //break;      
    //}
    if (i % T_ == 0){
      reset();
    }
    diffusion();
    kill();
    make_babies();
    all_eating();
    g <<i<< " " << amountofgA() << " "<< amountofgB() << std::endl;
    double Aout = 0;
    double Bout = 0;
    double Cout = 0;
    double Ain = 0;
    double Bin = 0;
    double Cin = 0;
    for ( unsigned int i =0;i<W_;++i) {
      for ( unsigned int j=0;j<H_;++j){
        Aout+=ptr_[i][j].A;
        Bout+=ptr_[i][j].B;
        Cout+=ptr_[i][j].C;
        Ain+=bact_[i][j].getPtr()->A;
        Bin+=bact_[i][j].getPtr()->B;
        Cin+=bact_[i][j].getPtr()->C;
      }
    }
    h<< i << " "<<Aout << " "<< Bout << " "<<  Cout << " "<< Ain << " "<<  Bin << " "<< Cin << std::endl;
    f<<Aout + Bout + Cout + Ain + Bin + Cin << std::endl;
  }
  f.close();
  g.close();
  h.close();

}

