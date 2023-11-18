#ifndef GROUPUSER_H
#define GROUPUSER_H

#include "user.hpp"
#include <string>

class GroupUser:public User
{
public :
    void setRole(string role){this->role=role;}//ld:估计是将身份改变
    string getRole(){return this->role;}//估计是获取组内成员身份
private:
    string role;
};

#endif