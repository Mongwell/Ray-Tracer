#!/bin/bash

rm study/BVH-data.txt
(time ./render 200 400 1 100) 2>> "study/BVH-data.txt"
(time ./render 200 400 1 1000) 2>> "study/BVH-data.txt"
(time ./render 200 400 1 10000) 2>> "study/BVH-data.txt"
