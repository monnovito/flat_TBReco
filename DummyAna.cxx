#ifndef _DUMMYANA_C
#define _DUMMYANA_C

#include "TBReco/DummyAna.h"


  
/*Init method*/////////////////////////////////////////
void DummyAna::Init() //here place general initialization 
{
	
	 _fout= _tb_option->getOutputFile();



  _analysed_chamber_name1="P0_RM1"; 
  _analysed_chamber_name2="P2_M01";
  //_analysed_chamber_name3="P3_M01";
  //_analysed_chamber_name4="P4_M01";
  

  _analysed_chamber1=NULL;
  _analysed_chamber2=NULL;
  //_analysed_chamber3=NULL;
  //_analysed_chamber4=NULL;

  event_counter = 0;
  a = 0;
  
  
  for(unsigned int ich=0; ich<_chambers.size(); ich++)
    {
      MMChamber* chamb = _chambers[ich];
      TString chambName = chamb->getName();
      if(chambName == _analysed_chamber_name1) _analysed_chamber1=chamb;
      if(chambName == _analysed_chamber_name2) _analysed_chamber2=chamb;
      //if(chambName == _analysed_chamber_name3) _analysed_chamber3=chamb;
      //if(chambName == _analysed_chamber_name4) _analysed_chamber4=chamb;
  
    }
  
  if(_analysed_chamber1 == NULL || _analysed_chamber2 == NULL)
    {
      cout<<"ERROR IN AUTOEFFICIENCYANA: ONE OF THE ANALYSED CHAMBERS HAS NOT BEEN FOUND, OUTPUT WILL NOT BE WRITTEN"<<endl;
      return;
    }

  
  
  
  //_outdirname="AutoEfficiencyAna";
  //_fout->mkdir(_outdirname);
  
  mytree = new TTree("datatree", "datatree"); 
  mytree->SetDirectory(_fout);

  /* DICHIARAZIONE DEI BREANCH VARIABILI DA PRENDERE */
  mytree->Branch("__event__", &__event__,  "__event__/I");
  mytree->Branch("__layer__", &__layer__, "__layer__/I");
  mytree->Branch("__Xstrip__", &__Xstrip__, "__Xstrip__/D");
  mytree->Branch("__charge__", &__charge__, "__charge__/D");
  mytree->Branch("__time__", &__time__, "__time__/D");


}

/*Reset method*/////////////////////////////////////////
void DummyAna::Reset() //destructor method, deallocate everything here
{
	delete mytree;
	
}

/*Init_event method*/////////////////////////////////////////
void DummyAna::Init_event() //here place initialization needed in each event
{
  __event__ =0;
  __layer__=0;
  __Xstrip__=0;
  __charge__=0;
  __time__=0;
}

/*Execute_event method*/////////////////////////////////////////
void DummyAna::Execute_event() 
{

  if(_analysed_chamber1 == NULL || _analysed_chamber2 == NULL)
    {
      cout<<"ERROR IN AutoEfficiencyAna2su3: ONE OF THE ANALYSED CHAMBERS HAS NOT BEEN FOUND, RESOLUTION WILL BE NOT CALCULATED"<<endl;
      return;
    }

  //SM1
  vector<MMHit*> analysed_chamber1x_hits = _analysed_chamber1->SelectGoodStrips(_analysed_chamber1->getStrips());  //metti 0 se non funziona
  vector<MMHit*> analysed_chamber1y_hits = _analysed_chamber1->SelectGoodStrips(_analysed_chamber1->getStripsSecondCoord());
  vector<MMHit*> analysed_chamber2_hits = _analysed_chamber2->SelectGoodStrips(_analysed_chamber2->getStripsSecondCoord());
  //vector<MMHit*> analysed_chamber3_hits = _analysed_chamber3->SelectGoodStrips(_analysed_chamber3->getStrips());
  //vector<MMHit*> analysed_chamber4_hits = _analysed_chamber4->SelectGoodStrips(_analysed_chamber4->getStrips());


/*MODIFICARE BRANCH PER VARIABILI VOLUTE*/

 event_counter++;
  __event__ = event_counter;

cout<<endl<<endl<<endl;

/* CICLI DI LETTURA */
// i cicli seguenti prendono dalla classe hits le variabili che vogliamno.
// Attenzione: la variabile Layer è finta e indica la coppia (chamber,coordinata) (avendo tutte e due un solo layer):
// Layer 1: Camera 1 coordinata x
// Layer 2: Camera 1 coordinata y
// Layer 3: Camera 2 coordinata y


  __layer__ = 1;
  
  for (unsigned int i = 0; i < analysed_chamber1x_hits.size(); i++) {

	   __Xstrip__ = analysed_chamber1x_hits[i]->gX();
	   __charge__ = analysed_chamber1x_hits[i]->getCharge();
     __time__ = analysed_chamber1x_hits[i]->getTime();
     cout<<"Xstrip "<<__Xstrip__<<"charge "<<__charge__<<"time "<<__time__<<endl;
	    mytree->Fill();
	  }
  cout<<endl<<endl<<endl;

__layer__ = 2;

  for (unsigned int i = 0; i < analysed_chamber1y_hits.size(); i++) {

	   __Xstrip__ = analysed_chamber1y_hits[i]->gY();
	   __charge__ = analysed_chamber1y_hits[i]->getCharge();
     __time__ = analysed_chamber1y_hits[i]->getTime();
	    mytree->Fill();
	  }
  
__layer__ = 3;

  for (unsigned int i = 0; i < analysed_chamber2_hits.size(); i++) {
	    

	    __Xstrip__ = analysed_chamber2_hits[i]->gY();
	    __charge__= analysed_chamber2_hits[i]->getCharge();   
      __time__ = analysed_chamber2_hits[i]->getTime();
	    
	    
	    mytree->Fill();

	  }

}
/*Finalize method*/////////////////////////////////////////
void DummyAna::Finalize() //here place finalization after all events
{

  _fout->WriteTObject(mytree);

  /*
  TString rootfname("./raw_data.root");
  orootfile = new TFile(rootfname, "RECREATE");

  orootfile->WriteTObject(mytree);

  
  //mytree->Print();
  //mytree->Write(); 

  //delete mytree;    
  orootfile->Close();
  //delete orootfile;	
  */
}


#endif
