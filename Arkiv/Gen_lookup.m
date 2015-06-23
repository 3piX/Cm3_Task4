%generate HEX files for lookup tabels!
clear;

base_angle_cnt = 0:1:600;
base_angle_deg = base_angle_cnt*(300/1024);
base_angle_rad = base_angle_deg * pi / 180;

b = 14.3;
a = 9.5;

top_angle_rad = (pi/2 - base_angle_rad) + acos((a*sin(base_angle_rad))/(b));
top_angle_deg = top_angle_rad *180 / pi
top_angle_cnt = top_angle_deg/(300/1024)


plot(base_angle_cnt,round(top_angle_cnt))


% generate HEX file

str = dec2hex(round(top_angle_cnt))

fileID = fopen('lookup2.hex','w');
for i = 1:numel(str(:,1))

fprintf(fileID,'0x');
    fprintf(fileID,dec2hex(round(top_angle_cnt(i))));
fprintf(fileID,',');

end
fclose(fileID);

