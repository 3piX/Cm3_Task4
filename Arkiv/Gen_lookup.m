%generate HEX files for lookup tabels!
clear;

A_angle_cnt = 0:1:600;
A_angle_deg = A_angle_cnt*(300/1024);
A_angle_rad = A_angle_deg * pi / 180;

b = 14.3;
a = 9.5;

B_angle_rad = (pi/2 - A_angle_rad) + acos((a*sin(A_angle_rad))/(b));
B_angle_deg = B_angle_rad *180 / pi;
B_angle_cnt = B_angle_deg/(300/1024);
C_angle_cnt = 180/(300/1024)-B_angle_cnt-A_angle_cnt;

figure()
h1 = plot(A_angle_cnt,round(B_angle_cnt))
hold on
set(gcf,'Paperunits','centimeters','Paperposition',[0 0 20 15])
h2 = plot(A_angle_cnt,round(C_angle_cnt))
grid on
set(h1, 'linewidth',2)
set(h2, 'linewidth',2)
set(gca,'Fontsize',18)
title(sprintf('Angle of motor B (blue) stored as LUT'))
xlabel('Angle alpha (encoder count motor A)')
ylabel('Angle (encoder count)')
legend('Angle motor B','Angle motor C')
saveas(gcf,'calcplot.eps','psc2')
saveas(gcf,'calcplot.png','png')

% generate HEX file

str = dec2hex(round(B_angle_cnt));

fileID = fopen('lookup2.hex','w');
for i = 1:numel(str(:,1))

fprintf(fileID,'0x');
    fprintf(fileID,dec2hex(round(B_angle_cnt(i))));
fprintf(fileID,',');

end
fclose(fileID);

