#include "pad.h"
#include "standardshapefactory.h"
#include "error.h"
#include "globals.h"
#include "layer.h"

void
Pad::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_xform = NULL;
  m_pinRef = NULL;
  m_standardShape = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Xform") {
        m_xform = new Xform();
        m_xform->initialize(xml);
      }
      else if (xml.name() == "Location") {
        m_location = QPointF(
            toInch(getDoubleAttribute(xml, "Location", "x"), units),
            toInch(getDoubleAttribute(xml, "Location", "y"), units));
      }
      else if (isSubstitutionGroupStandardShape(xml.name())) {
        m_standardShape = StandardShapeFactory().create(xml.name());
        m_standardShape->initialize(xml, units);
      }
      else if (xml.name() == "PinRef") {
        m_pinRef = new PinRef();
        m_pinRef->initialize(xml);
      }
    }
    else if (isEndElementWithName(xml, "Pad")) { // </Pad>
      if (m_standardShape == NULL) {
        throw new InvalidElementError("Pad::StandardShape");
      }
      return;
    }
  }
}

void
Pad::odbOutputLayerFeature(
    OdbFeatureFile& file, QString layerName, QString polarity)
{
  // if the shape is a reference, find it in the list
  QString refId = m_standardShape->refId();
  StandardShape *s;
  if (refId == "") {
    s = m_standardShape;
  }
  else if (g_entryStandards.contains(refId)) {
    s = g_entryStandards[refId];
  }
  else {
    throw new InvalidIdError(refId);
  }

  // find the layer by name
  int layerIdx;
  for (int i = 0; i < g_layers.size(); ++i) {
    if (g_layers[i].name() == layerName) {
      layerIdx = i;
      break;
    }
  }

#if 0
  // Because sometimes in IPC-2581 the symbol is defined
  // in TOP but the Component's layer is BOTTOM, so need to find
  // the Component's layer to output.
  // 1. For component in TOP/BOTTOM, need to check where exactly to output
  //    (for TOP/BOTTOM, layerFunction == CONDUCTOR)
  // 2. For component in other layer (soldermask, etc), just output
  Layer& layer = g_layers[layerIdx];
  if (m_pinRef != NULL && layer.layerFunction() == Layer::CONDUCTOR) {
    // find the component by name "refDes"
    QString compName = m_pinRef->componentRef();
    for (int i = 0; i < g_components.size(); ++i) {
      if (g_components[i].refDes() == compName) {
        QString layerName = g_components[i].layerRef();
        // draw feature in TOP/BOTTOM layer: 'f' (not the passed-in 'file')
        OdbFeatureFile& f = g_layerFeatureFiles[layerName];
        s->odbOutputLayerFeature(f, polarity, m_location, m_xform);
        f.featuresList().append("\n");
        break;
      }
    }
  }
  else {
#endif
  // call the shape to output
  s->odbOutputLayerFeature(file, polarity, m_location, m_xform);
  file.featuresList().append("\n");
}
