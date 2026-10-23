// read_file.cpp
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QList>
#include <QString>

#include <cstdlib>

#include "file_header.h"

int main(int argc, char *argv[])
{
  QFile file("temp.dat");
  if (!file.open(QIODevice::ReadOnly)){
    qDebug() << "Error: unable to open file for reading.";
    return EXIT_FAILURE;
  }

  QDataStream in(&file);

  // Read and check the header
  quint32 magic;
  in >> magic;
  if (magic != MAGIC){
    qDebug() << "Error: unexpected format.";
    return EXIT_FAILURE;
  }

  // Read the version
  qint32 version;
  in >> version;
  if(version != 1){
    qDebug() << "Error: unsupported file version.";
    return EXIT_FAILURE;
  }

  // use the same encoding format
  in.setVersion(QDataStream::Qt_5_0);

  // Read the data
  QList<QString> list;
  in >> list;

  qDebug() << "Read data from a file: ";
  for (const QString &msg : list) {
    qDebug() << "-" << msg;
  }

  return EXIT_SUCCESS;
}
