#!/bin/bash
./probc < test.txt | diff -y ./ans.txt -

