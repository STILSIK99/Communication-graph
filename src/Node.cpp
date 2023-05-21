#include "Node.h"

Node::Node()
{
    abonents = vector<int> (3, 0);
    count_by_cat_service = vector<map<Service, int>> (3, map<Service, int>());
}

int Node::getCountByServ (Service &serv)
{
    int res = 0;
    for (int cat = 0; cat < 3; ++cat) {
        if (count_by_cat_service[cat].count (serv))
            res += count_by_cat_service[cat][serv] * abonents[cat];
    }
    return res;
}

int Node::getSpeed (vector<Service> &dict)
{
    int res = 0;
    for (auto x : dict) {
        res += x.speed * getCountByServ (x);
    }
    return res;
}

int Node::getServices (vector<Service> &dict)
{
    int res = 0;
    for (auto x : dict) {
        res += getCountByServ (x);
    }
    return res;
}
