void compareMCData(TString suffix="hTowersHadEt_barrel"){
  
  TFile*f_MC=new TFile("fileMC.root");
  TFile*f_MC_5TeV=new TFile("fileMC_5TeV.root");
  TFile*f_Data=new TFile("fileData.root");
  TH1F*histo_MC=(TH1F*)f_MC->Get(suffix.Data());
  TH1F*histo_MC_5TeV=(TH1F*)f_MC_5TeV->Get(suffix.Data());
  TH1F*histo_Data=(TH1F*)f_Data->Get(suffix.Data());
  

  if(!(histo_MC_5TeV->GetEntries()==0)) histo_MC_5TeV->Scale(1./histo_MC_5TeV->GetEntries());
  if(!(histo_MC->GetEntries()==0)) histo_MC->Scale(1./histo_MC->GetEntries());
  if(!(histo_Data->GetEntries()==0)) histo_Data->Scale(1./histo_Data->GetEntries());

  TCanvas* canvas=new TCanvas("canvas","Distribution",600,500);  
  canvas->cd();
  canvas->SetLogy();
  
  histo_Data->GetXaxis()->SetTitle("towerEt");
  histo_Data->GetXaxis()->SetTitle("entries");
  histo_Data->GetXaxis()->SetTitleOffset(1.);
  histo_Data->GetYaxis()->SetTitleOffset(1.15);
  histo_Data->GetXaxis()->SetTitleSize(0.045);
  histo_Data->GetYaxis()->SetTitleSize(0.045);
  histo_Data->GetXaxis()->SetTitleFont(42);
  histo_Data->GetYaxis()->SetTitleFont(42);
  histo_Data->GetXaxis()->SetLabelFont(42);
  histo_Data->GetYaxis()->SetLabelFont(42);
  histo_Data->GetXaxis()->SetLabelSize(0.032);
  histo_Data->GetYaxis()->SetLabelSize(0.032);  
  histo_Data->SetMinimum(0.0001);
  histo_Data->SetMaximum(1);
  histo_Data->SetLineColor(1);
  histo_Data->SetMarkerColor(1);
  histo_Data->SetLineWidth(3);
  histo_Data->Draw();
  
  histo_MC->SetLineColor(2); 
  histo_MC->SetLineWidth(3);
  histo_MC->Draw("same");
  
  histo_MC_5TeV->SetLineColor(4); 
  histo_MC_5TeV->SetLineWidth(3);
  histo_MC_5TeV->Draw("same");
  
  TLegend* leg= new TLegend(0.57,0.68,0.87,0.88);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  TLegendEntry* ent;

  ent=leg->AddEntry(histo_Data,"DATA","L");
  ent=leg->AddEntry(histo_MC,"MC","L");
  ent=leg->AddEntry(histo_MC_5TeV,"MC 5 TeV","L");
  leg->Draw();
  
  canvas->SaveAs(Form("PlotsRecHit/%s.pdf",suffix.Data()));
  
  

}