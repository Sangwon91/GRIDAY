#pragma once

#include <string>
#include <array>
#include <vector>

#include "GridayTypes.hpp"
#include "GridayException.hpp"
#include "Vector.hpp"
#include "Cell.hpp"

class EnergyGrid
    {
public:
    EnergyGrid();
    EnergyGrid(std::string filename);

    void read(std::string filename);
    void print();
    void writeVisitInput(std::string fileStem, bool onlyInUnitCell = true);
    void writeVolumetricImage(std::string filename,
                              GIndex size,
                              bool fillBox = false);
    void writeEnergyHistogram(std::string filename,
                              const GReal bin,
                              const GReal max);

    GReal at(GIndex nx, GIndex ny, GIndex nz);
    GReal at(const GIndex3& n);

    GReal operator () (GIndex nx, GIndex ny, GIndex nz);
    GReal operator () (const GIndex3& n);
    //GReal periodicAt(GIndex nx, GIndex ny, GIndex nz);
    GReal interpolate(GReal x, GReal y, GReal z);
    GReal interpolate(const Vector& r);

    GReal interpolate3d(const Vector& r);
    GReal interpolate3d(GReal x, GReal y, GReal z);

    Vector getCellLengths();
    Vector getCellAngles();
    Vector getCellHeights();

    GIndex getMaxNx();
    GIndex getMaxNy();
    GIndex getMaxNz();
    GIndex getNumGrids();

    Cell getCell();
    Cell getContainingBox();
    GReal getVolume();
    GReal getMinimumEnergy();
    GIndex3 getMinimumEnergyIndex3();
    GReal getInaccessibleRangeRatio(GReal inf);
    std::vector<GIndex3> getLocalMinimumIndices(GReal maxEnergy);
    Vectors getLocalMinimumPositions(GReal maxEnergy);

    void transformToProbability(GReal temper);
    void transformToInverse();
    void transformToLog();
    void transformToPartialMap();
    void transformToMinus();

    const std::vector<GReal>& data();

    GReal henry(GReal temperature);
private:
    void makeCellInformation();
private:
    std::vector<GReal> mGrid;

    Vector mCellLengths;
    Vector mCellAngles;
    Vector mCellHeights;

    GIndex mMaxNx;
    GIndex mMaxNy;
    GIndex mMaxNz;

    GIndex mNumGrids;

    Cell mCell;
    Cell mInvCell;
    GReal mVolume;

    GReal mMinimumEnergy;
    GIndex3 mMinimumEnergyIndex3;

    // Test variables
    };
