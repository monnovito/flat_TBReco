#ifndef _DUMMYANA_H
#define _DUMMYANA_H

#include "TBReco/DummyBaseAna.h"
#include <map>
#include "TH1F.h"
#include "TEfficiency.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TBReco/MMChamber.h"
#include "TBReco/TBReader.h"


class DummyAna : public DummyBaseAna
{
	public:
	 DummyAna(vector<MMChamber*> &in_ch, TBReader* reader_in, TBOption* opt_in, TString run_name = "dummy_run") : DummyBaseAna(in_ch,reader_in,opt_in,run_name) {};
	 ~DummyAna(){this->Reset();};
	
  void Init();
  void Init_event() ;
  void Execute_event();
  void Finalize();
  void Reset();

 private:

  TString _analysed_chamber_name1;
  MMChamber* _analysed_chamber1;
  TString _analysed_chamber_name2;
  MMChamber* _analysed_chamber2;
  TString _analysed_chamber_name3;
  MMChamber* _analysed_chamber3;
  TString _analysed_chamber_name4;
  MMChamber* _analysed_chamber4;


  TFile *_fout;
  TString _outdirname;
  
  TFile* orootfile;
  TTree* mytree;
  
  int event_counter;
  int a;
  int __event__ ;
  int __layer__;
  double __Xstrip__;
  double __charge__;
  double __time__;
   	 

 

};

#endif
