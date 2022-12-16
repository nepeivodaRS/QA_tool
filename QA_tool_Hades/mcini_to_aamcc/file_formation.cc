void file_formation(Int_t files, const char* input_dirname, const char* output_filename)
{
  std::vector<double> MassOnSideA;
  std::vector<double> ChargeOnSideA;
  float btree;
  TFile* ReadFile = new TFile(output_filename,"RECREATE","Demo ROOT file with histograms & trees");
  TTree* tree = new TTree("Glauber","Events from glauber modeling");

  tree->Branch("A_on_A", "std::vector" ,&MassOnSideA);
  tree->Branch("Z_on_A", "std::vector" ,&ChargeOnSideA);
  tree->Branch("impact_parameter", &btree, "impact_parameter/f");

  TChain* fChain=new TChain("events");
  for (int i = 1; i <= files; i++) {fChain->Add(Form("%s/urqmd_aamcc_%d_mcini_.root", input_dirname, i));}
      //TFile* ReadFile = new TFile("../input/QA_dcmqgsm.root");
  cout<<"Number of entries equal "<<fChain->GetEntries()<<endl;
  UEvent* fEvent = new UEvent;
  EventInitialState* fIniState = new EventInitialState;
  
  URun *fRun = new URun;
  TFile *fIn = new TFile(Form("%s/urqmd_aamcc_1_mcini_.root", input_dirname), "read");
  fRun = (URun *)fIn->Get("run");
  Int_t A = fRun->GetAProj();
  Int_t Ab = fRun->GetATarg();
  Int_t Z = fRun->GetZProj();
  Int_t Zb = fRun->GetZTarg();
  Double_t pzB = fRun->GetPProj();
  Double_t pzA = fRun->GetPTarg();
  Double_t SqrtSnn = fRun->GetNNSqrtS();

  fChain->SetBranchAddress("event", &fEvent);
  fChain->SetBranchAddress("iniState", &fIniState);
      
  Long64_t lNEvents = fChain->GetEntries();
  Long64_t fNpa;
  UParticle* fParticle;
                      
  for (long i = 0; i < lNEvents; i++){
    if (i % 100 == 0) cout<<i<<endl;
    fChain->GetEntry(i);
    fNpa = fEvent->GetNpa();
    btree = fEvent->GetB();
    for (int j=0;j<fNpa;j++)
    {
      if(j >= (A + Ab)) break;
      fParticle = fEvent->GetParticle(j);
      TLorentzVector fMomentum = fParticle->GetMomentum();
      if (fMomentum.Pz() > 0)
      {
        if (fParticle->GetPdg()>1e9) {
          MassOnSideA.push_back(fParticle->GetPdg()/10%1000);
          ChargeOnSideA.push_back(fParticle->GetPdg()/10000%1000);
        }
        else if (fParticle->GetPdg()==2212) {
          MassOnSideA.push_back(1.);
          ChargeOnSideA.push_back(1.);
        }
        else if (fParticle->GetPdg()==2112) {
          MassOnSideA.push_back(1.);
          ChargeOnSideA.push_back(0.);
        }
      }
    }
    tree->Fill();
    MassOnSideA.clear();
    ChargeOnSideA.clear();
  }
  ReadFile->Write();
  ReadFile->Close();
}