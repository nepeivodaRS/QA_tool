# QA tool analysis of AAMCC or DCM root files

1. Create build folder in aamcc_to_mcini
2. cd build
3. $your_system_path/QA_TOOL/aamcc_to_mcini/macro/config.sh
4. source root_6_20
5. cmake ..
6. make
7. Copy these files
    * aamcc.png
    * AAMCC_run.py
    * QA_script
    * mult_aamcc_to_mcini
    * mult_pdf

from the main folder to the build folder you created on step 1

8. Change in QA_script, mult_aamcc_to_mcini and mult_pdf
    * PathToMcini
    * PathToDcmAamcc
    * PathToQA

to your system paths 

9. python ./AAMCC_run.py
