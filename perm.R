######################################################################
## Experiments with exact permutation tests for the mean in the two
## (independent) sample situation. We compare the two sample t-test,
## the Mann-Whitney U-test and the exact permutation test as well as
## the fast computations of it by Gebhard & Schmidt (1998) and by
## Kjäll.
##
## Author: Michael Höhle <http://www.math.su.se/~hoehle>
## Date: 2019-05-29
######################################################################

##Size of the two groups - assumption: let N[1] be the smaller
N <- c(8,10)
stopifnot(N[1] <= N[2])

##Fix seed
set.seed(123)
##Generate experiment
y1 <- rbeta(N[1],2,2)
y2 <- rbeta(N[2],2,2)
y <- c(y1,y2)

##Mean in each group
c(mu_group1=mean(y1), mu_group2=mean(y2))

######################################################################
## Compute some appropriate tests for the comparison of the two groups
######################################################################
##Simple t-test
t.test(y1,y2, alternative="greater")
##Mann-Whitney U-test (for independent samples!) - https://en.wikipedia.org/wiki/Mann–Whitney_U_test
wilcox.test(y1, y2 , paired=FALSE, correct=FALSE, exact=TRUE, alternative="greater")
##Number of permutations to investigate
choose(sum(N),N[1])
##Compute all permutations manually
perms <- combinat::combn(sum(N), m=N[1])
dist <- apply(perms, 2, function(i) sum(y[i]))
mean(dist>=sum(y1))

##Small helper function to write data to file in a format
##desired by the permtest program by Gebhard & Schmidt (1998)
write2file <- function(y1, y2, file_name="foo.txt") {
  f <- file(file.path("Data",file_name))
  writeLines(paste0(paste0(y1, collapse="\t"),"\n",paste0(y2, collapse="\t")),f)
  close(f)
}

##Write to file
write2file(y1, y2, file_name="foo.txt")
##Run the Software by Gebhard using the Green approximation
res <- system2("./Gebhard/bin/permtest", args="-ig Data/foo.txt", stdout=TRUE, stderr=TRUE)
cat(paste0(res, collapse="\n"))

## Trichtler approximation
res <- system2("./Gebhard/bin/permtest", args="-i Data/foo.txt", stdout=TRUE, stderr=TRUE)
cat(paste0(res, collapse="\n"))

##Same for the rank test. This should be the same value
##as the Mann-Whitney U test
res <- system2("./Gebhard/bin/permtest", args="-ir Data/foo.txt", stdout=TRUE, stderr=TRUE)
cat(paste0(res, collapse="\n"))

wilcox.test(y1, y2 , paired=FALSE, correct=FALSE, exact=TRUE, alternative="greater")$p.value

######################################################################
## Same, but now for a larger sample
######################################################################

N <- c(25,28)

set.seed(123)
y1 <- rbeta(N[1],2,2)
y2 <- rbeta(N[2],2,2)
y <- c(y1,y2)


##Use the Mann-Whitney U test
wilcox.test(y1, y2 , paired=FALSE, correct=FALSE, exact=FALSE, alternative="greater")

##Write to file
write2file(y1=y1, y2=y2, file_name="foo-large.txt")
## Green approximation (doesn't work - size too large (FEHLER: Zu
## viele Daten). One could look into the code and increase the
## threshold as it should work IMHO, but then one has to change the
## labelling index from unsigned int)
res <- system2("./Gebhard/bin/permtest", args="-ig Data/foo-large.txt", stdout=TRUE, stderr=TRUE)
cat(paste0(res, collapse="\n"))
choose(sum(N),N[1])
choose(sum(N),N[1]) > 4294967295

##Run the Software by Gebhard, use Trichtler approach
res <- system2("./Gebhard/bin/permtest", args="-i Data/foo-large.txt", stdout=TRUE, stderr=TRUE)
cat(paste0(res, collapse="\n"))

##Just run the Mann-Whitney U test
res <- system2("./Gebhard/bin/permtest", args="-ir Data/foo-large.txt", stdout=TRUE, stderr=TRUE)
cat(paste0(res, collapse="\n"))

##Compare with the asymptotic value
wilcox.test(y1, y2 , paired=FALSE, correct=FALSE, exact=FALSE, alternative="greater")$p.value

##For export to Python:
##cat(paste0("a = np.array([",paste0(y1, collapse=", "), "])"))
##cat(paste0("b = np.array([",paste0(y2, collapse=", "), "])"))
##Note: we get the following result using Lucas Kjälls program:
##p-value exact permutation test: 0.1979129829489084 (0.1979129829489084, 89450351099305.0, 903936161908052.0)
##Not clear if its a one or two-sided test, though.

######################################################################
##Values from Lucas Kjäll's python notebook
######################################################################
y1 <- c(2.5,  3.7, 4.2)
y2 <- c(8.2, 5.3, 7.6)
y <- c(y1, y2)
N <- c(length(y1), length(y2))

write2file(y1, y2, "foo-lk.txt")

##Run with the Green approach
##Run the software with the Trichtler approximation
res <- system2("./Gebhard/bin/permtest", args="-ig Data/foo-lk.txt", stdout=TRUE, stderr=TRUE)
cat(paste0(res, collapse="\n"))

##Run the software with the Trichtler approximation
res <- system2("./Gebhard/bin/permtest", args="-i Data/foo-lk.txt", stdout=TRUE, stderr=TRUE)
cat(paste0(res, collapse="\n"))

###########################################
# Simplest example for manual computation
###########################################

# set.seed(123)
# y1 <- rpois(10,5) #c(1,2)
# y2 <- rpois(8,5)# c(0,3)
# cat(paste0("a = np.array([",paste0(y1, collapse=", "), "])"))
# cat(paste0("b = np.array([",paste0(y2, collapse=", "), "])"))
# ##
# y1 <- y1[1:3]
# y2 <- y2[1:2]

##Some very simple data
y1 <- c(0,3,0)
y2 <- c(1,2,5)
y <- c(y1,y2)
N <- c(length(y1), length(y2))
y <- y-min(y)
y1 <- y[1:N[1]]
y2 <- y[(N[1]+1):sum(N)]
y1
y2
cat(paste0("a = np.array([",paste0(y1, collapse=", "), "])"))
cat(paste0("b = np.array([",paste0(y2, collapse=", "), "])"))

choose(sum(N),N[1])
##Compute all permutations manually
perms <- combinat::combn(sum(N), m=N[1])
perms
dist <- apply(perms, 2, function(i) sum(y[i]))
mean(dist>=sum(y1))
  
##Compare with python program
res <- system2("/Users/hoehle/anaconda3/bin/python3.6", args="Python/perm.py", stdout=TRUE, stderr=TRUE)
cat(paste0(res, collapse="\n"))
