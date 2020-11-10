# Devzilla

This is a personal fork of Mozilla's source code. The goal, currently, is not
to produce a functional web browser but rather get a deeper understanding of how
the various components of a web browser work together.

The source code in this repository is under the Mozilla Public License 2.0,
although some portions are older and date back to the Netscape Public Library.

# Requirements
libjpeg - http://libjpeg.sourceforge.net/

# Running
copy all shared objects into xpfe/bootstrap, then run ./apprunner with
LD\_LIBRARY\_PATH set properly

```
cd xpfe/bootstrap
LD_DEBUG=all LD_LIBRARY_PATH=. ./apprunner
```
