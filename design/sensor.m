N = 400;
t = linspace(0,5,N);
d = horzcat(ones(1,N*3/5)*200, linspace(200,5,N*2/5));

for n = [1:N*7/10]
   if rand() < 0.11
      d(n) = d(n) - 15;
   end
end


plot(t,d);
title('Front Sensor Distance vs. Time');
axis([0 5 0 250]);
xlabel('Time [s]');
ylabel('Front Sensor Distance [cm]');
