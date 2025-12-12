#!/bin/bash

#set -e
./build/slang examples/basics.slang
./build/slang examples/functions.slang
./build/slang examples/logic.slang
#export SLANG_LIVE_RENDER=1
./build/slang examples/synths.slang