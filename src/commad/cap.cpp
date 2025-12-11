#include "../../includes/class_hpp/Server.hpp"
#include "../../includes/class_hpp/Client.hpp"
#include "../../includes/class_hpp/Operation.hpp"

// Minimal CAP handler: respond with empty LS so clients proceed
void cap(Client *client, Operation &operation, Server *server)
{
    (void)server;
    const std::vector<std::string> &params = operation.getParameter();
    if (!params.empty() && params[0] == "LS")
    {
        client->sendMessage(":server CAP * LS :");
        return;
    }
    if (!params.empty() && params[0] == "END")
        return;
    client->sendMessage(":server CAP * LS :");
}
