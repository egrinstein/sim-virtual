
sim_data <- read.csv("sim.csv",header=TRUE)


gen_writes_per_fault_by_memory <- function(sim_data){
	sim_data_8kb <- sim_data[sim_data$TamanhoPagina == 8,]

	for (program in c("simulador","matriz","compressor","compilador")){
		sim_fixed_prog <- sim_data_8kb[sim_data_8kb$Arquivo == program,]
		i <- 1
		jpeg(paste(program,".jpeg",sep=""))
		algs <- c("LRU","NRU","SEG")
		colors <- c("red","green","blue")
		ylimit <- max(sim_fixed_prog$PaginasEscritas/sim_fixed_prog$PageFaults)
		for (algorithm in algs) {
			print(algorithm)
			sim_fixed_algorithm <- sim_fixed_prog[sim_fixed_prog$Algoritmo == algorithm,]
			Page_Faults <- sim_fixed_algorithm$PageFaults
			Pages_Written <- sim_fixed_algorithm$PaginasEscritas
			Pages_written_per_fault <- Pages_Written/Page_Faults
			Memoria_Total <- sim_fixed_algorithm$Memoria
			if (i == 1){
				plot(Memoria_Total,log='x',ylim=c(0.0,ylimit),Pages_written_per_fault,col=colors[i],xaxt='n',type="b",pch=14+i,xlab="Memória disponível",ylab="Páginas escritas page fault",main="(Páginas Escritas/ page fault)/Memória disponível (Página=8KB)")
			} else{
				print("Mamae")
				lines(Memoria_Total,Pages_written_per_fault,col=colors[i],type="b",pch=14+i)
			}
			axis(1,at=Memoria_Total,labels=T)
			#axis(2,at=c(1,max(Page_Faults)),labels=T)
			i <- i + 1
		}
		legend("topright",lty=1,algs,col=colors,bty='n', cex=1.4, pch=c(15,16,17))
		dev.off()
	}
}

gen_faults_by_page <- function(data){

	for (program in c("simulador","matriz","compressor","compilador")){
		sim_data <- data[data$Arquivo == program,]
		algs <- c("LRU","NRU","SEG")
		colors <- c("red","green","blue")
		page_sizes = c(8,16,32)
		for (algorithm in algs) {
			i <- 1	
			sim_fixed_alg <- sim_data[sim_data$Algoritmo == algorithm,]
			jpeg(paste(program,'-',algorithm,".jpeg",sep=""))
			ylimit = max(sim_fixed_alg$PageFaults)
			for (page_size in page_sizes){
				sim_fixed_size <- sim_fixed_alg[sim_fixed_alg$TamanhoPagina ==page_size,]
				Memoria_Total <- sim_fixed_size$Memoria
				Page_Faults <- sim_fixed_size$PageFaults
				if (i == 1){
					plot(Memoria_Total,log='x',ylim=c(1,ylimit),Page_Faults,col=colors[i],xaxt='n',type="b",pch=14+i,xlab="Memória disponível",ylab="Page Faults",main="Page Faults/Memória disponível")
					options(scipen=5)
				} else{
					lines(Memoria_Total,Page_Faults,col=colors[i],type="b",pch=14+i)
				}
				axis(1,at=Memoria_Total,labels=T)
				i <- i + 1
			}		
			legend("topright",lty=1,legend=c("8KB","16KB","32KB"),col=colors,bty='n', cex=1.4, pch=c(15,16,17))
			dev.off()
		}
	}
}
gen_writes_per_fault_by_memory(sim_data)
