#!/usr/bin/env bash


rosrun camera_calibration cameracalibrator.py --size 8x6 --square 0.025 image:=/camera_front/rgb_publisher/color/image


#/tmp/calibrationdata.tar.gz

# tar -xvzf /tmp/calibrationdata.tar.gz
# mv ost.yaml color.yaml

# fix color.yaml
# camera_name: color

#https://qiita.com/srs/items/416aa78f2c679ddb7c52
