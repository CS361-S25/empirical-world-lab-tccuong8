#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"
#include "emp/math/math.hpp"

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

    // First, you’ll need to make a new method in your World subclass that removes an organism from the population and returns it. I recommend calling it ExtractOrganism. You already know how to get an organism at a particular position in the world, and ‘removing’ it from the population just involves setting its spot to null:
    // pop[i] = nullptr;
    // Then you just need to return the organism that you grabbed.
    emp::Ptr<Organism> ExtractOrganism(int i)
    {
        emp::Ptr<Organism> org = pop[i];
        pop[i] = nullptr;
        return org;
    }

    std::vector<size_t> GetNeighbors(int i)
    {
        // Use i to calculate the neighbors' position in the world and check for occupancy via remainder and mosulus calculation. Add valid ones into a vector and randomly choose one of them to place the organism in. If there's no valid neighbors, just place it back at its original location.
        const int W = GetWidth();
        const int H = GetHeight();
        const int id = i;
        const int x = id % W;
        const int y = id / W;

        std::vector<size_t> neighbor_ids;
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;
                int nx = emp::Mod((x + dx), W);
                int ny = emp::Mod((y + dy), H);
                int pos = nx + ny * W;
                neighbor_ids.push_back(pos);
            }
        }
        return neighbor_ids;
    }

    int GetRandomEmptyNeighborSpot(std::vector<size_t> neighbor_ids)
    {
        emp::vector<size_t> empty_neighbors;
        for (size_t id : neighbor_ids)
        {
            if (!IsOccupied(id))
            {
                empty_neighbors.push_back(id);
            }
        }
        if (empty_neighbors.size() == 0)
        {
            return -1; // No empty neighbors
        }
        emp::vector<size_t> schedule = emp::GetPermutation(random, empty_neighbors.size());
        return empty_neighbors[schedule[0]];
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
            Organism &org = GetOrg(i);
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
            // this is implemented in Organism
            if (offspring)
            {
                // std::cout << "Org [" << i << "] has reproduced!" << std::endl;
                DoBirth(*offspring, i);
                // i is the parent's position in the world
            }
            emp::Ptr<Organism> movedOrg = ExtractOrganism(i);

            // Try 1: Newly defined methods
            // std::vector<size_t> neighbor_ids = GetNeighbors(i);
            // int pos_schedule = GetRandomEmptyNeighborSpot(neighbor_ids);

            // Try 2: Hardcoded loop limit
            int pos_target = i;
            for (int j = 0; j < 9; ++j)
            {
                emp::WorldPosition pos = GetRandomNeighborPos(i);
                if (pos.IsValid() && !IsOccupied(pos))
                {
                    pos_target = pos.GetIndex();
                    break;
                }
            }
           
            AddOrgAt(movedOrg, pos_target);
        }
    }
};
#endif
