/*
 * Merge a number of .root files into one output file.
 *
 * Execute the function like this from the command line:
 * echo outputfile.root input1.root input2.root... | root -b merge_root.C+
 *
 * This macro assumes that the TTree is named 'TMBTree'. Change
 * the corresponding line below if this is different for your case.
 */

#include <string>
#include <iostream>

#include "TList.h"
#include "TFile.h"
#include "TTree.h"

// Change this line if your TTree has a different name
const char *TreeName = "tauveto";
	

void merge_root()
{
    using namespace std;

    string outfile;
    cin >> outfile;

    TList tree_list;
    std::string filename;

    Int_t total_events = 0;

    while(cin >> filename) {
        TFile *f = new TFile(filename.c_str());

        if(TTree *tree = (TTree *)f->Get(TreeName)) {

            cout << "Adding file: " << filename << endl;
            tree_list.Add(tree);

            total_events += (Int_t )tree->GetEntries();

        } else {
	  cout << "File has no TTree named " << TreeName << endl;
        }
    }

    cout << "Opening output file: " << outfile << endl;
    TFile output(outfile.c_str(), "RECREATE");

    cout << "Merging trees...patience..." << endl;
    TTree::MergeTrees(&tree_list);
    output.Write();
    output.Close();

    cout << "Total Events: " << total_events << endl;
}
