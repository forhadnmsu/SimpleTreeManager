
 R__LOAD_LIBRARY(libfun4all_universal_output_manager)

int run(const char* fn_udst="/data2/e1039/dst/run_004621_spin.root") {
    Fun4AllServer* se = Fun4AllServer::instance();
    // se->Verbosity(1);  // Optionally set verbosity level if needed
    Fun4AllInputManager *in = new Fun4AllDstInputManager("DUMMY");
    se->registerInputManager(in);
    in->fileopen(fn_udst);

    Fun4AllUniversalOutputManager* tree = new Fun4AllUniversalOutputManager();
    tree->SetFileName("out.root");
    tree->SetTreeName("tree");
    se->registerOutputManager(tree);

    se->run();
    se->End();

    // Do not delete se; // Removing manual deletion of singleton

    return 0;
}

