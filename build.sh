#!/bin/bash
clear
make clean
make
ldd "bin\server.exe"