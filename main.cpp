#include <pistache/endpoint.h>
#include "parser/Parser.h"
#include "parser/Analyzer/AnalyzeFactoryCreator.h"
#include "parser/Scheduler/SchedulerCreator.h"
#include "server/DataBaseConnection.h"
#include "server/JsonExtractor.h"

using namespace Pistache;

class SimpleHandler : public Http::Handler {
 public:
  SimpleHandler() : parser(db) {}

 HTTP_PROTOTYPE(SimpleHandler)
  void onRequest(const Http::Request &request, Http::ResponseWriter writer) override {
    AlphabetType language = PythonLike;
    JsonExtractor extractor(request.body());
    Meta meta = extractor.extractMeta();
    std::string input = extractor.extractText();
    std::string lang = extractor.extractLang();

    std::cout << "in:\n" << input;
    if (lang == "russian") {
      language = RuPseudoCode;
      meta.setSW(meta.sw() / 2);
    }

    std::string output = parser.parse(input,
                                      AnalyzeFactoryCreator::create(Indent, language),
                                      SchedulerCreator::create(meta));

    std::cout << "out:\n" << output;
    writer.send(Http::Code::Ok, output.data(), output.size());
  }
 private:
  DataBaseConnection db;
  Parser parser;
};

int main() {
  Http::listenAndServe<SimpleHandler>("*:6000");
}
