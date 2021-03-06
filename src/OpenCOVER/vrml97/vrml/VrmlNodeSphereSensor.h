/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

//
//  Vrml 97 library
//  Copyright (C) 1998 Chris Morley
//
//  %W% %G%
//  VrmlNodeSphereSensor.h

#ifndef _VRMLNODESPHERESENSOR_
#define _VRMLNODESPHERESENSOR_

#include "VrmlNode.h"
#include "VrmlSFBool.h"
#include "VrmlSFRotation.h"
#include "VrmlSFVec3f.h"

#include "VrmlNodeChild.h"

namespace vrml
{

class VRMLEXPORT VrmlScene;

class VRMLEXPORT VrmlNodeSphereSensor : public VrmlNodeChild
{

public:
    // Define the fields of SphereSensor nodes
    static VrmlNodeType *defineType(VrmlNodeType *t = 0);
    virtual VrmlNodeType *nodeType() const;

    VrmlNodeSphereSensor(VrmlScene *scene = 0);
    virtual ~VrmlNodeSphereSensor();

    virtual VrmlNode *cloneMe() const;

    virtual std::ostream &printFields(std::ostream &os, int indent);

    virtual VrmlNodeSphereSensor *toSphereSensor() const;

    virtual const VrmlField *getField(const char *fieldName) const;

    virtual void setField(const char *fieldName, const VrmlField &fieldValue);

    void activate(double timeStamp, bool isActive, double *p);

    bool isEnabled()
    {
        return d_enabled.get();
    }

private:
    // Fields
    VrmlSFBool d_autoOffset;
    VrmlSFBool d_enabled;
    VrmlSFRotation d_offset;

    VrmlSFBool d_isActive;
    VrmlSFRotation d_rotation;
    VrmlSFVec3f d_trackPoint;

    VrmlSFVec3f d_activationPoint;
    VrmlSFVec3f d_centerPoint;
};
}
#endif //_VRMLNODESPHERESENSOR_
