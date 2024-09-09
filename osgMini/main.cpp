#include <iostream>

#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

int main()
{
    // 创建Viewer
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

    // 组织Node树
    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("D:/02-Code/OpenSceneGraph/OpenSceneGraph-Data/cow.osg");
    root->addChild(node);
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root);

    // 设置场景数据
    viewer->setSceneData(root);

    // 初始化并创建窗口
    viewer->realize();

    // 渲染
    viewer->run();

    return 0;
}
