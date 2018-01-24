# SEMPR - Examples
This project shows how to use and extend the existing sempr-library. This can be a bit tricky since we use the object relational mapping system "ODB". See  [sempr-tk/sempr](http://github.com/sempr-tk/sempr) for further details (and licensing information!).

## Using SEMPR
The subfolder [simple_use](simple_use) contains an example setup on how to use SEMPR without extending its persistent object model.
More examples regarding the functionality of SEMPR can be found in the main project. The interesting part here is the [CMakeLists.txt](simple_use/CMakeLists.txt) which shows how to find and use a previously installed SEMPR library. Basically, SEMPR provides a pkg-config file. Notice the `${SEMPR_CFLAGS_OTHER}`! These contain information about which database backend was used when compiling SEMPR, and must be used here, too, to select the correct traits-definitions for extended datatypes (like geometries).

## Extending SEMPR
If you want to extend the persistent object model of SEMPR, i.e., create your own entities to store in the database, follow the example [here](new_entity). It shows how to find SEMPR and ODB (and includes a CMake-script for the latter), and how to compile, link and use a custom entity.

> Note: I smell trouble. At some point we will compile with different settings, and wonder why things don't work out.
SEMPR exports a variable called "database" within its [pkg-config-file](https://github.com/sempr-tk/sempr/src/sempr-core.pc.in) that can be used to determine which database backend has been used by the core. 


## TODO
- CI for everything! Theres no better documentation than a working, tested script. :wink:
