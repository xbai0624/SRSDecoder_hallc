#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TTree.h>

void draw()
{
    const int _n = 1000;

    float x[_n], y[_n], xcharge[_n], ycharge[_n];
    float xsize[_n], ysize[_n];

    int n;

    TFile *f = new TFile("res.root");
    TTree * T = (TTree*)f->Get("T");

    T->SetBranchAddress("nhits0", &n);
    T->SetBranchAddress("x0", &x);
    T->SetBranchAddress("y0", &y);
    T->SetBranchAddress("x0_charge", &xcharge);
    T->SetBranchAddress("y0_charge", &ycharge);
    T->SetBranchAddress("x0_size", &xsize);
    T->SetBranchAddress("y0_size", &ysize);

    int N = T->GetEntries();


    // save histos
    TH1F *hx = new TH1F("hx", "x cluster distribution", 200, -80, 80);
    hx->GetXaxis()->SetTitle(" x (mm)");
    TH1F *hy = new TH1F("hy", "y cluster distribution", 200, -80, 80);
    hy->GetXaxis()->SetTitle(" y (mm)");
    TH1F *hxsize = new TH1F("hxsize", "x cluster size distribution", 40, 0, 20);
    hxsize->GetXaxis()->SetTitle(" x cluster size ");
    TH1F *hysize = new TH1F("hysize", "y cluster size distribution", 40, 0, 20);
    hysize->GetXaxis()->SetTitle(" y cluster size ");
    TH1F *hxcharge = new TH1F("hxcharge", "x cluster charge distribution", 2000, 0, 2000);
    hxcharge->GetXaxis()->SetTitle(" x cluster charge ");
    TH1F *hycharge = new TH1F("hycharge", "y cluster charge distribution", 2000, 0, 2000);
    hycharge->GetXaxis()->SetTitle(" y cluster charge ");
    TH1F *hchargeratio = new TH1F("hchargeratio", "charge ratio", 100, 0, 2);
    hchargeratio->GetXaxis()->SetTitle(" y cluster charge / x cluster charge ");
    TH1F *hn = new TH1F("hn", "number of clusters per trigger", 20, 0, 10);
    hn->GetXaxis()->SetTitle(" cluster mulitiplicity ");

    TH2F *hxy = new TH2F("hxy", "x, y cluster 2d distribution", 200, -80, 80, 200, -80, 80);
    hxy->GetXaxis()->SetTitle("x (mm)");
    hxy->GetYaxis()->SetTitle("y (mm)");
    TH2F *hc2d = new TH2F("hc2d", "x, y charge ratio 2d", 500, 0, 2000, 500, 0, 2000);
    hc2d->GetXaxis()->SetTitle("x charge");
    hc2d->GetYaxis()->SetTitle("y charge");



    for(int ii=0;ii<N;ii++)
    {
        T->GetEntry(ii);

        hn -> Fill(n);
	for(int i=0;i<n;i++)
	{
	    hx->Fill(x[i]);
	    hy->Fill(y[i]);
	    hxsize->Fill(xsize[i]);
	    hysize->Fill(ysize[i]);
	    hxcharge->Fill(xcharge[i]);
	    hycharge->Fill(ycharge[i]);
            hchargeratio -> Fill(ycharge[i]/xcharge[i]);

	    hxy->Fill(x[i], y[i]);
	    hc2d -> Fill(xcharge[i], ycharge[i]);
	}
    }

    TCanvas *c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
    hn->Draw();
    TCanvas *c2 = new TCanvas("c2", "c2", 20, 20, 800, 600);
    hx->Draw();
    TCanvas *c3 = new TCanvas("c3", "c3", 30, 30, 800, 600);
    hy->Draw();
    TCanvas *c4 = new TCanvas("c4", "c4", 40, 40, 800, 600);
    hxsize->Draw();
    TCanvas *c5 = new TCanvas("c5", "c5", 50, 50, 800, 600);
    hysize->Draw();
    TCanvas *c6 = new TCanvas("c6", "c6", 60, 60, 800, 600);
    hxcharge->Draw();
    TCanvas *c7 = new TCanvas("c7", "c7", 70, 70, 800, 600);
    hycharge->Draw();
    TCanvas *c8 = new TCanvas("c8", "c8", 80, 80, 800, 600);
    hchargeratio->Draw();
    TCanvas *c9 = new TCanvas("c9", "c9", 90, 90, 800, 600);
    hxy->Draw("colz");
    TCanvas *c0 = new TCanvas("c0", "c0", 100, 100, 800, 600);
    hc2d->Draw("colz");
}
