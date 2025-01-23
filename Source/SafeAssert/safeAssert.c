#include "safeAssert.h"
#include "../Error/error.h"

int safeAssert(int condition, Token * token){
    if(!condition){
        freeTokens(token);
        printErrorMessage(5);
        return 0;
    }
    return 1;
}
