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
        std::wstring str(request.body().begin(), request.body().end());
        std::wcout << str;
        JsonExtractor extractor(str);
        Meta meta = extractor.extractMeta();
        std::wstring input = extractor.extractText();

        std::wstring output = parser.parse(input,
                                           AnalyzeFactoryCreator::create(Indent, PythonLike),
                                           SchedulerCreator::create(meta));
        std::string out(output.begin(), output.end());
        std::cout << out << std::endl;
        writer.send(Http::Code::Ok, out.data(), out.size());
    }
private:
    DataBaseConnection db;
    Parser parser;
};

int main()
{
    Http::listenAndServe<SimpleHandler>("*:6000");
}
