#pragma once

#include <string>

struct User {
    std::string username;
    std::string password;
    
    bool isLoggedIn = false;
};

struct Computer {
    int id;
    User *user;
    std::string name;
    int sort;    
};

struct Notification {
    int id;
    User *user;
    Computer *computer;
    std::string title;
    std::string message;
};

struct Progress {
    int id;
    User *user;
    Computer *computer;
    std::string title;
    int progress;
    int progress_max;
    std::string message;
};

enum TaskStatus {
    CREATED,
    STARTED,
    RUNNING,
    DONE
};
struct Task {
    int id;
    User *user;
    Computer *computer;
    std::string title;
    TaskStatus status;
    std::string message;    
};
