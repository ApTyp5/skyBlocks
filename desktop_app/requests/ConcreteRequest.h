#ifndef DESKTOP_APP_CONCRETEREQUEST_H
#define DESKTOP_APP_CONCRETEREQUEST_H

class ConcreteRequest {
public:
    virtual ~ConcreteRequest() = default;

    virtual void GetRequestParams() = 0;
};

#endif //DESKTOP_APP_CONCRETEREQUEST_H
