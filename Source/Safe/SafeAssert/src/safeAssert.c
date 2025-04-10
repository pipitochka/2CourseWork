#include "../include/safeAssert.h"

#include "../../Error/include/error.h"

int safeAssert(const int condition, Token * token){
    if (!condition){
        deleteTokens(token);
        printErrorMessage(5);
        return 0;
    }
    return 1;
}
