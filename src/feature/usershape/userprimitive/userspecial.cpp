#include "userspecial.h"
#include "featurefactory.h"

void
UserSpecial::initialize(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      Feature* f = FeatureFactory().create(xml.name());
      if (f == NULL) {
        errorInvalidAttribute("UserSpecial", "");
        exit(1);
      }
      f->initialize(xml);
      // append to the feature list
      m_features.append(f);
    }
    else if (isEndElementWithName(xml, "UserSpecial")) {
      break;
    }
  }
}
