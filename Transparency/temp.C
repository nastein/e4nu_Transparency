#include <TCanvas.h>
#include <TLegend.h>
#include <TH1F.h>
#include <TGraph.h>

void temp() {
    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Canvas with Legend", 800, 600);

    // Create histograms or graphs to add to the canvas
    TH1F *hist1 = new TH1F("hist1", "Histogram 1", 100, -4, 4);
    hist1->FillRandom("gaus", 1000);
    hist1->SetLineColor(kBlue);
    hist1->SetMarkerStyle(kFullCircle);
    hist1->SetMarkerColor(kBlack);

    TGraph *graph1 = new TGraph();
    for (int i = 0; i < 100; ++i) {
        double x = i * 0.1;
        graph1->SetPoint(i, x, TMath::Sin(x));
    }
    graph1->SetLineWidth(2);
    graph1->SetLineColor(kBlue);

    // Draw the histogram and graph
    hist1->Draw();
    graph1->Draw("L SAME");

    // Create a legend and add entries
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9); // Position of the legend
    legend->AddEntry(hist1, "CLAS data", "p"); // "l" for line
    legend->AddEntry(graph1, "SuSAv2", "l");        // "l" for line
    legend->Draw();

    // Update the canvas
    canvas->Update();
}

