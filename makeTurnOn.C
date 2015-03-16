#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TString.h>
#include <TLegendEntry.h>
#include <TGraphAsymmErrors.h>
#include <TMath.h>

#include <vector>
#include <iostream>


void makeTurnOn(int optionData=true,bool is5TeV=false)
{ 

  TString inL1FileName;
  if(!optionData && !is5TeV)inL1FileName="../FilesForL1JetTrigger/HiForest_164_1_s7a.root";
  if(!optionData && is5TeV)inL1FileName="../FilesForL1JetTrigger/HiForest_190_2_lPA_5TeV.root";
  if(optionData)inL1FileName="../FilesForL1JetTrigger/0.root";
  TFile *fFile = TFile::Open(inL1FileName);
  TTree *fTree = (TTree*)fFile->Get("akPu3CaloJetAnalyzer/t");
  TTree *fEvtTree = (TTree*)fFile->Get("hiEvtAnalyzer/HiTree");
  TTree *fRecHit = (TTree*)fFile->Get("rechitanalyzer/tower");
  //TTree *fRecHit = (TTree*)fFile->Get("pfTowers/tower");
  fTree->AddFriend(fEvtTree);
  fTree->AddFriend(fRecHit);
  
  TTree *fSkimTree = (TTree*)fFile->Get("skimanalysis/HltTree");
  fTree->AddFriend(fSkimTree);

  
  Int_t f_evt, f_run, f_lumi, hiBin, f_n;
  Float_t f_eta[5000], f_phi[5000], f_et[5000],f_hadEt[5000],f_emEt[5000];


  fTree->SetBranchAddress("evt",&f_evt);
  fTree->SetBranchAddress("run",&f_run);
  fTree->SetBranchAddress("lumi",&f_lumi);
  fTree->SetBranchAddress("hiBin",&hiBin);
  
  fTree->SetBranchAddress("eta",&f_eta);
  fTree->SetBranchAddress("phi",&f_phi);
  fTree->SetBranchAddress("et",&f_et);
  fTree->SetBranchAddress("hadEt",&f_hadEt);
  fTree->SetBranchAddress("emEt",&f_emEt);
  fTree->SetBranchAddress("n",&f_n);
  
  Int_t pcollisionEventSelection, pHBHENoiseFilter;

  if (!is5TeV) fTree->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection);
  fTree->SetBranchAddress("pHBHENoiseFilter",&pHBHENoiseFilter);


  

  TH1F*hTowersHadEt_barrel=new TH1F("hTowersHadEt_barrel","hTowersHadEt_barrel",100,0,20);
  TH1F*hTowersHadEt_endcap=new TH1F("hTowersHadEt_endcap","hTowersHadEt_endcap",100,0,20);
  TH1F*hTowersHadEt_HF=new TH1F("hTowersHadEt_HF","hTowersHadEt_HF",100,0,20);

  TH1F*hTowersEmEt_barrel=new TH1F("hTowersEmEt_barrel","hTowersEmEt_barrel",100,0,20);
  TH1F*hTowersEmEt_endcap=new TH1F("hTowersEmEt_endcap","hTowersEmEt_endcap",100,0,20);
  TH1F*hTowersEmEt_HF=new TH1F("hTowersEmEt_HF","hTowersEmEt_HF",100,0,20);


  int entries = fTree->GetEntries();
  bool isHF=false;
  bool isendcap=false;
  bool isbarrel=false;
  
    
  for(long j = 0; j < entries; ++j){
    fTree->GetEntry(j);
    
      for(long int l = 0; l < f_n; l++){  
      
        isbarrel=(f_eta[l] > -1.479 && f_eta[l] < 1.479);
        isHF= (f_eta[l]<-3.0 || f_eta[l]>3.0 );
        isendcap= (f_eta[l]>-3.0 && f_eta[l]<-1.479) || (f_eta[l]>1.479 && f_eta[l]<3);
      
        if (optionData && pcollisionEventSelection==0) continue;
        if (optionData && pHBHENoiseFilter ==0) continue;
            
         if(f_hadEt[l]>0 && isbarrel){ hTowersHadEt_barrel->Fill(f_hadEt[l]);}
         if(f_hadEt[l]>0 && isHF) hTowersHadEt_HF->Fill(f_hadEt[l]);
         if(f_hadEt[l]>0 && isendcap) hTowersHadEt_endcap->Fill(f_hadEt[l]);

         if(f_emEt[l]>0 && isbarrel){ hTowersEmEt_barrel->Fill(f_emEt[l]);}
         if(f_emEt[l]>0 && isHF) hTowersEmEt_HF->Fill(f_emEt[l]);
         if(f_emEt[l]>0 && isendcap) hTowersEmEt_endcap->Fill(f_emEt[l]);
      }
  }


  TString fout;

  if(!optionData && !is5TeV) fout="fileMC.root";
  if(!optionData && is5TeV) fout="fileMC_5TeV.root";
  if(optionData) fout="fileData.root";

  TFile *foutfile=new TFile(fout.Data(),"recreate");
  foutfile->ls();
  
  hTowersHadEt_barrel->Write();
  hTowersHadEt_endcap->Write();
  hTowersHadEt_HF->Write();

  hTowersEmEt_barrel->Write();
  hTowersEmEt_endcap->Write();
  hTowersEmEt_HF->Write();
  
  foutfile->Close();
  
}
