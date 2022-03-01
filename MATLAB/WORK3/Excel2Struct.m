function [s] = Excel2Struct(fname,sheetname)
%Ron ben david
[num,txt,raw] = xlsread(fname,sheetname);
field1 = 'f';  value1 = raw(2:end,1);
field2 = 'A';  value2 = raw(2:end,2);
field3 = 'DC';  value3 = raw(2:end,3);
field4 = 'phase';  value4 = raw(2:end,4);
field5 = 'f_header';  value5 = raw(1,1);
field6 = 'A_header';  value6 = raw(1,2);
field7 = 'DC_header';  value7 = raw(1,3);
field8 = 'phase_header';  value8 = raw(1,4);
s = struct(field1,value1,field2,value2,field3,value3,field4,value4,field5,value5,field6,value6,field7,value7,field8,value8);
end

