#!/bin/bash

rm study/List-data.txt
(time ./render_linear 400 200 List_100 4 100) 2>> "study/List-data.txt"
(time ./render_linear 400 200 List_1000 4 1000) 2>> "study/List-data.txt"
(time ./render_linear 400 200 List_10000 4 10000) 2>> "study/List-data.txt"
