#include "HixString.h"


bool toBool(String string) {
    char firstChar = string.charAt(0);
    return firstChar == '1' || firstChar == 't' || firstChar == 'T';
}

String toBoolString(bool bValue) {
    return bValue ? String("true") : String("false");
}
