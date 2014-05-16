#!/usr/bin/env Rscript
# load the package
library(igraph)
sink("/home/mua193/Desktop/lfr_benchmark/set_4/igraph_results/im_lp_results")

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_s_0.1.net", format="pajek")
r <- scan("1000_s_0.1_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)

cat("Infomap: 1000_s_0.1\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_s_0.1\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")



###########################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_s_0.2.net", format="pajek")
r <- scan("1000_s_0.2_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 1000_s_0.2\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_s_0.2\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

######################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_s_0.3.net", format="pajek")
r <- scan("1000_s_0.3_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 1000_s_0.3\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_s_0.3\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_s_0.4.net", format="pajek")
r <- scan("1000_s_0.4_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 1000_s_0.4\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_s_0.4\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

##############################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_s_0.5.net", format="pajek")
r <- scan("1000_s_0.5_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 1000_s_0.5\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_s_0.5\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###############################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_s_0.6.net", format="pajek")
r <- scan("1000_s_0.6_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 1000_s_0.6\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_s_0.6\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

#############################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_s_0.7.net", format="pajek")
r <- scan("1000_s_0.7_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 1000_s_0.7\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", max_im, "\n")
cat("\n")

cat("Label Propagation: 1000_s_0.7\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###########################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_s_0.8.net", format="pajek")
r <- scan("1000_s_0.8_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)

cat("Infomap: 1000_s_0.8\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_s_0.8\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

#######################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_b_0.1.net", format="pajek")
r <- scan("1000_b_0.1_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)

cat("Infomap: 1000_b_0.1\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_b_0.1\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")



###########################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_b_0.2.net", format="pajek")
r <- scan("1000_b_0.2_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 1000_b_0.2\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_b_0.2\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

######################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_b_0.3.net", format="pajek")
r <- scan("1000_b_0.3_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 1000_b_0.3\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_b_0.3\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_b_0.4.net", format="pajek")
r <- scan("1000_b_0.4_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 1000_b_0.4\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_b_0.4\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

##############################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_b_0.5.net", format="pajek")
r <- scan("1000_b_0.5_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 1000_b_0.5\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_b_0.5\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###############################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_b_0.6.net", format="pajek")
r <- scan("1000_b_0.6_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 1000_b_0.6\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_b_0.6\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

#############################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_b_0.7.net", format="pajek")
r <- scan("1000_b_0.7_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 1000_b_0.7\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_b_0.7\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###########################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="1000_b_0.8.net", format="pajek")
r <- scan("1000_b_0.8_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)

cat("Infomap: 1000_b_0.8\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 1000_b_0.8\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###########################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_s_0.1.net", format="pajek")
r <- scan("5000_s_0.1_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)

cat("Infomap: 5000_s_0.1\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_s_0.1\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")



###########################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_s_0.2.net", format="pajek")
r <- scan("5000_s_0.2_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 5000_s_0.2\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_s_0.2\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

######################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_s_0.3.net", format="pajek")
r <- scan("5000_s_0.3_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 5000_s_0.3\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_s_0.3\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_s_0.4.net", format="pajek")
r <- scan("5000_s_0.4_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 5000_s_0.4\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_s_0.4\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

##############################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_s_0.5.net", format="pajek")
r <- scan("5000_s_0.5_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 5000_s_0.5\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_s_0.5\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###############################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_s_0.6.net", format="pajek")
r <- scan("5000_s_0.6_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 5000_s_0.6\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_s_0.6\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

#############################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_s_0.7.net", format="pajek")
r <- scan("5000_s_0.7_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 5000_s_0.7\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_s_0.7\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###########################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_s_0.8.net", format="pajek")
r <- scan("5000_s_0.8_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)

cat("Infomap: 5000_s_0.8\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_s_0.8\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

####################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_b_0.1.net", format="pajek")
r <- scan("5000_b_0.1_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)

cat("Infomap: 5000_b_0.1\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_b_0.1\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")



###########################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_b_0.2.net", format="pajek")
r <- scan("5000_b_0.2_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 5000_b_0.2\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_b_0.2\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

######################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_b_0.3.net", format="pajek")
r <- scan("5000_b_0.3_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 5000_b_0.3\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_b_0.3\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###################################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_b_0.4.net", format="pajek")
r <- scan("5000_b_0.4_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 5000_b_0.4\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_b_0.4\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

##############################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_b_0.5.net", format="pajek")
r <- scan("5000_b_0.5_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 5000_b_0.5\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_b_0.5\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###############################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_b_0.6.net", format="pajek")
r <- scan("5000_b_0.6_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 5000_b_0.6\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_b_0.6\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

#############################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_b_0.7.net", format="pajek")
r <- scan("5000_b_0.7_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)


cat("Infomap: 5000_b_0.7\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_b_0.7\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

###########################################################

nmi_im <- vector()
nmi_lp <- vector()
g <- read.graph(file="5000_b_0.8.net", format="pajek")
r <- scan("5000_b_0.8_comm.dat", sep="\n")
for(i in 1:50)
{
	im <- infomap.community(g)
	lp <- label.propagation.community(g)
	nmi_im[i] <- compare(r, membership(im), method="nmi")	
	nmi_lp[i] <- compare(r, membership(lp), method="nmi")
}

mean_im <- mean(nmi_im)
mean_lp <- mean(nmi_lp)

sd_im <- sd(nmi_im)
sd_lp <- sd(nmi_lp)

cv_im <- (sd_im / mean_im) * 100
cv_lp <- (sd_lp / mean_lp) * 100

mean_im <- round(mean_im, digits = 4)
mean_lp <- round(mean_lp, digits = 4)

sd_im <- round(sd_im, digits = 4)
sd_lp <- round(sd_lp, digits = 4)

cv_im <- round(cv_im, digits = 4)
cv_lp <- round(cv_lp, digits = 4)

max_im <- which.max(nmi_im)
max_lp <- which.max(nmi_lp)

cat("Infomap: 5000_b_0.8\n")
cat("Mean = ", mean_im, "\n")
cat("Std dev = ", sd_im, "\n")
cat("CV = ", cv_im, "\n")
cat("Best = ", nmi_im[max_im], "\n")
cat("\n")

cat("Label Propagation: 5000_b_0.8\n")
cat("Mean = ", mean_lp, "\n")
cat("Std dev = ", sd_lp, "\n")
cat("CV = ", cv_lp, "\n")
cat("Best = ", nmi_lp[max_lp], "\n")
cat("\n")

#####################################################

sink()
