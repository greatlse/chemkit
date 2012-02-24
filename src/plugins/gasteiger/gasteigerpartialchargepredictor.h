/******************************************************************************
**
** Copyright (C) 2009-2011 Kyle Lutz <kyle.r.lutz@gmail.com>
** All rights reserved.
**
** This file is a part of the chemkit project. For more information
** see <http://www.chemkit.org>.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in the
**     documentation and/or other materials provided with the distribution.
**   * Neither the name of the chemkit project nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/

#ifndef GASTEIGERPARTIALCHARGEPREDICTOR_H
#define GASTEIGERPARTIALCHARGEPREDICTOR_H

#include <chemkit/partialchargepredictor.h>

struct GasteigerParameters {
    chemkit::Real a;
    chemkit::Real b;
    chemkit::Real c;
};

class GasteigerPartialChargePredictor : public chemkit::PartialChargePredictor
{
public:
    // construction and destruction
    GasteigerPartialChargePredictor();
    ~GasteigerPartialChargePredictor();

    // partial charges
    chemkit::Real partialCharge(const chemkit::Atom *atom) const;

protected:
    void assignPartialCharges(const chemkit::Molecule *molecule);

private:
    const GasteigerParameters* atomParameters(const chemkit::Atom *atom) const;

private:
    std::vector<chemkit::Real> m_charges;
    std::vector<chemkit::Real> m_electronegativies;
    std::vector<const GasteigerParameters *> m_parameters;
};

#endif // GASTEIGERPARTIALCHARGEPREDICTOR_H
