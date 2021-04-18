#include "EnginePCH.h"

Bool LogCategoryBase::CheckActivate() const
{
    if (m_bActivation == true)
    {
        return true;
    }

    return false;
}
