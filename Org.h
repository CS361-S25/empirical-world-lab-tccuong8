#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism
{
private:
    int species;
    double points;
    emp::Ptr<emp::Random> random;

public:
    Organism(emp::Ptr<emp::Random> _random, double _points = 0.0) : random(_random), points(_points) { ; }

    void SetPoints(double _in) { points = _in; }
    void AddPoints(double _in) { points += _in; }
    int ShowPoints() { return points; }
    emp::Ptr<emp::Random> GetRandom() {return random;}

    virtual std::string GetColor() { return "black"; }

    virtual void Process(double _in)
    {
        points += _in;
    }

    virtual int CanReproduce()
    {
        return 0;
    }

    virtual emp::Ptr<Organism> CheckReproduction()
    {
        return nullptr;
    }
};
#endif