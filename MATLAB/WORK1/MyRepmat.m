function [matrix,vector] = MyRepmat(phonestr)
%UNTITLED9 Summary of this function goes here
%   Detailed explanation goes here
tempvector=zeros(1,10);
for vnum=1:10
   tempvector(vnum)=str2num(phonestr(vnum));
end
tempvector=tempvector';
if (tempvector(10)==0)||(tempvector(10)==1)
    tempvector(10)=5;
end
matrix=repmat(tempvector,1,tempvector(10));
vector=matrix(4,1:end);
end

