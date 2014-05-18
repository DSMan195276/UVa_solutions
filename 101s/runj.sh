#!/bin/bash
java Main < test.txt | diff -y -d ./ans.txt -

