# QA tool analysis of AAMCC or DCM root files

1. Create build folder in aamcc_to_mcini
2. cd build
3. cmake ..
4. make
5. Copy these files
    * aamcc.png
    * AAMCC_run.py
    * QA_script

from the main folder to the build folder you created on step 1

6. Change in QA_script
    * PathToMcini
    * PathToDcmAamcc
    * PathToQA

to your system paths 

8. python ./AAMCC_run.py
