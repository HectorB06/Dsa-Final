#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>

#include "student.h"
#include "max_heap.h"
#include "min_heap.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

void calculateMajorFromMinHeap(int userID, Min_heap& min_students) {
    auto start_time = high_resolution_clock::now();
    bool exact_match_found = false;
    int closest_difference = 2147483647;
    int closest_id = -1;
    vector<Student> matching_students;

    for (const auto& student : min_students.heap) {
        if (student.getID() == userID) {
            matching_students.push_back(student);
            exact_match_found = true;
        }
    }

    if (!exact_match_found) {
        for (const auto& student : min_students.heap) {
            int current_difference = abs(student.getID() - userID);
            if (current_difference < closest_difference) {
                closest_difference = current_difference;
                closest_id = student.getID();
            }
        }

        if (closest_id != -1) {
            for (const auto& student : min_students.heap) {
                if (student.getID() == closest_id) {
                    matching_students.push_back(student);
                }
            }
        }
    }

    if (matching_students.empty()) {
        cout << "No recommendation found" << endl;
        return;
    }

    sort(matching_students.begin(), matching_students.end(), [](const Student& a, const Student& b) {
        return stoi(a.getScale()) > stoi(b.getScale());
    });

    int highest_scale = stoi(matching_students.front().getScale());
    set<string> recommended_majors;

    for (const auto& student : matching_students) {
        if (stoi(student.getScale()) == highest_scale) {
            recommended_majors.insert(student.getRecommendation());
        }
    }

    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);
    cout << "Data Structure used: Min Heap" << "\nTime taken: " << duration.count() << " milliseconds" << endl;

    cout << "Your recommended major(s): ";
    set<string>::iterator it;
    for (it = recommended_majors.begin(); it != recommended_majors.end(); ++it) {
        cout << *it;
        if (next(it) != recommended_majors.end()) {
            cout << ", ";
        }
    }
    cout << "!\n" << endl;
}

void calculateMajorFromMaxHeap(int userID, Max_heap& max_students) {
    auto start_time = high_resolution_clock::now();
    bool exact_match_found = false;
    int closest_difference = 2147483647;
    int closest_id = -1;
    vector<Student> matching_students;

    for (const auto& student : max_students.heap) {
        if (student.getID() == userID) {
            matching_students.push_back(student);
            exact_match_found = true;
        }
    }

    if (!exact_match_found) {
        for (const auto& student : max_students.heap) {
            int current_difference = abs(student.getID() - userID);
            if (current_difference < closest_difference) {
                closest_difference = current_difference;
                closest_id = student.getID();
            }
        }

        if (closest_id != -1) {
            for (const auto& student : max_students.heap) {
                if (student.getID() == closest_id) {
                    matching_students.push_back(student);
                }
            }
        }
    }

    if (matching_students.empty()) {
        cout << "No recommendation found" << endl;
        return;
    }

    sort(matching_students.begin(), matching_students.end(), [](const Student& a, const Student& b) {
        return stoi(a.getScale()) > stoi(b.getScale());
    });

    int highest_scale = stoi(matching_students.front().getScale());
    set<string> recommended_majors;

    for (const auto& student : matching_students) {
        if (stoi(student.getScale()) == highest_scale) {
            recommended_majors.insert(student.getRecommendation());
        }
    }

    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);
    cout << "Data Structure used: Max Heap" << "\nTime taken: " << duration.count() << " milliseconds" << endl;

    cout << "Your recommended major(s): ";
    set<string>::iterator it;
    for (it = recommended_majors.begin(); it != recommended_majors.end(); ++it) {
        cout << *it;
        if (next(it) != recommended_majors.end()) {
            cout << ", ";
        }
    }
    cout << "!" << endl;
}

