//==================================================================//
//                                                                  //
// Xinzhan Bai                                                      //
// 03/20/2016                                                       //
// xb4zp@virginia.edu                                               //
//==================================================================//

#ifndef __GEMRAWPEDESTAL_H__
#define __GEMRAWPEDESTAL_H__
#include <TString.h>
#include <map>
#include <unordered_map>
#include <vector>

class GEMMapping;
class GEMConfigure;

class GEMRawPedestal
{
public:
    GEMRawPedestal();
    GEMRawPedestal( std::unordered_map<int, std::vector<int> >);
    ~GEMRawPedestal();

    void ClearMap();
    void ClearSingleEvent();
    void ClearStripRMS();
    void ClearStripOffset();
    void ApvEventDecode();
    void ComputeApvPedestal(int);
    void ComputeEventPedestal();
    void ComputeEventPedestal(std::unordered_map<int, std::vector<int> >);
    void PrintEventPedestal(); // for debug
    float GetStripNoise(int apvindex, int channelID);
    float GetStripOffset(int apvindex, int channelID);
    int CheckApvTimeSample();
    void SetGEMConfigure(GEMConfigure *c);

private:
    float fApvHeaderLevel;
    int NCH;
    int fTimeSample;
    int fTimeSample_pedestal=0;

    int fAPVID;
    TString fAPVStatus;
    int fFECID;
    int fADCCh;

    GEMMapping* mapping;
    GEMConfigure * config;

    std::unordered_map<int, std::vector<int> > mSrsSingleEvent;
    std::vector<int> vSingleApvData;
    std::map<int, std::vector<float> > mStripOffset;
    std::map<int, std::vector<float> > mStripRMS;

    std::vector<float> vCommonModeOffset;
    std::vector<float> vCommonModeOffset_split;
    std::multimap<int, float> mApvTimeBinData;
};

#endif
