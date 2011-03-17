/******************************************************************************
**
** Copyright (C) 2009-2011 Kyle Lutz <kyle.r.lutz@gmail.com>
**
** This file is part of chemkit. For more information see
** <http://www.chemkit.org>.
**
** chemkit is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** chemkit is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with chemkit. If not, see <http://www.gnu.org/licenses/>.
**
******************************************************************************/

#include "smifileformat.h"

// --- Construction and Destruction ---------------------------------------- //
SmiFileFormat::SmiFileFormat()
    : chemkit::ChemicalFileFormat("smi")
{

}

SmiFileFormat::~SmiFileFormat()
{
}

// --- Input/Output -------------------------------------------------------- //
bool SmiFileFormat::read(QIODevice *iodev, chemkit::ChemicalFile *file)
{
    iodev->setTextModeEnabled(true);

    chemkit::LineFormat *smilesFormat = chemkit::LineFormat::create("smiles");
    if(!smilesFormat){
        setErrorString("SMILES line format not supported.");
        return false;
    }

    while(!iodev->atEnd()){
        QString line = iodev->readLine().simplified();

        QStringList splitLine = line.split(' ', QString::SkipEmptyParts);
        if(splitLine.isEmpty()){
            continue;
        }

        QString smiles = splitLine[0];
        chemkit::Molecule *molecule = smilesFormat->read(smiles);
        if(!molecule){
            qDebug() << "Error with smiles: " << smiles;
            qDebug() << smilesFormat->errorString();
            continue;
        }

        if(splitLine.size() >= 2){
            QString name = line.mid(smiles.length()).trimmed();
            molecule->setName(name);
        }

        file->addMolecule(molecule);
    }

    delete smilesFormat;

    return true;
}

bool SmiFileFormat::write(const chemkit::ChemicalFile *file, QIODevice *iodev)
{
    iodev->setTextModeEnabled(true);

    chemkit::LineFormat *smilesFormat = chemkit::LineFormat::create("smiles");
    if(!smilesFormat){
        setErrorString("SMILES line format not supported.");
        return false;
    }

    foreach(const chemkit::Molecule *molecule, file->molecules()){
        QString smiles = smilesFormat->write(molecule);
        iodev->write(smiles.toAscii());

        if(!molecule->name().isEmpty()){
            iodev->write(" ");
            iodev->write(molecule->name().toAscii());
        }

        iodev->write("\n");
    }

    delete smilesFormat;

    return true;
}

