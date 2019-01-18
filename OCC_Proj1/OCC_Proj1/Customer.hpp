//
//  Customer.hpp
//  OCC_Proj1
//
//  Created by Anna Li on 9/4/18.
//  Copyright © 2018 Anna Li. All rights reserved.
//


#ifndef Customer_hpp
#define Customer_hpp
#include <string>
using namespace std;


class Customer{
    
    
    
public:
    
    Customer();  //default constructor
    
    Customer(string name, string device = "unknown", int wait_time = 0);   //parameterized constructor
    
    
    
    //return: name_
    
    string getName();
    
    
    
    //return: defective_device_
    
    string getDevice();
    
    
    
    //return: wait_time_
    
    int getWaitTime();
    
    
    
    //post: wait_time_ = new_wait_time
    
    void updateWaitTime(int new_wait_time);
    
    
    
private:
    
    string name_;
    
    string defective_device_;
    
    int wait_time_;
    
    
    
}; // end Customer

#endif //Customer_hpp
