#!/usr/bin/env bash

set -e
set -x

ціль герман.ll скомпілювати герман.ц
clang++ -o герман герман.ll hermann.cpp
./герман