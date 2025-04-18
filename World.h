#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Org.h"

class OrgWorld : public emp::World<Organism>
{

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;

public:
    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random)
    {
        random_ptr.New(_random);
    }

    ~OrgWorld()
    {
    }

    void Update()
    {
        emp::World<Organism>::Update();

        // We don’t want to give unfair advantage to organisms at the beginning of the list, since if they always get to reproduce first, genotypes could persist in the population even if they aren’t actually better, but just because they happen to be first in the list and so get checked for reproduction before everything else. Empirical has a useful function for getting a permutation of a list for this purpose:
        emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
        for (int i : schedule)
        {
            if (!IsOccupied(i))
            {
                continue;
            }
            Organism& org = GetOrg(i);
            org.Process(100);
        }

        // Organisms don’t have anyway of gaining points yet though. Change the Process method so that it takes an argument points and adds those points to what the organism has already. Give them 100 points per update for now. We could call the CheckReproduction method right away as well, but this could lead to similar problems mentioned before where some organisms are lucky and get resources and the chance to reproduce right away.
        // Instead, create another schedule and loop after your first one to check reproduction after everyone has gotten resources.
        schedule = emp::GetPermutation(random, GetSize());
        for (int i : schedule)
        {
            if (!IsOccupied(i))
            {
                continue;
            }
            // std::cout << "Org [" << i << "]: " << pop[i]->ShowPoints() << std::endl;
            emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
            //this is implemented in Organism 
            if(offspring) {
                // std::cout << "Org [" << i << "] has reproduced!" << std::endl;
                DoBirth(*offspring, i);  //i is the parent's position in the world
            }
        }
    }
};
#endif
