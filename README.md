# SEMPR - Examples
This project shows how to use and extend the existing sempr-library. This can be a bit tricky since we use the object relational mapping system "ODB". See  [sempr-tk/sempr](http://github.com/sempr-tk/sempr) for further details (and licensing information!).

## Using SEMPR
The `example.cpp` shows how to use SEMPR. More examples regarding the functionality of SEMPR can be found in the main project. The interesting part here is the [CMakeLists.txt](CMakeLists.txt) which shows how to find and use a previously installed SEMPR library. Basically, SEMPR provides a pkg-config file. Notice the `${SEMPR_CFLAGS_OTHER}`! These contain information about which database backend was used when compiling SEMPR, and must be used here, too.

> Note: I smell trouble. At some point we will compile with different settings, and wonder why things don't work out.

## TODO
- move example.cpp and CMakeLists into subfolder
- create separate example on how to extend sempr
- create another project that shows how to use multiple sempr-projects together
- CI for everything! Theres no better documentation than a working, tested script. :wink:
