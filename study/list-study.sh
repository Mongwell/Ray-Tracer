#!/bin/bash

rm study/List-data.txt
(time ./render_linear 200 400 1 100) 2>> "study/List-data.txt"
(time ./render_linear 200 400 1 1000) 2>> "study/List-data.txt"
(time ./render_linear 200 400 1 10000) 2>> "study/List-data.txt"
