N = 100;

trend = (1:N)/2;
y = trend + 2*randn(1,N);
x = 1:N;
s = ones(1,N); s(1) = y(1);
a = 0.7;

for i = 2:N
    s(i) = a*y(i-1) + (1-a)*s(i-1);
end

plot(x,y); hold on
plot(x,s, 'red');
