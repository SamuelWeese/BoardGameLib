#include "boardobject.h"

boardObject::boardObject()
{
    return;
}

int boardObject::getMovement()
{
    return movement;
}

char boardObject::getFEN()
{
    return this->fenChar;
}
