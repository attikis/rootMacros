#!/usr/bin env python
import ROOT

### Function to calculate efficiency of two numbers with Bayesian method.
def bayesDivide(passed, total):
    hp = ROOT.TH1F("tmp_passed", "", 1, 0, 1)
    ht = ROOT.TH1F("tmp_total", "", 1, 0, 1)
    hp.SetBinContent(1, passed)
    ht.SetBinContent(1, total)
    eff = ROOT.TGraphAsymmErrors()
    eff.BayesDivide(hp, ht, "xxx")
    return eff

# ### Usage example
# effObj = bayesDivide(50, 100)
# eff = effObj.GetY()[0]
# eff_errUp = effObj.GetEYhigh()[0]
# eff_errDown = effObj.GetEYlow()[0]
# print eff, eff_errUp, eff_errDown
