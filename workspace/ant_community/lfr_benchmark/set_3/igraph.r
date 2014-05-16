#!/usr/bin/env Rscript
# load the package
library(igraph)
sink("/home/mua193/Desktop/lfr_benchmark/set_3/igraph_results/igraph")

g <- read.graph(file="1000_s_0.1.net", format="pajek")
r <- scan("1000_s_0.1_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_s_0.1\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_s_0.1\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_s_0.1\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_s_0.1\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")



###########################################################################


g <- read.graph(file="1000_s_0.2.net", format="pajek")
r <- scan("1000_s_0.2_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_s_0.2\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_s_0.2\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_s_0.2\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_s_0.2\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

######################################################################


g <- read.graph(file="1000_s_0.3.net", format="pajek")
r <- scan("1000_s_0.3_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_s_0.3\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_s_0.3\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_s_0.3\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_s_0.3\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")


###################################################################

g <- read.graph(file="1000_s_0.4.net", format="pajek")
r <- scan("1000_s_0.4_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_s_0.4\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_s_0.4\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_s_0.4\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_s_0.4\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

##############################################################

g <- read.graph(file="1000_s_0.5.net", format="pajek")
r <- scan("1000_s_0.5_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_s_0.5\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_s_0.5\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_s_0.5\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_s_0.5\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")


###############################################################

g <- read.graph(file="1000_s_0.6.net", format="pajek")
r <- scan("1000_s_0.6_comm.dat", sep="\n")
fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_s_0.6\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_s_0.6\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_s_0.6\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_s_0.6\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

#############################################################

g <- read.graph(file="1000_s_0.7.net", format="pajek")
r <- scan("1000_s_0.7_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_s_0.7\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_s_0.7\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_s_0.7\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_s_0.7\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")


###########################################################

g <- read.graph(file="1000_s_0.8.net", format="pajek")
r <- scan("1000_s_0.8_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_s_0.8\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_s_0.8\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_s_0.8\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_s_0.8\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")


#######################################################

g <- read.graph(file="1000_b_0.1.net", format="pajek")
r <- scan("1000_b_0.1_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_b_0.1\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_b_0.1\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_b_0.1\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_b_0.1\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")



###########################################################################


g <- read.graph(file="1000_b_0.2.net", format="pajek")
r <- scan("1000_b_0.2_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_b_0.2\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_b_0.2\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_b_0.2\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_b_0.2\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

######################################################################


g <- read.graph(file="1000_b_0.3.net", format="pajek")
r <- scan("1000_b_0.3_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_b_0.3\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_b_0.3\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_b_0.3\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_b_0.3\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")


###################################################################

g <- read.graph(file="1000_b_0.4.net", format="pajek")
r <- scan("1000_b_0.4_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_b_0.4\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_b_0.4\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_b_0.4\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_b_0.4\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

##############################################################

g <- read.graph(file="1000_b_0.5.net", format="pajek")
r <- scan("1000_b_0.5_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_b_0.5\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_b_0.5\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_b_0.5\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_b_0.5\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")


###############################################################

g <- read.graph(file="1000_b_0.6.net", format="pajek")
r <- scan("1000_b_0.6_comm.dat", sep="\n")
fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_b_0.6\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_b_0.6\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_b_0.6\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_b_0.6\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

#############################################################

g <- read.graph(file="1000_b_0.7.net", format="pajek")
r <- scan("1000_b_0.7_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_b_0.7\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_b_0.7\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_b_0.7\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_b_0.7\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")


###########################################################

g <- read.graph(file="1000_b_0.8.net", format="pajek")
r <- scan("1000_b_0.8_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 1000_b_0.8\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 1000_b_0.8\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 1000_b_0.8\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 1000_b_0.8\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

##############################################################

g <- read.graph(file="5000_s_0.1.net", format="pajek")
r <- scan("5000_s_0.1_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_s_0.1\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_s_0.1\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_s_0.1\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_s_0.1\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")



###########################################################################


g <- read.graph(file="5000_s_0.2.net", format="pajek")
r <- scan("5000_s_0.2_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_s_0.2\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_s_0.2\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_s_0.2\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_s_0.2\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

######################################################################


g <- read.graph(file="5000_s_0.3.net", format="pajek")
r <- scan("5000_s_0.3_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)


nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")


cat("FastGreedy: 5000_s_0.3\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_s_0.3\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_s_0.3\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")


###################################################################

g <- read.graph(file="5000_s_0.4.net", format="pajek")
r <- scan("5000_s_0.4_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_s_0.4\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_s_0.4\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_s_0.4\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_s_0.4\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

##############################################################

g <- read.graph(file="5000_s_0.5.net", format="pajek")
r <- scan("5000_s_0.5_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_s_0.5\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_s_0.5\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_s_0.5\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_s_0.5\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")


###############################################################

g <- read.graph(file="5000_s_0.6.net", format="pajek")
r <- scan("5000_s_0.6_comm.dat", sep="\n")
fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_s_0.6\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_s_0.6\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_s_0.6\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_s_0.6\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

#############################################################

g <- read.graph(file="5000_s_0.7.net", format="pajek")
r <- scan("5000_s_0.7_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_s_0.7\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_s_0.7\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_s_0.7\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_s_0.7\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")


###########################################################

g <- read.graph(file="5000_s_0.8.net", format="pajek")
r <- scan("5000_s_0.8_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_s_0.8\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_s_0.8\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_s_0.8\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_s_0.8\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

#############################################################

g <- read.graph(file="5000_b_0.1.net", format="pajek")
r <- scan("5000_b_0.1_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_b_0.1\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_b_0.1\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_b_0.1\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_b_0.1\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")



###########################################################################


g <- read.graph(file="5000_b_0.2.net", format="pajek")
r <- scan("5000_b_0.2_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_b_0.2\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_b_0.2\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_b_0.2\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_b_0.2\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

######################################################################


g <- read.graph(file="5000_b_0.3.net", format="pajek")
r <- scan("5000_b_0.3_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_b_0.3\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_b_0.3\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_b_0.3\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_b_0.3\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")


###################################################################

g <- read.graph(file="5000_b_0.4.net", format="pajek")
r <- scan("5000_b_0.4_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_b_0.4\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_b_0.4\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_b_0.4\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_b_0.4\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

##############################################################

g <- read.graph(file="5000_b_0.5.net", format="pajek")
r <- scan("5000_b_0.5_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_b_0.5\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_b_0.5\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_b_0.5\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_b_0.5\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")


###############################################################

g <- read.graph(file="5000_b_0.6.net", format="pajek")
r <- scan("5000_b_0.6_comm.dat", sep="\n")
fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_b_0.6\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_b_0.6\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_b_0.6\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_b_0.6\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

#############################################################

g <- read.graph(file="5000_b_0.7.net", format="pajek")
r <- scan("5000_b_0.7_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_b_0.7\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_b_0.7\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_b_0.7\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_b_0.7\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")


###########################################################

g <- read.graph(file="5000_b_0.8.net", format="pajek")
r <- scan("5000_b_0.8_comm.dat", sep="\n")

fg <- fastgreedy.community(g)
lv <- multilevel.community(g)
wt <- walktrap.community(g)
eg <- leading.eigenvector.community(g)

nmi_fg <- compare(r, membership(fg), method="nmi")
nmi_lv <- compare(r, membership(lv), method="nmi")
nmi_wt <- compare(r, membership(wt), method="nmi")
nmi_eg <- compare(r, membership(eg), method="nmi")

cat("FastGreedy: 5000_b_0.8\n")
cat("NMI = ", nmi_fg, "\n")
cat("\n")

cat("Louvain: 5000_b_0.8\n")
cat("NMI = ", nmi_lv, "\n")
cat("\n")

cat("Walktrap: 5000_b_0.8\n")
cat("Walktrap = ", nmi_wt, "\n")
cat("\n")

cat("Eigenvector: 5000_b_0.8\n")
cat("NMI = ", nmi_eg, "\n")
cat("\n")

sink()
