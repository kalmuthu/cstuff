#!/bin/bash


TARGETS="make-system-test vtest cutils butils tutils stack iptools"

DIR=`dirname $0`

if [ "x$DIR" != "x" ]; then
  cd $DIR
fi

. common-build.sh



