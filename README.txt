SHNMBA004
Mbaliyethemba Shangase
CSC3022H
1 May 2019

An Image class which supports simple operations on pairs of PGM images.

Operations:
- `-a I1 I2` (add I1 and I2)
- `-s I1 I2` (subtract I2 from I1)
- `-i I1` (invert I1)
- `-l I1 I2` (mask I1 with I2)
- `-t I1 f` (threshold I1 with integer value f)

Usage:
Compile with `make`. 
Run with `./imageops <option> [image1name] [image2name] [OuitputImagename]` for -`a` `-s` and `-l`.  
Run with `./imageops -i [image1name] [OuitputImagename]` for `-i`.  
and run with `./imageops -t [image1name] f [OuitputImagename]` for `-t`.  
Compile tests with `make run_test`. 
Run tests with `./UnitTests`.

Files:
1. `image.h`: 
header file containing declarations of the class methods and operators.

2. `image.cpp`: 
source file containing definitions of the methods and operators declared in the header file.

3. `driver.cpp`: 
driver file containing the **main** function. **main** parses the command line arguments to determine which operation to run, retrieves the input and output image file names, peroforms the operation and saves the output image to disk.

4. `UnitTests.cpp`:
file which tests if the image class methods and operators are functioning correctly.

5. `catch.hpp`:
unit testing framework for `test.cpp`.

6. `Makefile`:
compilation and clean-up automation.
