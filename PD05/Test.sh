#!/bin/bash

search_dir=RootOut
for entry in "$search_dir"/*.root
do
  echo "$entry"
done