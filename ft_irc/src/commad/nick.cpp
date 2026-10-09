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

// NICK parameter

void nick(Client *client, Operation &operation, Server *server)
{
    (void)server;

    std::vector<std::string> param = operation.getParameter();

    // disallow mult parameter or no parameters
    if (param.size() != 1)
    {
        client->sendMessage(":server.example.com 432 * :Erroneous nickname");
        std::cout << "nickname too params\n";
        return;
    }

    std::string newNickname = param[0];

    // check Nickname
    if (!isValidName(newNickname, "-_[]\\`^{}", 9))
    {
        client->sendMessage(":server.example.com 432 * :Erroneous nickname");
        std::cout << "nickname invlaid char\n";
        return;
    }

    client->setNickname(operation.getParameter()[0]);
    maybeCompleteRegistration(client);
    std::cout << "set new nickname\n";
}
