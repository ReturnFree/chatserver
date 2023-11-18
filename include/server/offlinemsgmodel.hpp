#ifndef OFFLINEMESSAGEMODEL_H
#define OFFLINEMESSAGEMODEL_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class OfflineMsgModel
{
public:
    void insert(int userif,string msg);

    void remove(int userid);

    vector<string> query(int userid);
};

#endif