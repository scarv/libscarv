#!/bin/bash

# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which
# can be found at https://opensource.org/licenses/MIT (or should be included
# as LICENSE.txt within the associated archive or repository).

if [ -z ${REPO_HOME} ] ; then
  echo "REPO_HOME environment variable undefined: aborting" ; exit
fi

python3 -m venv --clear ${REPO_HOME}/build/venv

source ${REPO_HOME}/build/venv/bin/activate

python3 -m pip install --upgrade pip
python3 -m pip install -r ${REPO_HOME}/requirements.txt
