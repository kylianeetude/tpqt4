#ifndef WIDGETSTARRATING_H
#define WIDGETSTARRATING_H

#include <QPainter>
#include <QPolygonF>
#include <QSize>

// Classe de gestion des étoiles
class StarRating
{
public:
    enum class EditMode { Editable, ReadOnly };

    explicit StarRating(int starCount = 1, int maxStarCount = 5);

    void paint(QPainter *painter, const QRect &rect,
               const QPalette &palette, EditMode mode) const;
    QSize sizeHint() const;
    int starCount() const { return myStarCount; }
    int maxStarCount() const { return myMaxStarCount; }
    void setStarCount(int starCount) { myStarCount = starCount; }
    void setMaxStarCount(int maxStarCount) { myMaxStarCount = maxStarCount; }

private:
    QPolygonF starPolygon;
    int myStarCount;
    int myMaxStarCount;

    void initStarPolygon(); // Initialise la forme de l'étoile
};

Q_DECLARE_METATYPE(StarRating)

#endif // WIDGETSTARRATING_H
