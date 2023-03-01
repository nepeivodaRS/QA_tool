# QA tool analysis of AAMCC or MCINI root files

1. go to qa_exec folder

2. Change in QA_script, mult_pdf and mult_aamcc_to_mcini
    * PathToQAtool

to your system path

3. Change in mcini_to_aamcc/file_formation.cc and QA_AAMCC/FragmentationInput_mcini.cc 
* R__LOAD_LIBRARY path to your libMcIniData.so location (https://github.com/OlegGolosov/mcini)

4. Install Tkinter: 
   * apt-get install python3-tk

5. Run QA tool in qa_exec folder by
   * python3.9 AAMCC_run.py
