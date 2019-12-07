#include <pistache/endpoint.h>
#include "parser/Parser.h"
#include "parser/Analyzer/AnalyzeFactoryCreator.h"
#include "parser/Scheduler/SchedulerCreator.h"
#include "server/DataBaseConnection.h"
#include "server/JsonExtractor.h"


using namespace Pistache;

class SimpleHandler: public Http::Handler
{
public:
    SimpleHandler(): parser(db) {}

HTTP_PROTOTYPE(SimpleHandler)
    void onRequest(const Http::Request &request, Http::ResponseWriter writer) override
    {

        JsonExtractor extractor(request.body());
        Meta meta = extractor.extractMeta();
        std::string input = extractor.extractText();

        std::string output = parser.parse(input,
            AnalyzeFactoryCreator::create(),
            SchedulerCreator::create(meta));

        writer.send(Http::Code::Ok, output.data(), output.size());
    }
private:
    DataBaseConnection db;
    Parser parser;
};

int main()
{
    Http::listenAndServe<SimpleHandler>("*:9080");
}
