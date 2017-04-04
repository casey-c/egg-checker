#ifndef PROOF_H
#define PROOF_H

#include <QString>
#include "line.h"

/*
 * A Proof is a collection of Line objects. It takes in a filename and parses
 * that file. It reads it line by line, creating Line objects as needed, and
 * checks if the transition between lines is valid.
 */
class Proof
{
public:
    Proof(QString filename);

private:
    double eggVersion;
    QList<Line> lines;
};

#endif // PROOF_H
