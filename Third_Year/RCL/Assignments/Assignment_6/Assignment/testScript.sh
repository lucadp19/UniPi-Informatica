#!/bin/bash

PORT=6789
TEST_DIR=$(dirname "$(realpath $0)")
cd /tmp
wget http://localhost:${PORT}/${TEST_DIR}/testFile.txt