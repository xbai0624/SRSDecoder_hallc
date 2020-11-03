#include "GEMPhysics.h"
#include <iostream>
#include "GEMPedestal.h"
#include "GEMMapping.h"
#include "GEMOnlineHitDecoder.h"
#include "GEMSignalFitting.h"
#include <TCanvas.h>
#include "GEMTree.h"
#include "GEMCoord.h"

//#define PROD_GEM_OFFSET

using namespace std;

GEMPhysics::GEMPhysics()
{
    cout<<"GEMPhysics Constructor..."
        <<endl;
    mapping = GEMMapping::GetInstance();
}

GEMPhysics::~GEMPhysics()
{
}

void GEMPhysics::SetGEMPedestal(GEMPedestal *ped)
{
    pedestal = ped;
    pedestal -> LoadPedestal();

    hit_decoder = new GEMOnlineHitDecoder();
    hit_decoder -> SetPedestal(pedestal);

    sig_fitting = new GEMSignalFitting();
    sig_fitting->SetGEMOnlineHitDecoder(hit_decoder);

    gem_coord = new GEMCoord();
    gem_coord -> SetHitDecoder(hit_decoder);
}

void GEMPhysics::SetGEMConfigure(GEMConfigure *c)
{
    config = c;

    hit_decoder -> SetGEMConfigure(config);
}

void GEMPhysics::SetGEMTree(GEMTree *tree)
{
    rst_tree = tree;
}

void GEMPhysics::AccumulateEvent(int evtID, unordered_map<int, vector<int> > & event)
{
    //cout<<"event number from gem: "<<evtID<<endl;
    SetEvtID( evtID );
    hit_decoder -> ProcessEvent(event);
    CharactorizeGEM();
    CharactorizePhysics();

    sig_fitting -> Fit();
}

void GEMPhysics::CharactorizeGEM()
{
    int n = mapping->GetNbOfDetectors();

    vector<GEMClusterStruct> gem;
    for(int i=0;i<n;i++)
    {
	gem.clear();
	gem_coord->GetClusterGEM(i, gem);
	rst_tree -> PushDetector(i, gem);
    }
    rst_tree -> FillGEMTree();
}

void GEMPhysics::CharactorizePhysics()
{
    //#ifndef PROD_GEM_OFFSET
    CharactorizePlanePhysics();
    //#else
    CharactorizeOverlapPhysics();
    //#endif
}

void GEMPhysics::CharactorizePlanePhysics()
{
    gem_coord -> SetGEMOffsetX(0.);
    gem_coord -> SetGEMOffsetY(0.);

    // place holer
}

void GEMPhysics::CharactorizeOverlapPhysics()
{
    gem_coord -> SetGEMOffsetX(0.);
    gem_coord -> SetGEMOffsetY(0.);

    // place holer
}

void GEMPhysics::SavePhysResults()
{
    //rst_tree->WriteToDisk();
    sig_fitting->Write();
}

void GEMPhysics::SetEvtID(unsigned int id)
{
    evt_id = id;
}

unsigned int GEMPhysics::GetEvtID()
{
    return evt_id;
}

