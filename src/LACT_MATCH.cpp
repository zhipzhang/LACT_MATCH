#include "LHEvent.h"
#include "LACTree.h"
#include "Limits_defined.h"
#include <cstdlib>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include <ostream>
#include <string>

std::string prefix = " ";
#ifdef IHEP
prefix ="root://eos01.ihep.ac.cn/";
#endif




int main(int argc, char** argv)
{
    LHEvent* km2a_data = new LHEvent();
    LACTree* lact_data = new LACTree();
    std::cout << "Usage LACT_MATCH LACT_ROOT KM2A_ROOT DSTROOT (Be Careful Default reuse is 20)" << std::endl;

    std::string lact_file = prefix + argv[1];
    TFile* lact_root = TFile::Open(lact_file.c_str(), "read");
    TTree* lact_event = (TTree*) lact_root->Get("event");
    TTree* detector_tree = (TTree *)lact_root->Get("config_tree");
    lact_data->initEventTree(lact_event);


    std::string km2a_file = prefix + argv[2];
    TFile* km2a_root = TFile::Open(km2a_file.c_str(), "read");
    TTree* km2a_event = (TTree*) km2a_root->Get("event");
    km2a_event->SetBranchAddress("Event",&km2a_data);


    std::string out_file = prefix + argv[3];
    TFile* out_root  = TFile::Open(out_file.c_str(), "recreate");
    TTree* out_tree  = new TTree(); 
    TTree* config_tree = detector_tree->CloneTree();
    out_tree->SetName("match_events");
    out_tree->SetTitle("match_events");
    out_tree->Branch("km2a_events", &km2a_data);
    lact_data->initMatchTree(out_tree);

    if( lact_event->GetEntries() != km2a_event->GetEntries())
    {
        std::cout << "The Entries of KM2A and LACT are not Same" << std::endl;
        exit(EXIT_FAILURE);
    }
    int n = (lact_event->GetEntries() + 1 ) / 20;
    std:: cout << " n is " << n << std::endl;
    for( int i = 0; i < lact_event->GetEntries(); i++)
    {
        lact_event->GetEntry(i);
        int divide = i  / 20;
        int residual = i  % 20;
        int k = (residual ) * n  + divide;
        km2a_event->GetEntry(k );
        if( (km2a_data->GetE()/1000 - lact_data->energy) > 0.01 || (km2a_data->GetCorex() - lact_data->xcore) > 0.001 ||(km2a_data->GetCorey() - lact_data->ycore) > 0.001)
        {
            std::cout << " Not Match in Entry " << i << std::endl;
        }
        else 
        {
            out_tree->Fill();
        }
    }

    out_tree->Write();
    config_tree->Write();
    out_root->Close() ;



}