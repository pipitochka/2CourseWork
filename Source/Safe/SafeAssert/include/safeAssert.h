#ifndef SAFEASSERT_H
#define SAFEASSERT_H

#include "../../../All/Token/include/token.h"

//function like assert in cassert but not stop program
int safeAssert(const int condition, Token * token);


#endif //SAFEASSERT_H
