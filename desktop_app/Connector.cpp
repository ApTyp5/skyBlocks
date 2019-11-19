#include "Connector.h"

Connector &Connector::GetConnector() {
    static Connector instance;
    return instance;
}

void Connector::SendRequest(Request *request) {
    request->GetRequestParams();
}
