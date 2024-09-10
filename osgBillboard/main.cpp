#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Billboard>
#include <osg/Texture2D>
#include <osg/Image>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

osg::ref_ptr<osg::Node> createBillboardTree(osg::ref_ptr<osg::Image> image)
{
    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
    v->push_back(osg::Vec3(-0.5f, 0.0f, -0.5f));
    v->push_back(osg::Vec3(0.5f, 0.0f, -0.5f));
    v->push_back(osg::Vec3(0.5f, 0.0f, 0.5f));
    v->push_back(osg::Vec3(-0.5f, 0.0f, 0.5f));

    geometry->setVertexArray(v);

    osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array();
    normal->push_back(osg::Vec3(1.0f, 0.0f, 0.0f) ^ osg::Vec3(0.0f, 0.0f, 1.0f));

    geometry->setNormalArray(normal.get());
    geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

    osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();
    vt->push_back(osg::Vec2(0.0f, 0.0f));
    vt->push_back(osg::Vec2(1.0f, 0.0f));
    vt->push_back(osg::Vec2(1.0f, 1.0f));
    vt->push_back(osg::Vec2(0.0f, 1.0f));

    geometry->setTexCoordArray(0, vt.get());

    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

    if (image)
    {
        osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();

        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
        texture->setImage(image.get());
        stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
        stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
        stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
        geometry->setStateSet(stateset.get());
    }

    osg::ref_ptr<osg::Billboard> billboard1 = new osg::Billboard();
    billboard1->setMode(osg::Billboard::POINT_ROT_EYE);
    billboard1->addDrawable(geometry.get(), osg::Vec3(5.0f, 0.0f, 0.0f));

    osg::ref_ptr<osg::Billboard> billboard2 = new osg::Billboard();
    billboard2->setMode(osg::Billboard::AXIAL_ROT);
    billboard2->setAxis(osg::Vec3(0.0f, 0.0f, 1.0f));
    billboard2->addDrawable(geometry.get(), osg::Vec3(10.0f, 0.0f, 0.0f));

    osg::ref_ptr<osg::Group> billboard = new osg::Group();
    // billboard->addChild(billboard1.get());
    billboard->addChild(billboard2.get());

    return billboard.get();
}

int main()
{
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

    osg::ref_ptr<osg::Group> root = new osg::Group();

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("D:/02-Code/OpenSceneGraph/OpenSceneGraph-Data/Images/tree0.rgba");

    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
    pat->setScale(osg::Vec3(5.0f, 5.0f, 5.0f));
    pat->addChild(createBillboardTree(image.get()));

    root->addChild(pat);

    root->addChild(osgDB::readNodeFile("D:/02-Code/OpenSceneGraph/OpenSceneGraph-Data/cow.osg"));

    osgUtil::Optimizer optimizer;
    optimizer.optimize(root);

    viewer->setSceneData(root);

    viewer->realize();

    viewer->run();

    return 0;
}
