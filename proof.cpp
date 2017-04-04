#include "proof.h"
#include <QFile>
#include <QDebug>

Proof::Proof(QString filename)
{
    qDebug() << "Attempting to open " << filename;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Couldn't open file!";
        exit(-1);
    }

    // The file stream we're going to read from
    QTextStream in(&file);

    // Version information
    QString versionLine = in.readLine();

    // Empty file check
    if (versionLine.isEmpty())
    {
        qDebug() << "Empty file!";
        exit(-1);
    }

    // No version included
    if (!versionLine.startsWith("V:"))
    {
        qDebug() << "No versioning info";
        exit(-1);
    }

    // Determine what version is found
    eggVersion = ((QString) versionLine.split("V:", QString::SkipEmptyParts).
                  first()).toDouble();

    qDebug() << "Version determined to be " << eggVersion;

    // Parse the rest of the file
    int linesRead = 0;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        ++linesRead;

        if (line.isEmpty())
            continue;

        qDebug() << "line is " << line;

        Line l(line);
        if (l.isWellFormed())
            lines.append(l);
    }

    qDebug() << "Out of" << linesRead << "lines read,"
             << lines.size() << "are well formed lines";
    for (Line l : lines)
        l.print();
}
