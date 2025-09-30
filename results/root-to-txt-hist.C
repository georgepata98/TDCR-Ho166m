// Umplu un fisier text cu histograma din fisierul ROOT
{
    string rootFileName, txtFileName;

    
    cout << "\nNume fisier root cu histograma (ex: spectru-Run9.root):\n-> "; cin >> rootFileName;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    TFile *file = TFile::Open(rootFileName.c_str(), "READ");
    if(!file || file->IsZombie()) return 1;

    TH1F *hist = (TH1F*)file->Get("Edep"); // Edep trebuie sa fie numele histogramei din fisierul dat de variabila file
    if(!hist)
    {
        cout << "\nEROARE: Nu s-a deschis histograma 'Edep' !" << endl;
        return 1;
    }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // Incarcarea histogramei din root in fisierul txt

    cout << "Nume fisier text in care se incarca histograma (ex: spectru-Run9.txt):\n-> "; cin >> txtFileName;

    std::ofstream ofile(txtFileName);
    for(int i=1; i<=hist->GetNbinsX(); ++i)
    {
        ofile << hist->GetBinCenter(i) << " " << hist->GetBinContent(i) << " " << hist->GetBinError(i) << endl;
    }
    ofile.close();


    file->Close();

    cout << "Fisierul " << txtFileName << " a fost creat cu succes.\n" << endl;

    return 0;
}