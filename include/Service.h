#pragma once
#include <QString>


struct Service {
    QString name;
    int speed;

    Service (QString, int);
    bool operator< (const Service &) const;
    bool operator== (const Service &) const;
};
