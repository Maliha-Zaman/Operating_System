#!/bin/bash


mkdir -p last7days last30days older

find  -type f -mtime -7 -exec mv {} last7days/ \;
find  -type f -mtime +7 -mtime -30 -exec mv {} last30days/ \;
find  -type f -mtime +30 -exec mv {} older/ \;
