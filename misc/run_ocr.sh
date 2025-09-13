#!/bin/bash
work_path="/home/ocr"
echo ${work_path}
cd ${work_path}
source ocr_env/bin/activate
if [ $# -eq 0 ]; then
    echo "没有传入参数"
    exit 1
fi
python rapid_ocr_table.py $1
