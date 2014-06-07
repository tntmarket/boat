v = 100; % cm/s


A = 0.002; % 360/25/50^2 s/cm^2

D = 1; % deg

%Kp = 1.3;
%Ki = 0.1;
%Kd = 1.8;

Kp = 1.5;
Ki = 0.3;
Kd = 1.8;
Kdd = 0;

open('cross_track_error'); sim('cross_track_error');

[error, rudder, ref_boat_wall] = ScopeData.signals.values;
ref = ref_boat_wall(:,1);
boat = ref_boat_wall(:,2);
wall = ref_boat_wall(:,3);

figure(1)
subplot(3,1,1);
    plot(tout, ref); hold on;
    plot(tout, wall, 'red');
    title('Reference and Distance from Wall vs. Time'); 
    xlabel('time [s]');
    ylabel('distance [cm]');
    legend('reference', 'distance from wall');
subplot(3,1,2);
    plot(tout, rudder); hold on;
    plot(tout, boat, 'red');
    title('Rudder and Boat Angle vs. Time'); 
    xlabel('time [s]');
    ylabel('angle [deg]');
    legend('rudder angle', 'boat angle');
subplot(3,1,3);
    plot(tout, error);
    title('Cross Track Error vs. Time'); 
    xlabel('time [s]');
    ylabel('distance [cm]');
