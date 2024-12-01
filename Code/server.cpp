#include <iostream>
#include <cstring>
#include "medication.h"
#include "message.h"
#include "login.h"
#include "password_auth.h"
#include "reminder.h"

int main()
{

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;

    MessageQueue serverQueue("/server_queue", O_CREAT | O_RDONLY, 0666, &attr);

    // User *user;
    User *user = nullptr;

    while (1)
    {

        std::string msg;
        std::string receivedData;
        std::string username, password, choice;
        if (serverQueue.Receive(receivedData))
        {

            std::cout << "Received data from client: " << receivedData << std::endl;

            std::string receivedMessage(receivedData);

            size_t spacePos = receivedMessage.find(' ');

            if (spacePos != std::string::npos)
            {

                choice = receivedMessage.substr(0, spacePos); // extract choice

                size_t secondSpacePos = receivedMessage.find(' ', spacePos + 1); // Find the position of the next space

                if (secondSpacePos != std::string::npos)
                {

                    // Extract the username and password
                    username = receivedMessage.substr(spacePos + 1, secondSpacePos - spacePos - 1);
                    password = receivedMessage.substr(secondSpacePos + 1);
                }
            }
        }
        // Create a RegisterUser or LoggedInUser object based on choice
        if (choice == "Register")
        {

            if (user)
                delete user; // Clean up existing user object if any

            user = new RegisterUser(username, password);

            msg = user->Register();

            // Send status message back to the client
            mqd_t clientQueue = mq_open("/client_queue", O_WRONLY);

            if (clientQueue == (mqd_t)-1)
            {

                perror("mq_open client_queue");
            }
            else
            {

                if (mq_send(clientQueue, msg.c_str(), msg.length(), 1) == -1)
                {

                    perror("mq_send client_queue");
                }

                mq_close(clientQueue);

                mq_unlink("/client_queue");
            }
        }
        else if (choice == "Login")
        {

            if (user)
                delete user; // Clean up existing user object if any

            user = new LoggedInUser(username, password);

            msg = user->Login();

            // Send status message back to the client
            mqd_t clientQueue = mq_open("/client_queue", O_WRONLY);

            if (clientQueue == (mqd_t)-1)
            {

                perror("mq_open client_queue");
            }
            else
            {

                if (mq_send(clientQueue, msg.c_str(), msg.length(), 1) == -1)
                {

                    perror("mq_send client_queue");
                }

                mq_close(clientQueue);

                mq_unlink("/client_queue");
            }
            if (msg.compare("Invalid Credentials\n") != 0)
            {
                // Code for receiving medication data
                std::string medname, time, choice;
                int day, quantity;
                bool before;

                while (1)
                {
                    if (serverQueue.Receive(receivedData))
                    {

                        if(receivedData == "exit"){
                            break;
                        }
                        std::string receivedMedicationData(receivedData);

                        std::istringstream dataStream(receivedMedicationData);
                        if (dataStream >> choice >> medname >> day >> quantity >> before >> time)
                        {
                            if (choice == "exit")
                            {
                                break;
                            }
                            // Create a Medication object
                            std::cout << "Received medication data from client: " << receivedData << std::endl;

                            std::istringstream ss(time);
                            std::string token;
                            int hours, minutes, seconds = 0;

                            // Read hours (before ':')
                            if (std::getline(ss, token, ':'))
                            {
                                // Convert the token (string) to an integer
                                hours = std::stoi(token);
                            }

                            // Read minutes (after ':')
                            if (std::getline(ss, token))
                            {
                                // Convert the token (string) to an integer
                                minutes = std::stoi(token);
                            }

                            Reminder reminder(user->getId(), medname, day, hours, minutes, seconds);
                            reminder.SetReminder();
                            Medication *med;
                            if (before)
                            {
                                med = new Tablet(user->getId(), medname, day, quantity, true, time);
                                med->WriteToCSV("medication.csv");
                            }
                            else
                            {
                                med = new Tonic(user->getId(), medname, day, quantity, false, time);
                                med->WriteToCSV("medication.csv");
                            }
                        }
                        else
                        {
                            std::cout << "Failed to receive medication data." << std::endl;
                        }

                        clientQueue = mq_open("/client_queue", O_WRONLY);
                        if (clientQueue == (mqd_t)-1)
                        {
                            perror("mq_open client_queue");
                        }
                        else
                        {
                            msg = "Details added successfully\n";
                            if (mq_send(clientQueue, msg.c_str(), msg.length(), 1) == -1)
                            {
                                perror("mq_send client_queue");
                            }
                            mq_close(clientQueue);
                            mq_unlink("/client_queue");
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    if (user)
        delete user;

    return 0;
}