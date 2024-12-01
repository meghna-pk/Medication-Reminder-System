#include "message.h"

MessageQueue::MessageQueue(const std::string &queueName, int flags, mode_t mode, struct mq_attr *attr)
{

    queue = mq_open(queueName.c_str(), flags, mode, attr);

    if (queue == (mqd_t)-1)
    {

        perror("mq_open");

        exit(1);
    }
}

// function to send message
bool MessageQueue::Send(const std::string &message)
{

    if (mq_send(queue, message.c_str(), message.length(), 1) == -1)
    {

        perror("mq_send");

        return false;
    }

    return true;
}

// function to receive message
bool MessageQueue::Receive(std::string &message)
{

    char receivedData[1024];

    ssize_t receivedBytes = mq_receive(queue, receivedData, sizeof(receivedData), nullptr);

    if (receivedBytes == -1)
    {

        perror("mq_receive");

        return false;
    }

    receivedData[receivedBytes] = '\0';

    message = receivedData;

    return true;
}