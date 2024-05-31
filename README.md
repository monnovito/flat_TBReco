# flat_TBReco
a simple way to extract flat results from TBReco C++ program. This version is specified for Test Beam with P0_RM1 and P2_M01 chambers.

1. DummyAna.cxx and DummyAna.h are modified class files which help us to extract flat result from TBReco
2. Substitute DummyAna.cxx in TBReco/Root with the one avaible on this repository
3. Substitute DummyAna.h in TBReco/Root with the one avaible in this repository
4. In TBReco.C, add DummyAna to the vector _dummy_analyses. 
```
//...code of TBReco.C...
_dummy_analyses.push_back(new DummyAna(V_CHAMBERS, _reader, TB_OPTION, runname));
//...code of TBReco.C...
```
5. Run TBReco with known terminal command: root -l -b 'TBReco.C+("run_ID")'
```
root -l -b 'TBReco.C+("2001")'
```
6. Find your data in the folder 'reco/2001/run2001_tbreco.root' with the tree named 'datatree'
   
OPTIONAL) use TTree_toPy.py code if you want to import tree data into python dictionary of numpy arrays (this requires uproot library). Use e.g. 'print(data.dtype)' on Python notebook to print data structures with keys of dictionary.
