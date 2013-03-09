#include "linedesc.h"

void
LineDesc::initialize(QXmlStreamReader& xml)
{
  QString lineEnd = getAttribute(xml, "lineEnd");
  if (lineEnd == "ROUND") {
    m_lineEnd = LineDesc::ROUND;
  }
  else if (lineEnd == "SQUARE") {
    m_lineEnd = LineDesc::SQUARE;
  }
  else if (lineEnd == "NONE") {
    m_lineEnd = LineDesc::NONE;
  }
  else {
    errorInvalidAttribute("LineDesc", "lineEnd");
  }
  m_lineWidth = getNonNegativeDoubleAttribute(xml, "LineDesc", "lineWidth");
}
