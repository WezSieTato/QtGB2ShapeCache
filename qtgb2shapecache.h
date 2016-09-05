//
//  GB2ShapeCache.h
//
//  Loads physics sprites created with http://www.PhysicsEditor.de
//
//  Generic Shape Cache for box2d
//

#ifndef GB2SHAPECACHE_H
#define GB2SHAPECACHE_H

#include <Box2D.h>
#include <QString>
#include <QPoint>

class QtGB2ShapeCache
{
public:
    QtGB2ShapeCache();

    /**
     * Adds shapes to the shape cache
     * @param plist name of the plist file to load
     */
    void addShapeWithFile(QString plist);

    /**
     * Adds fixture data to a body
     * @param body body to add the fixture to
     * @param shapeName name of the shape
     */
    void addFixturesToBody(b2Body *body, QString shapeName);

    /**
     * Returns the anchor point of the given sprite
     * @param shapeName name of the shape to get the anchorpoint for
     * @return anchorpoint
     */
    QPoint anchorPointForShape(QString shapeName);
};

#endif // GB2SHAPECACHE_H
