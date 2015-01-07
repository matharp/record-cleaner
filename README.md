Record Cleaner for AoC
======================

A simple tool for easier management of Age of Empires recorded game files (.mgz).
AocZone thread: http://aoczone.net/viewtopic.php?f=104&t=97608.

Build and Usage Instructions
============================

Compile rec_cleaner.c on Windows:

gcc -o rclean rec_cleaner.c recanalyst.c -lgdi32

Keep the binary and rclean.py in the SaveGame directory along with recanalyst.dll and download_path.txt directory before running the script.

For distribution for systems without Python installed, py2exe is used for creating the software package. Distribute the dist and lib directories. Further instruction in the AoCZone thread.

Credits
=======

Biegleux for the Recanalyst library.
