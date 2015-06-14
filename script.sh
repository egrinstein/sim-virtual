#!/bin/sh

make

# p cada programa
#   varia algoritmo
#      varia memoria fisica(128,256,512,1024,2048,4096,8mb,16mb)
#         varia pagina(8,16,32)
#                pega write e fault                    
# 2*3*3*8*4 = 576 data points
modes=('LRU' 'NRU' 'SEG')
memories=(128 256 512 1024 2048 4096 8192 16384)
pages=(8 16 32)
for i in logs/*.log do
    for mode in modes do
        for memory in memories do
            for page in pages do
                sim-virtual $mode $i $page $memory
            done
        done
    done
done

make clean
