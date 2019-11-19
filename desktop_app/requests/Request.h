#ifndef DESKTOP_APP_REQUEST_H
#define DESKTOP_APP_REQUEST_H

#include "ConcreteRequest.h"

class Request {
public:
    Request() = default;
    ~Request() = default;

    void GetRequestParams();
    void SetRequest(ConcreteRequest *req);
private:
    ConcreteRequest *request;
};

#endif //DESKTOP_APP_REQUEST_H
