#include "reminder.h"
#include "message.h"
#include <iomanip>

Reminder::Reminder(const std::string &id, const std::string &medName, int day, int hour, int minute, int second)
    : id(id), medName(medName), day(day), hour(hour), minute(minute), second(second) {}

void Reminder::SetReminder()
{
    std::cout << "Inside Set Reminder\n";

    auto medNameCopy = medName;

    // Calculate the reminder time using chrono and local time
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert the current time to a tm struct to get the current hour and minute
    std::tm current_tm = *std::localtime(&now_time_t);
    int currentHour = current_tm.tm_hour;
    int currentMinute = current_tm.tm_min;

    // Calculate the remaining time until the specified time
    int hoursRemaining = hour - currentHour;
    int minutesRemaining = minute - currentMinute;

    if (hoursRemaining < 0 || (hoursRemaining == 0 && minutesRemaining < 0))
    {
        // If the specified time is in the past, add a day to the reminder
        hoursRemaining += 24;
    }

    auto reminderTime = now + std::chrono::hours(hoursRemaining) + std::chrono::minutes(minutesRemaining);

    // Create a thread to continuously check for the reminder time
    std::thread([medNameCopy, this, reminderTime]()
                {
        while (true)
        {
            auto currentTime = std::chrono::system_clock::now();
            if (currentTime >= reminderTime)
            {
                SendReminder(medNameCopy);
                break;
            }
        }
    }).detach();
}


void Reminder::SendReminder(const std::string &medName)
{
    reminderQueue = mq_open("/reminder_queue", O_WRONLY);
    if (reminderQueue == (mqd_t)-1)
    {
        perror("mq_open ");
    }

    std::string reminderMessage = medName + " - It's time to take your medication.";

    mq_send(reminderQueue, reminderMessage.c_str(), reminderMessage.length(), 1);
}
