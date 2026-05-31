#pragma once
class SpaceStation;
class Module{
public:
    virtual ~Module()=default;
    virtual void update(SpaceStation& station)=0;
};
