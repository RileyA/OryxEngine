#!/bin/bash

DIRECTORY=$(cd `dirname $0` && pwd)
ORIGINALDIR=$(pwd)

cd `dirname $0`
cd src
rm .sconsign.dblite
scons -Q -j 4
cd ALSubsystem
rm .sconsign.dblite
scons -Q -j 4
cd ../ENetSubsystem
rm .sconsign.dblite
scons -Q -j 4
cd ../OISSubsystem
rm .sconsign.dblite
scons -Q -j 4
cd ../OgreSubsystem
rm .sconsign.dblite
scons -Q -j 4
cd ../ChaiscriptSubsystem
rm .sconsign.dblite
scons -Q -j 4
cd ../BulletSubsystem
rm .sconsign.dblite
scons -Q -j 4
#cd ../ServerTest
#scons -Q -j 4

cd $ORIGINALDIR
