void runAlpha_T(const std::string FileList)
{
  gROOT->LoadMacro("alpha_T.C");
  alpha_T obj(FileList);
  obj.Loop();
}
