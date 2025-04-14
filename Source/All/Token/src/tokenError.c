#include "../include/tokenError.h"
#include "../../../Safe/Error/include/error.h"

//function for tests
//print error message and deallocate memory
void tokenError(Token *token, int x){
    printErrorMessage(x);
    deleteTokens(token);
}
