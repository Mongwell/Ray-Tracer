#!/bin/bash

rm study/BVH-data.txt
(time ./render 400 200 BVH_100 4 100) 2>> "study/BVH-data.txt"
(time ./render 400 200 BVH_1000 4 1000) 2>> "study/BVH-data.txt"
(time ./render 400 200 BVH_10000 4 10000) 2>> "study/BVH-data.txt"
