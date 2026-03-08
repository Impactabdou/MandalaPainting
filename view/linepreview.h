#ifndef LINEPREVIEW_H
#define LINEPREVIEW_H

#include <QFrame>
#include <QColor>
#include <QPaintEvent>

class LinePreview : public QFrame {
    Q_OBJECT
public:
    explicit LinePreview(QWidget* parent = nullptr);

    void setPenColor(const QColor& color);
    void setPenWidth(int width);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QColor _color = Qt::black;
    int _width = 3;
};

#endif // LINEPREVIEW_H
