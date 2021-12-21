#!/bin/sh

pkill -x sxhkd
sxhkd &

pkill -x dwmblocks
dwmblocks &

# Uncomment if using dwmblocks mpd module
# while true; do
#         pkill -RTMIN+4 dwmblocks
# 		mpc idle
# done &
