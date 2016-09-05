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
#include <QMap>
#include <QIODevice>

/**
 * Internal class to hold the fixtures
 */
struct FixtureDef
{
    ~FixtureDef()
    {
        delete fixture.shape;
    }

    b2FixtureDef fixture;
    int callbackData;
};

struct BodyDef
{
    QList<FixtureDef> fixtures;
    QPointF anchorPoint;
};

class QtGB2ShapeCache : QObject
{
public:
    QtGB2ShapeCache(QObject *parent=Q_NULLPTR);

    /**
     * Adds shapes to the shape cache
     * @param plist name of the plist file to load
     */
    void addShapeWithFile(QIODevice *plist);

    /**
     * Adds fixture data to a body
     * @param body body to add the fixture to
     * @param shapeName name of the shape
     */
    void addFixturesToBody(b2Body *body, const QString &shapeName);

    /**
     * Returns the anchor point of the given sprite
     * @param shapeName name of the shape to get the anchorpoint for
     * @return anchorpoint
     */
    QPointF anchorPointForShape(const QString &shapeName) const;

    float ptmRatio() const;

private:
    float _ptmRatio;
    QMap<QString, BodyDef> _shapeObjects;

};

#endif // GB2SHAPECACHE_H
