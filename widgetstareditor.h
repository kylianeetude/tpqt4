#ifndef WIDGETSTAREDITOR_H
#define WIDGETSTAREDITOR_H

#include <QWidget>
#include "widgetstarrating.h"

// Classe de widget pour permettre l'édition des étoiles
class StarEditor : public QWidget
{
    Q_OBJECT
public:
    StarEditor(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    void setStarRating(const StarRating &starRating) {
        myStarRating = starRating;
    }
    StarRating starRating() const { return myStarRating; }

signals:
    void editingFinished();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int starAtPosition(int x) const; // Retourne l'index de l'étoile sous le curseur

    StarRating myStarRating;
};

#endif // WIDGETSTAREDITOR_H
