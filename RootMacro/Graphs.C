#include <TFile.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFrame.h>
#include <TPaveText.h>
#include <TNtupleD.h>
#include <TLeafD.h>
#include <TLegend.h>
using namespace std;

void Graphs(){
    
    TFile* photon_z = new TFile("RootMacro/Photon_EMZ_10000.root", "READ");
    photon_z->cd();

    TH1D* spectrum_p_z = (TH1D*)gDirectory->Get("ShowerLongProfile");
    spectrum_p_z->Scale(100/(spectrum_p_z->Integral()));

    TNtupleD* ntuple_p_z = (TNtupleD*)gDirectory->Get("Detector");

    TFile* electron_z = new TFile("RootMacro/Electron_EMZ_10000.root", "READ");
    electron_z->cd();

    TH1D* spectrum_e_z = (TH1D*)gDirectory->Get("ShowerLongProfile");

    spectrum_e_z->Scale(100/(spectrum_e_z->Integral()));

    TNtupleD* ntuple_e_z = (TNtupleD*)gDirectory->Get("Detector");

    TFile* electron_v = new TFile("RootMacro/Electron_EMV_10000.root", "READ");
    electron_v->cd();

    TH1D* spectrum_e_v = (TH1D*)gDirectory->Get("ShowerLongProfile");

    spectrum_e_v->Scale(100/(spectrum_e_v->Integral()));

    TNtupleD* ntuple_e_v = (TNtupleD*)gDirectory->Get("Detector");

    TFile* electron_x = new TFile("RootMacro/Electron_EMX_10000.root", "READ");
    electron_x->cd();

    TH1D* spectrum_e_x = (TH1D*)gDirectory->Get("ShowerLongProfile");

    spectrum_e_x->Scale(100/(spectrum_e_x->Integral()));

    TNtupleD* ntuple_e_x = (TNtupleD*)gDirectory->Get("Detector");

    TFile* electron_y = new TFile("RootMacro/Electron_EMY_10000.root", "READ");
    electron_y->cd();

    TH1D* spectrum_e_y = (TH1D*)gDirectory->Get("ShowerLongProfile");

    spectrum_e_y->Scale(100/(spectrum_e_y->Integral()));

    TNtupleD* ntuple_e_y = (TNtupleD*)gDirectory->Get("Detector");

    gStyle->SetOptStat(kFALSE);
    gStyle->SetOptTitle(0);

    //--------- Depth spectrum -------------

    TCanvas* c1 = new TCanvas();
    c1->cd();

    spectrum_p_z->SetLineColor(kRed);
    spectrum_p_z->SetAxisRange(0., 6., "Y");
    spectrum_p_z->SetAxisRange(0., 40., "X");
    spectrum_p_z->SetXTitle("Depth [X_{0}]");
    spectrum_p_z->SetYTitle("Energy Deposit %");
    spectrum_p_z->SetTitle("30 GeV Photon");
    spectrum_p_z->Draw("Hist");

    spectrum_e_z->SetLineColor(kBlue);
    spectrum_e_z->SetTitleSize(0.5);
    spectrum_e_z->SetTitle("30 GeV Electron");
    spectrum_e_z->Draw("hist same");

    TPaveText *t = new TPaveText(0, 0.05, 0.3, 0, "blNDC");
    t->SetFillColor(kWhite);
    t->SetBorderSize(0);
    t->SetShadowColor(0);
    t->AddText("Shower Longitudinal Profile");
    t->Draw("");
    c1->BuildLegend();

    //----------- 5x0 fraction ------------
    
    TCanvas* c2 = new TCanvas();
    c2->cd();
    
    TH1D* h_p_5x0 = new TH1D("hp5x0", "hp5x0", 100, 0, 50);
    ntuple_p_z->Draw("EnergyDeposit5X0/300 >> hp5x0");
    h_p_5x0->SetLineColor(kRed);
    
    TH1D* h_e_5x0 = new TH1D("he5x0", "he5x0", 100, 0, 50);
    ntuple_e_z->Draw("EnergyDeposit5X0/300 >> he5x0");
    h_e_5x0->SetLineColor(kBlue);

    h_p_5x0->SetXTitle("% Fraction of Total Energy");
    h_p_5x0->SetYTitle("Counts");
    h_p_5x0->SetTitle("30 GeV Photon");
    h_p_5x0->Draw();

    h_e_5x0->SetTitle("30 GeV Electron");
    h_e_5x0->Draw("SAME");

    TPaveText *t2 = new TPaveText(0, 0.05, 0.3, 0, "blNDC");
    t2->SetFillColor(kWhite);
    t2->SetBorderSize(0);
    t2->SetShadowColor(0);
    t2->AddText("Energy Fraction Deposited in the First 5 X_{0}");
    t2->Draw("");

    c2->BuildLegend();

    //----------- Lateral containment ------------

    //----------- secondaries bar chart ----------

    TCanvas* c3 = new TCanvas();
    c3->cd();

    ROOT::RDataFrame* d_v = new ROOT::RDataFrame(*ntuple_e_v);
    ROOT::RDataFrame* d_x = new ROOT::RDataFrame(*ntuple_e_x);
    ROOT::RDataFrame* d_y = new ROOT::RDataFrame(*ntuple_e_y);
    ROOT::RDataFrame* d_z = new ROOT::RDataFrame(*ntuple_e_z);

    TH1D* h_s_v = new TH1D("sec v", "PhysList EMV", 3, 0, 3);
    TH1D* h_s_x = new TH1D("sec x", "PhysList EMX", 3, 0, 3); 
    TH1D* h_s_y = new TH1D("sec y", "PhysList EMY", 3, 0, 3); 
    TH1D* h_s_z = new TH1D("sec z", "PhysList EMZ", 3, 0, 3);  

    TString part_name[3] = {"Electron", "Positron", "Photon"};
    for (int i = 0; i < 3; i++){
        h_s_v->GetXaxis()->SetBinLabel(i+1,part_name[i]);
        h_s_v->Fill(part_name[i], d_v->Mean("N" + part_name[i]).GetValue());

        h_s_x->GetXaxis()->SetBinLabel(i+1,part_name[i]);
        h_s_x->Fill(part_name[i], d_x->Mean("N" + part_name[i]).GetValue());

        h_s_y->GetXaxis()->SetBinLabel(i+1,part_name[i]);
        h_s_y->Fill(part_name[i], d_y->Mean("N" + part_name[i]).GetValue());

        h_s_z->GetXaxis()->SetBinLabel(i+1,part_name[i]);
        h_s_z->Fill(part_name[i], d_z->Mean("N" + part_name[i]).GetValue());
    }

    h_s_v->SetAxisRange(0., 45000, "Y");
    h_s_v->SetYTitle("# of Secondary Particles");
    
    h_s_v->SetFillColor(kCoffee);
    h_s_v->SetBarWidth(0.20);
    h_s_v->SetBarOffset(0.1);
    h_s_v->Draw("hist bar");
    h_s_x->SetFillColor(kAzure);
    h_s_x->SetBarWidth(0.20);
    h_s_x->SetBarOffset(0.30);
    h_s_x->Draw("hist bar same");
    h_s_y->SetFillColor(kYellow);
    h_s_y->SetBarWidth(0.20);
    h_s_y->SetBarOffset(0.50);
    h_s_y->Draw("hist bar same");
    h_s_z->SetFillColor(kRed);
    h_s_z->SetBarWidth(0.20);
    h_s_z->SetBarOffset(0.70);
    h_s_z->Draw("hist bar same");

    TLegend *legend = new TLegend(0.55,0.65,0.76,0.82);
    legend->AddEntry(h_s_v,"PhysList EMV","f");
    legend->AddEntry(h_s_x,"PhysList EMX","f");
    legend->AddEntry(h_s_y,"PhysList EMY","f");
    legend->AddEntry(h_s_z,"PhysList EMZ","f");
    legend->Draw();

    TPaveText *t3 = new TPaveText(0, 0.05, 0.3, 0, "blNDC");
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetShadowColor(0);
    t3->AddText("Mean Number of Generated Secondaries");
    t3->Draw("");
    
    //----------- secondaries bar chart ----------

    ROOT::RDataFrame* d_p_z = new ROOT::RDataFrame(*ntuple_p_z);

    double ele_long = 17.40;
    double pho_long = 18.40;

    cout << "Photon long. containment " << spectrum_p_z->Integral(0., pho_long*2) << endl;
    cout << "Photon transv. containment " << d_p_z->Mean("EnergyDeposit4MolRad^2").GetValue()/300. << endl; 
    cout << "Electron long. containment " << spectrum_e_z->Integral(0., ele_long*2) << endl;
    cout << "Electron transv. containment " << d_z->Mean("EnergyDeposit4MolRad^2").GetValue()/300. << endl; 

    //----------- cointainment 5x0 comparison PhysList ----------

    TCanvas* c4 = new TCanvas();
    c4->cd();
    
    TH1D* h_e_5x0_v = new TH1D("he5x0v", "he5x0v", 100, 0, 50);
    ntuple_e_v->Draw("EnergyDeposit5X0/300 >> he5x0v");
    h_e_5x0_v->SetLineColor(kCoffee);

    TH1D* h_e_5x0_y = new TH1D("he5x0y", "he5x0y", 100, 0, 50);
    ntuple_e_y->Draw("EnergyDeposit5X0/300 >> he5x0y");
    h_e_5x0_y->SetLineColor(kYellow);

    TH1D* h_e_5x0_x = new TH1D("he5x0x", "he5x0x", 100, 0, 50);
    ntuple_e_x->Draw("EnergyDeposit5X0/300 >> he5x0x");
    h_e_5x0_x->SetLineColor(kAzure);

    h_e_5x0->SetLineColor(kRed);

    h_e_5x0->SetXTitle("% Fraction of Total Energy");
    h_e_5x0->SetYTitle("Counts");
    h_e_5x0->Draw();

    h_e_5x0_v->Draw("SAME");
    h_e_5x0_y->Draw("SAME");
    h_e_5x0_x->Draw("SAME");

    TPaveText *t4 = new TPaveText(0, 0.05, 0.3, 0, "blNDC");
    t4->SetFillColor(kWhite);
    t4->SetBorderSize(0);
    t4->SetShadowColor(0);
    t4->AddText("Energy Fraction Deposited in the First 5 X_{0}");
    t4->Draw("");

    TLegend *legend4 = new TLegend(0.55,0.65,0.76,0.82);
    legend4->AddEntry(h_e_5x0_v,"30 GeV Electron (EMV)","f");
    legend4->AddEntry(h_e_5x0_x,"30 GeV Electron (EMX)","f");
    legend4->AddEntry(h_e_5x0_y,"30 GeV Electron (EMY)","f");
    legend4->AddEntry(h_e_5x0,"30 GeV Electron (EMZ)","f");
    legend4->Draw();
}