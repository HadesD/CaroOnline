#include <QStyleOption>
#include <QPainter>
#include <QStyle>

#include "GbButton.hpp"

GbButton::GbButton(QWidget *parent) : QPushButton(parent)
{
}

common::Point2D GbButton::getPoint() const
{
  return m_point;
}

void GbButton::setPoint(const common::Point2D &p)
{
  m_point = p;
}
