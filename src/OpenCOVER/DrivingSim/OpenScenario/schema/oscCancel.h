/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl - 2.1.txt.

* License: LGPL 2 + */


#ifndef OSCCANCEL_H
#define OSCCANCEL_H

#include "../oscExport.h"
#include "../oscObjectBase.h"
#include "../oscObjectVariable.h"
#include "../oscObjectVariableArray.h"

#include "../oscVariables.h"
#include "oscConditionGroup.h"

namespace OpenScenario
{
class OPENSCENARIOEXPORT oscCancel : public oscObjectBase
{
public:
oscCancel()
{
        OSC_OBJECT_ADD_MEMBER(ConditionGroup, "oscConditionGroup", 0);
    };
        const char *getScope(){return "/OpenSCENARIO/Storyboard/Story/Act/ActConditions";};
    oscConditionGroupArrayMember ConditionGroup;

};

typedef oscObjectVariable<oscCancel *> oscCancelMember;
typedef oscObjectVariableArray<oscCancel *> oscCancelArrayMember;


}

#endif //OSCCANCEL_H
