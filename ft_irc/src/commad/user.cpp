#include <climits>
#include "../../includes/class_hpp/Server.hpp"
#include "../../includes/class_hpp/Client.hpp"
#include "../../includes/class_hpp/Channel.hpp"
#include "../../includes/class_hpp/Operation.hpp"
#include "../../includes/utils.hpp"

static void maybeCompleteRegistration(Client *client)
{
    if (!client->isRegistered() && client->isAuthenticated() && !client->getNickname().empty() && !client->getUsername().empty())
    {
        client->setRegistered(true);
        client->sendMessage(":server 001 " + client->getNickname() + " :Welcome");
    }
}

// USER username
void user(Client *client, Operation &operation, Server *server)
{
    (void)server;

    std::vector<std::string> param = operation.getParameter();

    // RFCでは4つのパラメータ (user host server :realname) を受け取る。
    // ここでは個数だけ確認し、内容はそのまま受け入れる。
    if (param.size() < 3)
    {
        client->sendMessage(":server 461 USER :Not enough parameters");
        return;
    }

    client->setUsername(param[0]);
    client->setHostname(param[1]);
    client->setServername(param[2]);
    client->setRealname(operation.getTrailing());
    maybeCompleteRegistration(client);
}
