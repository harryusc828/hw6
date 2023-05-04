#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <string> 
using namespace std; 
typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        HASH_INDEX_T target = 0; 
        string my_k = k; 
        unsigned long int num[5] = {0, 0, 0, 0, 0}; 
        if(my_k.size() % 6 != 0){
            for(size_t i = 0; i < 6 - k.size()%6; i++){
                my_k = 'a' + my_k; 
            }
        }
        // cout << "my k is " << my_k << endl; 
        size_t group_num = my_k.size() / 6; 
        int idx = 0; 
        for(size_t i = 5 - group_num; i < 5; i++){
            num[i] = ((((letterDigitToNumber(my_k[0 + 6*idx])*36 + letterDigitToNumber(my_k[1+ 6*idx]))*36 + letterDigitToNumber(my_k[2+ 6*idx]))*36 + letterDigitToNumber(my_k[3+ 6*idx]))*36 + letterDigitToNumber(my_k[4+ 6*idx]))*36 + letterDigitToNumber(my_k[5+ 6*idx]); 
            // cout << " my k [5] is " << my_k[5] << "the letter digit to number of my k 5 is " << letterDigitToNumber(my_k[5]) << endl; 
            // cout << " num i is " << num[i]; 
            idx++;   
        }
        target = rValues[0]*num[0]+ rValues[1]*num[1]+ rValues[2]*num[2]+ rValues[3]*num[3]+ rValues[4]*num[4]; 
        return target; 
     
    }

    // A limy_kely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        HASH_INDEX_T target = 0; 
        // Add code here or delete this helper function if you do not want it
        if('A' <= letter && letter <= 'Z'){
            letter = letter - 'A' + 'a'; 
        }
        if('a' <= letter && letter <= 'z'){
            target = letter - 'a'; 
            return target;
        }
        if('0' <= letter && letter <= '9'){
            target = letter - '0' + 26; 
            return target; 
        }
        return target; 
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
