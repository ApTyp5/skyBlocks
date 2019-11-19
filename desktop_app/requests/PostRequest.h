#ifndef DESKTOP_APP_POSTREQUEST_H
#define DESKTOP_APP_POSTREQUEST_H

#include "ConcreteRequest.h"

class PostRequest : public ConcreteRequest {
public:
    PostRequest() = default;
    ~PostRequest() = default;

    void GetRequestParams() override;
};

#endif //DESKTOP_APP_POSTREQUEST_H
