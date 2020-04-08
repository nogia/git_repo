#generate normal random numbers using A-R method with exponential random numbers
n<-10^6

N<-ceiling(n/0.76*1.1)
x<-runif(N) #uniform random numbers to generate exponential random numbers
w<-runif(N) #uniform random numbers used to check condition
v<-runif(n) #uniform random numbers to assign signs
y<--log(x) #generate exponential random numbers as candidates

#if you use while loop
z<-numeric(n)
k<-1
i=1
while (k<(n+1)){
 if (w[i]<=exp(-(y[i]-1)^2/2)) {
	z[k]<-y[i]
 	k<-k+1} 
 i<-i+1
}
z<-sign(v-0.5)*z #randomly assign signs
hist(z,main="Empirical Distribution of Accep-rejec. with Loop")


#without while loop
prez<-y[which(exp(-(y-1)^2/2)>=w)]
z1<-sign(v-0.5)*prez[1:n] #randomly assign signs
hist(z1,main="Empirical Distribution of Accep-rejec. without Loop")
