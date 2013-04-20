#ifndef __ODB_H__
#define __ODB_H__

#include <QtCore>
#include "toplevelhandler.h"
#include "odbfeaturefile.h"

class Odb
{
public:
  Odb(TopLevelHandler& h, QString& dst);
  void run();

private:
  // member functions
  void deleteOdbDir(const QString path); // path relative to odb root
  void createOdbDir(const QString path); // path relative to odb root
  void createFileSystem(); // Job->xxx
  void createMatrix(); // Job->matrix->matrix
  void createStepLayerDirs(); // (create dirs) Job->step->layers->xxx
  void createLayerFeature(); // Job->steps->xxx->layers->yyy->features
  // create all attrlists (job, step, layer)
  //   job   -- Job->misc->attrlist
  //   step  -- Job->steps->xxx->attrlist
  //   layer -- Job->steps->xxx->layers->yyy->attrlist
  void createAttrlists();
  void createJobAttribute();
  void createStepAttribute(QString stepName);
  void createLayerAttribute(QString stepName, QString layerName);

  // data members
  TopLevelHandler m_handler;
  QDir            m_dir;
  QString         m_odbRootPath;
  QList<QString>  m_allSteps;
  QList<QString>  m_allLayers;
};

#endif
