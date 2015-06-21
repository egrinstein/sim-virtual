require(ggplot2)

sim_data <- read.csv("sim.csv",header=TRUE)


sim_data_8kb <- sim_data[sim_data$TamanhoPagina == 8,]

for (program in c("simulador","matriz","compressor","compilador")){
	sim_data <- sim_data_8kb[sim_data_8kb$Arquivo == program,]
	i <- 1
	jpeg(paste(program,".jpeg",sep=""))
	algs <- c("LRU","NRU","SEG")
	colors <- c("red","green","blue")
	for (algorithm in algs) {
		Page_Faults <- sim_data$PageFaults[sim_data$Algoritmo == algorithm]
		Memoria_Total <- sim_data$Memoria[sim_data$Algoritmo == algorithm]
		if (i == 1){
			plot(Memoria_Total,Page_Faults,col=colors[i],type="b",pch=14+i)
		} else{
			lines(Memoria_Total,Page_Faults,col=colors[i],type="b",pch=14+i)
		}
		i <- i + 1
	}
	legend("topright",lty=1,algs,col=colors,bty='n', cex=1.4, pch=c(15,16,17))
	dev.off()
}

