#ifndef DESKTOP_APP_GETREQUEST_H
#define DESKTOP_APP_GETREQUEST_H

#include "ConcreteRequest.h"

class GetRequest: public ConcreteRequest {
public:
    GetRequest() = default;
    ~GetRequest() = default;

    void GetRequestParams() override ;
};

#endif //DESKTOP_APP_GETREQUEST_H
