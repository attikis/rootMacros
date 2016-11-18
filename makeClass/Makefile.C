{
  // Execute the Makefile by: root[0] .x Makefile.C
  std::cout << "*** Attempting to complile all libraries..." << std::endl;
  gSystem->CompileMacro("bareROOTmacro.C");
  //  gSystem->CompileMacro("?.C");
  std::cout << "*** Compilation was successful!" << std::endl;
}
