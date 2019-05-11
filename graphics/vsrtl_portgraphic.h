#ifndef VSRTL_PORTGRAPHIC_H
#define VSRTL_PORTGRAPHIC_H

#include "eda/gridport.h"
#include "eda/vsrtl_placeroute.h"
#include "vsrtl_graphics_defines.h"
#include "vsrtl_graphicsbase.h"
#include "vsrtl_wiregraphic.h"

#include <QFont>
#include <QPen>

QT_FORWARD_DECLARE_CLASS(QPropertyAnimation)

namespace vsrtl {

class Port;

enum class PortType { in, out };

class PortGraphic : public GraphicsBase {
    Q_OBJECT
    Q_PROPERTY(QColor penColor MEMBER m_penColor)

public:
    PortGraphic(eda::GridPort& port, PortType type, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget*) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    void postSceneConstructionInitialize2() override;
    void updateGeometry();
    Port* getPort() { return m_gridPort.port(); }
    eda::GridPort& getGridPort() { return m_gridPort; }
    void setInputWire(WireGraphic* wire);
    void updateInputWire();
    void updateWireGeometry();

    void setNet(eda::NetPtr& net);

    QPointF getInputPoint() const;
    QPointF getOutputPoint() const;

    const QPen& getPen();

private slots:
    void updatePenColor();

private:
    void redraw();
    void propagateRedraw();
    void updatePen(bool aboutToBeSelected = false, bool aboutToBeDeselected = false);
    void updateSlot();

    // m_selected: does not indicate visual selection (ie. isSelected()), but rather whether any port in the port/wire
    // connection of this port has been selected.
    bool m_selected = false;
    bool m_showValue = false;
    ValueDisplayFormat m_valueBase = ValueDisplayFormat::baseTen;

    QRectF m_boundingRect;
    QRectF m_textRect;

    PortType m_type;
    eda::GridPort& m_gridPort;

    WireGraphic* m_outputWire = nullptr;
    WireGraphic* m_inputWire = nullptr;

    QPropertyAnimation* m_colorAnimation;

    QString m_widthText;
    QFont m_font;
    QPen m_pen;
    QColor m_penColor;
    QPen m_oldPen;  // Pen which was previously used for paint(). If a change between m_oldPen and m_pen is seen, this
                    // triggers redrawing of the connected wires
};

}  // namespace vsrtl

#endif  // VSRTL_PORTGRAPHIC_H
