#pragma once
#include <vector>
#include <map>
#include "Service.h"

using namespace std;

struct Node {
    vector<int> abonents;
    //count
    vector<map<Service, int>> count_by_cat_service;
    int thread;
    int cons;
    Node();

    int getSpeed (vector<Service> &dict) ;
    int getServices (vector<Service> &dict);
    int getCountByServ (Service &serv);
};
