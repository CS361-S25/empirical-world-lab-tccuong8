#include <iostream>

#include "Org.h"
#include "emp/base/vector.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "World.h"

// This is the main function for the NATIVE version of this project.

int main(int argc, char* argv[])
{
  emp::Random random(2);
  OrgWorld world(random);

  Organism* org1 = new Organism(&random);
  world.Inject(*org1);
  Organism* org2 = new Organism(&random);
  world.Inject(*org2);

  std::cout << world.size() << std::endl;

  world.Resize(10, 10);
  
  std::cout << world.GetNumOrgs() << std::endl;
  // world.Update();

  for ( int i = 0; i < 20; i++ ) {
    world.Update();
  }
  
  std::cout << world.GetNumOrgs() << std::endl;

}
