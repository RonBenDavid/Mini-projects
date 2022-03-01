function [struct] = LoadDataStruct(fname)
%Ron ben david
[num,txt,raw]= xlsread(fname);
struct.xName=raw(1,1);
struct.x=raw(2:end,1);
struct.yName=raw(1,2);
struct.y=raw(2:end,2);
end

