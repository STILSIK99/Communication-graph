#include "Service.h"

Service::Service (QString _name, int _speed):
    name (_name), speed (_speed)
{}

bool Service::operator< (const Service &a) const
{
    return this->name < a.name;
}

bool Service::operator== (const Service &a) const
{
    return a.name == this->name && a.speed == this->speed;
}
