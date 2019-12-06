//
// Created by arthur on 05.12.2019.
//

#include <string>
#include<iostream>
#include "Parser.h"
#include "Analyzer/AnalyzeFactoryType.h"
#include "Analyzer/AnalyzeFactoryCreator.h"
#include "Scheduler/SchedulerCreator.h"


/*
#include <vector>

template <typename T>
using pvector = std::vector<T*>;

class A{
public:
    virtual int doThis() const {
        return 5;
    }
};

class B: public A{
public:
    int doThis() const override {
        return 10;
    }
};

template <typename T>
void func(const pvector<T> &vec){
    std::cout << vec.size();
}


void func(const pvector<A> &vec){
    for (const auto &i : vec){
        std::cout << i->doThis();
    }
}


int main(){
    pvector<A> va;
    pvector<B> vb;
    for (int i = 0; i < 10; i++){
        va.push_back(new A);
        vb.push_back(new B);
    }

    func(va);
    func(vb);

    return 0;
}
*/




int main()
{
    std::string input = "some text, some text\n"
                        "moooore text\n"
                        "\n"
                        "ano block\n"
                        "of\n"
                        "text\n"
                        "\n"
                        "if some condition\n"
                        "   it is multiline condition\n"
                        "\tdo smth useless\n"
                        "else коммент\n"
                        "   while top text;bot text\n"
                        "\t\tinner block\n"
                        "   after while block\n"
                        "after if block\n"
                        "\n"
                        "bye-bye block";
/*    std::string input = "do smth\n"
                        "\n"
                        "do ano smth\n";*/


    Meta meta;
    DataBaseConnection db;
    Parser parser(db);
    std::string output = parser.parse(input, AnalyzeFactoryCreator::create(), SchedulerCreator::create(meta));
    std::cout << output;

    return 0;
}
