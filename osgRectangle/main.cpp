#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ref_ptr>
#include <osgDB/Registry>
#include <osgDB/WriteFile>
#include <osg/Notify>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/CompositeViewer>
#include <osgGA/MultiTouchTrackballManipulator>

#include <iostream>

osg::ref_ptr<osg::Node> createSceneGraph()
{
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

    double x1 = -50;
    double x2 = 50;
    double y1 = -50;
    double y2 = 50;
    double z1 = -50;
    double z2 = 50;

    // set vertex
    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
    geom->setVertexArray(v.get());
    v->push_back(osg::Vec3(x1, y1, z1));
    v->push_back(osg::Vec3(x1, y1, z2));
    v->push_back(osg::Vec3(x1, y2, z2));
    v->push_back(osg::Vec3(x1, y2, z1));

    v->push_back(osg::Vec3(x1, y1, z1));
    v->push_back(osg::Vec3(x1, y2, z1));
    v->push_back(osg::Vec3(x2, y2, z1));
    v->push_back(osg::Vec3(x2, y1, z1));

    v->push_back(osg::Vec3(x2, y1, z1));
    v->push_back(osg::Vec3(x2, y1, z2));
    v->push_back(osg::Vec3(x2, y2, z2));
    v->push_back(osg::Vec3(x2, y2, z1));

    v->push_back(osg::Vec3(x1, y1, z2));
    v->push_back(osg::Vec3(x1, y2, z2));
    v->push_back(osg::Vec3(x2, y2, z2));
    v->push_back(osg::Vec3(x2, y1, z2));

    v->push_back(osg::Vec3(x1, y1, z1));
    v->push_back(osg::Vec3(x1, y1, z2));
    v->push_back(osg::Vec3(x2, y1, z2));
    v->push_back(osg::Vec3(x2, y1, z1));

    v->push_back(osg::Vec3(x1, y2, z1));
    v->push_back(osg::Vec3(x1, y2, z2));
    v->push_back(osg::Vec3(x2, y2, z2));
    v->push_back(osg::Vec3(x2, y2, z1));

    // set color
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
    geom->setColorArray(c, osg::Array::Binding::BIND_OVERALL);
    c->push_back(osg::Vec4(0.5, 0.5, 0.5, 1.0));

    // set normal
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
    geom->setNormalArray(n.get(), osg::Array::Binding::BIND_PER_VERTEX);
    n->push_back(osg::Vec3(-1.0f, 0.0f, 0.0f));
    n->push_back(osg::Vec3(-1.0f, 0.0f, 0.0f));
    n->push_back(osg::Vec3(-1.0f, 0.0f, 0.0f));
    n->push_back(osg::Vec3(-1.0f, 0.0f, 0.0f));
    
    n->push_back(osg::Vec3(0.0f, 0.0f, -1.0f));
    n->push_back(osg::Vec3(0.0f, 0.0f, -1.0f));
    n->push_back(osg::Vec3(0.0f, 0.0f, -1.0f));
    n->push_back(osg::Vec3(0.0f, 0.0f, -1.0f));
    
    n->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
    n->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
    n->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
    n->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
    
    n->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
    n->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
    n->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
    n->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
    
    n->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
    n->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
    n->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
    n->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
    
    n->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
    n->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
    n->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
    n->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));

    // draw polygon
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, v->size()));

    // add geometry to geode
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geom.get());

    return geode.get();
}

int main(int argc, const char *argv[])
{
    osg::ref_ptr<osg::Group> root = new osg::Group();
    root->addChild(createSceneGraph());

    osgViewer::CompositeViewer* viewer = new osgViewer::CompositeViewer;

    auto view = new osgViewer::View;
    viewer->addView(view);

    auto camera = view->getCamera();

    camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );

    // Set up window size and position
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->x = 100; // Window position x
    traits->y = 100; // Window position y
    traits->width = 800; // Window width
    traits->height = 600; // Window height
    traits->windowDecoration = true; // Enable window decoration
    traits->doubleBuffer = true;
    traits->samples = 4; // Anti-aliasing

    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
    camera->setGraphicsContext(gc.get());
    camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));

    view->setSceneData( root );
    view->addEventHandler( new osgViewer::StatsHandler );

    auto manipulator = new osgGA::MultiTouchTrackballManipulator;
    manipulator->setAllowThrow( false );
    view->setCameraManipulator( manipulator );

    viewer->realize();
    viewer->run();

    return 0;
}
