#include <iostream>
#include "message.h"
#include "reminder.h"
#include "client.h"
#include <cstring>
#include <thread>

void ReceiveReminders(const std::string &reminderQueueName)
{
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;

    MessageQueue reminderQueue(reminderQueueName, O_CREAT | O_RDONLY, 0666, &attr);
    while (true)
    {
        std::string reminderData;
        if (reminderQueue.Receive(reminderData))
        {
            std::cout << "Received reminder: " << reminderData << std::endl;
        }
    }
}

int main()
{
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;

    MessageQueue clientQueue("/server_queue", O_WRONLY, 0666, &attr);

    // Start a thread to receive reminders
    std::thread reminderThread(ReceiveReminders, "/reminder_queue");

    while (true)
    {
        User user;
        Client client;

        std::string username, password;

        std::cout << "Choose an option:\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Exit\n";
        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            client.registration();

            std::string ch = "Register";
            std::string userData = ch + " " + client.getUsername() + " " + client.getPassword();

            if (clientQueue.Send(userData))
            {
                std::cout << "Sent data to server: " << userData << std::endl;
            }

            // Open the message queue for receiving the registration message
            MessageQueue serverQueue("/client_queue", O_CREAT | O_RDONLY, 0666, &attr);
            std::string receivedMessage;
            if (serverQueue.Receive(receivedMessage))
            {
                std::cout << "Received registration message from server: " << receivedMessage << std::endl;
            }
        }
        else if (choice == 2)
        {
            client.login();

            std::string ch = "Login";
            std::string userData = ch + " " + client.getUsername() + " " + client.getPassword();

            if (clientQueue.Send(userData))
            {
                std::cout << "Sent data to server: " << userData << std::endl;
            }

            // Open the message queue for receiving the registration message
            MessageQueue serverQueue("/client_queue", O_CREAT | O_RDONLY, 0666, &attr);
            std::string receivedMessage;
            serverQueue.Receive(receivedMessage);
            std::cout << receivedMessage;

            if (receivedMessage.compare("Invalid Credentials\n") != 0)
            {

                int ch;
                std ::string choice;
                std ::cout << "Choose an option:\n";
                std ::cout << "1. Add Medication details\n";
                // std ::cout << "2. Edit Medication details\n";
                // std ::cout << "3. Remove Medication details\n";
                std ::cout << "2. Log out\n";

                std ::cin >> ch;

                switch (ch)
                {

                case 1:
                    int c;
                    do
                    {
                        choice = "add";
                        client.addMedicine();
                        std::string medicationData;
                        medicationData = choice + " " + client.getMedname() + " " + client.getDay() + " " + client.getQuantity() + " " + (client.getBefore() ? "1" : "0") + " " + client.getTime();

                        if (clientQueue.Send(medicationData))
                        {
                            std::cout << "Sent medication data to server: " << medicationData << std::endl;
                        }

                        MessageQueue serverQueue("/client_queue", O_CREAT | O_RDONLY, 0666, &attr);
                        std::string receivedMessage;
                        serverQueue.Receive(receivedMessage);
                        std::cout << receivedMessage;
                        std ::cout << "Do you want to add another medicine?(1/0)\n";
                        std ::cin >> c;

                    } while (c == 1);
                    if(c==0){
                        clientQueue.Send("exit");
                    }

                    break;

                case 2:
                    choice = "exit";
                    break;
                default:
                    std::cout << "Invalid Choice\n";
                }
            }
        }
        else if (choice == 3)
        {
            exit(0);
            break;
        }
        else
        {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    reminderThread.join(); // Wait for the reminder thread to finish

    return 0;
}