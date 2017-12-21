#include "LennardJones.hpp"

#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

#include "GridayException.hpp"

LennardJones::LennardJones(GReal eps, GReal sig, GReal rcut) :
    PairEnergy {},
    mEps {eps},
    mSig {sig},
    mSigSq {sig * sig},
    mRcut {rcut},
    mRcutSq {rcut * rcut}
    {

    }

void
LennardJones::setSimulationBox(const Cell& box)
    {
    mBox = box;
    mInvBox = inverse(box);
    }

GReal
LennardJones::calculate(const Vectors& r1, const Vectors& r2)
    {
    int size1 = r1.size();
    int size2 = r2.size();

    if (size1 == 0 || size2 == 0)
        return static_cast<GReal>(0.0);

    GReal zero = static_cast<GReal>(0.0001);

    bool cond1 = mEps  < zero;
    bool cond2 = mSig  < zero;
    bool cond3 = mRcut < zero;

    if (cond1 || cond2 || cond3)
        return static_cast<GReal>(0.0);

    GReal overlapDistSq = zero;
    GReal one = 1.0;
    GReal energy = 0.0;
    for (int i = 0; i < size1; ++i)
        {
        const Vector& ri = r1[i];

        for (int j = 0; j < size2; ++j)
            {
            const Vector& rj = r2[j];

            auto s = mInvBox * (ri - rj);

            for (auto& si : s)
                {
                if (si >  0.5)
                    si -= 1.0;
                if (si < -0.5)
                    si += 1.0;
                }

            auto r = mBox * s;
            auto rsq = r[0] * r[0] + r[1] * r[1] + r[2] * r[2];

            if (rsq < mRcutSq)
                {
                if (rsq < overlapDistSq)
                    return std::numeric_limits<GReal>::max();

                auto r2 = mSigSq / rsq;
                auto r6 = r2 * r2 * r2;

                energy += r6 * (r6 - one);
                }
            }
        }

    energy *= 4.0 * mEps;

    return energy;
    }

std::unique_ptr<PairEnergy>
LennardJones::clone()
    {
    return std::make_unique<LennardJones>(mEps, mSig, mRcut);
    }

void
LennardJones::print()
    {
    using namespace std;

    cout << "Pair Type: LennardJones, Parameter: " <<
                 setw(10) << "Eps = "  << setw(10) << mEps <<
                 setw(10) << "Sig = "  << setw(10) << mSig <<
                 setw(10) << "Rcut = " << setw(10) << mRcut <<
                 endl;
    }

std::string
LennardJones::getName()
    {
    return "LennardJones";
    }

GReal
LennardJones::getEps()
    {
    return mEps;
    }

GReal
LennardJones::getSig()
    {
    return mSig;
    }

GReal
LennardJones::getRcut()
    {
    return mRcut;
    }

template <>
PairEnergy::PairEnergyPtr
mixPairEnergy<LennardJones>(PairEnergy& e1, PairEnergy& e2)
    {
    LennardJones* p1 = nullptr;
    LennardJones* p2 = nullptr;

    p1 = dynamic_cast<LennardJones*>(&e1);
    p2 = dynamic_cast<LennardJones*>(&e2);

    if (p1 == nullptr or p2 == nullptr)
        THROW_EXCEPT("Invalid mixing occurs");

    double eps  = std::sqrt(p1->getEps() * p2->getEps());
    double sig  = 0.5 * (p1->getSig()  + p2->getSig());
    double rcut = 0.5 * (p1->getRcut() + p2->getRcut());

    return std::make_unique<LennardJones>(eps, sig, rcut);
    }
