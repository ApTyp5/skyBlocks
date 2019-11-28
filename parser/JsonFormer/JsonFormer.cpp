//
// Created by arthur on 22.11.2019.
//

#include "JsonFormer.h"
#include "../Scheduler/Figure/FArrorw.h"

jsonString JsonFormer::formJson(ptrVector<AFigure> &figures)
{
    jsonString out;
    boost::property_tree::ptree tree;

    for (const auto &i : figures) {
        i->acceptJsonFormer(tree, *this);
    }

    boost::property_tree::write_json(out, tree);

    return out;
}