int main() {

    Max_heap max_students = Max_heap();
    Min_heap min_students = Min_heap();


    string filename = "/Users/eddy/Desktop/UF Fall 24/DSA/Dsa-Final-main/enhanced_user_major_dataset.csv";

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "F" << endl;
        return 1;
    }

    string student_line;
    string header;
    getline(file, header);

    while(getline(file, student_line)){
        stringstream ss(student_line);

        string id;
        string subject;
        string creativity;
        string tasks;
        string interpersonal;
        string goals;
        string recommendation;
        string scale;

        getline(ss, id, ',');
        getline(ss, subject, ',');
        getline(ss, creativity, ',');
        getline(ss, tasks, ',');
        getline(ss, interpersonal,',');
        getline(ss, goals, ',');
        getline(ss, recommendation,',');
        getline(ss, scale, ',');

        if(subject == "Business and Finance")
            subject = "3";
        else if(subject == "Math and Science")
            subject = "1";
        else if(subject == "Arts and Humanities")
            subject = "2";
        else if(subject == "Technology and Engineering")
            subject = "4";
        else
            subject = "5";

        if(tasks == "Solving logical problems")
            tasks = "1";
        else if(tasks == "Designing or creating")
            tasks = "2";
        else if(tasks == "Leading teams")
            tasks = "3";
        else if(tasks == "Writing code")
            tasks = "4";
        else
            tasks = "5";

        if(goals == "Developing technology")
            goals = "1";
        else if (goals == "Creating art")
            goals = "2";
        else if(goals == "Building a business")
            goals = "3";
        else if(goals == "Healthcare"){
            goals = "4";
        }
        else{
            goals = "5";
        }

        string unique_id = subject + creativity + tasks + interpersonal + goals;
        int final_id = stoi(unique_id);

        Student new_student = Student(subject, creativity, tasks, interpersonal, goals, recommendation, scale, final_id);
        max_students.heap.push_back(new_student);
        min_students.heap.push_back(new_student);
    }

    max_students.buildHeap();
    min_students.buildHeap();


    cout << "==========================================================\n"
            "Welcome to the Major Recommender! \n"
            "Based on the answers you provide, the major that we believe \n"
            "best fits your interests will be provided!\n"
            "========================================================== " << endl;

    string userID = "";
    string temp1;
    cout << "Question 1: What subjects do you enjoy the most?\n"
            "(1) Math and Science\n"
            "(2) Arts and Humanities\n"
            "(3) Business and Finance\n"
            "(4) Technology and Engineering\n"
            "(5) Social Sciences and Psychology\n"
            "(please choose a number between 1-5)\n"
            "==========================================================" << endl;
    while (true) {
        cin >> temp1;
        try {
            if (stoi(temp1) == 1 || stoi(temp1) == 2 || stoi(temp1) == 3 || stoi(temp1) == 4 || stoi(temp1) == 5) {
                userID += temp1;
                break;
            }
            else
                cout << "invalid number, try again: " << endl;

        }
        catch(const std::exception& e) {
            cout << "not a number, try again: " << endl;
        }

    }

    string temp2;
    cout << "Question 2: How would you rate your creativity?\n"
            "(1) Highly creative (I enjoy brainstorming, designing, and creating new things)\n"
            "(2) Moderately creative (I enjoy problem-solving and some level of creative freedom)\n"
            "(3) Neutral (I am fine with either routine or creative work)\n"
            "(4) Low creativity (I prefer structured tasks over creative ones\n)"
            "(please choose a number between 1-4) \n"
            "==========================================================" << endl;
    while (true) {
        cin >> temp2;
        try {
            if (stoi(temp2) == 1 || stoi(temp2) == 2 || stoi(temp2) == 3 || stoi(temp2) == 4) {
                userID += temp2;
                break;
            }
            else
                cout << "invalid number, try again: " << endl;

        }
        catch(const std::exception& e) {
            cout << "not a number, try again: " << endl;
        }

    }

    string temp3;
    cout << "Question 3: What type of tasks excite you the most?\n"
            "(1) Solving logical problems or working with numbers\n"
            "(2) Designing, drawing, or creating visual content\n"
            "(3) Leading teams or managing projects\n"
            "(4) Writing code or working with machines\n"
            "(5) Analyzing human behavior or studying social dynamics\n"
            "(please choose an answer between 1-5)\n"
            "==========================================================" << endl;
    while (true) {
        cin >> temp3;
        try {
            if (stoi(temp3) == 1 || stoi(temp3) == 2 || stoi(temp3) == 3 || stoi(temp3) == 4 || stoi(temp3) == 5) {
                userID += temp3;
                break;
            }
            else
                cout << "invalid number, try again: " << endl;

        }
        catch(const std::exception& e) {
            cout << "not a number, try again: " << endl;
        }

    }

    string temp4;
    cout << "Question 4: How would you describe your interpersonal skills?\n"
            "(1) Excellent (I enjoy collaborating and communicating with others)\n"
            "(2) Good (I enjoy working with people but also value independence)\n"
            "(3) Moderate (I am comfortable with minimal interaction)\n"
            "(4) Low (I prefer working on tasks independently)\n"
            "(please choose an answer between 1-4)\n"
            "==========================================================" << endl;
    while (true) {
        cin >> temp4;
        try {
            if (stoi(temp4) == 1 || stoi(temp4) == 2 || stoi(temp4) == 3 || stoi(temp4) == 4) {
                userID += temp4;
                break;
            }
            else
                cout << "invalid number, try again: " << endl;

        }
        catch(const std::exception& e) {
            cout << "not a number, try again: " << endl;
        }

    }

    string temp5;
    cout << "Question 5: Which of these career goals appeals to you the most?\n"
            "(1) Developing groundbreaking technology\n"
            "(2) Creating artistic works or entertainment\n"
            "(3) Building a successful business\n"
            "(4) Working in healthcare or improving lives\n"
            "(5) Understanding and solving social problems\n"
            "(please choose an answer between 1-5)\n"
            "==========================================================" << endl;
    while (true) {
        cin >> temp5;
        try {
            if (stoi(temp5) == 1 || stoi(temp5) == 2 || stoi(temp5) == 3 || stoi(temp5) == 4 || stoi(temp5) == 5) {
                userID += temp5;
                break;
            }
            else
                cout << "invalid number, try again: " << endl;

        }
        catch(const std::exception& e) {
            cout << "not a number, try again: " << endl;
        }

    }

    int new_id = stoi(userID);

    calculateMajorFromMaxHeap(new_id, max_students);
    calculateMajorFromMinHeap(new_id, min_students);
}

