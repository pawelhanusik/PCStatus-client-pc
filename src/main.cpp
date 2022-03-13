#include <iostream>

#include "config.h"
#include "Client.h"
#include "Logger.h"

using namespace std;

int main() {
    CurlSender sender;
    Client client(sender);
    return 0;
}
