//
// Created by arthur on 27.11.2019.
//
#include "FContinue.h"

char FContinue::name[2] = "A";

size_t FContinue::counter = 0;

void FContinue::reset()
{
    *name = 'A';
    name[1] = 0;
    counter = 0;
}
