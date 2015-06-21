
sim_data <- read.csv("sim.csv",header=TRUE)


gen_writes_by_memory <- function(sim_data){
	sim_data_8kb <- sim_data[sim_data$TamanhoPagina == 8,]

	for (program in c("simulador","matriz","compressor","compilador")){
		sim_data <- sim_data_8kb[sim_data_8kb$Arquivo == program,]
		i <- 1
		jpeg(paste(program,".jpeg",sep=""))
		algs <- c("LRU","NRU","SEG")
		colors <- c("red","green","blue")
		for (algorithm in algs) {
			Pages_Written <- sim_data$PaginasEscritas[sim_data$Algoritmo == algorithm]
			Memoria_Total <- sim_data$Memoria[sim_data$Algoritmo == algorithm]
			if (i == 1){
				plot(Memoria_Total,log='x',ylim=c(1,max(Pages_Written)),Pages_Written,col=colors[i],xaxt='n',type="b",pch=14+i,xlab="Memória disponível",ylab="Páginas escritas em disco",main="Páginas Escritas/Memória disponível (Tam.Página=8KB)")
			} else{
				lines(Memoria_Total,Pages_Written,col=colors[i],type="b",pch=14+i)
			}
			axis(1,at=Memoria_Total,labels=T)
			#axis(2,at=c(1,max(Pages_Written)),labels=T)
			i <- i + 1
		}
		legend("topright",lty=1,algs,col=colors,bty='n', cex=1.4, pch=c(15,16,17))
		dev.off()
	}
}

gen_writes_by_memory(sim_data)
