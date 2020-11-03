//==================================================================//
//                                                                  //
// Xinzhan Bai                                                      //
// 03/20/2016                                                       //
// xb4zp@virginia.edu                                               //
//==================================================================//

#ifndef GEMPHYSICS_H
#define GEMPHYSICS_H

#include <unordered_map>
#include <vector>
#include <fstream>
#include "datastruct.h"
#include "GEMDataStruct.h"

class GEMPedestal;
class GEMMapping;
class GEMOnlineHitDecoder;
class GEMTree;
class GEMCoord;
class GEMSignalFitting;
class GEMConfigure;

class GEMPhysics
{
public:
    GEMPhysics();
    ~GEMPhysics();
    void AccumulateEvent(int evtID, std::unordered_map<int, std::vector<int> > & event);
    void CharactorizeGEM();
    void CharactorizePhysics();
    void CharactorizePlanePhysics();
    void CharactorizeOverlapPhysics();
    void SavePhysResults();
    void SetGEMTree(GEMTree *);
    void SetGEMPedestal(GEMPedestal *ped);
    void SetGEMConfigure(GEMConfigure *c);
    void SetEvtID(unsigned int);
    unsigned int GetEvtID();

private:
    unsigned int evt_id;
    GEMPedestal *pedestal;
    GEMMapping * mapping;
    GEMOnlineHitDecoder * hit_decoder;
    GEMTree *rst_tree;
    GEMCoord *gem_coord;
    GEMConfigure *config;
    GEMSignalFitting *sig_fitting;
};

#endif
