#include <string.h>
R__LOAD_LIBRARY(/home/rnepeiv/inr/mcini/build/libMcIniData.so)

void FragmentationInput_mcini(int flag_dcm, const char* input_path_mcini, const char* input_path_aamcc, string output_dirname, string root_fin_filename, string QA_filename, Int_t files)
{
	TChain* fChain=new TChain("events");
    TChain* ReadFile = new TChain("Glauber");
    TChain* ReadFile2 = new TChain("MST-Clusters");
    URun *fRun = new URun;
    // flag_dcm is set to 1 if QA is performed for MCINI files
    if(flag_dcm == 0){ 
        if(files == 1){
            fChain->Add((input_path_mcini));
            ReadFile->Add((input_path_aamcc));
            ReadFile2->Add((input_path_aamcc));
        }
        else{
            for (int i = 1; i <= files; i++) {
                fChain->Add(Form("%s/%d_mcini.root", input_path_mcini, i));
                ReadFile->Add(Form("%s/%d.root", input_path_aamcc, i));
                ReadFile2->Add(Form("%s/%d.root", input_path_aamcc, i));
            }
        }
    }
    else
    {
        if(files == 1){
            for (int i = 1; i <= files; i++) {fChain->Add(Form("%s/%d_mcini_.root", input_path_mcini, i));}
            ReadFile->Add(Form("%s", input_path_aamcc));
            ReadFile2->Add(Form("%s", input_path_aamcc));
        }
        else{
            for (int i = 1; i <= files; i++) {fChain->Add(Form("%s/%d_mcini_.root", input_path_mcini, i));}
            ReadFile->Add(Form("%s", input_path_aamcc)); 
            ReadFile2->Add(Form("%s", input_path_aamcc));
        }
    }

    // Run info, 1 mcini file is enough
    if(files > 1 || flag_dcm == 1){
        TFile *fIn = new TFile(Form("%s/1_mcini_.root", input_path_mcini), "read");
        fRun = (URun *)fIn->Get("run");
    }
    else{
        TFile *fIn = new TFile(input_path_mcini, "read");
        fRun = (URun *)fIn->Get("run");
    }

    Int_t A = fRun->GetAProj();
    Int_t Ab = fRun->GetATarg();
    Int_t Z = fRun->GetZProj();
    Int_t Zb = fRun->GetZTarg();
    Double_t pzB = fRun->GetPProj();
    Double_t pzA = fRun->GetPTarg();
    Double_t SqrtSnn = fRun->GetNNSqrtS();

    std::cout << A << " " << pzB << " " << SqrtSnn << std::endl; 

    std::vector<float>* MassOnSideA = 0;
    Float_t b, ExEn;
    Double_t crd;
  
    ReadFile->SetBranchAddress("A_on_A", &MassOnSideA);
    if(flag_dcm == 0){
        ReadFile->SetBranchAddress("Ex_En_per_nucleon", &ExEn);
    }
    ReadFile->SetBranchAddress("impact_parameter", &b);

    //TTree *ftree1 = nullptr;
    if(flag_dcm == 0){
        //tree1 = (TTree*) ReadFile->GetTree("MST-Clusters"); //MST: Clusters info 
        ReadFile2->SetBranchAddress("d", &crd);
    }

    cout<<"Number of entries equal "<< fChain->GetEntries() <<endl;
    UEvent* fEvent = new UEvent;
    EventInitialState* fIniState = new EventInitialState;
	fChain->SetBranchAddress("event", &fEvent); 
    fChain->SetBranchAddress("iniState", &fIniState);

    gStyle -> SetOptStat(111111111);
    gStyle -> SetStatX (0.3);
    //gStyle -> SetOptStat(0);


    TH1F* hImpactParameter =                    new TH1F("b",";b, fm;counts",200,0,20);
    TH1F* hNpart =                              new TH1F("Npart",";Npart;counts",A + 2,0,A + 2);
    TH1F* hNspec =                              new TH1F("Nspec",";Nspec;counts",200,0,200);
    TH1F* hNcoll =                              new TH1F("Ncoll",";Ncoll;counts",A*3,0,A*6);
    TH2F* hNpart_vs_ImpactParameter =           new TH2F("Npart_VS_B",";Npart;b, fm",200,0,200,200,0,20);
    TH2F* hNspec_vs_ImpactParameter =           new TH2F("Nspec_VS_B",";Nspec;b, fm",200,0,200,200,0,20);
    TH2F* hNcoll_vs_ImpactParameter =           new TH2F("Ncoll_VS_B",";Ncoll;b, fm",1000,0,1000,200,0,20);
    TH2F* hNspec_vs_Npart =                     new TH2F("Nspec_VS_Npart",";Nspec;Npart",200,0,200,200,0,200);
    TH2F* hNspec_vs_Ncoll =                     new TH2F("Nspec_VS_Ncoll",";Nspec;Ncoll",200,0,200,1000,0,1000);
    TH2F* hNpart_vs_Ncoll =                     new TH2F("Npart_VS_Ncoll",";Npart;Ncoll",200,0,200,1000,0,1000);

/*    TH2F* hEcc1_vs_B =                new TH2F ("Ecc1_VS_B", ";#epsilon_{1};B, fm",200,0,1,200,0,20);
    TH2F* hEcc2_vs_B =                new TH2F ("Ecc2_VS_B", ";#epsilon_{2};B, fm",200,0,1,200,0,20);
    TH2F* hEcc3_vs_B =                new TH2F ("Ecc3_VS_B", ";#epsilon_{3};B, fm",200,0,1,200,0,20);
    TH2F* hEcc4_vs_B =                new TH2F ("Ecc4_VS_B", ";#epsilon_{4};B, fm",200,0,1,200,0,20);*/
    
    TH1F* hNfrag =                              new TH1F("A_Fragments",";A_{fr};counts",A+3,0,A+3);
    TH1F* hEnergy =                             new TH1F("Energy",";E_{event}, GeV;counts",SqrtSnn*A/2. + 5,0,SqrtSnn*A/2. + 5);
    TH1F* hP =                                  new TH1F("P",";P/A, GeV/c;counts",Int_t(SqrtSnn*A/2.),0,SqrtSnn/2. + 0.2);
    TH1F* hPz =                                 new TH1F("P_z",";Pz/A, GeV/c;counts",Int_t(SqrtSnn*A/2.),0,SqrtSnn/2. + 0.2);
    TH1F* hPTnucl =                             new TH1F("Pt_nucl",";P_{t} for nucleons, GeV/c;counts",100,0,pzB);
    TH2F* hPT_vs_A =                            new TH2F("Pt_vs_A",";P_{t}, GeV/c;A",100,0,4,A+2,0,A+2);
    TH2F* hPz_vs_A =                            new TH2F("Pz_vs_A",";P_{z}/A, GeV/c;A",Int_t(SqrtSnn*A/2.),0,SqrtSnn/2. + 0.2,A+2,0,A+2);
    TH2F* hP_vs_A =                             new TH2F("P_vs_A",";P/A, GeV/c;A",Int_t(SqrtSnn*A/2.),0,SqrtSnn/2. + 0.2,A+2,0,A+2);
    TH1F* hPznucl =                             new TH1F("P_z_nucleons",";Pz/A, GeV/c;counts",Int_t(SqrtSnn*A/2.),0,SqrtSnn/2. + 0.2);
    TH1F* hPnucl =                              new TH1F("P_nucleons",";Pz/A, GeV/c;counts",Int_t(SqrtSnn*A/2.),0,SqrtSnn/2. + 0.2);
    TH1F* hPimf =                               new TH1F("P_imf",";P/A, GeV/c;counts",Int_t(SqrtSnn*A/2.),0,SqrtSnn/2. + 0.2);
    TH1F* hPheavy =                             new TH1F("P_heavy",";P/A, GeV/c;counts",Int_t(SqrtSnn*A/2.),0,SqrtSnn/2. + 0.2);
    TH1F* hPzimf =                              new TH1F("P_z_imf",";Pz/A, GeV/c;counts",Int_t(SqrtSnn*A/2.),0,SqrtSnn/2. + 0.2);
    TH1F* hPzheavy =                            new TH1F("P_z_heavy",";Pz/A, GeV;counts",Int_t(SqrtSnn*A/2.),0,SqrtSnn/2. + 0.2);
    TH1F* hRapidity =                           new TH1F("Y_nucleon",";Rapidity;counts",500,0,1.5);
    TH1F* hPseudoRapidity =                     new TH1F("Eta",";Pseudorapidity;counts",180,0,15);
    TH1F* hPseudoRapidityAll =                  new TH1F("Eta_all",";Pseudorapidity: target+projectile;counts",280,-14,14);
    TH1F* hPseudoRapidity_nucl =                new TH1F("Eta_nucl",";Pseudorapidity (Z=1);counts",180,0,13);
    TH2F* hNprotons_vs_Nneutrons =              new TH2F("Nprotons_VS_Nneutrons",";N in fragment;Z in fragment",A-Z + 1,0,A-Z + 1,Z + 1,0,Z + 1);
    TH2F* hNfrag_vs_ImpactParameter =           new TH2F("A_VS_B",";A_{fr};b, fm",A+3,0,A+3,200,0,20);
    TH2F* hNfrag_vs_Energy =                    new TH2F("A_VS_E",";A_{fr};E_{frag}, GeV",A+3,0,A+3,SqrtSnn*A/2. + 5,0,SqrtSnn*A/2. + 5);
    TH2F* hNfrag_vs_Energy_scaled =             new TH2F("A_VS_E_scaled",";A_{fr};E_{frag}-E_{beam}(A-1), GeV",200,0,200,150,-100,200);
    TH2F* hNfrag_vs_Rapidity =                  new TH2F("A_VS_Y",";A_{fr};Rapidity",A+3,0,A+3,500,0,1.5);
    TH2F* hImpactParameter_vs_Energy_Fragment = new TH2F("B_VS_E",";b, fm;E_{event}, GeV",200,0,20,250,0,260);
    TH2F* hImpactParameter_vs_Rapidity =        new TH2F("B_VS_Y",";b, fm;Rapidity",200,0,20,250,0,1.6);
    TH2F* hRapidity_vs_Energy =                 new TH2F("Y_VS_E",";E, GeV;Rapidity",250,0,300,250,0,1.6);
    TH2F* hPseudoRapidity_vs_A =                new TH2F("Eta_VS_A",";Pseudorapidity;A",180,2,14,A+3,0,A+3);
    TH2F* hPx_vs_Py =                           new TH2F("Py_VS_Px",";Px, GeV;Py, GeV",200,-5,5,200,-4,4);

    TH2F* hEnergyA_vs_ImpactParameter_proj =    new TH2F("EperA_VS_B_proj",";b, fm;E_{frag}/A, GeV",200,0,20,SqrtSnn*100,0,SqrtSnn);
    TH2F* hNspect_vs_Espect_proj =              new TH2F("Espect_VS_Nspect_proj",";Nspect;Espect, GeV",A/2.,0,A/2.,SqrtSnn*A/2. + 5,0,SqrtSnn*A/2. + 5);
    TH2F* hNspect_vs_sumZ_proj =                new TH2F("sumZ_VS_Nspect_proj",";sumZ;Nspect",Z + 2,0,Z + 2, A/2.,0,A/2.);
    TH2F* hNspect_vs_Zb2 =                      new TH2F("Zb3_VS_Nspect_proj",";Zb3;Nspect",Z + 2,0,Z + 2, A/2.,0,A/2.);
    TH2F* hNnucl_vs_Nfrag_proj =                new TH2F("Nnucl_vs_Nfrag_proj",";Nfrag;Nnucl",A/4.,0,A/4.,A/2.,0,A/2.);

    TH2F* hEnergyE_vs_sumZ_proj =               new TH2F("EnergyE_VS_sumZ_proj",";sumZ;E_{event}, GeV",Z + 2,0,Z + 2,SqrtSnn*A/2. + 5,0,SqrtSnn*A/2. + 5);
    TH2F* hEnergyE_vs_Nnucl_proj =              new TH2F("EnergyE_VS_Nnucl_proj",";Nnucl;E_{event}, GeV",A/2,0,A/2.,SqrtSnn*A/5,0,SqrtSnn*A/2. + 5);
    TH2F* hEnergyE_vs_Nimf_proj =               new TH2F("EnergyE_VS_Nimf_proj",";N_{IMF};E_{event}, GeV",Int_t(A/15.),0,Int_t(A/15.),SqrtSnn*A/2. + 5,0,SqrtSnn*A/2. + 5);
    TH2F* hImpactParameter_vs_Energy  =         new TH2F("B_VS_Energy_proj",";b, fm;E_{event} (projectile), GeV",200,0,20,SqrtSnn*A/2. + 5,0,SqrtSnn*A/2. + 5);

    TH2F* hImpactParameter_vs_ExEn  =           new TH2F("B_VS_ExEn",";b, fm;E*/A_{pf}, MeV",200,0,20,250,0,12);
    TH2F* hImpactParameter_vs_d  =              new TH2F("B_VS_d",";b, fm; d, fm",200,0,20,200,1.,3.);
    TH2F* hImpactParameter_vs_A  =              new TH2F("B_VS_A_{pf}/A",";b, fm; A_{pf}/A",200,0,20,198,0,1);
    TH2F* hRelA_vs_ExEn  =                      new TH2F("ApfA_VS_ExEn",";E*/A_{pf}, MeV; A_{pf}/A",360,0,12,198,0,1);
    TH2F* hNspect_vs_ExEn  =                    new TH2F("Nspect_VS_ExEn",";Nspect;E*/A, MeV",A/2.,0,A/2.,250,0,12);
        
	Long64_t lNEvents = fChain->GetEntries();
    Long64_t fNpa;
    UParticle* fParticle;
    
    Double_t fEnergy=0;
            
	for (long i = 0; i < lNEvents; i++)
	{
		if (i % 100 == 0) cout<<i<<endl;
        fChain->GetEntry(i);
        fEnergy=0;
        Int_t sumZ = 0, Zb2 = 0, fNnucl = 0, fNfrag = 0, fNimf = 0, fNspect = 0;
        fNpa = fEvent->GetNpa();

        for (int j=0;j<fNpa;j++)
        {
            fParticle = fEvent->GetParticle(j);
            TLorentzVector fMomentum = fParticle->GetMomentum();

            if (fParticle->GetPdg()>1e9 || fParticle->GetPdg()==2212 || fParticle->GetPdg()==2212){
                hPseudoRapidityAll                          ->Fill(fMomentum.PseudoRapidity());
            }
            if (fParticle -> T() == 1)
            {
                if (fParticle->GetPdg()>1e9) 
                {
                    hNprotons_vs_Nneutrons                  ->Fill(fParticle->GetPdg()/10%1000-fParticle->GetPdg()/10000%1000,fParticle->GetPdg()/10000%1000);
                    hNfrag                                  ->Fill(fParticle->GetPdg()/10%1000);
                    hNfrag_vs_ImpactParameter               ->Fill(fParticle->GetPdg()/10%1000, fEvent->GetB());
                    hNfrag_vs_Energy                        ->Fill(fParticle->GetPdg()/10%1000, fMomentum.E());
                    hEnergyA_vs_ImpactParameter_proj        ->Fill(fEvent->GetB(), fMomentum.E()/(fParticle->GetPdg()/10%1000));
                    //hImpactParameter_Nfrag_vs_Energy_scaled ->Fill(fEvent->GetB(), fParticle->GetPdg()/10%1000, fMomentum.E()-E_beam*(fParticle->GetPdg()/10%1000-1));
                    //hNfrag_vs_Energy_scaled                 ->Fill(fParticle->GetPdg()/10%1000, fMomentum.E()-E_beam*(fParticle->GetPdg()/10%1000-1));
                    hNfrag_vs_Rapidity                      ->Fill(fParticle->GetPdg()/10%1000, fMomentum.Rapidity());
                    hImpactParameter_vs_Energy_Fragment     ->Fill(fEvent->GetB(), fMomentum.E());
                    hImpactParameter_vs_Rapidity            ->Fill(fEvent->GetB(), fMomentum.Rapidity());
                    hPx_vs_Py                               ->Fill(fMomentum.Px(), fMomentum.Py());
                    hRapidity_vs_Energy                     ->Fill(fMomentum.E(), fMomentum.Rapidity());
                    hP                                      ->Fill(fMomentum.P()/(fParticle->GetPdg()/10%1000));
                    hPz                                     ->Fill(fMomentum.Pz()/(fParticle->GetPdg()/10%1000));
                    hPT_vs_A                                ->Fill(pow(fMomentum.Px()*fMomentum.Px() + fMomentum.Py()*fMomentum.Py(),0.5), fParticle->GetPdg()/10%1000);
                    hPz_vs_A                                ->Fill(fMomentum.Pz()/(fParticle->GetPdg()/10%1000), fParticle->GetPdg()/10%1000);
                    hP_vs_A                                 ->Fill(fMomentum.P()/(fParticle->GetPdg()/10%1000), fParticle->GetPdg()/10%1000);
                    hRapidity                               ->Fill(fMomentum.Rapidity());
                    hPseudoRapidity                         ->Fill(fMomentum.PseudoRapidity());
                    hPseudoRapidity_vs_A                    ->Fill(fMomentum.PseudoRapidity(),fParticle->GetPdg()/10%1000);
                    fEnergy=fEnergy+fMomentum.E();
                    sumZ+=fParticle->GetPdg()/10000%1000;
                    if (fParticle->GetPdg()/10000%1000 > 2) Zb2+=fParticle->GetPdg()/10000%1000;
                    if (fParticle->GetPdg()/10000%1000 < 80 && fParticle->GetPdg()/10000%1000 < 198) fNfrag+=1;
                    if (fParticle->GetPdg()/10000%1000 < 80 && fParticle->GetPdg()/10000%1000 < 198) fNspect+=1;
                    if ( fParticle->GetPdg()/10000%1000 <= 30 && fParticle->GetPdg()/10000%1000 >=3){
                        fNimf+=1;
                        hPimf->Fill(fMomentum.P()/(fParticle->GetPdg()/10%1000));
                        hPzimf->Fill(fMomentum.Pz()/(fParticle->GetPdg()/10%1000));
                    }
                    if (fParticle->GetPdg()/10000%1000 > 30) {
                        hPheavy->Fill(fMomentum.P()/(fParticle->GetPdg()/10%1000)); 
                        hPzheavy->Fill(fMomentum.Pz()/(fParticle->GetPdg()/10%1000)); 
                    }
                }       
                else if (fParticle->GetPdg()==2212) 
                {
                    hNprotons_vs_Nneutrons                  ->Fill(1, 0.1);
                    hNfrag                                  ->Fill(1);
                    hNfrag_vs_ImpactParameter               ->Fill(1, fEvent->GetB());
                    hNfrag_vs_Energy                        ->Fill(1, fMomentum.E());
                    hNfrag_vs_Rapidity                      ->Fill(1, fMomentum.Rapidity());
                    hEnergyA_vs_ImpactParameter_proj        ->Fill(fEvent->GetB(), fMomentum.E());
                    //hImpactParameter_Nfrag_vs_Energy_scaled ->Fill(fEvent->GetB(), 1, fMomentum.E());
                    hNfrag_vs_Energy_scaled                 ->Fill(1, fMomentum.E());
                    hImpactParameter_vs_Rapidity            ->Fill(fEvent->GetB(), fMomentum.Rapidity());
                    hImpactParameter_vs_Energy_Fragment     ->Fill(fEvent->GetB(), fMomentum.E());
                    hPx_vs_Py                               ->Fill(fMomentum.Px(), fMomentum.Py());
                    hRapidity_vs_Energy                     ->Fill(fMomentum.E(), fMomentum.Rapidity());                
                    hP                                      ->Fill(fMomentum.P());
                    hPz                                     ->Fill(fMomentum.Pz());
                    hPTnucl     -> Fill (pow( fMomentum.Px()*fMomentum.Px() + fMomentum.Py()*fMomentum.Py(),0.5));
                    hPT_vs_A                                -> Fill (pow(fMomentum.Px()*fMomentum.Px() + fMomentum.Py()*fMomentum.Py(),0.5), fParticle->GetPdg()/10%1000);
                    hPz_vs_A                                -> Fill (fMomentum.Pz(), fParticle->GetPdg()/10%1000);
                    hP_vs_A                                 -> Fill (fMomentum.P(), fParticle->GetPdg()/10%1000);
                    hPnucl                                  ->Fill(fMomentum.P());
                    hPznucl                                 ->Fill(fMomentum.Pz());
                    hRapidity                               ->Fill(fMomentum.Rapidity());
                    hPseudoRapidity                         ->Fill(fMomentum.PseudoRapidity());
                    //hPseudoRapidity_nucl                    ->Fill(fMomentum.PseudoRapidity());
                    hPseudoRapidity_vs_A                    ->Fill(fMomentum.PseudoRapidity(),1);

                    fEnergy=fEnergy+fMomentum.E();
                    sumZ+=1;
                    fNnucl +=1;
                    fNspect+=1;
                }
                else if (fParticle->GetPdg()==2112) 
                {
                    hNprotons_vs_Nneutrons                  ->Fill(0.1, 1);
                    hNfrag                                  ->Fill(1);
                    hNfrag_vs_ImpactParameter               ->Fill(1, fEvent->GetB());
                    hNfrag_vs_Energy                        ->Fill(1, fMomentum.E());
                    hEnergyA_vs_ImpactParameter_proj        ->Fill(fEvent->GetB(), fMomentum.E());
                    //hImpactParameter_Nfrag_vs_Energy_scaled ->Fill(fEvent->GetB(), 1, fMomentum.E());
                    hNfrag_vs_Energy_scaled                 ->Fill(1, fMomentum.E());
                    hNfrag_vs_Rapidity                      ->Fill(1, fMomentum.Rapidity());
                    hImpactParameter_vs_Energy_Fragment     ->Fill(fEvent->GetB(), fMomentum.E());
                    hImpactParameter_vs_Rapidity            ->Fill(fEvent->GetB(), fMomentum.Rapidity());
                    hPx_vs_Py                               ->Fill(fMomentum.Px(), fMomentum.Py());
                    hRapidity_vs_Energy                     ->Fill(fMomentum.E(), fMomentum.Rapidity());
                    hP                                      ->Fill(fMomentum.P());
                    hPz                                     ->Fill(fMomentum.Pz());
                    hPTnucl                                 ->Fill(pow( fMomentum.Px()*fMomentum.Px() + fMomentum.Py()*fMomentum.Py(),0.5));
                    hPT_vs_A                                ->Fill(pow(fMomentum.Px()*fMomentum.Px() + fMomentum.Py()*fMomentum.Py(),0.5), fParticle->GetPdg()/10%1000);
                    hPz_vs_A                                ->Fill(fMomentum.Pz(), fParticle->GetPdg()/10%1000);
                    hP_vs_A                                 ->Fill(fMomentum.P(), fParticle->GetPdg()/10%1000);
                    hPnucl                                  ->Fill(fMomentum.P());
                    hPznucl                                 ->Fill(fMomentum.Pz());
                    hRapidity                               ->Fill(fMomentum.Rapidity());
                    hPseudoRapidity                         ->Fill(fMomentum.PseudoRapidity());
                    hPseudoRapidity_nucl                    ->Fill(fMomentum.PseudoRapidity());
                    hPseudoRapidity_vs_A                    ->Fill(fMomentum.PseudoRapidity(),1);
                    fEnergy=fEnergy+fMomentum.E();
                    fNnucl+=1;
                    fNspect+=1;
                }
            }
        }

        hNspect_vs_Espect_proj        ->Fill(fNspect, fEnergy);
        hNspect_vs_sumZ_proj          ->Fill(sumZ, fNspect);
        hNspect_vs_Zb2                ->Fill(Zb2, fNspect);
        hNnucl_vs_Nfrag_proj          ->Fill (fNfrag, fNnucl);
        hEnergyE_vs_sumZ_proj         ->Fill (sumZ, fEnergy);
        hEnergyE_vs_Nnucl_proj        ->Fill (fNnucl, fEnergy);
        hEnergyE_vs_Nimf_proj         ->Fill (fNimf, fEnergy);

        hEnergy                       ->Fill(fEnergy);
        hImpactParameter_vs_Energy    ->Fill(fEvent->GetB(), fEnergy);
        hImpactParameter              ->Fill(fEvent->GetB());
        hNpart                        ->Fill(fIniState->getNPart());
        hNspec                        ->Fill(A-fIniState->getNPart());
        hNcoll                        ->Fill(fIniState->getNColl());
        hNpart_vs_ImpactParameter     ->Fill(fIniState->getNPart(), fEvent->GetB());
        hNspec_vs_ImpactParameter     ->Fill(A-fIniState->getNPart(), fEvent->GetB());
        hNcoll_vs_ImpactParameter     ->Fill(fIniState->getNColl(), fEvent->GetB());
        hNspec_vs_Npart               ->Fill(A-fIniState->getNPart(), fIniState->getNPart());
        hNspec_vs_Ncoll               ->Fill(A-fIniState->getNPart(), fIniState->getNColl());
        hNpart_vs_Ncoll               ->Fill(fIniState->getNPart(), fIniState->getNColl());
		
	}
    
    for(int k = 0; k < ReadFile->GetEntries(); k++){
        ReadFile->GetEntry(k);
        int sumA_proj=0;

        for (Int_t ipart = 0; ipart < (MassOnSideA->size()); ipart++){
            sumA_proj+=MassOnSideA->at(ipart);
        }
        
        if(flag_dcm == 0){
            ReadFile2->GetEntry(k);
            hRelA_vs_ExEn -> Fill (ExEn, double(sumA_proj)/A);
            hNspect_vs_ExEn -> Fill(MassOnSideA->size(), ExEn);
            hImpactParameter_vs_ExEn -> Fill(b, ExEn);
            hImpactParameter_vs_d -> Fill (b, crd);
        }
        hImpactParameter_vs_A  -> Fill(b, double(sumA_proj)/A);
    }

    // Converter from string to char
    string output_dirname_pdf = output_dirname + "/histos" + QA_filename;
    int n = output_dirname_pdf.length();
    char char_output_pdf[n + 1];
    strcpy(char_output_pdf, output_dirname_pdf.c_str());

    string output_dirname_pdf_begin = output_dirname_pdf + "[";
    n = output_dirname_pdf_begin.length();
    char char_output_pdf_begin[n + 1];
    strcpy(char_output_pdf_begin, output_dirname_pdf_begin.c_str());

    string output_dirname_pdf_end = output_dirname_pdf + "]";
    n = output_dirname_pdf_end.length();
    char char_output_pdf_end[n + 1];
    strcpy(char_output_pdf_end, output_dirname_pdf_end.c_str());

    string output_dirname_root = output_dirname + "/root_files" + root_fin_filename;
    n = output_dirname_root.length();
    char char_output_dirname_root[n + 1];
    strcpy(char_output_dirname_root, output_dirname_root.c_str());

    TCanvas* canvas = new TCanvas("canvas");
    gPad->SetTickx();
    gPad->SetTicky();
    canvas->Print(char_output_pdf_begin,"pdf");
    hNpart                                      ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");
    gPad->SetLogy();
    hNcoll                                      ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");
    gPad->SetLogy(0);
    hImpactParameter                            ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");

    gPad->SetLogz();
    
    hEnergyE_vs_sumZ_proj                       ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");
    hEnergyE_vs_Nnucl_proj                      ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");
    hEnergyE_vs_Nimf_proj                       ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");

    gStyle -> SetOptStat(1000100001);
    hEnergyA_vs_ImpactParameter_proj            ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");

    
    hNspect_vs_sumZ_proj                        ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");

    hNspect_vs_Zb2                              ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");

    
    hNspect_vs_Espect_proj                      ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");
    //hNspect_vs_Espect_targ ->Draw("COLZ");
    //canvas->Print(output_dirname_pdf);
    gStyle -> SetOptStat(1000000001);

        hNnucl_vs_Nfrag_proj                    ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");

   
    
    gPad->SetLogy();
    hNfrag                                      ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");
    gPad->SetLogy(0);
    hEnergy                                     ->Draw("COLZ");
    canvas->Print(char_output_pdf,"pdf");

    gPad->SetLogy();
    hP                                          ->Draw("");
    hPnucl -> SetLineColor(2);
    hPnucl                                      ->Draw("SAME");
    hPimf -> SetLineColor(4);
    hPimf                                       ->Draw("SAME");
    hPheavy -> SetLineColor(6);
    hPheavy                                     ->Draw("SAME");


    auto legend = new TLegend(0.75,0.61,0.96,0.96);
    legend -> AddEntry(hP, "all");
    legend -> AddEntry(hPnucl, "nucleons");
    legend -> AddEntry(hPimf, "IMF");
    legend -> AddEntry(hPheavy, "Z>30");
    //legend -> SetTextSize(0.045);
    legend -> Draw();


    canvas->Print(char_output_pdf,"pdf");
   

    hPTnucl                                     ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");

    hPz                                         ->Draw("COLZ");
    hPznucl -> SetLineColor(2);
    hPznucl                                     ->Draw("SAME");
    hPzimf -> SetLineColor(4);
    hPzimf                                      ->Draw("SAME");
    hPzheavy -> SetLineColor(6);
    hPzheavy                                    ->Draw("SAME");

    auto legend1 = new TLegend(0.75,0.61,0.96,0.96);
    legend1 -> AddEntry(hPz, "all");
    legend1 -> AddEntry(hPznucl, "nucleons");
    legend1 -> AddEntry(hPzimf, "IMF");
    legend1 -> AddEntry(hPzheavy, "Z>30");
    //legend -> SetTextSize(0.045);
    legend1 -> Draw();


    canvas->Print(char_output_pdf, "pdf");

    hRapidity                                   ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    hPseudoRapidity                             ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    hPseudoRapidityAll                          ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    hPseudoRapidity_nucl                        ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    gPad->SetLogy(0);
    hPT_vs_A                                    ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    hPz_vs_A                                    ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    hP_vs_A                                     ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    hNprotons_vs_Nneutrons                      ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    hNfrag_vs_ImpactParameter                   ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");

    hNfrag_vs_Energy                            ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    //hNfrag_vs_Energy_scaled                   ->Draw("COLZ");
    //canvas->Print(output_dirname_pdf);

    hNfrag_vs_Rapidity                          ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");

    hImpactParameter_vs_Energy                  ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");

    hImpactParameter_vs_Energy_Fragment         ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    hImpactParameter_vs_Rapidity                ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    hRapidity_vs_Energy                         ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    hPx_vs_Py                                   ->Draw("COLZ");
    canvas->Print(char_output_pdf, "pdf");
    if (flag_dcm == 0){
        hPseudoRapidity_vs_A                    ->Draw("COLZ");
        canvas->Print(char_output_pdf, "pdf");
        hImpactParameter_vs_ExEn                ->Draw("COLZ");
        canvas->Print(char_output_pdf, "pdf");
        hImpactParameter_vs_d                   ->Draw("COLZ");
        canvas->Print(char_output_pdf, "pdf");
        hImpactParameter_vs_A                   ->Draw("COLZ");
        canvas->Print(char_output_pdf, "pdf");
        hRelA_vs_ExEn                           ->Draw("COLZ");
        canvas->Print(char_output_pdf, "pdf");
        hNspect_vs_ExEn                         ->Draw("COLZ");
        canvas->Print(char_output_pdf, "pdf");
        canvas->Print(char_output_pdf_end, "pdf");
    }
    else {
        hPseudoRapidity_vs_A                    ->Draw("COLZ");
        canvas->Print(char_output_pdf, "pdf");
        canvas->Print(char_output_pdf_end, "pdf");
    }

    TFile *fout = new TFile(char_output_dirname_root, "recreate");
    
    hImpactParameter                     ->Write();
    gPad->SetLogy();
    hNfrag                               ->Write();
    gPad->SetLogy(0);
    hEnergy                              ->Write();
    hP                                   ->Write();
    hPz                                  ->Write();
    hRapidity                            ->Write();
    hNprotons_vs_Nneutrons               ->Write();
    hNfrag_vs_ImpactParameter            ->Write();
    hNfrag_vs_Energy                     ->Write();
    //hNfrag_vs_Energy_scaled              ->Write();
    hNfrag_vs_Rapidity                   ->Write();
    //hImpactParameter_vs_Energy           ->Write();
    hImpactParameter_vs_Energy_Fragment  ->Write();
    hImpactParameter_vs_Rapidity         ->Write();
    hRapidity_vs_Energy                  ->Write();
    hPx_vs_Py                            ->Write();
    hPseudoRapidity                      ->Write();
    hPseudoRapidityAll                   ->Write();
    hPseudoRapidity_nucl                 ->Write();
    hPseudoRapidity_vs_A                 ->Write();
    hPTnucl                              ->Write();
    hPT_vs_A                             ->Write();
    hPz_vs_A                             ->Write();
    hP_vs_A                              ->Write();
    hNspect_vs_Zb2                       ->Write();


    hEnergyA_vs_ImpactParameter_proj     ->Write();
    //hEnergyA_vs_ImpactParameter_targ     ->Write();
    hNspect_vs_Espect_proj               ->Write();
   //hNspect_vs_Espect_targ                ->Write();
    hNspect_vs_sumZ_proj                 ->Write();
    hNspect_vs_Zb2                       ->Write();
    hNnucl_vs_Nfrag_proj                 ->Write();
    hEnergyE_vs_sumZ_proj                ->Write();
    hEnergyE_vs_Nnucl_proj               ->Write();
    hEnergyE_vs_Nimf_proj                ->Write();
    
    //hImpactParameter_Nfrag_vs_Energy_scaled ->Write();
    
	fout->Close();
}