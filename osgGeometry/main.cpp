#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ref_ptr>
#include <osgDB/Registry>
#include <osgDB/WriteFile>
#include <osg/Notify>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <iostream>

osg::ref_ptr<osg::Node> createSceneGraph()
{
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

    // set vetex
    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
    geom->setVertexArray(v.get());
    v->push_back(osg::Vec3(-1.f, 0.f, -1.f));
    v->push_back(osg::Vec3(1.f, 0.f, -1.f));
    v->push_back(osg::Vec3(1.f, 0.f, 1.f));
    v->push_back(osg::Vec3(-1.f, 0.f, 1.f));

    // set color
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
    geom->setColorArray(c.get());
    geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
    c->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
    c->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));

    // set normal
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
    geom->setNormalArray(n.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    n->push_back(osg::Vec3(0.f, -1.f, 0.f));

    // draw polygon
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

    // add geometry to geode
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geom.get());

    return geode.get();
}

int main(int argc, const char *argv[])
{
    osg::ref_ptr<osg::Group> root = new osg::Group();
    root->addChild(createSceneGraph());

    osgViewer::Viewer viewer;
    viewer.addEventHandler(new osgViewer::StatsHandler);
    viewer.setSceneData(root);
    viewer.realize();
    viewer.run();

    return 0;
}
