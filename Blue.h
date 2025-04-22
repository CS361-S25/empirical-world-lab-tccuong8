#ifndef BLUE_H
#define BLUE_H

#include "Org.h"

class Blue : public Organism
{
    int intake;
    int birth_cost;
    int species;

public:
    Blue(emp::Ptr<emp::Random> _random, double _intake = 50, double _birth_cost = 2000, double _points = 0.0) : 
    Organism(_random, _points), intake(_intake), birth_cost(_birth_cost), species(1) { ; }

    int GetSpecies() { return species; }

    std::string GetColor() { return "blue"; }

    void Process()
    {
        this->AddPoints(intake);
    }

    int CanReproduce()
    {
        if (this->ShowPoints() >= birth_cost)
        {
            return 1;
        }
        return 0;
    }

    emp::Ptr<Organism> CheckReproduction()
    {
        if (this->CanReproduce() == 1)
        {
            emp::Ptr<Organism> offspring = new Blue(this->GetRandom());
            this->SetPoints(0.0);
            return offspring;
        }
        return nullptr;
    }
};

#endif#include "Org.h"