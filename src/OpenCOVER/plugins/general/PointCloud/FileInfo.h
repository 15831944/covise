#ifndef POINTCLOUD_FILEINFO_H
#define POINTCLOUD_FILEINFO_H

#include <osg/ref_ptr>
#include <osg/Node>
#include <string>
#include <vector>

struct PointSet;

class NodeInfo
{
public:
    osg::ref_ptr<osg::Geode> node;
};

class FileInfo
{
public:
    std::string filename;
    std::vector<NodeInfo> nodes;
    int pointSetSize;
    PointSet *pointSet;
	osg::Matrixd Rotation;
	osg::Matrixd Translation;
};

#endif
