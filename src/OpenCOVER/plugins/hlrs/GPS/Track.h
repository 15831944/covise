/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

#ifndef _GPS_PLUGIN_TRACK_H
#define _GPS_PLUGIN_TRACK_H
/****************************************************************************\ 
 **                                                            (C)2008 HLRS  **
 **                                                                          **
 ** Description: GPS OpenCOVER Plugin (is polite)                            **
 **                                                                          **
 **                                                                          **
 ** Author: U.Woessner, T.Gudat		                                     **
 **                                                                          **
 ** History:  								     **
 ** June 2008  v1	    				       		     **
 **                                                                          **
 **                                                                          **
\****************************************************************************/
#include <cover/coVRPlugin.h>
#include <xercesc/dom/DOM.hpp>
#include <osg/Vec3>
#include <osg/Material>

using namespace opencover;
using namespace covise;
namespace opencover
{
class coVRLabel;
}

class GPSPoint;

//Single Track
class Track
{
public:
    Track();
    ~Track();
    void setIndex(int i);
    void addPoint(GPSPoint *p);
    void drawBirdView();
    void readFile(xercesc::DOMElement *node);
    void drawTrack();
    osg::ref_ptr<osg::Group> SingleTrack;
    std::list<GPSPoint*> TrackPoints;
    osg::Vec3Array *PointsCoVec;
    std::list<float> PointsSpeed;
    static osg::ref_ptr<osg::Material> globalDefaultMaterial;
};

#endif