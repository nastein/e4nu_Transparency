This file was created by Jacob Smith (smithja) at 4:23 pm US Central Time.

To run these files in the scripts/ directory, you must first start root.
After doing so, you can execute any of the files in the scripts/ 
directory by doing '.x <MACRO NAME>.C("<PATH TO ROOT DATA FILE>")'.
To run all of the scripts (or only some depending on which files are
commented out/in in the run_all_scripts.C file) you can do
'.x run_all_scripts.C("<PATH TO ROOT DATA FILE>")'.

smithja (11/02/2021):
Today I added in new plotting scripts for the CLAS data. Since the
CLAS experiment does not have the ability to separate events into
interaction components or FSI vs. no FSI contributions like GENIE
MC does, I have added the h1_el_mom.C and h1_prot_mom.C plotting
scripts. These plotting scripts take in the same histograms as
their intSeparated and intAndFSISeparated script counterparts.
However, when running genie_analysis, the data populates 
histograms according to which interaction. When running CLAS data,
Interaction = 0. The h1_el_mom.C and h1_prot_mom.C files have 
simply used the Interaction = 0 histograms and therefore only need
to combine each of the sector distributions (instead of the sectors,
interactions, and FSI/no FSI distributions).

Today I also added the functionality in the intSeparated and
intAndFSISeparated plotting scripts to only accept GENIE MC files.
I have also added code to run_all_scripts.C so that if 'genie' or
'data' is not the first non-underscore word in the file name 
(excluding file path), run_all_scripts.C will print an informative 
output and not call any of the plotting scripts.
