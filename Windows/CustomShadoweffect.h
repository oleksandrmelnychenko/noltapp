#ifndef CUSTOMSHADOWEFFECT_H
#define CUSTOMSHADOWEFFECT_H

#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>


class CustomShadowEffect : public QGraphicsEffect
{
    Q_OBJECT
    public:
        explicit CustomShadowEffect(QObject *parent = 0);

        void draw(QPainter* painter);
        QRectF boundingRectFor(const QRectF& rect) const;

        void setDistance(qreal distance) { mDistance = distance; updateBoundingRect(); }
        qreal distance() const { return mDistance; }

        void setBlurRadius(qreal blurRadius) { mBlurRadius = blurRadius; updateBoundingRect(); }
        qreal blurRadius() const { return mBlurRadius; }

        void setColor(const QColor& color) { mColor = color; }
        QColor color() const { return mColor; }

    private:
        qreal  mDistance;
        qreal  mBlurRadius;
        QColor mColor;
};

#endif // CUSTOMSHADOWEFFECT_H
