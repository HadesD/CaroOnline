#ifndef GBBUTTON_HPP
#define GBBUTTON_HPP

#include <QPushButton>

#include "../Common/Point2D.hpp"

class GbButton : public QPushButton
{
    Q_OBJECT
  public:
    explicit GbButton(QWidget *parent = nullptr);

  public:
    void paintEvent(QPaintEvent *);

  signals:

  public slots:

  public:
    common::Point2D getPoint() const;
    void setPoint(const common::Point2D &p);

  private:
    common::Point2D m_point;
};

#endif // GBBUTTON_HPP
