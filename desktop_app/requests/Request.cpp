#include "Request.h"

void Request::GetRequestParams() {
    request->GetRequestParams();
}

void Request::SetRequest(ConcreteRequest *req) {
    request = req;
}
