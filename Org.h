#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism {
    private:
        int species;
        double points;
        emp::Ptr<emp::Random> random;

    public:
    Organism(emp::Ptr<emp::Random> _random, double _points=0.0) :
        random(_random), points(_points) {;}

    void SetPoints(double _in) {points = _in;}
    void AddPoints(double _in) {points += _in;}
    int ShowPoints() {return points;}

    virtual std::string GetColor() {return "black";}


    void Process(double _in) {
        points += _in;
    }

    int CanReproduce() {
        if ((species == 1 && points >= 1000) || (species == 2 && points >= 2000)) {
            return 1;
        }
        return 0;
    }

    emp::Ptr<Organism> CheckReproduction() {
        if (species == 2 && CanReproduce() == 1) {
            emp::Ptr<Organism> offspring = new Organism(random);
            points = 0;
            return offspring;
        }
        return nullptr;
    }
};
#endif