#include <iostream>

#include "emp/base/vector.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "World.h"
#include "Org.h"
#include "Red.h"
#include "Blue.h"

// This is the main function for the NATIVE version of this project.

int main(int argc, char* argv[])
{
  emp::Random random(2);
  OrgWorld world(random);

  emp::Ptr<Organism> org1 = new Red(&random);
  world.AddOrgAt(org1, 0);
  emp::Ptr<Organism> org2 = new Blue(&random);
  world.AddOrgAt(org2, 1);

  std::cout << world.size() << std::endl;

  world.Resize(10, 10);
  
  std::cout << world.GetNumOrgs() << std::endl;
  // world.Update();

  for ( int i = 0; i < 20; i++ ) {
    world.Update();
  }
  
  std::cout << world.GetNumOrgs() << std::endl;

}
