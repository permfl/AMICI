#!/bin/bash
# Run jupyter notebooks as given on command line, show output only on error. 
# If a directory is provided, run all contained notebooks non-recursively.
set -x
SCRIPT_PATH=$(dirname $BASH_SOURCE)
AMICI_PATH=$(cd $SCRIPT_PATH/.. && pwd)

runNotebook () {
    tempfile=$(mktemp)
    jupyter nbconvert --debug --stdout --execute --to markdown $@ &> $tempfile
    ret=$?
    if [[ $ret != 0 ]]; then cat $tempfile; fi
    rm $tempfile
    exit $ret
}

if [ $# -eq 0 ]; then
    echo "Usage: $0 [notebook.ipynb] [dirContainingNotebooks/]"
    exit 1
fi

source ${AMICI_PATH}/build/venv/bin/activate
pip3 show ipython || (pip3 install --upgrade jupyter && python3 -m ipykernel install --name amici --display-name "Python (amici)")

for arg in "$@"; do
    if [ -d $arg ]; then
        for notebook in $(ls -1 $arg | grep -E ipynb\$); do
            runNotebook $arg/$notebook
        done
    elif [ -f $arg ]; then
        runNotebook $arg
    fi
done
