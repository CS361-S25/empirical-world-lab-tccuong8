#ifndef RED_H
#define RED_H

#include "Org.h"

class Red : public Organism {
    int intake;
    int birth_cost;
    int species;
    public:
        Red(emp::Ptr<emp::Random> _random, int _intake = 100, int _birth_cost = 1000, double _points=0.0): 
        Organism(_random, _points), intake(_intake), birth_cost(_birth_cost), species(1) {;}

        int GetSpecies() {return species;}

        std::string GetColor() {return "red";}

        
};

#endif