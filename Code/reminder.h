#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include <mqueue.h>

class Reminder
{

    std::string medName, id;
    int day, hour, minute, second;
    mqd_t reminderQueue;

public:
    Reminder(const std::string &id, const std::string &medName, int day, int hour, int minute, int second);
    void SetReminder();
    void SendReminder(const std::string &);
    
};
