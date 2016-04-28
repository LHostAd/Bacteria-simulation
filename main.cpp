//les includes
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Bacteria.h"
#include "Petri.h"
#include "Concentration.h"



int main() {
  srand(time(NULL));
  printf("Hello World! \n");

 
//========================Test code Bacteria============================
  
  // TOUT MARCHE !
 /* 
// ===============Genotype================
  std :: cout << "    Genotype: " << std :: endl;
  Bacteria Ecoli=Bacteria("Bparameters.txt");
  std :: cout <<"Avant mut: "<< Ecoli.getGen() << std :: endl;
  //Ecoli.mutation();
  //std :: cout <<"Apres mut: "<< Ecoli.getGen() << std :: endl;
  
  Bacteria Anabaena = Bacteria(Ecoli);
  std :: cout <<"proba mort "<< Ecoli.getPdeath() << std :: endl;
  Anabaena.death();
  std :: cout <<"is Alive ? "<< Anabaena.isAlive() << std :: endl;
  
  
 
// ===============Fitness================
  std :: cout << "    Test fitness " << std :: endl;
  std :: cout << "Concentration interne en A B C" << "\n" << Ecoli.getPtrA() << std :: endl;
  std :: cout << Ecoli.getPtrB() << std :: endl;
  std :: cout << Ecoli.getPtrC() << std :: endl;
  std :: cout << "Resultat de Fitness: " << Ecoli.fitness() <<std :: endl;
  
  
// ===============Death================
  std :: cout << "    Test death " << std :: endl;
  std :: cout << "    Pdeath: " << Ecoli.getPdeath() << "  puis la mort : " << std :: endl;
  Ecoli.death();    
  std :: cout << "isALive ? :  " << Ecoli.isAlive() << std :: endl; 
  
// ===============Mother================
  std :: cout << "    Test mother " << std :: endl;
  std :: cout << "did divide ? : " <<Ecoli.didDivide() << "  mother now" << std :: endl;
  Ecoli.mother();
  std :: cout << "Concentration interne en A B C" << "\n" << Ecoli.getPtrA() << std :: endl;
  std :: cout << Ecoli.getPtrB() << std :: endl;
  std :: cout << Ecoli.getPtrC() << std :: endl;
  std :: cout << "did divide ? : " <<Ecoli.didDivide() << std :: endl;


// ============== =operator =======================
  Bacteria Ecoli = Bacteria();
  Bacteria Anabaena = Bacteria (0.001,0,0.05);
  Ecoli = Anabaena;
  std::cout<<Ecoli.getPdeath()<<std::endl;
*/
//========================Test code Petri===============================
  
  Petri TabledeTP = Petri("Pparameters.txt");
/*
  // TOUT MARCHE !
  
  std :: cout << "\n Genotype bact : "<< TabledeTP.getBact(1,0)->getGen() << std :: endl;

  std :: cout << "\n Test metabolisme : concentration boite" << std :: endl;
  std::cout<<TabledeTP.getPtrA(1,0)<<std::endl;
  std::cout<<TabledeTP.getPtrB(1,0)<<std::endl;
  std::cout<<TabledeTP.getPtrC(1,0)<< "\n" << "all_eating()" <<std::endl;
  TabledeTP.all_eating();
  std :: cout << "\n new Concentration ds boite:" << std :: endl;
  std::cout<<TabledeTP.getPtrA(1,0)<<std::endl;
  std::cout<<TabledeTP.getPtrB(1,0)<<std::endl;
  std::cout<<TabledeTP.getPtrC(1,0)<< "\n" << std::endl;
  
  std :: cout << "\n new Concentration ds bact" << std :: endl;
  std::cout<<TabledeTP.getBact(1,0)->getPtrA() << std::endl;
  std::cout<<TabledeTP.getBact(1,0)->getPtrB() << std::endl;
  std::cout<<TabledeTP.getBact(1,0)->getPtrC() << std::endl;

  
  std::cout<< "\n" << "Is Alive  : " << TabledeTP.getBact(1,0)->isAlive()<< "\n" << "  Petri.kill() " <<  std::endl;
  TabledeTP.kill();
  std::cout<<  "Is Alive  : " << TabledeTP.getBact(1,0)->isAlive()<< "\n" <<  std::endl;
  std::cout<<TabledeTP.getPtrA(1,0)<<std::endl;
  std::cout<<TabledeTP.getPtrB(1,0)<<std::endl;
  std::cout<<TabledeTP.getPtrC(1,0)<<std::endl;
  TabledeTP.diffusion();
  std::cout<< " \n une petite diffusion ! " << std::endl;   
  std::cout<<TabledeTP.getPtrA(1,0)<<std::endl;
  std::cout<<TabledeTP.getPtrB(1,0)<<std::endl;
  std::cout<<TabledeTP.getPtrC(1,0)<<std::endl; 


//========================Test Reproduction=============================


  std::cout<< "     Reproduction" << std::endl;
  std::cout<< " nb de A :  " << TabledeTP.amountofgA() << std::endl;
  std::cout<< " nb de B :  " << TabledeTP.amountofgB() << std::endl;
  
  std::cout<< "Nb de morts : "<< TabledeTP.getNbDeaths() << std::endl;
  
  std::cout<< " \n Une diffusion, puis repas " << std::endl;
  TabledeTP.diffusion();
  TabledeTP.all_eating();
  std::cout<< " concentration ds bact(0,1) " << std::endl;
  std::cout<<TabledeTP.getBact(1,0)->getPtrA() << std::endl;
  std::cout<<TabledeTP.getBact(1,0)->getPtrB() << std::endl;
  std::cout<<TabledeTP.getBact(1,0)->getPtrC() << std::endl;
  TabledeTP.all_eating();
  std::cout<< " \n all_eating()" << "\n concentration ds bact(0,1) " << std::endl;
  std::cout<<TabledeTP.getBact(1,0)->getPtrA() << std::endl;
  std::cout<<TabledeTP.getBact(1,0)->getPtrB() << std::endl;
  std::cout<<TabledeTP.getBact(1,0)->getPtrC() << std::endl;
  
  std::cout<< " .kill() "  << std::endl;
  TabledeTP.kill();

  std::cout<< " .all_eating() "  << std::endl;
  TabledeTP.all_eating();
  
  std::cout<< " .state() "  << std::endl;
  std :: cout <<TabledeTP.state()<<std :: endl;

  std::cout<< TabledeTP.getNbDeaths() << std::endl;  
  TabledeTP.make_babies();
  std::cout<< TabledeTP.getNbDeaths() << std::endl;  
  TabledeTP.make_babies();
  std::cout<< "\n" << TabledeTP.getNbDeaths() << std::endl;  

  std::cout<< " \n Test Petri_reset \n " << std::endl;
  std::cout<< " Concentration avant :" << std::endl;   
  std::cout<<TabledeTP.getPtrA(1,0)<<std::endl;
  std::cout<<TabledeTP.getPtrB(1,0)<<std::endl;
  std::cout<<TabledeTP.getPtrC(1,0)<<std::endl;
  TabledeTP.reset();
  std::cout<< " Concentration apres :" << std::endl;   
  std::cout<<TabledeTP.getPtrA(1,0)<<std::endl;
  std::cout<<TabledeTP.getPtrB(1,0)<<std::endl;
  std::cout<<TabledeTP.getPtrC(1,0)<<"\n"<<std::endl;
  

*/
  std::cout<< " \n Simulation: \n " << std::endl;
  TabledeTP.opt_diagram(0);

  //TabledeTP.conservation(2,950,10000);
  
  
  
//========================Test parametres===============================

  
  
  return 0;
}
