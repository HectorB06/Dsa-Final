//
// Created by steff on 11/30/2024.
//

#ifndef DSAFINAL_STUDENT_H
#define DSAFINAL_STUDENT_H

#include <iostream>

using namespace std;

class Student {
private:
    int userID;
    string subject;
    string creativity;
    string tasks;
    string interpersonal;
    string goals;
    string recommendation;
    string scale;

public:
    Student(string subject, string creativity, string tasks, string interpersonal, string goals, string recommendation, string scale, int id){
        this->subject = subject;
        this->creativity = creativity;
        this->tasks = tasks;
        this->interpersonal = interpersonal;
        this->goals = goals;
        this->recommendation = recommendation;
        this->scale = scale;
        userID = id;
    }

    int getID(){
        cout << this->userID << endl;
    }
    // getBestFitMajor function
    // getTime function


    /*
     REMINDERS:
     - make sure that max heap and min heap count as 2 different data structures
     - import the csv file into this folder and use that to make the heap

     NOTES:
     - Steffano: created the front end for the console, getting the ID from the user
     based on number inputs, created the student class and templates of other functions.
     I will continue the front end once the time taken and heap functions are created to
     obtain data from them. Lmk if you guys need help with any of the functions.

    */


};


#endif //DSAFINAL_STUDENT_H
