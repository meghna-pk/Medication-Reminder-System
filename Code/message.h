#include <mqueue.h>
#include <string>

class MessageQueue
{

    mqd_t queue;

public:
    MessageQueue(const std::string &queueName, int flags, mode_t mode, struct mq_attr *attr);

    bool Send(const std::string &message); // send message

    bool Receive(std::string &message); // receive message
};
