#ifndef __POLYSTEP_H__
#define __POLYSTEP_H__

#include <QtCore>

class PolyStep
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
  QPointF& point() { return m_point; }

protected:
  QPointF m_point; // (x, y)
};

#endif
