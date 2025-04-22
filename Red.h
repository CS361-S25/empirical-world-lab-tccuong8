#ifndef RED_H
#define RED_H

#include "Org.h"

class Red : public Organism
{
    int intake;
    int birth_cost;
    int species;

public:
    Red(emp::Ptr<emp::Random> _random, double _intake = 100, double _birth_cost = 1000, double _points = 0.0) : 
    Organism(_random, _points), intake(_intake), birth_cost(_birth_cost), species(1) { ; }

    int GetSpecies() { return species; }

    std::string GetColor() { return "red"; }

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
            emp::Ptr<Organism> offspring = new Red(this->GetRandom());
            this->SetPoints(0.0);
            return offspring;
        }
        return nullptr;
    }
};

#endif