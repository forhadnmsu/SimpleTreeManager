#include <string>
#include <iostream>

R__LOAD_LIBRARY(libfun4all_universal_output_manager)
R__LOAD_LIBRARY(libcalibrator)
R__LOAD_LIBRARY(libktracker)

int run(const char* fn_udst="/data2/e1039/dst/run_006178/run_006178_spill_001951171_spin.root") {
    Fun4AllServer* se = Fun4AllServer::instance();
    // se->Verbosity(1);  // Optionally set verbosity level if needed
    Fun4AllInputManager *in = new Fun4AllDstInputManager("DUMMY");
    se->registerInputManager(in);
    in->fileopen(fn_udst);

    TString cmd = Form("basename %s | cut -c5-11", fn_udst);
    TString run_id_str = gSystem->GetFromPipe(cmd);
    run_id_str.Chop(); // Remove any trailing newline characters
    int run_id = run_id_str.Atoi();

    std::cout << "Run ID: " << run_id << std::endl;

    recoConsts* rc = recoConsts::instance();
    //rc->set_IntFlag("RUNNUMBER", run_id);
    rc->set_IntFlag("RUNNUMBER", 6178);
   
    CalibDriftDist* cal_dd = new CalibDriftDist();
    se->registerSubsystem(cal_dd);


    int compressionLevel = 1;  // Compression level (0-9)
    int basketSize = 32000;  // Basket size in bytes
    int autoFlush = 0;  // Auto flush size


    Fun4AllUniversalOutputManager* tree = new Fun4AllUniversalOutputManager();
    tree->SetTreeName("tree");
    tree->SetFileName(Form("data/out_kLZMA_%d_%dkb_flush%d.root",  compressionLevel, basketSize / 1000, autoFlush));
    //tree->SetDimuonMode(true);
    tree->SetCompressionLevel(compressionLevel);
    tree->SetBasketSize(basketSize);
    tree->SetAutoFlush(autoFlush);
    se->registerOutputManager(tree);

    se->run();
    se->End();

    // Do not delete se; // Removing manual deletion of singleton

    return 0;
}

