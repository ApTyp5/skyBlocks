#ifndef DESKTOP_APP_CONNECTOR_H
#define DESKTOP_APP_CONNECTOR_H

#include "requests/Request.h"

class Connector {
public:
    ~Connector() = default;

    static Connector &GetConnector();

    void SendRequest(Request *request);

    Connector(const Connector &con) = delete;
    Connector &operator=(const Connector &con) = delete;
private:
    Connector() = default;
};

#endif //DESKTOP_APP_CONNECTOR_H
