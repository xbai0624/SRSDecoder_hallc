//==================================================================//
//                                                                  //
// Xinzhan Bai                                                      //
// 03/20/2016                                                       //
// xb4zp@virginia.edu                                               //
//==================================================================//

#ifndef GEMTREE_H
#define GEMTREE_H
#include "GEMDataStruct.h"
#include <vector>
#include <unordered_map>
#include <cstring>
#include "datastruct.h"
#include <unordered_map>

#define NDETECTOR 4

class TTree;
class TFile;
class TH1F;
class GEMConfigure;

class GEMTree
{
    // ------------------------------- common setting --------------------------------------
public:
    GEMTree();
    ~GEMTree();
    void WriteToDisk();
    void SetGEMConfigure(GEMConfigure *con);

private:
    TFile *file;
    GEMConfigure *configure;

    // for all trees
    unsigned int evt_id;


    // ------------------------------- gem tree -------------------------------------
public:
    void PushData(std::vector<GEMClusterStruct> & gem1,
	    std::vector<GEMClusterStruct> &gem2,
	    std::unordered_multimap<std::string, double> &tdc_map);

    void PushDetector(int, std::vector<GEMClusterStruct>);
    void PushTDCValue(std::unordered_multimap<std::string, double> &tdc_map);

    void FillGEMTree();
    void InitGEMTree(int ndet);
    void InitTDCGroup();

private:
    TTree *gem_tree;

    bool empty_gem_event;
    // number of hits on each detector
    const int static _nhits = 500; // if _nhits is not large enough, it will become a potential break threat
    std::string scin_group[2];
    int hycal_group_q;
    std::string hycal_group[9];

    // max 4 detectors
    int nhits[NDETECTOR] = {0, 0, 0, 0};
    float x[NDETECTOR][_nhits];
    float y[NDETECTOR][_nhits];
    float x_charge[NDETECTOR][_nhits];
    float y_charge[NDETECTOR][_nhits];
    float energy[NDETECTOR][_nhits];
    float z[NDETECTOR][_nhits];
    float x_size[NDETECTOR][_nhits];
    float y_size[NDETECTOR][_nhits];

    // tdc information
    int n_S2;
    int n_S1;
    int n_hycal;
    float TDCS2[_nhits];
    float TDCS1[_nhits];
    float TDCHyCal[_nhits];

    // ------------------------------- epics tree -------------------------------------
public:
    void PushEpics(std::unordered_map<std::string, double> &);
    void FillEpicsTree();
    void InitEpicsTree();
    void SetEventID(unsigned int &id);

private:
    TTree *epics_tree;
    bool empty_epics_event;
    EpicsStruct _epics_tree;
    int event_id;

};

#endif
