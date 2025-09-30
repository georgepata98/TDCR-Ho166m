// Merge-uieste toate histogramele pentru fiecare linie gama din Ho-166m si le normeaza in functie de intensitatea de emisie a cuantelor respective.
// Toate histogramele se normeaza la 10^6 evenimente, dupa care valorile normate se inmultesc cu intensitatile de emisie.

{
    // ---> Se introduc mai jos numele fisierelor root care au histogramele:

    string rootFileName[13];  // array cu nr. total de histograme
    TFile *files[13];
    TH1F  *hists[13];
    double counts[13][1000]; // 1000 = nr. de bini dintr-o histograma
    double c[1000];

    for(int i=0; i<1000; i++)
    {
        c[i] = 0;
    }

    rootFileName[0] = "spectru-Run0_2e6.root";
    rootFileName[1] = "spectru-Run1_2e6.root";
    rootFileName[2] = "spectru-Run2_2e6.root";
    rootFileName[3] = "spectru-Run3_2e6.root";
    rootFileName[4] = "spectru-Run4_2e6.root";
    rootFileName[5] = "spectru-Run5_4e6.root";
    rootFileName[6] = "spectru-Run6_6e6.root";
    rootFileName[7] = "spectru-Run7_6e6.root";
    rootFileName[8] = "spectru-Run8_10e6.root";
    rootFileName[9] = "spectru-Run9_12e6.root";
    rootFileName[10] = "spectru-Run10_17e6.root";
    rootFileName[11] = "spectru-Run11_25e6.root";
    rootFileName[12] = "spectru-Run12_60e6.root";


    for(int i=0; i<13; i++)
    {
        files[i] = TFile::Open(rootFileName[i].c_str(), "READ");
        if(!files[i] || files[i]->IsZombie()) return 1;

        hists[i] = (TH1F*)files[i]->Get("Edep");  // Edep este numele histogramei din fisierul root

        for(int j=1; j<=hists[i]->GetNbinsX(); ++j)
        {
            // se impart valorile din fiecare bin la coeficientul cu care este inmultit 10^6 si apoi se inmulteste cu intensitatea de emisie pentru gama respectiva:
            if(i==0) counts[i][j-1] = (hists[i]->GetBinContent(j)/2) * 0.3001;
            if(i==1) counts[i][j-1] = (hists[i]->GetBinContent(j)/2) * 0.0624;
            if(i==2) counts[i][j-1] = (hists[i]->GetBinContent(j)/2) * 0.1266;
            if(i==3) counts[i][j-1] = (hists[i]->GetBinContent(j)/2) * 0.7250;
            if(i==4) counts[i][j-1] = (hists[i]->GetBinContent(j)/2) * 0.2954;
            if(i==5) counts[i][j-1] = (hists[i]->GetBinContent(j)/4) * 0.1135;
            if(i==6) counts[i][j-1] = (hists[i]->GetBinContent(j)/6) * 0.0940;
            if(i==7) counts[i][j-1] = (hists[i]->GetBinContent(j)/6) * 0.0543;
            if(i==8) counts[i][j-1] = (hists[i]->GetBinContent(j)/10) * 0.0534;
            if(i==9) counts[i][j-1] = (hists[i]->GetBinContent(j)/12) * 0.5490;
            if(i==10) counts[i][j-1] = (hists[i]->GetBinContent(j)/17) * 0.1220;
            if(i==11) counts[i][j-1] = (hists[i]->GetBinContent(j)/25) * 0.5730;
            if(i==12) counts[i][j-1] = (hists[i]->GetBinContent(j)/60) * 0.0972;
        }

        files[i]->Close();
    }
    

    std::ofstream ofile("spectru-combinat.txt");
    for(int i=0; i<1000; i++)
    {
        for(int j=0; j<13; j++)
        {
            c[i] += counts[j][i];
        }

        ofile << (i+1) * 0.9 - 0.9/2 << " " << c[i] << endl; // centrul binului i+1, 0.9 keV/bin, 1000 bini de la 0 la 900 keV
    }
    ofile.close();

    cout << "\nFisierul spectru-combinat.txt a fost creat cu succes.\n" << endl;

    return 0;
}