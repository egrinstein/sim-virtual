#! /bin/bash

make cleanout

# p cada programa
#   varia algoritmo
#      varia memoria fisica(128,256,512,1024,2048,4096,8mb,16mb)
#         varia pagina(8,16,32)
#                pega write e fault                    
# 2*3*3*8*4 = 576 data points
declare -a modes=('LRU' 'NRU' 'SEG')
declare -a memories=( 128 256 512 1024 2048 4096 8192 16384 )
declare -a pages=( 8 16 32 )
for i in logs/*.log 
do
    filename=$(basename "$i")
    filename="${filename%.*}"
    out=$filename
    out+=".txt"
	
    for mode in "${modes[@]}" 
    do
        for memory in "${memories[@]}" 
        do
            for page in "${pages[@]}" 
            do
				#echo $mode $i $page $memory 
				./sim-virtual $mode $i $page $memory  	
            done
        done
    done
done

make clean
