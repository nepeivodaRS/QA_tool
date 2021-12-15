# An application to run a QA analysis of AAMCC or DCM root files

1. Create build folder in aamcc_to_mcini
2. cd build
3. cmake ..
4. make
5. copy these files to the build folder
  1) aamcc.png
  2) AAMCC_run.py
  3) QA_script
  to the build folder
6. change in QA_script
  1) PathToMcini
  2) PathToDcmAamcc
  3) PathToQA
  to your system paths 
8. python ./AAMCC_run.py
