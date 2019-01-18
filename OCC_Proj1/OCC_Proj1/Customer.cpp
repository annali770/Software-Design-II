//
//  Customer.cpp
//  OCC_Proj1
//  CSCI 235, Fall 2018, Project 1
//
//  Implements the Customer class.
//
//  Created by Anna Li on 9/4/18.
//  Copyright © 2018 Anna Li. All rights reserved.
//


#include "Customer.hpp"
#include <string>
using namespace std;



    Customer::Customer() {
    }  //default constructor
    
    Customer::Customer(string name, string device, int wait_time) {
        name_ = name;
        wait_time_ = wait_time;
        defective_device_ = device;
    }   //parameterized constructor
    
    
    
    //return: name_
    
    string Customer::getName() {
        return name_;
    }
    
    
    
    //return: defective_device_
    
    string Customer::getDevice() {
        return defective_device_;
    }
    
    
    
    //return: wait_time_
    
   int Customer::getWaitTime() {
        return wait_time_;
    }
    
    
    
    //post: wait_time_ = new_wait_time
    
    void Customer::updateWaitTime(int new_wait_time) {
        wait_time_ = new_wait_time;
    }
    

 // end Customer





