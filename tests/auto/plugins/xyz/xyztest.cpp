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

#include "xyztest.h"

#include <algorithm>

#include <chemkit/molecule.h>
#include <chemkit/moleculefile.h>
#include <chemkit/moleculefileformat.h>

const std::string dataPath = "../../../data/";

void XyzTest::initTestCase()
{
    std::vector<std::string> formats = chemkit::MoleculeFileFormat::formats();
    QVERIFY(std::find(formats.begin(), formats.end(), "xyz") != formats.end());
}

void XyzTest::read_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QString>("formula");

    QTest::newRow("methane") << "methane.xyz" << "CH4";
    QTest::newRow("benzene") << "benzene.xyz" << "C6H6";
}

void XyzTest::read()
{
    QFETCH(QString, fileName);
    QFETCH(QString, formula);

    chemkit::MoleculeFile file(dataPath + fileName.toStdString());
    bool ok = file.read();
    if(!ok)
        qDebug() << file.errorString().c_str();
    QVERIFY(ok);

    QCOMPARE(file.moleculeCount(), 1);
    chemkit::Molecule *molecule = file.molecule();
    QVERIFY(molecule != 0);
    QCOMPARE(molecule->formula(), formula.toStdString());
}

QTEST_APPLESS_MAIN(XyzTest)
