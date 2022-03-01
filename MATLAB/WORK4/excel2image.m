function [outimage] = excel2image(fname)
%Ron ben david
[status,sheets] = xlsfinfo(fname);
b=size(sheets);
if ((b(1,end)==2)||(b(1,end)==4))
    if (b(1,end)==2)
    outimage=xlsread(fname,2);
    end
    if (b(1,end)==4)
    outimage = cat(3,xlsread(fname,2),xlsread(fname,3),xlsread(fname,4));
    outimage=uint8(outimage);
    end
else
outimage=[];
end
end

