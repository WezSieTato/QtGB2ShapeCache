#include "gb2shapecache.h"

#include "gb2helper.h"

#include <QVariantMap>
#include <QtGlobal>
#include <plistparser.h>

GB2ShapeCache &GB2ShapeCache::getSharedShapeCache()
{
    static GB2ShapeCache instance;
    return instance;
}

void GB2ShapeCache::addShapeWithFile(QIODevice *plist)
{
    QVariantMap map = PListParser::parsePList(plist).toMap();

    QVariantMap metadataMap = map["metadata"].toMap();
    int format = metadataMap["format"].toInt();
    _ptmRatio = metadataMap["ptm_ratio"].toFloat();

    Q_ASSERT(format == 1);

    QVariantMap bodyMap = map["bodies"].toMap();

    b2Vec2 vertices[b2_maxPolygonVertices];

    for (QString bodyName : bodyMap.keys())
    {
        // get the body data
        QVariantMap bodyData = bodyMap[bodyName].toMap();

        // create body object
        BodyDef bodyDef;

        bodyDef.anchorPoint = GB2Helper::pointFromString(bodyMap["anchorpoint"].toString());

        // iterate through the fixtures
        QVariantList fixtureList = bodyData["fixtures"].toList();

        for (QVariant fixtureDataVariant : fixtureList)
        {
            QVariantMap fixtureData = fixtureDataVariant.toMap();

            b2FixtureDef basicData;
            basicData.filter.categoryBits = fixtureData["filter_categoryBits"].toInt();
            basicData.filter.maskBits = fixtureData["filter_maskBits"].toInt();
            basicData.filter.groupIndex = fixtureData["filter_groupIndex"].toInt();
            basicData.friction = fixtureData["friction"].toFloat();
            basicData.density = fixtureData["density"].toFloat();
            basicData.restitution = fixtureData["restitution"].toFloat();
            basicData.isSensor = fixtureData["isSensor"].toBool();
            int callbackData = fixtureData["userdataCbValue"].toInt();

            QString fixtureType = fixtureData["fixture_type"].toString();

            if(fixtureType == "POLYGON")
            {
                QVariantList polygonsArray = fixtureData["polygons"].toList();

                for(QVariant polygonArrayVariant : polygonsArray)
                {
                    QVariantList polygonArray = polygonArrayVariant.toList();
                    FixtureDef fix;
                    fix.fixture = basicData;
                    fix.callbackData = callbackData;

                    b2PolygonShape *polyshape = new b2PolygonShape();
                    int vindex = 0;

                    Q_ASSERT(polygonArray.count() <= b2_maxPolygonVertices);
                    for(QVariant pointStringVariant : polygonArray)
                    {
                        QString pointString = pointStringVariant.toString();
                        QPointF offset = GB2Helper::pointFromString(pointString);
                        vertices[vindex].x = offset.x() / _ptmRatio;
                        vertices[vindex].y = offset.y() / _ptmRatio;
                        vindex++;
                    }

                    polyshape->Set(vertices, vindex);
                    fix.fixture.shape = polyshape;

                    bodyDef.fixtures.append(fix);
                }
            }
            else if(fixtureType == "CIRCLE")
            {
                FixtureDef fix;
                fix.fixture = basicData;
                fix.callbackData = callbackData;

                QVariantMap circleData = fixtureData["circle"].toMap();

                b2CircleShape *circleShape = new b2CircleShape();
                circleShape->m_radius = circleData["radius"].toFloat() / _ptmRatio;
                QPointF p = GB2Helper::pointFromString(fixtureData["center"].toString());
                circleShape->m_p = b2Vec2(p.x() / _ptmRatio, p.y() / _ptmRatio);
                fix.fixture.shape = circleShape;

                bodyDef.fixtures.append(fix);
            }
            else
            {
                // unknow type
                Q_ASSERT(0);
            }
        }

        // add the body element to the hash
       _shapeObjects[bodyName] = bodyDef;
    }
}

void GB2ShapeCache::addFixturesToBody(b2Body *body, const QString &shapeName)
{
    BodyDef so = _shapeObjects[shapeName];

    for (FixtureDef fix : so.fixtures)
    {
        body->CreateFixture(&fix.fixture);
    }
}

QPointF GB2ShapeCache::anchorPointForShape(const QString &shapeName) const
{
    BodyDef bd = _shapeObjects[shapeName];
    return bd.anchorPoint;
}

float GB2ShapeCache::ptmRatio() const
{
    return _ptmRatio;
}
